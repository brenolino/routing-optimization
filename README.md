# Roteamento de Veículos Capacitados (PRVC)

Este repositório contém a implementação de algoritmos construtivos gulosos para abordar o Problema de Roteamento de Veículos Capacitados (PRVC) em um ambiente modelado sobre um grafo simples e não direcionado. Os algoritmos desenvolvidos incluem abordagens gulosa, gulosa randomizada e gulosa randomizada reativa.

Além disso, foi empregado um algoritmo de busca local como tentativa de melhorar os resultados obtidos pelos algoritmos construtivos.
## Contexto

Este projeto foi desenvolvido como parte de um trabalho acadêmico na disciplina de Teoria dos Grafos. Ele aborda o desafio de otimizar o roteamento de veículos em um ambiente com capacidades limitadas.

## Estrutura do Projeto

- **`/Instancias`**: Pasta contendo instâncias utilizadas nos testes.
- **`/Resultados`**: Pasta para armazenar os resultados obtidos.
- **`/Scripts-Instancias`**: Pasta com scripts para automatizar os experimentos.
- **`GrafoAlgoritmo.cpp`**: Código-fonte do projeto.
- **`GrafoAlgoritmo.h`**: Código-fonte do projeto.
- **`main.cpp`**: Código-fonte do projeto.
- **`run_code.sh`**: Script para compilar o programa.

## Como Utilizar

Para compilar o programa, utilize o seguinte comando:

```bash
g++ *.c* -o main
```

Após compilar o programa, utilize o seguinte comando para a execução:

```bash
./main "nome-instancia" <0, 1 ou 2> <alfa> <numIteracoes>
```

Onde o nome da instância deve constar na pasta Instancias. Para executar o Algoritmo Guloso, o primeiro parâmetro deve ser 0; para o Algoritmo Guloso Randomizado, deve ser 1; e para o Algoritmo Guloso Randomizado Reativo, deve ser 2. Os valores de alfa devem estar entre [0, 1], sendo 0 na execução do Algoritmo Guloso e 1 para o Reativo.

Dentro da pasta Scripts-Instancias, você encontrará scripts que facilitam a execução dos algoritmos. Basta conceder permissões de execução apropriadas e, em seguida, executá-los normalmente.

Os resultados gerados serão escritos em formato .txt dentro da pasta Resultados.

---

*Breno Lino Prado, estudante da Universidade Federal de Juiz de Fora (UFJF).*
