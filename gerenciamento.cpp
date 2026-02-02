#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>
#include <regex>
#include <queue>
#include <fstream>
#include <sstream>
#include "recepcionista.h"
#include "medico.h"
#include "gerenciamento.h"

using namespace std;

void pause(){ //Função simples criada apenas para gerar uma pausa no decorrer dos processos entre as ações.
    cout << "\nPressione a tecla ENTER para prosseguir!" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
};

void clear(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
};

void salvar_fila_externa(){

    ofstream arquivo("fila_pacientes.txt");

    if(!arquivo.is_open()){
        cout << "Erro ao acessar arquivo para salvar a fila de pacientes atual";
        return;
    }

    EsperaAtendimento paciente;

    while(!fila_pacientes.empty()){
        paciente = fila_pacientes.top();
        fila_pacientes.pop();

        arquivo << paciente.info_paciente.id << "|" << paciente.info_paciente.nome << "|" << paciente.info_paciente.cpf << "|" << paciente.info_paciente.dataNascimento << "|" << paciente.info_paciente.sexo << "|" << paciente.info_paciente.telefone << "|"  << paciente.senha << "|" << paciente.prioridade << "|" << endl;
    }

    arquivo.close();

    return;

};

void carregar_fila_externa(){
    ifstream fila("fila_pacientes.txt");

    if(!fila.is_open()){
        cout << "Erro ao acessar arquivo para carregar a fila de pacientes atual";
        return;
    }

    string linha;
    EsperaAtendimento paciente;
    while(getline(fila,linha)){   
         stringstream leitor(linha);

        string campo;
        int index=0,copia_id;

        while(getline(leitor,campo,'|')){
            if (index == 0) paciente.info_paciente.id = stoi(campo);
            else if(index == 1) paciente.info_paciente.nome = campo;
            else if(index == 2) paciente.info_paciente.cpf = campo;
            else if(index == 3) paciente.info_paciente.dataNascimento = campo;
            else if(index == 4) paciente.info_paciente.sexo = campo;
            else if(index == 5) paciente.info_paciente.telefone = campo;
            else if(index == 6) paciente.senha = stoi(campo);
            else if(index == 7) paciente.prioridade = stoi(campo);

            index++;
        }

        fila_pacientes.push(paciente);
    }

    fila.close();

};

bool busca_por_cpf(const string& cpf_procurado){
    ifstream cadastros("pacientes_cadastrados.txt");
    if(!cadastros.is_open()){
        cout << "Falha ao acessar o arquivo de pacientes cadastrados." << endl;
        return false;
    }

    string linha;
    while(getline(cadastros,linha)){
        stringstream leitor(linha);

        string campo,cpf_arquivo;
        int index_leitor = 0;

        while(getline(leitor,campo,'|')){
            if(index_leitor == 2){
                cpf_arquivo = campo;
                break;
            }
            index_leitor++;
        }

        if(cpf_arquivo == cpf_procurado) return true;

    }
    cadastros.close();

    return false;
};




