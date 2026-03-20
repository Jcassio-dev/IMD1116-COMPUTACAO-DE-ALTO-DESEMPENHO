DATA_DIR = data

all: clean build run plot

build:
	@mkdir -p $(DATA_DIR)
	@echo "Compilando o programa..."
	gcc main.c -o calcula_pi -lm

run:
	@echo "Executando o programa..."
	./calcula_pi

plot:
	@echo "Gerando os gráficos com Python..."
	python3 plot.py

clean:
	@echo "Limpando arquivos antigos..."
	rm -f calcula_pi
	rm -rf $(DATA_DIR)/*.csv
	rm -rf $(DATA_DIR)/*.png