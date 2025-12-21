CXX := g++
CXXFLAGS := -O3

SRC_DIR := src
BIN_DIR := bin
PLOT_DIR := plots
CSV_DIR := csvs

SRCS := $(SRC_DIR)/benchmark.cpp
BENCH := $(BIN_DIR)/benchmark
CSVS := $(CSV_DIR)/sieve.csv $(CSV_DIR)/trial-division.csv
PNGS := $(PLOT_DIR)/sieve-runtime.png $(PLOT_DIR)/trial-division-runtime.png

all: pngs
.PHONY: all

clean:
	@rm -rf $(BIN_DIR) $(PLOT_DIR) $(CSV_DIR)
.PHONY: clean

$(BENCH): $(SRCS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $^ -o $@

csvs: $(BENCH)
	@mkdir -p $(CSV_DIR)
	@./$(BENCH)
.PHONY: csvs

pngs: plot-results.py csvs
	@mkdir -p $(PLOT_DIR)
	@python3 plot-results.py
.PHONY: pngs
