/*
 * Set.cpp
 *
 *  Created on: 15 de ago de 2019
 *      Author: marcio
 */

#include "Set.h"
#include <cstdio>


Set::Set(){
	
}
/*
 * Cria um conjunto de tamanho n, para armzenar os elementos de 0 até n-1
 * */
Set::Set(int size){
	//TOOD
	int* ver = new int[size];
	this->vertices = ver;
	this->numVer = size;
	this->currIndex = 0;
	for (int i = 0; i < size; i++)
		this->vertices[i] = 0;
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
	this->vertices[elem] = 1;
}

/*
 * Adiciona todos os elementos ao conjunto
 * */
void Set::addAll(){
	//TODO
	for (int i = 0; i < this->numVer; i++)
		this->vertices[i] = 1;
}

/*
 * Remove um elemento do conjunto
 * */
void Set::remove(long elem){
	//TODO
	this->vertices[elem] = 0;
}

/*
 * Remove todos os elementos do conjunto
 * */
void Set::removeAll(){
	//TODO
	free(&this->vertices);
	Set(this->numVer);
	this->currIndex = 0;
}

/*
 * Verifica se um elemento está no conjunto
 * */
bool Set::isIn(long elem){
	//TODO
	for (int i = 0; i < this->numVer; i++)
		if (this->vertices[i] == elem)
			return true;
	
	return false;
}

/*
 * Faz a interseção do conjunto com o conjunto passado de argumento
 * */
void Set::inter(Set* s){
	//TODO
	Set* q = new Set(this->numVer);
	for (int i = 0; i < this->numVer ; i++)
		if (this->vertices[i] == 1 && s->vertices[i] == 1)
			q->vertices[i] = 1;
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
	Set* s = new Set(this->numVer);
	for (int i = 0; i < this->numVer; i++)
		s[i] = this->vertices[i];
	
	return s;
}

/**
 *
 * Verifica se os conjuntos são iguais
 */
bool Set::isEqual(Set* s){
	//TODO
	if (s->numVer != this->numVer)
		return false;

	for (int i = 0; i < this->numVer; i++)
		if (s->vertices[i] != this->vertices[i])
			return false;
	
	return true;
}

/*
 * Subtrai o conjunto do conjunto corrente
 * */
void Set::subtr(Set* s){
	//TODO
	for (int i = 0; i < this->numVer; i++)
		if (this->vertices[i] == 1 && s->vertices[i] == 1)
			this->vertices[i] = 0;
}

/*
 * Uni o conjunto passado como argumento ao conjunto corrente
 * */
void Set::unio(Set* s){
	//TODO
	for (int i = 0; i < this->numVer; i++)
		if (s->vertices[i] == 1)
			this->vertices[i] == 1;
}

/*
 * Recupera o primeiro elemento do conjunto
 * */
long Set::firstElem(){
	//TODO
	return this->numVer > 0 ? this->vertices[0] : -1;
}

/*
 * recupera o primeiro elemento logo após o elemento dado de argunento.
 * */
long Set::firstElemAfter(long elem){
	//TODO
	int ind = -1;
	for (int i = elem + 1; i < this->numVer; i++)
		if (this->vertices[i] == 1){
			ind = i;
			break;
		}
	return ind;
}

/*
 * Conta o numero de elementos
 * */
long Set::count(){
	int n = 0;
	for (int i = 0; i < this->numVer; i++)
		if (this->vertices[i] == 1)
			n++;
	return n;
}

/*
 * Verifica se o conjunto é vazio
 * */
bool Set::isEmpty(){
	//TODO
	return this->count() == 0 ? true : false;
}

/*
 * Verifica se a interseção é vazia sem modificar os conjuntos
 * */
bool Set::isIntersEmpty(Set* s){
	//TODO
	for (int i = 0; i < this->numVer; i++)
		if (this->vertices[i] == 1 && s->vertices[i] == 1)
			return false;
	return true;
}

/*
 * Verifica se a subtração é vazia sem modificar os conjuntos
 *
 * */
bool Set::isSubtEmpty(Set* s){
	//TODO
	return this->isEqual(s) == true ? true: false;
}

/*
 * Imprimi i conjunto
 * */
void Set::print(){
	//TODO
	if (this->numVer == 0 ){
		printf("O conjunto não possui nenhum elemento!\n");
		return;
	}
	for (int i = 0; i < this->numVer; i++)
	{
		printf("%d ",this->vertices[i]);
	}
		printf("\n");
}
