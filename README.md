# Informações do Trabalho Final de Estrutura De Dados I

## Informações básicas

Deve-se implementar um sistema de organização de eventos acadêmicos, utilizando diferentes estruturas de dados dinâmicas:

* [ ] Lista Encadeada Circular
* [ ] Lista Encadeada Simples
* [ ] Lista Duplamente Encadeada
* [ ] Fila
* [ ] Pilha
* [ ] Dois algoritmos de ordenação (um recursivo e outro iterativo)

## Descrição Geral

A universidade realiza eventos, e cada evento possui várias atividades. Cada atividade possui participantes. O sistema deve:

* [ ] Organizar os eventos e suas atividades
* [ ] Gerenciar participantes
* [ ] Controlar fila de chegada para check-in
* [ ] Permitir desfazer remoções com uma pilha
* [ ] Ordenar atividades por horário e participantes por nome (um algoritmo deve ser recursivo e outro iterativo)

## Estruturas necessárias

* [ ] Lista Encadeada Circular de Eventos
  * Cada nó representa um evento (nome, data, ponteiro para lista de atividades)
* [ ] Lista Encadeada Simples de Atividades
  * Cada nó representa uma atividade (título, horário, ponteiro para participantes)
* [ ] Lista Duplamente Encadeada de Participantes
  * Cada nó representa um participante (nome, matrícula, e-mail)
* [ ] Fila de Check-in por Evento (Ponteiro - Lista Encadeada)
  * Gerencia a ordem de chegada dos participantes no dia do evento
* [ ] Pilha de Desfazer (Ponteiro - Lista Encadeada)
  * Armazena operações de remoção (atividade ou participante) e permite restaurar a última
* [ ] Algoritmo de Ordenação (um deve ser recursivo e outro iterativo) aplicados em:
  * Atividades por horário
  * Participantes por nome (ordem alfabética)

## Funcionalidades

### Eventos

* [ ] Cadastrar
* [ ] Listar
* [ ] Remover

### Atividades (por evento)

* [ ] Cadastrar
* [ ] Listar
* [ ] Remover

### Participantes (por atividade)

* [ ] Cadastrar
* [ ] Listar
* [ ] Remover

### Check-in (dos part. em uma fila)

* [ ] Realizar check-in

### Outras

* [ ] Desfazer a última remoção usando pilha
* [ ] Ordenar e exibir atividades ou participantes confome solicitado no menu
