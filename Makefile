# Jeopardy 1.0.0 (C) Karim 'TheSola10' Vergnes <thesola10@bobile.fr>
# License: GNU GPL 3.0
# You... don't wanna deal with this program.

BUILD_DIR    = build
SOURCE_DIR   = src
SOURCE       = $(wildcard $(SOURCE_DIR)/*.c)
SOURCE_ASM   = $(wildcard $(SOURCE_DIR)/*.asm)

OBJ_ASM      = $(patsubst $(SOURCE_DIR)/%.asm,$(BUILD_DIR)/%.o,$(SOURCE_ASM))

MUSIC_FILE   = jeopardy.wav

CC           = gcc
NASM         = nasm

CC_DBG_FLAGS = -ggdb
CC_FLAGS     = -lasound 
NASM_FLAGS   = -dsndfile=$(MUSIC_FILE) -felf64

OUTPUT_INT   = build/jeopardy-intlock
OUTPUT       = build/jeopardy

all: $(OUTPUT)

re: fclean all

intlock: $(OUTPUT_INT)

$(OUTPUT_INT): $(SOURCE) $(OBJ_ASM)
	$(CC) $(CC_FLAGS) -DSIGINT_LOCK $(SOURCE) $(OBJ_ASM) -o $@
	
$(OUTPUT): $(SOURCE) $(OBJ_ASM) 
	$(CC) $(CC_FLAGS) $(SOURCE) $(OBJ_ASM) -o $@
	
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.asm 
	$(NASM) $(NASM_FLAGS) $< -o $@

clean: 
	rm -f $(BUILD_DIR)/*.o
	
fclean: clean
	rm -f $(OUTPUT) $(INTLOCK)
	
.PHONY: all re intlock clean fclean
