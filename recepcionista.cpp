#include <iostream>
#include <string>
#include <queue>
#include <limits>
#include <fstream>
#include <sstream>
#include "recepcionista.h"
#include "gerenciamento.h"

using namespace std;

priority_queue<EsperaAtendimento,vector<EsperaAtendimento>,CompararPrioridades> fila_pacientes;

int senha_atualizada(){
    int senha_atual=1;

    priority_queue<EsperaAtendimento,vector<EsperaAtendimento>,CompararPrioridades> fila_contagem = fila_pacientes;

    while(!fila_contagem.empty()){
        senha_atual ++;
        fila_contagem.pop();
    }

    return senha_atual;
};

int senha=senha_atualizada();

void cadastrar_paciente(){
    ofstream cadastros("pacientes_cadastrados.txt",ios::app);

    if(!cadastros.is_open()){
        cout << "Falha ao acessar o arquivo de pacientes cadastrados." << endl;
        return;
    }

    Ficha paciente;

    cout << "Cadastro do paciente iniciado." << endl;
    cout << "Por favor, informe os dados solicitados a seguir." << endl << endl;

    paciente.id = gerador_id();

    cout << "Nome completo: ";
    paciente.nome = leitor_nome();

    cout << "CPF: " ;
    paciente.cpf = leitor_cpf();
    if(busca_por_cpf(paciente.cpf)){
        cout << "O paciente que está sendo cadastrado já possui registro em nosso sistema!" << endl;



        return;
    }

    cout << "Data de nascimento: " ;
    paciente.dataNascimento = leitor_data();

    cout << "Insira a seguir o sexo do paciente (M = Masculino, F = Feminino, O = Outro/Não-binário): " ;
    paciente.sexo = leitor_sexo();

    cout << "Número para contato: " ;
    paciente.telefone  = leitor_telefone();

    cadastros << paciente.id << "|" << paciente.nome << "|" << paciente.cpf << "|" << paciente.dataNascimento << "|" <<paciente.sexo << "|" <<paciente.telefone << endl;

    cout << "\nO Paciente foi cadastro com sucesso e possui o seguinte ID: " << paciente.id << endl;

    cadastros.close();
}

void atualizar_dados(const string& cpf_paciente){
    ifstream cadastros("pacientes_cadastrados.txt");
    ofstream atualizados("processamento.txt");

    if(!cadastros.is_open()){
        cout << "Falha ao acessar o arquivo de pacientes cadastrados." << endl;
        return;
     }
     
    if(!busca_por_cpf(cpf_paciente)){
        cout << "\nO Paciente não foi encontrado nos registros do sistema!" << endl;
    } 
    else{
        string linha;
        while(getline(cadastros,linha)){
            stringstream leitor(linha);

            string campo,cpf_lido,id_paciente;
            int index_leitor = 0;

            while(getline(leitor,campo,'|')){
                if(index_leitor == 0){
                    id_paciente = campo;
                }
                if(index_leitor == 2){
                    cpf_lido = campo;
                    break;
                }
                index_leitor ++;
            }

            if(cpf_lido == cpf_paciente){
                Ficha paciente;

                cout << "\nA atualização da ficha de cadastro está sendo realizada. Por favor insira os dados atualizados.\n" << endl;

                paciente.id = stoi(id_paciente);

                cout << "Nome completo: ";
                paciente.nome = leitor_nome();

                cout << "Data de nascimento: " ;
                paciente.dataNascimento = leitor_data();

                cout << "Insira a seguir o sexo do paciente (M = Masculino, F = Feminino, O = Outro/Não-binário): " ;
                paciente.sexo = leitor_sexo();

                cout << "Número para contato: " ;
                paciente.telefone  = leitor_telefone();
            
                atualizados << paciente.id << "|" << paciente.nome << "|" << cpf_paciente << "|" << paciente.dataNascimento << "|" <<paciente.sexo << "|" <<paciente.telefone << endl;

                cout << "\nOs dados do paciente foram atualizados com sucesso." << endl;
            }
            else{
                atualizados << linha << endl;
            }
        }

        remove("pacientes_cadastrados.txt");
        rename("processamento.txt","pacientes_cadastrados.txt");
        
    }
            
    atualizados.close();
    cadastros.close();

    return;
}

bool verificar_duplicidade(int id_comparador){
    priority_queue<EsperaAtendimento,vector<EsperaAtendimento>,CompararPrioridades> fila_comparativa = fila_pacientes;
    

    EsperaAtendimento comparador;
    while(!fila_comparativa.empty()){
        comparador = fila_comparativa.top();
        fila_comparativa.pop();

        if(id_comparador == comparador.info_paciente.id){
            return true;
        }
    }

    return false;
}

void adicionar_fila_atendimento(){
    EsperaAtendimento paciente;
    int id_verificador,id_limitador;

    cout << "\nInsira a seguir o ID do paciente que será adicionado a fila de atendimento." << endl;
    cout << "ID do paciente: ";
    id_verificador = leitor_inteiros();
    id_limitador = gerador_id();

    if(id_verificador < 0 || id_verificador >= id_limitador){
        cout << "\nO paciente ainda não possui cadastro no sistema para que possa ser inserido na fila de atendimento." << endl;
        cout << "Realize o cadastro do paciente para que ele possa ser inserido na fila de atendimento do hospital!" << endl;
    }
    else{

        if(verificar_duplicidade(id_verificador)){
            cout << "\nEsse paciente já se encontra na fila de espera para realizar um atendimento, portanto não será possível realizar a inserção." << endl;
        
            return;
        }

        EsperaAtendimento paciente;

        ifstream cadastros("pacientes_cadastrados.txt");

        string linha;
        while(getline(cadastros,linha)){
            stringstream leitor(linha);

            string campo;
            int index=0,copia_id;

            while(getline(leitor,campo,'|')){
                if(index == 0){
                    copia_id = stoi(campo);
                    if(copia_id != id_verificador) break;
                    else paciente.info_paciente.id = copia_id;
                }
                else if(index == 1) paciente.info_paciente.nome = campo;
                else if(index == 2) paciente.info_paciente.cpf = campo;
                else if(index == 3) paciente.info_paciente.dataNascimento = campo;
                else if(index == 4) paciente.info_paciente.sexo = campo;
                else if(index == 5) paciente.info_paciente.telefone = campo;

                index++;
            }
        }

        cout << "\nQual o grau de gravidade do incidente: ";
        paciente.prioridade = leitor_prioridade();

        paciente.senha = senha_atualizada();

        fila_pacientes.push(paciente);

        cout << "\nO paciente de ID " << paciente.info_paciente.id << " está inserido na fila de atendimento e possui a senha: " << paciente.senha << "." << endl;

    }

    return;
}

void visualizar_fila(){

    if(fila_pacientes.empty()){
        cout << "A fila se encontra vazia. Nenhum paciente cadastrado." << endl;
        return;
    }

    cout << "A fila de pacientes será mostrada a seguir: " << endl << endl;

    priority_queue<EsperaAtendimento,vector<EsperaAtendimento>,CompararPrioridades> fila_auxiliar;
    fila_auxiliar = fila_pacientes;

    EsperaAtendimento paciente;

    while(!fila_auxiliar.empty()){
        paciente = fila_auxiliar.top();
        fila_auxiliar.pop();

        cout << "Nome completo: " << paciente.info_paciente.nome << endl;

        cout << "Grau de prioridade: " << paciente.prioridade << endl;

        cout << "Senha do paciente: " << paciente.senha << endl << endl;
    }
}