#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <regex>
#include "menus.h"

using namespace std;

void pause(){
    cout << "\nPressione a tecla ENTER para prosseguir!" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
};

int leitor_inteiros(){
    int valor;

    while(!(cin >> valor)){
        cout << "Entrada inválida!" << endl;
        cout << "Insira um valor numérico inteiro." << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
};

bool verificador_cpf(){

};

string leitor_cpf(){
    string cpf,analise;

    getline(cin, cpf);

    for(char c : cpf){
        if(isdigit(static_cast<unsigned char>(c))){
            analise+= c;
        }
    }

    if((size(analise) < 11)){
        cout << "\nFormato de CPF inválido!"<< endl;
        cout << "Por favor realize o preenchimento em seu formato comum." << endl;
        cout << "\nCPF: ";
    }
    

    return cpf;
};

int menu_inicial(){ // Após a mensagem de boas vindas essa é a opção que será apresentada, permitindo que selecione o perfil do usuário para que fique separado a aba do médico e da recepcionista, já que ambos possuem diferentes funções dentro do uso do sistema.
    int profile;

    system("clear");
    
    cout << "O atendimento será iniciado, por favor selecione qual o perfil que será utilizado: " << endl << endl;
    cout << "0 - Encerrar o sistema;" << endl;
    cout << "1 - Recepcionista;" << endl;
    cout << "2 - Médico." << endl;

    profile = leitor_inteiros();

    return profile;
}

int menu_recepcionista(){ // Após selecionar o perfil de recepcionista essas são as opções disponíveis para realizar o gerenciomento de paciente e da rotina do hospital.
    int option;
    
    system("clear");

    cout << "Perfil: RECEPCIONISTA" << endl << "Por favor selecione a próxima ação no menu: " << endl << endl;
    cout << "0 - Retornar;" << endl;
    cout << "1 - Cadastrar paciente;" << endl;
    cout << "2 - Atualizar dados do paciente;" << endl;
    cout << "3 - Visualizar fila de pacientes;" << endl;
    //cout << "4 - Agendar consulta;" << endl;
    //cout << "5 - Cancelar consulta;" << endl;
    //cout << "6 - Visualizar agenda do dia." << endl;
    option = leitor_inteiros();

    return option;
}

int menu_medico(){ // Com a seleção do perfil médico as opções serão voltadas a parte clinica e não de gestão dos pacientes, com foco na parte prática sem acesso ao gerenciamento.
    int option;
    
    system("clear");

    cout << "Perfil: MÉDICO" << endl << "Por favor selecione a próxima ação no menu: " << endl << endl;
    cout << "0 - Retornar;" << endl;
    cout << "1 - Visualizar fila de pacientes;" << endl;
    cout << "2 - Iniciar atendimento;" << endl;
    cout << "3 - Consultar prontuário;" << endl;
    cout << "4 - Registrar diagnóstico;" << endl;
    cout << "5 - Prescrever medicamento;" << endl;
    //cout << "6 - Solicitar exame;" << endl;
    //cout << "7 - Visualizar resultados de exames." << endl;

    option = leitor_inteiros();

    return option;
}