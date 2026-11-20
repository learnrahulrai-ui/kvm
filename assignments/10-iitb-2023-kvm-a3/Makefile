CC ?= cc
CFLAGS ?= -std=c11 -O2 -g -Wall -Wextra -Werror -Wpedantic
.PHONY: all smoke puzzle kvm-probe clean
all: build/fixture_reader build/kvm_probe
build/fixture_reader: src/fixture_reader.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
build/kvm_probe: src/kvm_probe.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
smoke: all
	@./build/fixture_reader cases/observations.csv
puzzle: all
	@./build/fixture_reader --puzzle cases/observations.csv
kvm-probe: all
	@./build/kvm_probe
clean:
	rm -rf build
