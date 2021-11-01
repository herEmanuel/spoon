CC := g++

OUT_NAME := spoon.elf

CFLAGS := -I ./src

SRC := $(shell find -name '*.cpp')

OBJS := $(subst .cpp,.o,$(subst src,objs,$(SRC)))

.PHONY: all clean dirs

all: $(OUT_NAME)

run: $(OUT_NAME)
	./$(OUT_NAME)

$(OUT_NAME): $(OBJS)
	$(CC) -o $(OUT_NAME) $(OBJS)

objs/%.o: SRC/%.cpp | dirs
	$(CC) $(CFLAGS) -c $< -o $@ 

dirs:
	mkdir -p $(shell dirname $(OBJS))

clean:
	rm -f $(OUT_NAME)