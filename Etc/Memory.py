import ctypes

class Pymory:
    def __init__(self, size):
        self.size = size
        self.memory = (ctypes.c_char * size)()
    
    def read(self, address, length):
        return bytes(self.memory[address:address+length])
    
    def write(self, address, data):
        self.memory[address:address+len(data)] = data
    
    def fill(self, value):
        for i in range(self.size):
            self.memory[i] = value

# 테스트 코드
if __name__ == "__main__":
    memory = Pymory(1024)  # 1024바이트의 메모리 생성
    memory.write(0, b'Hello')  # 주소 0부터 Hello 쓰기
    print(memory.read(0, 5))  # 주소 0부터 5바이트 읽기
    memory.fill(b'\xFF')  # 메모리를 0xFF로 채우기
