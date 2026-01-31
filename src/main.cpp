#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>


struct WavHeader {
    char riff[4];
    uint32_t chunkSize;
    char wave[4];

    char fmt[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

void print_header(WavHeader &header) {
    std::cout << std::dec;
    std::cout << "=====Print Header======" << "\n";
    std::cout << "Chunk ID: " << std::string(header.riff,4) << "\n";
    std::cout << "Chunk size: " << header.chunkSize << "\n";
    std::cout << "wave: " << std::string(header.wave,4) << "\n";
    std::cout << "fmt: " << std::string(header.fmt,4) << "\n";
    std::cout << "subchunk1size: " <<  header.subchunk1Size << "\n";
    std::cout << "audioFormat: " << header.audioFormat << "\n";
    std::cout << "num channels: " << header.numChannels << "\n";
    std::cout << "sample rate: " << header.sampleRate << "\n";
    std::cout << "byte rate: " << header.byteRate << "\n";
    std::cout << "blockalign: " << header.blockAlign << "\n";
    std::cout << "bitPerSample: " << header.bitsPerSample << "\n";
    std::cout << "=======================" << "\n";
}

int read_wav_to_buff(std::ifstream &file, int numSamples, std::vector<std::int16_t> &samples){
    char dataId[4];
    uint32_t dataSize;
    samples.resize(numSamples);

    // Read chunks until we hit "data"
    while (file) {
        file.read(dataId, 4);
        file.read(reinterpret_cast<char*>(&dataSize), 4);

        if (std::string(dataId, 4) == "data") {
            break;
        }

        // Skip this chunk
        file.seekg(dataSize, std::ios::cur);
    }
    file.read(reinterpret_cast<char*>(samples.data()),
              numSamples * sizeof(int16_t));
    if(!file){
        return -1;
    }

    return 1;
}



int main() {
    std::ifstream file("../data/tone.wav", std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::vector<unsigned char> buffer(64);
    file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    WavHeader header;
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    print_header(header);
     
    int numSamples = 10;
    std::vector<int16_t> samples(numSamples);

    read_wav_to_buff(file, numSamples, samples);

    
    for (auto s : samples) {
        std::cout << s << " ";
    }
    std::cout << "\n";

}

