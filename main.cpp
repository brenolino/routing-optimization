#include <iostream>
#include "vector"
#include "fstream"
#include "GrafoAlgoritmo.h"
#include <random>

using namespace std;

bool validarEntradas(int algoritmo, double alfa, int numIteracoes) {
    if (algoritmo < 0 || algoritmo > 2) {
        cout << "Erro: O algoritmo escolhido deve ser [0], [1] ou [2]." << endl;
        return false;
    }

    if (alfa < 0.0 || alfa > 1.0) {
        cout << "Erro: O valor de alfa deve estar entre 0 e 1." << endl;
        return false;
    }

    if (numIteracoes <= 0) {
        cout << "Erro: O número de iterações deve ser maior que 0." << endl;
        return false;
    }

    return true;
}

int main(int argc, char **argv) {
    
    if (argc != 5) {
    cout << "Uso: " << argv[0] << " <instancia> <algoritmo> <alfa> <numIteracoes>" << endl;
        return 1;
    }

    string instancia = argv[1];
    int algoritmo = stoi(argv[2]);
    double alfa = stod(argv[3]);
    int numIteracoes = stoi(argv[4]);
    string arquivoSaida = "saida" + instancia + ".txt";

    // Verifica a validade dos argumentos de entrada.
    if (!validarEntradas(algoritmo, alfa, numIteracoes)) {
        return 1;
    }

    // Verifica se a instância existe.
    ifstream arquivoInstancia("Instancias/" + instancia + ".txt");
    if (!arquivoInstancia.is_open()) {
        cout << "Erro: Nome da instância não encontrado." << endl;
        return 1;
    }
    arquivoInstancia.close();

    Grafo grafo;
    GrafoAlgoritmo grafoAlgoritmo(&grafo, instancia, algoritmo, alfa, numIteracoes);
    grafoAlgoritmo.lerInstancia("Instancias/" + instancia + ".txt");

    Solucao solucao;
    Solucao melhorSolucao;

    if (algoritmo == 0) {
        solucao = grafoAlgoritmo.algoritmoGuloso();
        melhorSolucao = grafoAlgoritmo.algoritmoGulosoComBuscaLocal(solucao);
    } else if (algoritmo == 1) {
        solucao = grafoAlgoritmo.algoritmoGulosoRandomizado(alfa, numIteracoes);
        melhorSolucao = grafoAlgoritmo.algoritmoGulosoRandomizadoComBuscaLocal(solucao);
    } else if (algoritmo == 2) {
        const double alfas[] = {0.05, 0.1, 0.15, 0.3, 0.5};
        solucao = grafoAlgoritmo.algoritmoGulosoRandomizadoReativo(alfas, 5, numIteracoes);
        melhorSolucao = grafoAlgoritmo.algoritmoGulosoRandomizadoReativoComBuscaLocal(solucao);
    } else {
        cout << "Algoritmo inválido." << endl;
        return 1;
    }

    // Exiba informações ou salve no arquivo de saída
    ofstream saidaArquivo("Resultados/" + arquivoSaida, ios::app);
    if (saidaArquivo.is_open()) {
        grafoAlgoritmo.exibirRotas(melhorSolucao, saidaArquivo);
        saidaArquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    return 0;
}