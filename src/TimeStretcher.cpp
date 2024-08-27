#include "TimeStretcher.h"
#include <filesystem>
#include <iostream>
#include <vector>
#include <soundtouch/SoundTouch.h>
#include <sndfile.hh>

namespace fs = std::filesystem;

TimeStretcher::TimeStretcher(const std::string& inputDir, const std::vector<int>& bpms, const std::string& outputDir)
    : inputDir(inputDir), bpms(bpms), outputDir(outputDir) {}

void TimeStretcher::processFiles() {
    for (const auto& entry : fs::directory_iterator(inputDir)) {
        if (entry.is_regular_file()) {
            if (entry.path().extension() == ".wav") {
                for (int bpm : bpms) {
                    // Determine output folder
                    std::string outputFolder = outputDir.empty() ? (inputDir + "/" + std::to_string(bpm)) : outputDir + "/" + std::to_string(bpm);
                    createOutputDir(outputFolder);
                    stretchFile(entry.path().string(), bpm, outputFolder);
                }
            } else {
                std::cout << "Skipping non-wav file: " << entry.path().string() << std::endl;
            }
        }
    }
}

void TimeStretcher::stretchFile(const std::string& filePath, int bpm, const std::string& outputFolder) {
    SndfileHandle inputFile(filePath);
    if (inputFile.error()) {
        std::cerr << "Error reading file: " << filePath << std::endl;
        return;
    }

    int sampleRate = inputFile.samplerate();
    int channels = inputFile.channels();
    int originalBPM = 120; // Assuming original BPM, you may want to derive this based on metadata or input

    double stretchFactor = static_cast<double>(bpm) / originalBPM;

    std::vector<short> samples(inputFile.frames() * channels);
    inputFile.readf(samples.data(), inputFile.frames());

    // Convert short samples to float samples
    std::vector<float> floatSamples(samples.size());
    for (size_t i = 0; i < samples.size(); ++i) {
        floatSamples[i] = samples[i] / 32768.0f; // Normalize 16-bit PCM to float
    }

    soundtouch::SoundTouch soundTouch;
    soundTouch.setSampleRate(sampleRate);
    soundTouch.setChannels(channels);
    soundTouch.setTempo(stretchFactor);

    soundTouch.putSamples(floatSamples.data(), floatSamples.size() / channels);

    std::vector<float> processedFloatSamples;
    int numSamples;
    do {
        std::vector<float> tempBuffer(4096 * channels);
        numSamples = soundTouch.receiveSamples(tempBuffer.data(), 4096);
        processedFloatSamples.insert(processedFloatSamples.end(), tempBuffer.begin(), tempBuffer.begin() + numSamples * channels);
    } while (numSamples != 0);

    // Convert processed float samples back to short
    std::vector<short> processedSamples(processedFloatSamples.size());
    for (size_t i = 0; i < processedFloatSamples.size(); ++i) {
        processedSamples[i] = static_cast<short>(processedFloatSamples[i] * 32768.0f); // Convert back to 16-bit PCM
    }

    std::string filename = fs::path(filePath).filename().string();
    std::string outputFile = outputFolder + "/" + std::to_string(bpm) + "_" + filename;

    std::cout << "Saving to: " << outputFile << std::endl;

    saveToWavFile(outputFile, processedSamples, sampleRate, channels);
}

void TimeStretcher::saveToWavFile(const std::string& outputFile, std::vector<short>& samples, int sampleRate, int channels) {
    SndfileHandle outputFileHandle(outputFile, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, channels, sampleRate);
    if (outputFileHandle.error()) {
        std::cerr << "Error writing file: " << outputFile << " - " << sf_strerror(NULL) << std::endl;
        return;
    }
    sf_count_t framesWritten = outputFileHandle.writef(samples.data(), samples.size() / channels);
    if (framesWritten != static_cast<sf_count_t>(samples.size() / channels)) {
        std::cerr << "Warning: Not all frames were written to " << outputFile << std::endl;
    } else {
        std::cout << "Successfully saved: " << outputFile << std::endl;
    }
}

void TimeStretcher::createOutputDir(const std::string& dir) {
    fs::create_directories(dir);
}

