#include "TimeStretcher.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>

std::vector<int> parseBPMs(const std::string& bpmList) {
    std::vector<int> bpms;
    std::stringstream ss(bpmList);
    std::string bpmStr;
    while (std::getline(ss, bpmStr, ',')) {
        bpms.push_back(std::stoi(bpmStr));
    }
    return bpms;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_folder> <bpm_list> [-o <output_folder>]" << std::endl;
        return 1;
    }

    std::string inputDir = argv[1];
    std::vector<int> bpms = parseBPMs(argv[2]);
    std::string outputDir;

    // Parse optional -o flag for output directory
    for (int i = 3; i < argc; ++i) {
        if (std::string(argv[i]) == "-o" && i + 1 < argc) {
            outputDir = argv[i + 1];
            break;
        }
    }

    TimeStretcher stretcher(inputDir, bpms, outputDir);
    stretcher.processFiles();

    return 0;
}

