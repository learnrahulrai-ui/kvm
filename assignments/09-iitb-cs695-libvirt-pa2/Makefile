CC ?= cc
CFLAGS ?= -std=c11 -O0 -g3 -Wall -Wextra -Werror -Wpedantic
.PHONY: all smoke puzzle clean status check drill inventory
all: build/fixture_reader build/logic_drill
build/fixture_reader: src/fixture_reader.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
build/logic_drill: src/logic_drill.c
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@
inventory:
	@pkg-config --exists libvirt || { echo 'Missing libvirt-devel'; exit 2; }
	@mkdir -p build
	$(CC) $(CFLAGS) $$(pkg-config --cflags libvirt) src/libvirt_inventory.c -o build/inventory $$(pkg-config --libs libvirt)
	./build/inventory
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
