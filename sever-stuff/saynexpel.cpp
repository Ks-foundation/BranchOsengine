#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class ConnectionHandler {
private:
    int serverSocket;
    std::vector<int> clientSockets;
    std::mutex clientMutex;

public:
    ConnectionHandler() : serverSocket(0) {}

    bool Initialize(int port) {
        // Create socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) {
            std::cerr << "Error: Could not create socket\n";
            return false;
        }

        // Prepare the sockaddr_in structure
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        // Bind
        if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "Error: Bind failed\n";
            return false;
        }

        // Listen
        listen(serverSocket, 5);

        return true;
    }

    void AcceptConnections() {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);

        while (true) {
            int newSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen);
            if (newSocket < 0) {
                std::cerr << "Error: Accept failed\n";
                continue;
            }

            std::lock_guard<std::mutex> lock(clientMutex);
            clientSockets.push_back(newSocket);

            std::thread clientThread(&ConnectionHandler::HandleClient, this, newSocket);
            clientThread.detach();
        }
    }

    void HandleClient(int clientSocket) {
        // 클라이언트로부터 받은 데이터를 무시하고, 서버가 클라이언트에게만 데이터를 보냅니다.
        const char *message = "Hello from server!";
        send(clientSocket, message, strlen(message), 0);

        std::lock_guard<std::mutex> lock(clientMutex);
        close(clientSocket);
        auto it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
        if (it != clientSockets.end())
            clientSockets.erase(it);
    }

    void Close() {
        close(serverSocket);
        for (int clientSocket : clientSockets) {
            close(clientSocket);
        }
    }
};

int main() {
    ConnectionHandler server;
    if (!server.Initialize(8888)) {
        std::cerr << "Error: Server initialization failed\n";
        return 1;
    }

    std::cout << "Server initialized. Listening on port 8888...\n";
    server.AcceptConnections();

    return 0;
}