int leitor_inteiros(){ // Função criada para garantir que vai ocorrer o preenchimento correto com números inteiros para que não ocorra quebras na execução do próprio sistema e preenchimento de dados de forma indevida.
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

int gerador_id(){
    ifstream cadastros("pacientes_cadastrados.txt");
    int id=1;

    if(!cadastros.is_open()){
        cout << "Falha ao acessar o arquivo de pacientes cadastrados." << endl;
        return -1;
    }

    string linha;

    while(getline(cadastros,linha)){
        id++;
    }

    return id;
};


bool validador_nome(const string& nome){ // Verificador criado para assegurar que no preenchimento do nome não ocorrar violações com números ou espaço sem preenchimento.
    if (nome.empty() || nome[0] == ' ') return false;

    for(int i=0;i<nome.size();i++){
        if(isdigit(nome[i])) return false;
    }

    return true;
};

string leitor_nome(){ // leitor que chama a função verificadora e emite a mensagem de erro caso seja preenchido de forma incorreta o campo de nome no formulário mas que se estiver tudo certo retorna a string com o nome do paciente.
    string nome;
    bool valido = false;
    
    do{
        getline(cin,nome);

        valido = validador_nome(nome);

        if(valido) break;
        else{
            cout << "\nO nome informado não é válido. Use apenas letras."<< endl;
            cout << "Por favor realize o preenchimento de forma correta." << endl;
            cout << "\nNome Completo: ";
        }

    }while(!valido);

    return nome;
};

bool verificador_cpf(const string& cpf){ // Verificador para assegurar que a informação será preenchida no padrão para o CPF usando regex.

    regex padrao(R"(^\d{3}\.\d{3}\.\d{3}-\d{2}$)");
    
    return regex_match(cpf, padrao);
}

bool validador_cpf(const string& cpf) { // Validador que garante que após o preenchimento ser realizado no padrão exigido o CPF inserido é válido de acordo com as regras de validação para os digitos verificadores.
    int transformada[11],soma_validacao,resto_validacao;
    int k = 0;

    for (int i = 0; i < cpf.size(); i++) {
        if (isdigit(cpf[i])) {
            if (k >= 11) return false;
            transformada[k] = cpf[i] - '0';
            k++;
        }
    }

    if (k != 11) return false;

    bool digitos_iguais = true;
    for(int i=1;i<11;i++){
        if(transformada[i] != transformada[0]){
            digitos_iguais = false;
            break;
        }
    }
    if(digitos_iguais) return false;

    soma_validacao = 0;

    for(int j=10,i=0;i<9;i++,j--){
        soma_validacao+= transformada[i] * j;
    }

    resto_validacao = soma_validacao * 10 % 11;

    if(resto_validacao == 10) resto_validacao = 0;

    if(resto_validacao != transformada[9]) return false;

    soma_validacao = 0;

    for(int j=11,i=0;i<10;i++,j--){
        soma_validacao+= transformada[i] * j;
    }

    resto_validacao = soma_validacao * 10 % 11;

    if(resto_validacao == 10) resto_validacao = 0;

    if(resto_validacao != transformada[10]) return false;

    return true;
}

string leitor_cpf(){ // Função responsável por chamar tanto o verificador quanto o validador e a partir dos resultados deles mostrar uma mensagem de orientação de erros ou retornar a string com o CPF correto e válido para a ficha do Paciente.
    string cpf;

    bool valido = false;

    do{
        getline(cin, cpf);

        valido = verificador_cpf(cpf);

        if(valido == false){
            cout << "\nFormato de CPF inválido!"<< endl;
            cout << "Por favor realize o preenchimento em seu formato comum." << endl;
            cout << "\nCPF: ";
        }
        else{
            valido = validador_cpf(cpf);

            if(valido == false){
                cout << "\nO CPF inserido não é válido!"<< endl;
                cout << "Por favor realize o preenchimento com um CPF válido." << endl;
                cout << "\nCPF: ";
            }
            else break;
        }
    }while(!valido);

    return cpf;
};

bool validador_data(const string& data){ // Validador criado para assegurar o preenchimento tanto na formatação padrão exigida pelo sistema quanto para verificar se é uma data válida dentro das limitações de dias e meses.

    regex padrao(R"(^\d{2}/\d{2}/\d{4}$)");

    if(!regex_match(data,padrao)) return false;

    int dia = stoi(data.substr(0,2));
    int mes = stoi(data.substr(3,2));
    int ano = stoi(data.substr(6,4));

    if(mes < 1 || mes > 12) return false;

    int dias_mes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) dias_mes[1] = 29;

    if(dia < 1 || dia > dias_mes[mes - 1]) return false;

    return true;
}

string leitor_data(){ // Função responsável por chamar o validador e com base no seu resultado imprimir a mensagem de orientação devido a um erro ou retornar a data de nascimento validada (Ainda não verifica se é maior de idade).
    string data;

    bool valido = false;

    do{
        getline(cin,data);

        valido = validador_data(data);

        if(valido) break;
        else{
            cout << "\nA data inserida não é válida!"<< endl;
            cout << "Por favor realize o preenchimento com uma data coerente e na formatação padrão (DD/MM/AAAA)." << endl;
            cout << "\nData de nascimento: ";
        }


    }while(!valido);

    return data;
};

bool validador_sexo(const string& sexo){
    if(sexo == "M" || sexo == "F" || sexo == "O" ) return true;

    return false;
};

string leitor_sexo(){
    string sexo;
    bool valido = false;

    do{
        getline(cin,sexo);
        valido = validador_sexo(sexo);

        if(valido) break;
        else{
            cout << "\nA opção inserida não é válida!"<< endl;
            cout << "Por favor realize o preenchimento com uma opção coerente conforme o orientado." << endl;
            cout << "\nsexo do paciente (M = Masculino, F = Feminino, O = Outro/Não-binário): ";
        }
    }while(!valido);

    return sexo;
};

