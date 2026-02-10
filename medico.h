#ifndef MEDICO_H
#define MEDICO_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "recepcionista.h"


struct Atendimento{
    std::string data;
    std::string queixa;
    std::string ocorrido;
    std::vector<std::string> sintomas;
};

struct Prontuario{
    Ficha cadastro_paciente;
    std::vector<std::string> doenças_previas;
    std::vector<std::string> cirurgias;
    std::vector<std::string> alergias;
    std::vector<std::string> medicamentos;
    std::vector<std::string> habitos;
    std::vector<Atendimento> historico;
};

struct Historico{
    Prontuario paciente;
    std::vector<Atendimento> historico;
};

void iniciar_atendimento();

void criar_prontuario(Ficha paciente_cadastrado);


#endif