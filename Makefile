# Jeopardy 1.0.0 (C) Karim 'TheSola10' Vergnes <thesola10@bobile.fr>
# License: GNU GPL 3.0
# You... don't wanna deal with this program.

BUILD_DIR    = build
SOURCE_DIR   = src
SOURCE       = $(wildcard $(SOURCE_DIR)/*.c)
SOURCE_ASM   = $(wildcard $(SOURCE_DIR)/*.asm)

TESTS_DIR    = tests
TESTS        = $(wildcard $(TESTS_DIR)/*.c)
TESTS_OUT    = $(patsubst $(TESTS_DIR)/%.c,$(BUILD_DIR)/tests/%,$(TESTS))

OBJ_ASM      = $(patsubst $(SOURCE_DIR)/%.asm,$(BUILD_DIR)/%.o,$(SOURCE_ASM))

MUSIC_FILE   = jeopardy.wav

CC           = gcc
NASM         = nasm

CC_FLAGS     = -lasound -lpthread -ggdb
NASM_FLAGS   = -dsndfile=\"$(MUSIC_FILE)\" -felf64

OUTPUT       = build/jeopardy

ifneq (,$(findstring vollock,$(MAKECMDGOALS)))
	CC_FLAGS += -DVOLUME_LOCK
endif

ifneq (,$(findstring intlock,$(MAKECMDGOALS)))
	CC_FLAGS += -DSIGINT_LOCK
endif

all: $(OUTPUT)

re: fclean all

vollock: all

intlock: all

tests: $(TESTS_OUT)

$(BUILD_DIR)/tests/%: $(TESTS_DIR)/%.c
	$(CC) $(CC_FLAGS) $< -o $@
	
$(OUTPUT): $(SOURCE) $(OBJ_ASM) 
	$(CC) $(CC_FLAGS) $(SOURCE) $(OBJ_ASM) -o $@
	
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.asm 
	$(NASM) $(NASM_FLAGS) $< -o $@

clean: 
	rm -f $(BUILD_DIR)/*.o

testclean:
	rm -f $(TESTS_OUT)
	
fclean: clean testclean
	rm -f $(OUTPUT) $(OUTPUT_INT)
	
.PHONY: all re intlock vollock tests clean fclean testclean
