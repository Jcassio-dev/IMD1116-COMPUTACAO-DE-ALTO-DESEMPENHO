import os
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('data/resultados.csv')

otimizacoes = ['O0', 'O2', 'O3']
os.makedirs('data', exist_ok=True)

for opt in otimizacoes:
    dados_opt = df[df['OptLevel'] == opt]
    
    plt.figure(figsize=(10, 6))
    plt.plot(dados_opt['N'], dados_opt['TempoAcum'], marker='o', color='red', label='Acumulativa (Dependência)')
    plt.plot(dados_opt['N'], dados_opt['TempoILP'], marker='s', color='blue', label='Múltiplas Variáveis (ILP)')
    
    plt.title(f'ILP vs Dependência de Dados - Otimização: GCC -{opt}', fontsize=14, fontweight='bold')
    plt.xlabel('Tamanho do Vetor (N)')
    plt.ylabel('Tempo de Execução (Segundos)')
    
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    
    arquivo_saida = f'data/grafico_ilp_{opt}.png'
    plt.savefig(arquivo_saida)
    plt.close() 
    print(f"Gráfico gerado com sucesso em '{arquivo_saida}'!")

fig, axes = plt.subplots(1, 3, figsize=(18, 6), sharey=True)
fig.suptitle('ILP e Níveis de Otimização do Compilador', fontsize=16, fontweight='bold')

for i, opt in enumerate(otimizacoes):
    dados_opt = df[df['OptLevel'] == opt]
    
    axes[i].plot(dados_opt['N'], dados_opt['TempoAcum'], marker='o', color='red', label='Acumulativa')
    axes[i].plot(dados_opt['N'], dados_opt['TempoILP'], marker='s', color='blue', label='ILP')
    
    axes[i].set_title(f'Otimização: GCC -{opt}')
    axes[i].set_xlabel('Tamanho do Vetor (N)')
    if i == 0:
        axes[i].set_ylabel('Tempo de Execução (Segundos)')
    
    axes[i].legend()
    axes[i].grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('data/grafico_ilp_comparativo.png')
plt.close()
print("Gráfico comparativo gerado com sucesso em 'data/grafico_ilp_comparativo.png'!")