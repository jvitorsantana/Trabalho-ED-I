#include <stdio.h>
#include "lista_encadeada_atividade.h"

int main() {
    ListaAtividade *lista = inicializar();
    lista = inserirAtividade(lista, "Reunião de equipe", "15:00");
    lista = inserirAtividade(lista, "Almoço", "12:00");
    lista = inserirAtividade(lista, "Reunião com cliente", "14:00");
    lista = inserirAtividade(lista, "Reunião de equipe", "15:00");

    exibirAtividades(lista);

    lista = removerAtividade(lista, "Almoço");
    exibirAtividades(lista);

    ListaAtividade *atividade = buscarAtividade(lista, "sda de equipe");
    
    if (atividade != NULL && atividade->info != NULL) {
        printf("Atividade encontrada: \nTítulo: %s, Horário: %s\n", atividade->info->titulo, atividade->info->horario);
    } else {
        printf("Atividade não encontrada.\n");
    }

    liberarAtividades(lista);
    
    return 0;
}