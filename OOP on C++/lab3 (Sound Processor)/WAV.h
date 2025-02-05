#ifndef LAB3_WAV_H
#define LAB3_WAV_H
#include <iostream>
#include <vector>
#include <memory>

typedef struct {
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;
} wav_header;

class WAV {
public:
    ~WAV();
    WAV(std::string filename);
    std::vector<short int> parse();
    void write(std::vector<short int> data, wav_header header);
    std::unique_ptr<wav_header> header;

private:
    std::string filename;
};

#endif // LAB3_WAV_H