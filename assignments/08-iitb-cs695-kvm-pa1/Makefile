CC ?= cc
CFLAGS ?= -std=c11 -O0 -g3 -Wall -Wextra -Werror -Wpedantic
.PHONY: all smoke puzzle clean status check drill kvm-probe
all: build/fixture_reader build/logic_drill build/kvm_probe
build/fixture_reader: src/fixture_reader.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
build/logic_drill: src/logic_drill.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
build/kvm_probe: src/kvm_probe.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
kvm-probe: all
	./build/kvm_probe
smoke: all
	./build/fixture_reader cases/observations.csv
status: all
	./build/logic_drill --status
check: all
	./build/logic_drill
drill: status
puzzle: all
	./build/fixture_reader --puzzle cases/observations.csv
clean:
	rm -rf build
