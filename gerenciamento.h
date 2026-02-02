#ifndef MENUS_H
#define MENUS_H

int menu_inicial();
int menu_recepcionista();
int menu_medico();

void salvar_fila_externa();

void carregar_fila_externa();

void pause();

void clear();

bool busca_por_cpf(const std::string& cpf_procurado);

int leitor_inteiros();

int gerador_id();

std::string leitor_nome();

std::string leitor_cpf();

std::string leitor_data();

std::string leitor_sexo();

std::string leitor_telefone();

int leitor_prioridade();


#endif