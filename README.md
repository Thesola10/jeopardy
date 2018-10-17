# jeopardy
> I swear, you don't want to deal with this program.  
>                  -- Edgar Allan Poe

## Build

For copyright reasons, the `jeopardy.wav` file is **not included**. To build, download the Jeopardy music (or whichever you want), convert it to standard **16-bit** PCM wave, and place it at the root of this repo as `jeopardy.wav`.

Prerequisites: `libasound` (ALSA), `cc`, `nasm`.

1) Make sure the `jeopardy.wav` file is at the root of the repo.
2) Make the `build` directory at the root of this repo.
3) Run `make` to build the program.
4) You will find the product in `build/jeopardy`.
5) Try this **ONLY IF YOU DARE**: Run `make intlock` to make a version of the program which cannot be stopped by `^C`, found in `build/jeopardy-intlock`.

## Install

How to install on your ~~victim's~~ computer:

bash: Write the following in `~/.bashrc`

        PROMPT_COMMAND="/path/to/jeopardy"

zsh: Write the following in `~/.zshrc`

        precmd_functions+=("/path/to/jeopardy")
        
fish: Write the following in `~/.config/fish/config.fish`

        function fish_prompt
            "/path/to/jeopardy"
        end
        
tcsh: Write the following in `~/.tcshrc`

        alias precmd "/path/to/jeopardy"

