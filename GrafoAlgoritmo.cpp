#include "GrafoAlgoritmo.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

GrafoAlgoritmo::GrafoAlgoritmo(Grafo* grafo, const std::string& instancia, int algoritmo, double alfa, int numIteracoes){
    this->grafo = grafo;
    this->instancia = instancia;
    this->algoritmo = algoritmo;
    this->alfa = alfa;
    this->numIteracoes = numIteracoes;
}

GrafoAlgoritmo::~GrafoAlgoritmo() {
}

int GrafoAlgoritmo::getNumeroClientes() const {
    return grafo->nos.size() - 1;
}

GrafoAlgoritmo GrafoAlgoritmo::lerInstancia(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        exit(1);
    }

    string linha;
    int numVeiculos = 0;
    int dimensao = 0;
    double capacidade = 0;
    bool leituraCoordenadas = false;
    bool leituraDemandas = false;

    while (getline(arquivo, linha)) {
        if (linha.find("NAME") != string::npos) {
            int posInicio = linha.find("k");
            if (posInicio != string::npos) {
                string numVeiculosStr = linha.substr(posInicio + 1);
                numVeiculos = stoi(numVeiculosStr);
            }
        }

        else if (linha.find("DIMENSION") != string::npos) {
            istringstream iss(linha);
            string tag;
            iss >> tag >> dimensao;
            grafo->nos.reserve(dimensao);
        } 
        
        else if (linha.find("CAPACITY") != string::npos) {
            int posInicio = linha.find_first_of("0123456789");
            if (posInicio != string::npos) {
                string capacidadeStr = linha.substr(posInicio);
                capacidade = stoi(capacidadeStr);
                grafo->capacidadeMaximaVeiculo = capacidade;
            }
        }

        else if (linha.find("NODE_COORD_SECTION") != string::npos) {
            leituraCoordenadas = true;
        } 
        
        else if (linha.find("DEMAND_SECTION") != string::npos) {
            leituraCoordenadas = false;
            leituraDemandas = true;
        } 
        
        else if (linha.find("DEPOT_SECTION") != string::npos) {
            leituraDemandas = false;
        } 
        
        else if (leituraCoordenadas) {
            int id;
            double x, y;
            istringstream iss(linha);
            iss >> id >> x >> y;
            grafo->nos.push_back({id, x, y, 0.0});
        } 
        
        else if (leituraDemandas) {
            int id, demanda;
            istringstream iss(linha);
            iss >> id >> demanda;
            grafo->nos[id - 1].demanda = demanda;
        }
    }

    grafo->capacidadeMaximaVeiculo = capacidade;
    grafo->numVeiculos = numVeiculos;

    // Calcula as matrizes de distâncias e demandas
    calcularMatrizDistancias();

    arquivo.close();
    return *this;
}

void GrafoAlgoritmo::exibirInformacoesGrafo() {
    cout << "Número de clientes: " << grafo->nos.size() - 1 << endl;
    cout << "Número de veículos: " << grafo->numVeiculos << endl;
    cout << "Capacidade máxima do veículo: " << grafo->capacidadeMaximaVeiculo << endl;

    cout << "Coordenadas dos nós:" << endl;
    for (const No& no : grafo->nos) {
        cout << "Nó " << no.id << ": (" << no.x << ", " << no.y << ") - Demanda: " << no.demanda << endl;
    }
}

