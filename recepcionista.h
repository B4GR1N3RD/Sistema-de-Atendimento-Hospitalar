#ifndef RECEPCIONISTA_H
#define RECEPCIONISTA_H

#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Ficha{ // A estrutura base das informações que serão armazenadas no cadastro de cada paciente
    string nome;
    string cpf;
    string dataNascimento;
    string sexo;
    string telefone;
    int prioridade;
    int id;
};

extern queue<Ficha> fila_pacientes; // Aqui ocorreu a declaração de uma fila global, para que possa ser compartilhada entre os diversos arquivos.

// Logo abaixo será realizado a declaração das funções realizadas no menu rececpcionista.
void cadastrar_paciente();

void atualizar_dados(int id);

void visualizar_fila();

#endif