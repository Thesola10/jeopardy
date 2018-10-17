# Jeopardy 1.0.0 (C) Karim 'TheSola10' Vergnes <thesola10@bobile.fr>
# License: GNU GPL 3.0
# You... don't wanna deal with this program.

BUILD_DIR    = build
SOURCE_DIR   = src
SOURCE       = $(wildcard $(SOURCE_DIR)/*.c)
SOURCE_ASM   = $(wildcard $(SOURCE_DIR)/*.asm)

OBJ_ASM      = $(patsubst %.asm,%.o,$(SOURCE_ASM))

MUSIC_FILE   = jeopardy.wav
MUSIC_RATE   = 44100
MUSIC_CHAN   = 2
MUSIC_LEN    = 32

CC           = gcc
NASM         = nasm

CC_DBG_FLAGS = -ggdb
CC_FLAGS     = -lasound 
CC_FLAGS    += -DRATE=$(MUSIC_RATE) -DNCH=$(MUSIC_CHAN) -DLEN=$(MUSIC_LEN)
NASM_FLAGS   = -Dsndfile=$(MUSIC_FILE) -felf64

OUTPUT       = build/jeopardy

all: $(OUTPUT)
	echo Not yet implemented

re: fclean all
	
$(OUTPUT): $(SOURCE) $(OBJ_ASM) 
	$(CC) $(CC_FLAGS) $(SOURCE) $(OBJ_ASM) -o $(OUTPUT)
	
%.o: %.asm 
	$(NASM) $(NASM_FLAGS) $< -o $@

clean: 
	rm -f $(BUILD_DIR)/*.o
	
fclean: clean
	rm -f $(OUTPUT) 
	
.PHONY: all re clean fclean
