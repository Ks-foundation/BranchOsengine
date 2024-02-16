#include <iostream>
#include <vector>
#include <utility>

class Database {
private:
    std::vector<std::pair<std::string, std::string>> buffer;

public:
    void insert(const std::string& key, const std::string& value) {
        buffer.push_back(std::make_pair(key, value));
    }

    std::string get(const std::string& key) {
        for (const auto& entry : buffer) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        return "Key not found";
    }

    void remove(const std::string& key) {
        for (auto it = buffer.begin(); it != buffer.end(); ++it) {
            if (it->first == key) {
                buffer.erase(it);
                return;
            }
        }
        std::cout << "Key not found.\n";
    }

    void update(const std::string& key, const std::string& value) {
        for (auto& entry : buffer) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        std::cout << "Key not found. Inserting as new entry.\n";
        insert(key, value);
    }
};

int main() {
    Database db;
    db.insert("name", "John");
    db.insert("age", "30");
    
    std::cout << "Name: " << db.get("name") << std::endl;
    std::cout << "Age: " << db.get("age") << std::endl;
    
    db.update("age", "31");
    std::cout << "Updated Age: " << db.get("age") << std::endl;
    
    db.remove("age");
    std::cout << "Age after removal: " << db.get("age") << std::endl;

    return 0;
}
