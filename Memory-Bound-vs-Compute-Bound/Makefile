CC = gcc
CFLAGS = -O2 -fopenmp -lm
TARGETS = cpu_bound mem_bound

.PHONY: all clean

all: $(TARGETS)

cpu_bound: cpu_bound.c
	$(CC) $(CFLAGS) -o cpu_bound cpu_bound.c

mem_bound: mem_bound.c
	$(CC) $(CFLAGS) -o mem_bound mem_bound.c

run: $(TARGETS)
	@echo "Executando CPU-bound..."
	./cpu_bound
	@echo "Executando Memory-bound..."
	./mem_bound
clean:
	rm -f $(TARGETS)
