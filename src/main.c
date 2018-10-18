/**
 * Jeopardy 1.0.0 (C) Karim 'TheSola10' Vergnes <thesola10@bobile.fr>
 * License: GNU GPL 3.0
 * You REALLY don't wanna deal with this program. Just don't.
 */

#include "wavefile.h"

int loops;
char *buf;

// Allocate ALSA parameter pointers
snd_pcm_t *pcm_handle;
snd_pcm_hw_params_t *params;
snd_pcm_uframes_t frames;

#ifdef VOLUME_LOCK
#include <pthread.h>
// Allocate ALSA mixer pointers
long int volmin, volmax;

snd_mixer_t *mixer_handle;
snd_mixer_selem_id_t *sid;
snd_mixer_elem_t *element;

pthread_t thread_id;

int drained = 0;

void *volume_keep(void *vargp)
{
    while (!drained)
    {
        snd_mixer_selem_set_playback_volume_all(element, volmax);
        snd_mixer_selem_set_playback_switch_all(element, 1);
        sleep(1);
    }
    return 0;
}
#endif

#ifdef SIGINT_LOCK
#include <signal.h>
void loop_reset()
{
    signal(SIGINT, loop_reset);
}
#endif

int main(int argc, char *argv[])
{
    int pcm;      // Exit code for ALSA snd_pcm functions
    int tmp;      // Temporary variable (See line 88)
    int buf_size; // The increment to use for buffer feed loops.
    int countl;   // Count Loops, how many buffer feed loops we need to reach EOF
    int seconds = music_start.wav_size / music_start.byte_rate;
                  // Number of seconds the wave file will last. Important for 
                  // loop number calculation
    
    // Try and open the default ALSA device
    if (pcm = snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0) < 0) 
    {
        printf("ERROR: Could not open device \"%s\": %s",
                                PCM_DEVICE, snd_strerror(pcm));
    }
    
    // Retrieve default params
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_handle, params);
    
    // Modify them to fit our needs
    snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcm_handle, params, music_start.num_channels);
    snd_pcm_hw_params_set_rate_near(pcm_handle, params, &music_start.sample_rate, 0);
    
    // Write params to hardware device
    if ((pcm = snd_pcm_hw_params(pcm_handle, params)) < 0)
    {
        printf("ERROR: Can't set harware parameters: %s\n", snd_strerror(pcm));
    }
    
#ifdef VOLUME_LOCK
    // Retrieve and set mixer params
    snd_mixer_open(&mixer_handle, 0);
    snd_mixer_attach(mixer_handle, PCM_DEVICE);
    snd_mixer_selem_register(mixer_handle, NULL, NULL);
    snd_mixer_load(mixer_handle);
    
    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, MIXER_ELEM);
    element = snd_mixer_find_selem(mixer_handle, sid);
    
    snd_mixer_selem_get_playback_volume_range(element, &volmin, &volmax);
#endif
    
    // Determine buffer increment
    snd_pcm_hw_params_get_period_size(params, &frames, 0);
    
    buf_size = frames * music_start.num_channels * 2;
    buf = music_start.bytes;
    
    snd_pcm_hw_params_get_period_time(params, &tmp, NULL);
    
    countl = (seconds * 1000000) / tmp;
        
#ifdef SIGINT_LOCK
    // Start blocking SIGINT (^C)
    signal(SIGINT, loop_reset);
#endif
    
#ifdef VOLUME_LOCK
    pthread_create(&thread_id, NULL, volume_keep, NULL);
#endif
    
    // Feed our wav file to ALSA
    for (loops = 0; loops < countl; loops++)
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
    
    // Clean up
    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);
#ifdef VOLUME_LOCK
    drained = 1;
    pthread_join(thread_id, NULL);
    snd_mixer_close(mixer_handle);
#endif
    
    return (0);
}
