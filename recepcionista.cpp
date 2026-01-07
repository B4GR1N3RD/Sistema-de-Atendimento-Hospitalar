#include <iostream>
#include <string>
#include <queue>
#include <limits>
#include "recepcionista.h"
#include "menus.h"

using namespace std;

queue<Ficha> fila_pacientes;

int id=1;

void cadastrar_paciente(){
    Ficha paciente;

    cout << "Cadastro do paciente iniciado." << endl;
    cout << "Por favor, informe os dados solicitador a seguir." << endl << endl;

    cout << "Nome completo: ";
    getline(cin >> ws, paciente.nome);

    cout << "CPF: " ;
    paciente.cpf = leitor_cpf();

    cout << "Data de nascimento: " ;
    getline(cin, paciente.dataNascimento);

    cout << "Sexo: " ;
    getline(cin,paciente.sexo);

    cout << "Número para contato: " ;
    getline(cin,paciente.telefone);

    cout << "Grau de prioridade: " ;
    paciente.prioridade = leitor_inteiros();

    paciente.id = id++;

    fila_pacientes.push(paciente);

    cout << "\nPaciente de id: "<< paciente.id <<" adicionado à fila!" << endl;
    
}

void atualizar_dados(int id){
     if(fila_pacientes.empty()){
        cout << "A fila se encontra vazia. Nenhum paciente cadastrado." << endl;
        return;
     }

     queue<Ficha> fila_auxiliar;
     bool encontrado = false;

    while(!fila_pacientes.empty()){
        Ficha paciente = fila_pacientes.front();
        fila_pacientes.pop();

        if(paciente.id == id){
            encontrado = true;

            cout << "\nA atualização da ficha de cadastro está sendo realizada.Por favor insira os dados atualizados.\n" << endl;

            cout << "Nome completo: ";
            getline(cin >> ws, paciente.nome);

            cout << "CPF: " ;
            getline(cin, paciente.cpf);

            cout << "Data de nascimento: " ;
            getline(cin, paciente.dataNascimento);

            cout << "Sexo: " ;
            getline(cin,paciente.sexo);

            cout << "Número para contato: " ;
            getline(cin,paciente.telefone);

            cout << "Grau de prioridade: " ;
            paciente.prioridade = leitor_inteiros();

        }

        fila_auxiliar.push(paciente);
    }

    fila_pacientes = fila_auxiliar;

    if(encontrado){
        cout << "\nOs dados do paciente foram atualizados com sucesso." << endl;
    }
    else{
        cout << "\nO Paciente de ID: " << id << " não foi encontrado na fila." << endl;
    }

}

void visualizar_fila(){

    if(fila_pacientes.empty()){
        cout << "A fila se encontra vazia. Nenhum paciente cadastrado." << endl;
        return;
    }

    cout << "A fila de pacientes será mostrada a seguir: " << endl << endl;

    queue<Ficha> fila_auxiliar;
    fila_auxiliar = fila_pacientes;

    Ficha paciente;

    while(!fila_auxiliar.empty()){
        paciente = fila_auxiliar.front();
        fila_auxiliar.pop();

        cout << "Nome completo: " << paciente.nome << endl;

        cout << "Grau de prioridade: " << paciente.prioridade << endl;

        cout << "Id do paciente: " << paciente.id << endl << endl;
    }
}