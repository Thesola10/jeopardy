; Jeopardy 1.0.0 (C) Karim 'TheSola10' Vergnes
; License: GNU GPL 3.0
; File to link the wave file into the program

section .data

global music_start
global music_end
global music_len

music_start:
    incbin sndfile
music_end:

music_len:   equ   music_end-music_start
