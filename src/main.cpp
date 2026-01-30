#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>

int main() {
    std::ifstream file("../data/tone.wav", std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::vector<unsigned char> buffer(64);
    file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

    for (size_t i = 0; i < buffer.size(); ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(buffer[i]) << " ";
        if ((i + 1) % 16 == 0) std::cout << "\n";
    }
}

