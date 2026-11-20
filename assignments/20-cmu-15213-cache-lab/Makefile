CC ?= cc
CFLAGS ?= -std=c11 -O2 -g -Wall -Wextra -Werror -Wpedantic
.PHONY: all smoke puzzle trace clean
all: build/fixture_reader build/trace_reader
build/fixture_reader: src/fixture_reader.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
build/trace_reader: src/trace_reader.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
smoke: all
	@./build/fixture_reader cases/observations.csv
	@./build/trace_reader cases/sample.trace
puzzle: all
	@./build/fixture_reader --puzzle cases/observations.csv
trace: all
	@./build/trace_reader cases/sample.trace
clean:
	rm -rf build
