#ifndef GRAFO_ALGORITMO_H
#define GRAFO_ALGORITMO_H

#include <vector>
#include <string>

using namespace std;

struct Aresta {
    int origem;
    int destino;
    double peso;
};

struct No {
    int id;
    double x;
    double y;
    double demanda;
};

struct Grafo {
    vector<Aresta> arestas;
    vector<No> nos;
    double capacidadeMaximaVeiculo;
    int numVeiculos;

    vector<vector<double>> matrizDistancias;
    vector<vector<int>> matrizDemandas;
};

class Solucao {
public:
    Solucao(int numVeiculos) : rotas(numVeiculos) {}
    Solucao() = default;

    vector<vector<int>> rotas;
};

class GrafoAlgoritmo {
public:
    GrafoAlgoritmo(Grafo* grafo, const string& instancia, int algoritmo, double alfa, int numIteracoes);
    ~GrafoAlgoritmo();

    // Métodos gerais.
    int getNumeroClientes() const;
    GrafoAlgoritmo lerInstancia(const string& nomeArquivo);
    void exibirInformacoesGrafo();
    void exibirRotas(const Solucao& solucao, ostream& output);

    // Métodos para calculos de distância dos Algoritmos Gulosos.
    double calcularDistancia(const No& ponto1, const No& ponto2);
    double calcularDistanciaTotal(const Solucao& solucao);
    void calcularMatrizDistancias();
    int encontrarNoMaisProximoRandomizado(const No& ponto, const vector<bool>& visitados, double capacidadeAtual, double alfa);

    // Método de escolha aleatória do alfa para o Algoritmo Guloso Randomizado Reativo.
    int escolherAlfa(const vector<double>& probabilidades);
    void inicializarContadoresAlfa(int numAlfas);
    void atualizarContadoresAlfa(int indiceAlfa, double custo);

    Solucao algoritmoGuloso();
    Solucao algoritmoGulosoRandomizado(double alfa, int numIteracoesMinimas);
    Solucao algoritmoGulosoRandomizadoReativo(const double alfas[], int numAlfas, int numIteracoesMinimas);

    // Busca local para otimizar as rotas geradas.
    Solucao buscaLocal(const Solucao& solucaoInicial);

    Solucao algoritmoGulosoComBuscaLocal(const Solucao& solucaoInicial);
    Solucao algoritmoGulosoRandomizadoComBuscaLocal(const Solucao& solucaoInicial);
    Solucao algoritmoGulosoRandomizadoReativoComBuscaLocal(const Solucao& solucaoInicial);

private:
    Grafo* grafo;
    vector<double> probabilidadesAlfa;
    int indiceAlfaMelhorSolucao;

    string instancia;
    int algoritmo;
    double alfa;
    int numIteracoes;

    vector<int> utilizacoesAlfa;
    vector<double> custosAlfa;

    void inicializarProbabilidadesAlfa(int numAlfas);
    void atualizarProbabilidade(double probabilidadeAtual);
};

#endif