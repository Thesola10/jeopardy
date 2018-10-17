/**
 * Jeopardy 1.0.0 (C) Karim 'TheSola10' Vergnes <thesola10@bobile.fr>
 * License: GNU GPL 3.0
 * Headers with definitions on how to read the embedded wav file
 */

#ifndef __WAVEFILE_H
#define __WAVEFILE_H

#include <alsa/asoundlib.h>

#define PCM_DEVICE "default"

typedef struct {
    // RIFF Header
    char riff_header[4];    // Contains "RIFF"
    int wav_size;           // Size of the wav portion of the file, which follows the first 8 bytes.
    char wave_header[4];    // Contains "WAVE"
    
    // Format Header
    char fmt_header[4];     // Contains "fmt " (includes trailing space)
    int fmt_chunk_size;     // Should be 16 for PCM
    short audio_format;     // Should be 1 for PCM. 3 for IEEE Float
    short num_channels; 
    int sample_rate;
    int byte_rate;          // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
    short sample_alignment; // num_channels * Bytes Per Sample
    short bit_depth; // Number of bits per sample
    
    // Data
    char data_header[4];    // Contains "data"
    int data_len;           // Number of bytes in data. Number of samples * num_channels * sample byte size
    
    uint8_t bytes[];        // Actual data
} wav_file_t;

extern wav_file_t music_start;
extern void *music_end;
extern int music_len;

#endif //__WAVEFILE_H
