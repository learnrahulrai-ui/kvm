CC ?= cc
CFLAGS ?= -std=c11 -O0 -g3 -Wall -Wextra -Werror -Wpedantic
.PHONY: all inspect clean
all: build/host_preflight
build/host_preflight: src/host_preflight.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
inspect: all
	./build/host_preflight
clean:
	rm -rf build
