/**
 * Jeopardy Tests (C) Karim 'TheSola10' Vergnes <thesola10@bobile.fr>
 * License: GNU GPL 3.0
 * Program to test the code that sets the volume to maximum.
 */
 
#include <alsa/asoundlib.h>

#define PCM_DEVICE "default"
#define MIXER_ELEM "Master"

int main(int argc, char *argv[])
{
    // Allocate ALSA mixer pointers
    int volmin, volmax;
    
    snd_mixer_t *mixer_handle;
    snd_mixer_selem_id_t *sid;
    snd_mixer_elem_t *element;
    
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
    
    snd_mixer_selem_set_playback_volume_all(element, volmax);
    snd_mixer_selem_set_playback_switch_all(element, 1);
    printf("The main audio device should have been set to maximum volume, \
            and been unmuted.");
    
    snd_mixer_close(mixer_handle);
    return (0);
}
