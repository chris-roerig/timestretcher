#pragma once

#include <string>
#include <vector>

class TimeStretcher {
public:
    TimeStretcher(const std::string& inputDir, const std::vector<int>& bpms, const std::string& outputDir = "");
    void processFiles();

private:
    std::string inputDir;
    std::vector<int> bpms;
    std::string outputDir;

    void stretchFile(const std::string& filePath, int bpm, const std::string& outputFolder);
    void saveToWavFile(const std::string& outputFile, std::vector<short>& samples, int sampleRate, int channels);
    void createOutputDir(const std::string& dir);
};

