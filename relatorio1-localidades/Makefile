CC = gcc
CFLAGS = -Wall
SRC = main.c
TARGET = main
DATA_DIR = data

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	mkdir -p $(DATA_DIR)
	./$(TARGET)

plot:
	python3 plot.py

clean:
	rm -f $(TARGET) $(DATA_DIR)/resultados.csv $(DATA_DIR)/grafico.png
