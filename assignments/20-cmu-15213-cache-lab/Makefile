CC ?= cc
CFLAGS ?= -std=c11 -O0 -g3 -Wall -Wextra -Werror -Wpedantic
.PHONY: all smoke puzzle clean status check drill trace
all: build/fixture_reader build/logic_drill build/trace_reader
build/fixture_reader: src/fixture_reader.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
build/logic_drill: src/logic_drill.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
build/trace_reader: src/trace_reader.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
trace: all
	./build/trace_reader cases/sample.trace
smoke: all
	./build/fixture_reader cases/observations.csv
	./build/trace_reader cases/sample.trace
status: all
	./build/logic_drill --status
check: all
	./build/logic_drill
drill: status
puzzle: all
	./build/fixture_reader --puzzle cases/observations.csv
clean:
	rm -rf build
