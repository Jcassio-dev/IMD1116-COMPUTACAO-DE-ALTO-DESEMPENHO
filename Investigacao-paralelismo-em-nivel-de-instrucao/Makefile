DATA_DIR = data

all: clean build run plot

build:
	@mkdir -p $(DATA_DIR)
	@echo "Compilando as 3 versões com otimizações diferentes..."
	gcc main.c -O0 -o main_O0
	gcc main.c -O2 -o main_O2
	gcc main.c -O3 -o main_O3

run:
	@echo "OptLevel,N,TempoInit,TempoAcum,TempoILP" > $(DATA_DIR)/resultados.csv
	@echo "Executando -O0..."
	./main_O0 O0
	@echo "Executando -O2..."
	./main_O2 O2
	@echo "Executando -O3..."
	./main_O3 O3

plot:
	@echo "Gerando os gráficos com Python..."
	python3 plot.py

clean:
	@echo "Limpando arquivos antigos..."
	rm -f main_O0 main_O2 main_O3
	rm -rf $(DATA_DIR)/*.csv