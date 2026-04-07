CC = gcc
CFLAGS = -Wall -Wextra -O3 -fopenmp
LDFLAGS = -lm -fopenmp

TARGET = primos
SRCS = main.c
OBJS = $(SRCS:.c=.o)

ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

THREADS ?= $(if $(RUN_ARGS),$(RUN_ARGS),4)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@echo "========================================="
	@echo "Executando openmp com $(THREADS) threads"
	@echo "========================================="
	OMP_NUM_THREADS=$(THREADS) ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) main

.PHONY: all clean run 
