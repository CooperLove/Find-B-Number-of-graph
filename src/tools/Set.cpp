/*
 * Set.cpp
 *
 *  Created on: 15 de ago de 2019
 *      Author: marcio
 */

#include "Set.h"

/*
 * Cria um conjunto de tamanho n, para armzenar os elementos de 0 até n-1
 * */
Set::Set(int size){
	//TOOD
}

/*
 * Destructor
 * */
Set::~Set(){
	//TODO
}

/*
 * Adiciona o elemento elem no conjunto
 * */
void Set::add(long elem){
	//TODO
}

/*
 * Adiciona todos os elementos ao conjunto
 * */
void Set::addAll(){
	//TODO
}

/*
 * Remove um elemento do conjunto
 * */
void Set::remove(long elem){
	//TODO
}

/*
 * Remove todos os elementos do conjunto
 * */
void Set::removeAll(){
	//TODO
}

/*
 * Verifica se um elemento está no conjunto
 * */
bool Set::isIn(long elem){
	//TODO
	return false;
}

/*
 * Faz a interseção do conjunto com o conjunto passado de argumento
 * */
void Set::inter(Set* s){
	//TODO
}

/*
 * Complemento do conjunto em relação ao tamanho
 * */
Set* Set::complement(){
	//TODO
	return NULL;
}

/**
 * copia o conjunto
 * */
Set* Set::copy(){
	//TODO
	return NULL;
}

/**
 *
 * Verifica se os conjuntos são iguais
 */
bool Set::isEqual(Set* s){
	//TODO
}

/*
 * Subtrai o conjunto do conjunto corrente
 * */
void Set::subtr(Set* s){
	//TODO
}

/*
 * Uni o conjunto passado como argumento ao conjunto corrente
 * */
void Set::unio(Set* s){
	//TODO
}

/*
 * Recupera o primeiro elemento do conjunto
 * */
long Set::firstElem(){
	//TODO
	return 0;
}

/*
 * recupera o primeiro elemento logo após o elemento dado de argunento.
 * */
long Set::firstElemAfter(long elem){
	//TODO
	return 0;
}

/*
 * Conta o numero de elementos
 * */
long Set::count(){
	//TODO
	return 0;
}

/*
 * Verifica se o conjunto é vazio
 * */
bool Set::isEmpty(){
	//TODO
	return 0;
}

/*
 * Verifica se a interseção é vazia sem modificar os conjuntos
 * */
bool Set::isIntersEmpty(Set* s){
	//TODO
	return 0;
}

/*
 * Verifica se a subtração é vazia sem modificar os conjuntos
 *
 * */
bool Set::isSubtEmpty(Set* s){
	//TODO
	return 0;
}

/*
 * Imprimi i conjunto
 * */
void Set::print(){
	//TODO
}
