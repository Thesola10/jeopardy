/**
 * Jeopardy 1.0.0 (C) Karim 'TheSola10' Vergnes <thesola10@bobile.fr>
 * License: GNU GPL 3.0
 * You REALLY don't wanna deal with this program. Just don't.
 */
 
#include "wavefile.h"

int main(int argc, char *argv[])
{
    int pcm;
    int tmp;
    int seconds = music_start.data_len / music_start.byte_rate;
    
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frames;
    char *buf;
    int buf_size;
    int loops;
    
    
    if (pcm = snd_pcm_open(&pcm_handle, PCM_DEVICE, 
                            SND_PCM_STREAM_PLAYBACK, 0) < 0) 
    {
        printf("ERROR: Could not open device \"%s\": %s",
                                PCM_DEVICE, snd_strerror(pcm));
    }
    
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_handle, params);
    
    if ((pcm = snd_pcm_hw_params_set_access(pcm_handle, params,
                            SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
        printf("ERROR: Could not set playback mode: %s", snd_strerror(pcm));
    }
    if ((pcm = snd_pcm_hw_params_set_format(pcm_handle, params,
                            SND_PCM_FORMAT_S16_LE)) < 0)
    {
        printf("ERROR: Could not set playback format: %s", snd_strerror(pcm));
    } 
    if ((pcm = snd_pcm_hw_params_set_channels(pcm_handle, params, 
                            music_start.num_channels)) < 0)
    {
        printf("ERROR: Could not set channels: %s", snd_strerror(pcm));
    } 
    if ((pcm = snd_pcm_hw_params_set_rate_near(pcm_handle, params, 
                            &music_start.sample_rate, 0)) < 0)
    {
        printf("ERROR: Could not set sample rate: %s", snd_strerror(pcm));
    }
    
    // set params
    if ((pcm = snd_pcm_hw_params(pcm_handle, params)) < 0)
        printf("ERROR: Can't set harware parameters: %s\n", snd_strerror(pcm));
        
    snd_pcm_hw_params_get_period_size(params, &frames, 0);
    
    buf_size = frames * music_start.num_channels * 2;
    buf = music_start.bytes;
    
    snd_pcm_hw_params_get_period_time(params, &tmp, NULL);
    
    for (loops = (seconds * 1000000) / tmp; loops; loops--)
    {
        pcm = snd_pcm_writei(pcm_handle, buf, frames); 
        if (pcm == -EPIPE)
        {
            snd_pcm_prepare(pcm_handle);
        } else if (pcm < 0)
        {
            printf("ERROR: Can't write to device: %s", snd_strerror(pcm));
        }
        
        buf += buf_size;
    }
    
    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);
    
    return (0);
}
