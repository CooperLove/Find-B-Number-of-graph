/*
 * Set.h
 *
 *  Created on: 15 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_TOOLS_SET_H_
#define SRC_TOOLS_SET_H_

#include <cstdlib>

class Set {
public:

	int* vertices;
	int numVer;
	/*
	 * Cria um conjunto de tamanho n, para armzenar os elementos de 0 até n-1
	 * */
	Set();
	Set(int size);

	/*
	 * Destructor
	 * */
	virtual ~Set();

	/*
	 * Adiciona o elemento elem no conjunto
	 * */
	void add(long elem);

	/*
	 * Adiciona todos os elementos ao conjunto
	 * */
	void addAll();

	/*
	 * Remove um elemento do conjunto
	 * */
	void remove(long elem);

	/*
	 * Remove todos os elementos do conjunto
	 * */
	void removeAll();

	/*
	 * Verifica se um elemento está no conjunto
	 * */
	bool isIn(long elem);

	/*
	 * Faz a interseção do conjunto com o conjunto passado de argumento
	 * */
	void inter(Set* s);

	/*
	 * Complemento do conjunto em relação ao tamanho
	 * */
	Set* complement();

	/**
	 * copia o conjunto
	 * */
	Set* copy();

	/**
	 *
	 * Verifica se os conjuntos são iguais
	 */
	bool isEqual(Set* s);

	/*
	 * Subtrai o conjunto do conjunto corrente
	 * */
	void subtr(Set* s);

	/*
	 * Uni o conjunto passado como argumento ao conjunto corrente
	 * */
	void unio(Set* s);

	/*
	 * Recupera o primeiro elemento do conjunto
	 * */
	long firstElem();

	/*
	 * recupera o primeiro elemento logo após o elemento dado de argunento.
	 * */
	long firstElemAfter(long elem);

	/*
	 * Conta o numero de elementos
	 * */
	long count();

	/*
	 * Verifica se o conjunto é vazio
	 * */
	bool isEmpty();

	/*
	 * Verifica se a interseção é vazia sem modificar os conjuntos
	 * */
	bool isIntersEmpty(Set* s);

	/*
	 * Verifica se a subtração é vazia sem modificar os conjuntos
	 *
	 * */
	bool isSubtEmpty(Set* s);

	/*
	 * Imprimi i conjunto
	 * */
	void print();
private:
	int currIndex;
};

#endif /* SRC_TOOLS_SET_H_ */
