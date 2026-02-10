#include <iostream>
#include <string>

#include "gerenciamento.h"
#include "recepcionista.h"
#include "medico.h"

using namespace std;

int main(){
    int option,profile;

    clear();
    
    carregar_fila_externa();
    
    cout << "Olá, seja bem-vindo ao sistema do Hospital São Gabriel, o hospital com cuidado que protege e saúde que transforma." << endl ;
    cout << "\nPressione a tecla Enter para iniciar o sistema!" << endl; // Mensagem de Boas Vindas ao inicializar o sistema pela primeira vez. 
    
   cin.get();

    while(true){ // Looping para manter o sistema ativo até que por vontade própria o usuário encerre o funcionamento selecionando a opção '0'. 
        profile = menu_inicial();

        if(profile == 0){
            cout << "A sessão será encerrada!" << endl;

            salvar_fila_externa();

            break;
        }

        switch(profile){
            case 1:
                while(true){ // Looping que mantém conectado ao perfil selecionado, nesse caso sendo o da recepcionista, com acesso a organização de dados.
                    option = menu_recepcionista();

                    if(option == 0){
                        cout << "Retornando ao menu inicial." << endl;

                        break;
                    };

                    switch(option){
                        case 1:
                             clear();

                            cadastrar_paciente();
                        break;
                        case 2:{
                            clear();

                            string cpf_searcher;

                            cout << "A atualização de um cadastro já existente de um paciente foi inicializada." << endl;
                            cout << "\nInsira a seguir o CPF do paciente cujo cadastro deseja atualizar." << endl;
                            cout << "CPF do paciente: ";
                            cpf_searcher = leitor_cpf();

                            atualizar_dados(cpf_searcher);
                        break;
                        }
                        case 3:
                            clear();

                            adicionar_fila_atendimento();
                        break;
                        case 4:
                            clear();

                            visualizar_fila();
                        break;
                        default:
                            cout << "Selecione uma opção válida para o perfil selecionado." << endl;
                        break;
                    }
                    pause();
                }
            break;
            case 2:
                while(true){ // Looping que mantém conectado ao perfil selecionado, nesse caso sendo o do Médico, com acesso a funções de tratamento.
                    option = menu_medico();

                    if(option == 0){
                        cout << "Retornando ao menu inicial." << endl;

                        break;
                    };
                    

                    switch(option){
                        case 1:
                            clear();

                            visualizar_fila();
                        break;
                        case 2:{
                            clear();

                            iniciar_atendimento();
                        }
                        default:
                            cout << "Selecione uma opção válida para o perfil selecionado." << endl;
                        break;
                    }
                    pause();
                }
            break;
            default:
                cout << "Selecione um perfil válido para continuar o atendimento." << endl;
            break;
        }
        pause();
    }

    return 0;
}