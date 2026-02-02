#ifndef RECEPCIONISTA_H
#define RECEPCIONISTA_H

#include <iostream>
#include <string>
#include <queue>

struct Ficha{ // A estrutura base das informações que serão armazenadas no cadastro de cada paciente
    int id;
    std::string nome;
    std::string cpf;
    std::string dataNascimento;
    std::string sexo;
    std::string telefone;
};

struct EsperaAtendimento{
    Ficha info_paciente;
    int prioridade;
    int senha;
};

struct CompararPrioridades{ // Comparador externo criado para ordenar por prioridade de gravidade e id na fila de prioridade.
    bool operator()(const EsperaAtendimento& a, const EsperaAtendimento& b) const{
        if (a.prioridade != b.prioridade) return a.prioridade < b.prioridade;
        else return a.senha > b.senha;
    }
};

extern std::priority_queue<EsperaAtendimento,std::vector<EsperaAtendimento>,CompararPrioridades> fila_pacientes; // Aqui ocorreu a declaração de uma fila global, para que possa ser compartilhada entre os diversos arquivos.

// Logo abaixo será realizado a declaração das funções realizadas no menu rececpcionista.
void cadastrar_paciente();

void atualizar_dados(const std::string& cpf_paciente);

void adicionar_fila_atendimento();

void visualizar_fila();

#endif