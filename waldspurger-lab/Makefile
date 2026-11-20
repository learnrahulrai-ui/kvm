CC ?= cc
CFLAGS ?= -std=c11 -O0 -g3 -Wall -Wextra -Werror -Wpedantic
LDLIBS ?= -lm
SRC := src
BIN := build
.PHONY: all check clean preflight
all: $(BIN)/idle_tax $(BIN)/scheduler $(BIN)/mrc $(BIN)/ksm_demo
$(BIN):
	mkdir -p $(BIN)
$(BIN)/idle_tax: $(SRC)/idle_tax.c | $(BIN)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)
$(BIN)/scheduler: $(SRC)/scheduler.c | $(BIN)
	$(CC) $(CFLAGS) $< -o $@
$(BIN)/mrc: $(SRC)/mrc.c | $(BIN)
	$(CC) $(CFLAGS) $< -o $@
$(BIN)/ksm_demo: $(SRC)/ksm_demo.c | $(BIN)
	$(CC) $(CFLAGS) $< -o $@
check: all
	python3 -m unittest discover -s tests -p 'test_*.py' -v
	python3 -m py_compile scripts/qmp.py
	bash -n scripts/preflight.sh scripts/launch_pair.sh scripts/observe_ksm.sh scripts/snapshot.sh scripts/observe_vms.sh scripts/stop_pair.sh scripts/run_ksm_pair.sh
preflight:
	bash scripts/preflight.sh
clean:
	rm -rf $(BIN)
