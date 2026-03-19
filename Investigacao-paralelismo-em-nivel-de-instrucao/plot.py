import os
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('data/resultados.csv')

fig, axes = plt.subplots(1, 3, figsize=(18, 6), sharey=True)
fig.suptitle('ILP e Níveis de Otimização do Compilador', fontsize=16, fontweight='bold')

otimizacoes = ['O0', 'O2', 'O3']

for i, opt in enumerate(otimizacoes):
    dados_opt = df[df['OptLevel'] == opt]
    
    axes[i].plot(dados_opt['N'], dados_opt['TempoAcum'], marker='o', color='red', label='Acumulativa (Dependência)')
    axes[i].plot(dados_opt['N'], dados_opt['TempoILP'], marker='s', color='blue', label='Múltiplas Variáveis (ILP)')
    
    axes[i].set_title(f'Otimização: GCC -{opt}')
    axes[i].set_xlabel('Tamanho do Vetor (N)')
    if i == 0:
        axes[i].set_ylabel('Tempo de Execução (Segundos)')
    
    axes[i].legend()
    axes[i].grid(True, linestyle='--', alpha=0.7)

os.makedirs('data', exist_ok=True)
plt.tight_layout()
plt.savefig('data/grafico_ilp.png')
print("Gráfico gerado com sucesso em 'data/grafico_ilp.png'!")