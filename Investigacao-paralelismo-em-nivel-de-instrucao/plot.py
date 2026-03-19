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
    
    # Salva um gráfico separado para cada otimização
    arquivo_saida = f'data/grafico_ilp_{opt}.png'
    plt.savefig(arquivo_saida)
    plt.close() # Fecha a figura para não sobrepor com a próxima
    print(f"Gráfico gerado com sucesso em '{arquivo_saida}'!")