void GrafoAlgoritmo::exibirRotas(const Solucao& solucao, ostream& output) {
    output << "==================================================================== " << endl;
    output << "Resultados para instância " << instancia << ":" << endl;

    if (algoritmo == 0) {
        output << "Algoritmo Guloso" << endl << endl;
    } else if (algoritmo == 1) {
        output << "Algoritmo Guloso Randomizado" << endl;
        output << "Alfa: " << alfa << endl;
        output << "Número de Iterações: " << numIteracoes << endl;
    } else if (algoritmo == 2) {
        output << "Algoritmo Guloso Randomizado Reativo" << endl;
        output << "Número de Iterações: " << numIteracoes << endl;
    }

    // Saída das rotas.
    for (size_t i = 0; i < solucao.rotas.size(); ++i) {
        output << "Rota " << i + 1 << ":" << endl;

        for (size_t j = 0; j < solucao.rotas[i].size(); ++j) {
            output << solucao.rotas[i][j];

            if (j < solucao.rotas[i].size() - 1) {
                output << " -> ";
            }
        }

        output << endl << endl;
    }

    // Cálculo e saída da distância total.
    int distanciaTotal = calcularDistanciaTotal(solucao);
    output << "Distância total percorrida: " << distanciaTotal << endl;
    output << "==================================================================== " << endl;
}

