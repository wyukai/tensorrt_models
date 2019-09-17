//
// Created by alex on 12.09.19.
//

#ifndef TENSORRT_MODELS_ENTROPYCALIBRATOR_H
#define TENSORRT_MODELS_ENTROPYCALIBRATOR_H

#include <NvInfer.h>
#include <imageIO.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cuda_runtime.h>

class EntropyCalibrator : public nvinfer1::IInt8EntropyCalibrator
{
public:
    EntropyCalibrator(
            const std::string& file_list,
            const int& batchSize,
            const int& width,
            const int& height,
            const int& channel,
            bool readCache);

    ~EntropyCalibrator() override ;

    int getBatchSize() const override;

    bool getBatch(void* bindings[], const char* names[], int nbBindings) override;

    const void* readCalibrationCache(size_t& length) override;

    void writeCalibrationCache(const void* cache, size_t length) override;

private:
    static std::string calibrationTableName();
    bool mReadCache{ true };
    size_t mInputCount1;
    void* mDeviceInput1{ nullptr };
    std::vector<char> mCalibrationCache;

    int _cur_id;
    std::string _file_list;
    std::vector<std::string> _fnames;
    float* _batch;
    nvinfer1::DimsNCHW dims;
};


#endif //TENSORRT_MODELS_ENTROPYCALIBRATOR_H