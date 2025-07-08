#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../estruturas/struct_participante.h"
#include "lista_duplamente_encadeada_participante.h"
#include "pilha_participante.h"
#include "fila_check_in.h"

// Manipulação de participantes na lista duplamente encadeada

ListaParticipante* inicializarListaParticipantes(){
  return NULL;
}

ListaParticipante* criarParticipante(char matricula[], char nome[], char email[]){ // Cria um novo participante com os dados fornecidos.
  ListaParticipante* novoParticipante = (ListaParticipante*)malloc(sizeof(ListaParticipante));

  if (novoParticipante == NULL){
    printf("Erro ao criar participante\n");
    return NULL;
  }

  strncpy(novoParticipante->info.matricula, matricula, sizeof(novoParticipante->info.matricula) - 1); // Copia a matrícula do participante.
  novoParticipante->info.matricula[sizeof(novoParticipante->info.matricula) - 1] = '\0'; // Garante que a string esteja terminada com nulo.

  strncpy(novoParticipante->info.nome, nome, sizeof(novoParticipante->info.nome) - 1);
  novoParticipante->info.nome[sizeof(novoParticipante->info.nome) - 1] = '\0';

  strncpy(novoParticipante->info.email, email, sizeof(novoParticipante->info.email) - 1);
  novoParticipante->info.email[sizeof(novoParticipante->info.email) - 1] = '\0';

  novoParticipante->anterior = NULL;
  novoParticipante->proximo = NULL; // seta os ponteiros anterior e proximo inicialmente como NULL.

  return novoParticipante; // Retorna o novo participante criado.
}

int existeParticipante(ListaParticipante *lista, char matriculaParticipante[]) { // Verifica se um participante com a matrícula fornecida já existe na lista.
    int existe = 0;
    ListaParticipante *atual = lista;
    while (atual != NULL) {
        if (strcasecmp(atual->info.matricula, matriculaParticipante) == 0){
            existe = 1;
            return existe;
        }
        atual = atual->proximo;
    }

    return existe;
}

int inserirParticipante(ListaParticipante** lista, ListaParticipante* novoParticipante){ // Insere um novo participante na lista duplamente encadeada.
  if (*lista == NULL){
    *lista = novoParticipante;
    return 1;
  }

  ListaParticipante* atual = *lista;

  while (atual != NULL){
    if (strcmp(atual->info.matricula, novoParticipante->info.matricula) == 0){ // Se a matrícula do novo participante já existe na lista não cadastra.
      printf("Participante já existe na lista\n");
      free(novoParticipante); // Se a matrícula já existe, libera a memória alocada para o novo participante.
      return 0;
    }
    if (atual->proximo == NULL){ // Garante que o nó atual seja o último participante da lista.
        break;
    }
    atual = atual->proximo;
  }
  // Insere o novo participante no final da lista alterando os ponteiros.
  atual->proximo = novoParticipante;
  novoParticipante->anterior = atual;
  novoParticipante->proximo = NULL;

  return 1;
}