double GrafoAlgoritmo::calcularDistancia(const No& ponto1, const No& ponto2) {
    double deltaX = ponto1.x - ponto2.x;
    double deltaY = ponto1.y - ponto2.y;
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

// Calcula a distância total da rota.
double GrafoAlgoritmo::calcularDistanciaTotal(const Solucao& solucao) {
    double distanciaTotal = 0.0;

    for (const auto& rota : solucao.rotas) {
        for (int i = 0; i < rota.size() - 1; ++i) {
            int noAtual = rota[i] - 1;
            int proximoNo = rota[i + 1] - 1;

            distanciaTotal += calcularDistancia(grafo->nos[noAtual], grafo->nos[proximoNo]);
        }
    }

    return distanciaTotal;
}

// Faz o cálculo de todas as distâncias, criando uma matriz quadrada numClientes x numClientes.
void GrafoAlgoritmo::calcularMatrizDistancias() {
    int numNos = grafo->nos.size();
    grafo->matrizDistancias.resize(numNos, vector<double>(numNos, 0.0));

    for (int i = 0; i < numNos; ++i) {
        for (int j = 0; j < numNos; ++j) {
            grafo->matrizDistancias[i][j] = calcularDistancia(grafo->nos[i], grafo->nos[j]);
        }
    }
}

Solucao GrafoAlgoritmo::algoritmoGuloso() { 
    int quantidadeClientes = grafo->nos.size();
    int quantidadeVeiculos = grafo->numVeiculos;
    double capacidadeMaximaVeiculo = grafo->capacidadeMaximaVeiculo;

    Solucao solucao(quantidadeVeiculos);

    vector<bool> visitados(quantidadeClientes, false);
    vector<double> capacidadeAtual(quantidadeVeiculos, capacidadeMaximaVeiculo);
    vector<bool> veiculoRetornouAoDeposito(quantidadeVeiculos, false);

    // Inicializa todas as rotas a partir do depósito.
    for (int rota = 0; rota < quantidadeVeiculos; ++rota) {
        solucao.rotas[rota].push_back(0);
    }

    visitados[0] = true;

    int rotaAtual = 0;
    int veiculosRetornados = 0;

    // Enquanto todas as rotas não forem finalizadas, continua no loop.
    while (veiculosRetornados < quantidadeVeiculos) {
        int ultimoNoRota = solucao.rotas[rotaAtual].back();

        // Verifica se o veículo foi para o depósito, se ele já foi não faz nada.
        if (!veiculoRetornouAoDeposito[rotaAtual]) {
            int proximoNo = encontrarNoMaisProximoRandomizado(grafo->nos[ultimoNoRota], visitados, capacidadeAtual[rotaAtual], 0);

            // Se proximoNo != -1, então há clientes para serem atendidos naquela rota.
            if (proximoNo != -1) {
                solucao.rotas[rotaAtual].push_back(proximoNo);
                visitados[proximoNo] = true;
                capacidadeAtual[rotaAtual] -= grafo->nos[proximoNo].demanda;
            } else {
                // Se não foi possível adicionar um cliente, o veículo volta ao depósito.
                solucao.rotas[rotaAtual].push_back(0);
                capacidadeAtual[rotaAtual] = capacidadeMaximaVeiculo;
                veiculoRetornouAoDeposito[rotaAtual] = true;
                veiculosRetornados++;
            }
        }

        // Atualiza para a próxima rota.
        rotaAtual = (rotaAtual + 1) % quantidadeVeiculos;
    }
    
    // Verifica se todas as rotas terminaram no depósito, se não ele é adicionado.
    for (int rota = 0; rota < quantidadeVeiculos; ++rota) {
        if (solucao.rotas[rota].back() != 0) {
            solucao.rotas[rota].push_back(0);
        }
    }

    // Ajusta o índice.
    for (auto& rota : solucao.rotas) {
        for (int& no : rota) {
            ++no;
        }
    }

    return solucao;
}

Solucao GrafoAlgoritmo::algoritmoGulosoRandomizado(double alfa, int numIteracoesMinimas) {
    int quantidadeClientes = grafo->nos.size();
    int quantidadeVeiculos = grafo->numVeiculos;
    double capacidadeMaximaVeiculo = grafo->capacidadeMaximaVeiculo;
    double melhorDistanciaTotal = numeric_limits<double>::infinity();

    Solucao melhorSolucao(quantidadeVeiculos);

    for (int iteracao = 0; iteracao < numIteracoesMinimas; iteracao++) {
        Solucao solucaoAtual(quantidadeVeiculos);
        vector<bool> visitados(quantidadeClientes, false);
        vector<double> capacidadeAtual(quantidadeVeiculos, capacidadeMaximaVeiculo);
        vector<bool> veiculoRetornouAoDeposito(quantidadeVeiculos, false);

        // Inicializa todas as rotas a partir do depósito.  
        for (int rota = 0; rota < quantidadeVeiculos; rota++) {
            solucaoAtual.rotas[rota].push_back(0);
        }

        visitados[0] = true;

        int rotaAtual = 0;
        int veiculosRetornados = 0;

        // Enquanto todas as rotas não forem finalizadas, continua no loop. 
        while (veiculosRetornados < quantidadeVeiculos) {
            int ultimoNoRota = solucaoAtual.rotas[rotaAtual].back();

            // Verifica se o veículo foi para o depósito, se ele já foi não faz nada.
            if (!veiculoRetornouAoDeposito[rotaAtual]) {
                int proximoNo = encontrarNoMaisProximoRandomizado(grafo->nos[ultimoNoRota], visitados, capacidadeAtual[rotaAtual], alfa);

                // Se proximoNo != -1, então há clientes para serem atendidos naquela rota.
                if (proximoNo != -1) {
                    solucaoAtual.rotas[rotaAtual].push_back(proximoNo);
                    visitados[proximoNo] = true;
                    capacidadeAtual[rotaAtual] -= grafo->nos[proximoNo].demanda;
                } else {
                    // Se não foi possível adicionar um cliente, o veículo volta ao depósito.
                    solucaoAtual.rotas[rotaAtual].push_back(0);
                    capacidadeAtual[rotaAtual] = capacidadeMaximaVeiculo;
                    veiculoRetornouAoDeposito[rotaAtual] = true;
                    veiculosRetornados++;
                }
            }

            // Atualiza para a próxima rota.
            rotaAtual = (rotaAtual + 1) % quantidadeVeiculos;
        }

        // Verifica se todas as rotas terminaram no depósito, se não ele é adicionado.
        for (int rota = 0; rota < grafo->numVeiculos; rota++) {
            if (solucaoAtual.rotas[rota].back() != 0) {
                solucaoAtual.rotas[rota].push_back(0);
            }
        }

        for (auto& rota : solucaoAtual.rotas) {
            for (int& no : rota) {
                no++;
            }
        }

        double distanciaTotalAtual = calcularDistanciaTotal(solucaoAtual);

        // Ajusta o índice.
        if (distanciaTotalAtual < melhorDistanciaTotal) {
            melhorDistanciaTotal = distanciaTotalAtual;
            melhorSolucao = solucaoAtual;
        }
    }

    return melhorSolucao;
}

int GrafoAlgoritmo::encontrarNoMaisProximoRandomizado(const No& ponto, const vector<bool>& visitados, double capacidadeAtual, double alfa) {
    vector<pair<int, double>> candidatos;
    int indiceEscolhido = -1;

    // Procura algum cliente que ainda não foi visitado 
    // e se sua demanda pode ser coberta pela capacidade do veículo.
    for (int i = 0; i < grafo->nos.size(); i++) {
        if (!visitados[i] && capacidadeAtual >= grafo->nos[i].demanda) {
            double distancia = grafo->matrizDistancias[ponto.id - 1][i];
            candidatos.push_back({i, distancia});
        }
    }

    // Verifica se teve algum candidato possível, se não retorna -1.
    if (!candidatos.empty()) {

        // Ordena os candidatos em ordem crescente de distância.
        sort(candidatos.begin(), candidatos.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        // Se alfa é diferente de zero, escolhe aleatoriamente dentro do intervalo permitido.
        if (alfa != 0.0) {
            int limite = min(static_cast<int>(alfa * candidatos.size()), static_cast<int>(candidatos.size()) - 1);

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, limite);

            indiceEscolhido = candidatos[dis(gen)].first;

        // Se não, esse método foi chamado pelo guloso, então retorna o cliente com menor distância.
        } else {
            indiceEscolhido = candidatos[0].first;
        }
    }

    // Retorna id do cliente escolhido.
    return indiceEscolhido;
}

void GrafoAlgoritmo::inicializarProbabilidadesAlfa(int numAlfas) {
    probabilidadesAlfa.resize(numAlfas, 1.0 / numAlfas);
}

void GrafoAlgoritmo::atualizarProbabilidade(const double melhorDistanciaTotal) {
    vector<double> medias(utilizacoesAlfa.size(), 0.0);

    // Calcular as médias baseadas no valor acumulado da soluçao dado cada alfa
    // dado a quantidade de vezes que ele foi utilizado.
    for (int i = 0; i < utilizacoesAlfa.size(); i++) {
        if (utilizacoesAlfa[i] > 0) {
            medias[i] = custosAlfa[i] / utilizacoesAlfa[i];
        }
    }

    // Calcular a soma valores de q.
    double somaQi = 0.0;
    for (int i = 0; i < medias.size(); i++) {
        if (medias[i] > 0) {
            double valorQi = pow(melhorDistanciaTotal / medias[i], 10);
            somaQi += valorQi;
        }
    }

    // Atualizar as probabilidades.
    for (int i = 0; i < medias.size(); i++) {
        if (utilizacoesAlfa[i] > 0 && medias[i] > 0) {
            double valorQi = pow(melhorDistanciaTotal / medias[i], 10);
            probabilidadesAlfa[i] = valorQi / somaQi;
        }
    }
}

int GrafoAlgoritmo::escolherAlfa(const vector<double>& probabilidades) {
    // Gera um número no intervalo (0, 1).
    double probEscolhida = (static_cast<double>(rand()) + 1.0) / (RAND_MAX + 2.0); 
    double acumulado = 0.0;

    for (int i = 0; i < probabilidades.size(); i++) {
        // Acumula as probabilidades até que a condição seja verdadeira.
        acumulado += probabilidades[i];

        if (probEscolhida <= acumulado) {
            // Retorna o índice do alfa escolhido aleatoriamente.
            return i;
        }
    }

    return probabilidades.size() - 1;
}

void GrafoAlgoritmo::inicializarContadoresAlfa(int numAlfas) {
    utilizacoesAlfa.resize(numAlfas, 0);
    custosAlfa.resize(numAlfas, 0.0);
}

void GrafoAlgoritmo::atualizarContadoresAlfa(int indiceAlfa, double custo) {
    // Incrementa a utilização e a solução obtida quando 
    // o alfa i foi utilizado.
    utilizacoesAlfa[indiceAlfa]++;
    custosAlfa[indiceAlfa] += custo;
}

Solucao GrafoAlgoritmo::algoritmoGulosoRandomizadoReativo(const double alfas[], int numAlfas, int numIteracoesMinimas) {
    int quantidadeVeiculos = grafo->numVeiculos;
    double melhorDistanciaTotal = numeric_limits<double>::infinity();
    int totalIteracoes = 0;

    // Número de iterações definido como 10% do número de iterações.
    int bloco = numIteracoesMinimas * 0.1;
    Solucao melhorSolucao(quantidadeVeiculos);

    // Inicializando todos os alfas começam com a mesma probabilidade.
    inicializarProbabilidadesAlfa(numAlfas);
    inicializarContadoresAlfa(numAlfas);

    while (totalIteracoes < numIteracoesMinimas) {

        // Verifica se está no momento de atualizar as probabilidades.
        if(numIteracoesMinimas % bloco == 0){
            atualizarProbabilidade(melhorDistanciaTotal);
        }

        // Escolhe um alfa com base nas probabilidades.
        int indiceAlfaEscolhido = escolherAlfa(probabilidadesAlfa);
        double alfaAtual = alfas[indiceAlfaEscolhido];

        Solucao solucaoRandomizado = algoritmoGulosoRandomizado(alfaAtual, 1);
        double distanciaTotalRandomizado = calcularDistanciaTotal(solucaoRandomizado);

        if (distanciaTotalRandomizado < melhorDistanciaTotal) {
            melhorDistanciaTotal = distanciaTotalRandomizado;
            melhorSolucao = solucaoRandomizado;
        }

        atualizarContadoresAlfa(indiceAlfaEscolhido, distanciaTotalRandomizado);
        totalIteracoes += 1;
    }

    return melhorSolucao;
}

Solucao GrafoAlgoritmo::buscaLocal(const Solucao& solucao) {
    Solucao solucaoModificada = solucao;
    double melhorDistanciaTotal = calcularDistanciaTotal(solucaoModificada);

    // Itera sobre todas as rotas do conjunto solução e verifica se a ordem dos clientes
    // em uma rota pode ser modificada para diminuir a distância total percorrida.

    for (auto& rota : solucaoModificada.rotas) {
        for (int i = 1; i < rota.size() - 2; ++i) {
            for (int j = i + 1; j < rota.size() - 1; ++j) {

                // Realiza a troca de dois clientes na rota.
                swap(rota[i], rota[j]);

                // Calcula a nova distância total após a troca.
                double novaDistancia = calcularDistanciaTotal(solucaoModificada);

                // Se a nova solução for melhor, mantém a troca.
                if (novaDistancia < melhorDistanciaTotal) {
                    melhorDistanciaTotal = novaDistancia;
                } else {
                    // Se não, a troca é desfeita.
                    swap(rota[i], rota[j]);
                }
            }
        }
    }

    // Retorna a solução modificada.
    return solucaoModificada;
}

Solucao GrafoAlgoritmo::algoritmoGulosoComBuscaLocal(const Solucao& solucaoInicial) {
    Solucao solucaoMelhorada = buscaLocal(solucaoInicial);
    return solucaoMelhorada;
}

Solucao GrafoAlgoritmo::algoritmoGulosoRandomizadoComBuscaLocal(const Solucao& solucaoInicial) {
    Solucao solucaoMelhorada = buscaLocal(solucaoInicial);
    return solucaoMelhorada;
}

Solucao GrafoAlgoritmo::algoritmoGulosoRandomizadoReativoComBuscaLocal(const Solucao& solucaoInicial) {
    Solucao solucaoMelhorada = buscaLocal(solucaoInicial);
    return solucaoMelhorada;
}