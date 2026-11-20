CC ?= cc
CFLAGS ?= -std=c11 -O2 -g -Wall -Wextra -Werror -Wpedantic
.PHONY: all smoke puzzle inventory clean
all: build/fixture_reader
build/fixture_reader: src/fixture_reader.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
smoke: all
	@./build/fixture_reader cases/observations.csv
puzzle: all
	@./build/fixture_reader --puzzle cases/observations.csv
inventory:
	@pkg-config --exists libvirt || { echo 'libvirt development package not installed'; exit 2; }
	@mkdir -p build
	$(CC) $(CFLAGS) $$(pkg-config --cflags libvirt) src/libvirt_inventory.c -o build/inventory $$(pkg-config --libs libvirt)
	./build/inventory
clean:
	rm -rf build
