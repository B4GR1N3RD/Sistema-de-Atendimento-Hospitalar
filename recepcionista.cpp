#include <iostream>
#include <string>
#include <queue>
#include <limits>
#include "recepcionista.h"
#include "gerenciamento.h"

using namespace std;

priority_queue<Ficha,vector<Ficha>,CompararPrioridades> fila_pacientes;

int id=1;

void cadastrar_paciente(){
    Ficha paciente;

    cout << "Cadastro do paciente iniciado." << endl;
    cout << "Por favor, informe os dados solicitados a seguir." << endl << endl;

    cout << "Nome completo: ";
    paciente.nome = leitor_nome();

    cout << "CPF: " ;
    paciente.cpf = leitor_cpf();

    cout << "Data de nascimento: " ;
    paciente.dataNascimento = leitor_data();

    cout << "Insira a seguir o sexo do paciente (M = Masculino, F = Feminino, O = Outro/Não-binário): " ;
    paciente.sexo = leitor_sexo();

    cout << "Número para contato: " ;
    paciente.telefone  = leitor_telefone();

    cout << "Grau de prioridade (1 = menos grave, 5 = mais grave): " ;
    paciente.prioridade = leitor_prioridade();

    paciente.id = id++;

    fila_pacientes.push(paciente);

    cout << "\nPaciente de id: "<< paciente.id <<" adicionado à fila!" << endl;
    
}

void atualizar_dados(int id_paciente){
     if(fila_pacientes.empty()){
        cout << "A fila se encontra vazia. Nenhum paciente cadastrado." << endl;
        return;
     }

    priority_queue<Ficha,vector<Ficha>,CompararPrioridades> fila_auxiliar;
     bool encontrado = false;

    while(!fila_pacientes.empty()){
        Ficha paciente = fila_pacientes.top();
        fila_pacientes.pop();

        if(paciente.id == id_paciente){
            encontrado = true;

            cout << "\nA atualização da ficha de cadastro está sendo realizada. Por favor insira os dados atualizados.\n" << endl;

            cout << "Nome completo: ";
            paciente.nome = leitor_nome();

            cout << "CPF: " ;
            paciente.cpf = leitor_cpf();

            cout << "Data de nascimento: " ;
            paciente.dataNascimento = leitor_data();

            cout << "Insira a seguir o sexo do paciente (M = Masculino, F = Feminino, O = Outro/Não-binário): " ;
            paciente.sexo = leitor_sexo();

            cout << "Número para contato: " ;
            paciente.telefone  = leitor_telefone();

            cout << "Grau de prioridade (1 = menos grave, 5 = mais grave): " ;
            paciente.prioridade = leitor_prioridade();

        }

        fila_auxiliar.push(paciente);
    }

    fila_pacientes = fila_auxiliar;

    if(encontrado){
        cout << "\nOs dados do paciente foram atualizados com sucesso." << endl;
    }
    else{
        cout << "\nO Paciente de ID: " << id_paciente << " não foi encontrado na fila." << endl;
    }

}

void visualizar_fila(){

    if(fila_pacientes.empty()){
        cout << "A fila se encontra vazia. Nenhum paciente cadastrado." << endl;
        return;
    }

    cout << "A fila de pacientes será mostrada a seguir: " << endl << endl;

    priority_queue<Ficha,vector<Ficha>,CompararPrioridades> fila_auxiliar;
    fila_auxiliar = fila_pacientes;

    Ficha paciente;

    while(!fila_auxiliar.empty()){
        paciente = fila_auxiliar.top();
        fila_auxiliar.pop();

        cout << "Nome completo: " << paciente.nome << endl;

        cout << "Grau de prioridade: " << paciente.prioridade << endl;

        cout << "Id do paciente: " << paciente.id << endl << endl;
    }
}