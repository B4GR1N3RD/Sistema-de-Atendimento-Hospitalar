#include <iostream>
#include <string>
#include <queue>
#include <limits>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "medico.h"
#include "recepcionista.h"
#include "gerenciamento.h"

using namespace std;

bool verificacao_prontuarios(const int& id_verificador){
    ifstream prontuarios("prontuarios_medicos.txt");

    string linha;
    char verificador;
    while(getline(prontuarios,linha)){

        verificador = linha[0];
        if(!isdigit(verificador)) continue;

        stringstream leitor(linha);

        string campo;

        while(getline(leitor,campo,'|')){
            if(isdigit(campo[0])){
                if(stoi(campo) == id_verificador){
                    return true;
                }
            }
            }
    }

    return false;
}

void criar_prontuario(Ficha paciente_cadastrado){
    ofstream prontuarios("prontuarios_medicos.txt",ios::app);

    if(!prontuarios.is_open()){
        cout << "Falha ao acessar o arquivo de prontuarios médicos dos pacientes." << endl;
        return;
    }

    if(verificacao_prontuarios(paciente_cadastrado.id)){
        cout << "O paciente "<< paciente_cadastrado.nome <<" já possui um prontuario médico em nosso sistema!" << endl;
        return;
    }

    Prontuario paciente;
    paciente.cadastro_paciente = paciente_cadastrado;

    cout << "\nA seguir, algumas perguntas serão respondidas para iniciarmos a anamnese. Por favor, preencha com atenção." << endl;

    cout << "\nExiste algum diagnóstico prévio de alguma doença? Caso positivo, escreva abaixo um diagnóstico por vez e ao final escreva 'fim', se não existir nenhum diagnóstico prévio escreva 'n/a'." << endl;

    string leitor;
    do{
        getline(cin,leitor);

        if(validador_strings(leitor)){
            transform(leitor.begin(), leitor.end(), leitor.begin(),
            [](unsigned char c){ return std::tolower(c); });

            if(leitor == "n/a"){
                paciente.doenças_previas.push_back(leitor);
                break;
            }
            else if(leitor == "fim"){
                if(paciente.doenças_previas.size() == 0){
                    paciente.doenças_previas.push_back("n/a");
                }
                break;
            }
            else{
                if(paciente.doenças_previas.size() == 0){
                    paciente.doenças_previas.push_back("| ");
                }
                paciente.doenças_previas.push_back(leitor);
                paciente.doenças_previas.push_back(" | ");
            }
        };

    }while(true);

    cout << "\nExiste alguma cirurgia que já foi realizada? Caso positivo, escreva abaixo o nome de cada cirurgia, uma por vez e ao final escreva 'fim', se nunca fez nenhuma cirurgia escreva 'n/a'." << endl;

    do{
        getline(cin,leitor);

        if(validador_strings(leitor)){
            transform(leitor.begin(), leitor.end(), leitor.begin(),
            [](unsigned char c){ return std::tolower(c); });

            if(leitor == "n/a"){
                paciente.cirurgias.push_back(leitor);
                break;
            }
            else if(leitor == "fim"){
                if(paciente.cirurgias.size() == 0){
                    paciente.cirurgias.push_back("n/a");
                }
                break;
            }
            else{
                if(paciente.cirurgias.size() == 0){
                    paciente.cirurgias.push_back("| ");
                }
                paciente.cirurgias.push_back(leitor);
                paciente.cirurgias.push_back(" | ");
            }
        };

    }while(true);

    cout << "\nExiste alguma alergia conhecida? Caso positivo, escreva abaixo o nome de todas elas uma por vez e ao final escreva 'fim', se não possui nenhuma alergia escreva 'n/a'." << endl;

    do{
        getline(cin,leitor);

        if(validador_strings(leitor)){
            transform(leitor.begin(), leitor.end(), leitor.begin(),
            [](unsigned char c){ return std::tolower(c); });

            if(leitor == "n/a"){
                paciente.alergias.push_back(leitor);
                break;
            }
            else if(leitor == "fim"){
                if(paciente.alergias.size() == 0){
                    paciente.alergias.push_back("n/a");
                }
                break;
            }
            else{
                if(paciente.alergias.size() == 0){
                    paciente.alergias.push_back("| ");
                }
                paciente.alergias.push_back(leitor);
                paciente.alergias.push_back(" | ");
            }
        };

    }while(true);


    cout << "\nFaz uso de algum tipo de medicamento? Caso positivo, escreva abaixo o nome de cada medicamento, um por vez e ao final escreva 'fim', se não toma nenhum remédio escreva 'n/a'." << endl;

    do{
        getline(cin,leitor);

        if(validador_strings(leitor)){
            transform(leitor.begin(), leitor.end(), leitor.begin(),
            [](unsigned char c){ return std::tolower(c); });

            if(leitor == "n/a"){
                paciente.medicamentos.push_back(leitor);
                break;
            }
            else if(leitor == "fim"){
                if(paciente.medicamentos.size() == 0){
                    paciente.medicamentos.push_back("n/a");
                }
                break;
            }
            else{
                if(paciente.medicamentos.size() == 0){
                    paciente.medicamentos.push_back("| ");
                }
                paciente.medicamentos.push_back(leitor);
                paciente.medicamentos.push_back(" | ");
            }
        };

    }while(true);

    cout << "\nMe liste os seus hábitos, sejam eles saúdaveis ou não, (desde praticar atividade física até alcoolismo) um por vez e ao final escreva 'fim'." << endl;

    do{
        getline(cin,leitor);

        if(validador_strings(leitor)){
            transform(leitor.begin(), leitor.end(), leitor.begin(),
            [](unsigned char c){ return std::tolower(c); });

            if(leitor == "fim"){
                if(paciente.doenças_previas.size() == 0){
                   continue;
                }
                break;
            }
            else{
                if(paciente.habitos.size() == 0){
                    paciente.habitos.push_back("| ");
                }
                paciente.habitos.push_back(leitor);
                paciente.habitos.push_back(" | ");
            }
        };

    }while(true);

    stringstream linha(leitor);

    prontuarios << endl << paciente.cadastro_paciente.id << "|" << paciente.cadastro_paciente.nome << "|" << paciente.cadastro_paciente.cpf << "|" << paciente.cadastro_paciente.dataNascimento << "|" << paciente.cadastro_paciente.sexo << "|" << paciente.cadastro_paciente.telefone << endl;
    for(const auto& d : paciente.doenças_previas){
        prontuarios << d;
    }
    prontuarios << endl;
    for(const auto& d : paciente.cirurgias){
        prontuarios << d;
    }
    prontuarios << endl;
    for(const auto& d : paciente.alergias){
        prontuarios << d;
    }
    prontuarios << endl;
    for(const auto& d : paciente.medicamentos){
        prontuarios << d;
    }
    prontuarios << endl;
    for(const auto& d : paciente.habitos){
        prontuarios << d;
    }
    prontuarios << endl;

    prontuarios.close();

};

void iniciar_atendimento(){
    EsperaAtendimento auxiliar;
    Ficha paciente_atendido;

    auxiliar = fila_pacientes.top();
    paciente_atendido = auxiliar.info_paciente;
    fila_pacientes.pop();

    criar_prontuario(paciente_atendido);
    
};