bool validador_telefone(const string& telefone){ // Validador responsável por realizar a verificação tanto da formatação do número (seja telefone fixo ou número de celular) e verificar se segue um DDD existente e o digitor iniciador adequado.
    regex padrao (R"(^\(\d{2}\)\s9\d{4}-\d{4}$)");
    regex padrao_fixo(R"(^\(\d{2}\)\s[2-5]\d{3}-\d{4}$)");

    if(!regex_match(telefone,padrao) && !regex_match(telefone,padrao_fixo)) return false;

    int vetor_DDDs[] = {11,12,13,14,15,16,17,18,19,21,22,24,27,28,31,32,33,34,35,37,38,41,42,43,44,45,46,47,48,49,51,53,54,55,61,62,63,64,65,66,67,68,69,71,73,74,75,77,79,81,82,83,84,85,86,87,88,89,91,92,93,94,95,96,97,98,99};

    int verificador_DDD = stoi(telefone.substr(1,2)) , fim = (sizeof(vetor_DDDs) / sizeof(vetor_DDDs[0])), inicio = 0;

    while(inicio <= fim){
        int meio  = (inicio + fim)/2;

        if(vetor_DDDs[meio] == verificador_DDD) return true;
        else if(verificador_DDD > vetor_DDDs[meio]){
            inicio = meio + 1;
        }
        else if(verificador_DDD < vetor_DDDs[meio]){
            fim = meio - 1;
        }
    }

    return false;
};

string leitor_telefone(){ // Função responsável por chamar o validador e com base no seu resultado imprimir a mensagem de orientação devido a um erro ou retornar o númeto já validado para o formulário.
    string telefone;
    bool valido = false;

    do{
        getline(cin,telefone);

        valido = validador_telefone(telefone);

        if(valido) break;
        else{
            cout << "\nO número de telefone inserido não é válido!"<< endl;
            cout << "Por favor realize o preenchimento com um número para contato coerente e na formatação padrão para telefones fixos ou números de telefones móveis." << endl;
            cout << "\nNúmero para contato: ";
        }
    }while(!valido);

    return telefone;
};

int leitor_prioridade(){ // Função responsável por chamar o leitor de inteiros e validar se a prioridade está no intervalo adequado e com base no seu resultado imprimir a mensagem de orientação devido a um erro ou retornar a prioridade para a ficha do paciente.
    int prioridade;
    bool valido = false;

    do{
        prioridade = leitor_inteiros();

        if(prioridade < 1 || prioridade > 5){
            cout << "\nNível de prioridade inválido!"<< endl;
            cout << "Por favor realize o preenchimento em seu intervalo padrão [1 a 5]." << endl;
            cout << "\nGrau de prioridade: ";
        }
        else{
            valido = true;
        }
    }while(!valido);

    return prioridade;
};

int menu_inicial(){ // Após a mensagem de boas vindas essa é a opção que será apresentada, permitindo que selecione o perfil do usuário para que fique separado a aba do médico e da recepcionista, já que ambos possuem diferentes funções dentro do uso do sistema.
    int profile;

    clear();
    
    cout << "O atendimento será iniciado, por favor selecione qual o perfil que será utilizado: " << endl << endl;
    cout << "0 - Encerrar o sistema;" << endl;
    cout << "1 - Recepcionista;" << endl;
    cout << "2 - Médico." << endl;

    profile = leitor_inteiros();

    return profile;
}

int menu_recepcionista(){ // Após selecionar o perfil de recepcionista essas são as opções disponíveis para realizar o gerenciomento de paciente e da rotina do hospital.
    int option;
    
    clear();

    cout << "Perfil: RECEPCIONISTA" << endl << "Por favor selecione a próxima ação no menu: " << endl << endl;
    cout << "0 - Retornar;" << endl;
    cout << "1 - Cadastrar paciente;" << endl;
    cout << "2 - Atualizar dados do paciente;" << endl;
    cout << "3 - Adicionar paciente a fila de atendimento;" << endl;
    cout << "4 - Visualizar fila de pacientes;" << endl;
    //cout << "5 - Cancelar consulta;" << endl;
    //cout << "6 - Visualizar agenda do dia." << endl;
    option = leitor_inteiros();

    return option;
}

int menu_medico(){ // Com a seleção do perfil médico as opções serão voltadas a parte clinica e não de gestão dos pacientes, com foco na parte prática sem acesso ao gerenciamento.
    int option;
    
    clear();

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