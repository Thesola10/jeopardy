# jeopardy
> I swear, you don't want to deal with this program.  
>                  -- Edgar Allan Poe

## Build

For copyright reasons, the `jeopardy.wav` file is **not included**. To build, download the Jeopardy music (or whichever you want), convert it to standard PCM wave, and place it at the root of this repo as `jeopardy.wav`.

Afterwards, (this part is not yet implemented, bear with me)

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

