# Informações do Trabalho Final de Estrutura De Dados I

## Informações básicas

Deve-se implementar um sistema de organização de eventos acadêmicos, utilizando diferentes estruturas de dados dinâmicas:

* [x] Lista Encadeada Circular
* [x] Lista Encadeada Simples
* [x] Lista Duplamente Encadeada
* [x] Fila
* [x] Pilha
* [x] Dois algoritmos de ordenação (um recursivo e outro iterativo)

## Descrição Geral

A universidade realiza eventos, e cada evento possui várias atividades. Cada atividade possui participantes. O sistema deve:

* [x] Organizar os eventos e suas atividades
* [x] Gerenciar participantes
* [x] Controlar fila de chegada para check-in
* [ ] Permitir desfazer remoções com uma pilha
* [x] Ordenar atividades por horário e participantes por nome (um algoritmo deve ser recursivo e outro iterativo)

## Estruturas necessárias

* [x] Lista Encadeada Circular de Eventos
  * Cada nó representa um evento (nome, data, ponteiro para lista de atividades)
* [x] Lista Encadeada Simples de Atividades
  * Cada nó representa uma atividade (título, horário, ponteiro para participantes)
* [x] Lista Duplamente Encadeada de Participantes
  * Cada nó representa um participante (nome, matrícula, e-mail)
* [x] Fila de Check-in por Evento (Ponteiro - Lista Encadeada)
  * Gerencia a ordem de chegada dos participantes no dia do evento
* [ ] Pilha de Desfazer (Ponteiro - Lista Encadeada)
  * Armazena operações de remoção (atividade ou participante) e permite restaurar a última
* [x] Algoritmo de Ordenação (um deve ser recursivo e outro iterativo) aplicados em:
  * Atividades por horário
  * Participantes por nome (ordem alfabética)

## Funcionalidades

### Eventos

* [x] Cadastrar
* [x] Listar
* [x] Remover

### Atividades (por evento)

* [x] Cadastrar
* [x] Listar
* [x] Remover

### Participantes (por atividade)

* [x] Cadastrar
* [x] Listar
* [x] Remover

### Check-in (dos part. em uma fila)

* [x] Realizar check-in

### Outras

* [ ] Desfazer a última remoção usando pilha
* [x] Ordenar e exibir atividades ou participantes conforme solicitado no menu
