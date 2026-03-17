import matplotlib.pyplot as plt
import csv
import os

file_path = 'data/resultados.csv'

if not os.path.exists(file_path):
    print(f"Erro: Arquivo '{file_path}' não encontrado. Execute o programa primeiro.")
    exit(1)

n_vals = []
linha_vals = []
coluna_vals = []

with open(file_path, 'r') as f:
    reader = csv.reader(f)
    header = next(reader) 
    for row in reader:
        if not row: continue
        n_vals.append(int(row[0]))
        linha_vals.append(float(row[1]))
        coluna_vals.append(float(row[2]))

plt.figure(figsize=(10, 6))
plt.plot(n_vals, linha_vals, label='Acesso por Linhas', marker='o', linestyle='-', color='b')
plt.plot(n_vals, coluna_vals, label='Acesso por Colunas', marker='s', linestyle='-', color='r')

plt.title('Benchmark de Localidade de Referência: Linhas vs Colunas')
plt.xlabel('Dimensão da Matriz (N x N)')
plt.ylabel('Tempo de Execução (segundos)')
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)

output_img = 'data/grafico.png'
plt.savefig(output_img, dpi=300)
print(f"Gráfico salvo com sucesso em '{output_img}'")