void liberarListaParticipantes(ListaParticipante** lista){ // Libera toda a memória alocada para a lista de participantes.
    ListaParticipante* atual = *lista;
    while (atual != NULL){
        ListaParticipante* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *lista = NULL;
}

int removerParticipante(ListaParticipante** lista, char matricula[], PilhaParticipante* pilha, FilaCheckIn** fila) { // remove um participante da lista duplamente encadeada e o empilha na pilha de participantes removidos.
    if (*lista == NULL){
        printf("Não há participantes para serem removidos!\n");
        return 0;
    }

    ListaParticipante* atual = *lista;

    while (atual != NULL && strcmp(atual->info.matricula, matricula) != 0){ // Encontra o participante com a matrícula fornecida ou atual é NULL.
        atual = atual->proximo;
    }
    if (atual == NULL){
        printf("Participante não encontrado!\n");
        return 0;
    }
    
    // remove o participante da lista se ele existir.
    if (atual->anterior != NULL){
        atual->anterior->proximo = atual->proximo;
    } else{
        *lista = atual->proximo;
    }

    if (atual->proximo != NULL){
        atual->proximo->anterior = atual->anterior;
    }

    // Cria um participante temporário para armazenar os dados do participante removido.
    Participante temp;
    strcpy(temp.matricula, atual->info.matricula);
    strcpy(temp.nome, atual->info.nome);
    strcpy(temp.email, atual->info.email);

    if (!empilharParticipante(pilha, temp)){ // Empilha o participante removido na pilha de participantes removidos.
        printf("Não foi possível remover o participante! (pilha não suporta)\n");
        return 0;
    }

    if (existeNaFila(*fila, matricula)){ // Verifica se o participante está na fila de check-in e o remove.
        removerFila(*fila, matricula);
    }
    

    free(atual);

    printf("Participante removido com sucesso!\n");

    return 1;
}
// Desfaz a remoção de um participante, desempilhando o último participante removido e inserindo-o de volta na lista.
int desfazerRemocaoParticipante(ListaParticipante** lista, PilhaParticipante* pilha){ 
    if (pilha->topo == NULL){
        printf("Não há nada para desfazer!\n");
        return 0;
    }

    Participante p;

    if (!desempilharParticipante(pilha, &p)){ // Desempilha o último participante removido da pilha.
        printf("Não foi possível desfazer a remoção do participante!\n");
        return 0;
    }

    ListaParticipante* novoParticipante = (ListaParticipante*)malloc(sizeof(ListaParticipante));
    if (novoParticipante == NULL){
        printf("Não foi possível desfazer a remoção do participante!\n");
        return 0;
    }
    // Copia os dados do participante desempilhado para o novo participante.
    strcpy(novoParticipante->info.matricula, p.matricula);
    strcpy(novoParticipante->info.nome, p.nome);
    strcpy(novoParticipante->info.email, p.email);
    novoParticipante->anterior = NULL;
    novoParticipante->proximo = NULL;

    return inserirParticipante(lista, novoParticipante); // Insere o participante desempilhado de volta na lista.
}

ListaParticipante *copiarListaParticipante(ListaParticipante *lista) { // Cria uma cópia da lista de participantes.
    if (lista == NULL) {
        return NULL;
    }

    ListaParticipante *copia = NULL;
    ListaParticipante *ultimo = NULL;

    ListaParticipante *atual = lista;
    while (atual != NULL) {
        ListaParticipante* novoNo = malloc(sizeof(ListaParticipante));
        if (novoNo == NULL) {
            perror("Erro ao alocar na memoria");
            exit(1);
        }

        novoNo->info = atual->info;
        novoNo->proximo = NULL;
        novoNo->anterior = ultimo;

        if (ultimo == NULL) {
            copia = novoNo;
        } else {
            ultimo->proximo = novoNo;
        }
        ultimo = novoNo;

        atual = atual->proximo;
    }

    return copia;
}

ListaParticipante* ordernarListaParticipantesPeloNome(ListaParticipante* lista){ // Ordena a lista de participantes pelo nome usando o algoritmo Merge Sort.
    if (lista == NULL || lista->proximo == NULL){
        return lista;
    }
    ListaParticipante* lento = lista;
    ListaParticipante* rapido = lista;

    while (rapido->proximo != NULL && rapido->proximo->proximo){ // Usa dois ponteiros, um lento e outro rápido, para encontrar o meio da lista.
        lento = lento->proximo;
        rapido = rapido->proximo->proximo;
    }
    // Divide a lista em duas metades.
    ListaParticipante* meio = lento->proximo; // Ponteiro que marca o início da segunda metade
    lento->proximo = NULL;// "Corta" a lista em duas partes.
    if (meio != NULL){ 
        meio->anterior = NULL; // Garante que a segunda metade não tenha um ponteiro anterior.
    }
    // Recursivamente ordena as duas metades.
    ListaParticipante* esquerda = ordernarListaParticipantesPeloNome(lista); 
    ListaParticipante* direita = ordernarListaParticipantesPeloNome(meio);

    ListaParticipante* resultado = NULL;
    ListaParticipante** ponteiroAtual = &resultado;

    // Mescla as duas listas ordenadas
    // Compara os nomes e junta os nós em ordem alfabética
    while (esquerda != NULL && direita != NULL){
        if (strcmp(esquerda->info.nome, direita->info.nome) <= 0){
            *ponteiroAtual = esquerda; // Insere o nó da esquerda na lista ordenada.
            esquerda->anterior = NULL; // Garante que o nó da esquerda não tenha um ponteiro anterior.
            esquerda = esquerda->proximo;
        } else{
            *ponteiroAtual = direita; // Insere o nó da direita na lista ordenada.
            direita->anterior = NULL; // Garante que o nó da direita não tenha um ponteiro anterior.
            direita = direita->proximo;
        }
        ponteiroAtual = &((*ponteiroAtual)->proximo);
    }
    // Se uma das listas ainda tiver nós, adiciona-os ao final da lista ordenada.
    if (esquerda != NULL){
        *ponteiroAtual = esquerda;
    } else{
        *ponteiroAtual = direita;
    }
    // Corrige os ponteiros "anterior" da lista duplamente encadeada
    ListaParticipante* atual = resultado;
    ListaParticipante* anterior = NULL;
    while (atual != NULL){
        atual->anterior = anterior;
        anterior = atual;
        atual = atual->proximo;
    }
    
    return resultado; // Retorna a lista ordenada.
}

void imprimirListaParticipantesOrdenada(ListaParticipante *lista) { // Imprime a lista de participantes ordenada pelo nome.
    ListaParticipante *copia = copiarListaParticipante(lista);
    ListaParticipante *resultado = ordernarListaParticipantesPeloNome(copia); // Ordena a lista de participantes pelo nome.
    
    printf("\nParticipantes cadastrados:\n");
    ListaParticipante *atual = resultado;
    while (atual != NULL) {
        printf("Nome: %s | Matricula: %s | E-mail: %s\n", atual->info.nome, atual->info.matricula, atual->info.email);
        atual = atual->proximo;
    }
    printf("\n");

    // Libera a memória alocada para a lista ordenada.
    atual = resultado;
    while (atual != NULL) {
        ListaParticipante *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}