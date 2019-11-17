/*
 * TreeNode.h
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_SOLVER_TREENODE_H_
#define SRC_SOLVER_TREENODE_H_

#include "../tools/Graph.h"

class TreeNode {
	private:         
		int* Cand;                           // Array de Candidatos
		int* currCand;                       // Array de candidatos atuais
		int* Bvts;                           // Array de bvertices
		short numcand;                       // Numero de candidatos
		short sizeB;                         // Numero de bvertices
		short posBvt;                        // Não utilizado
		short posCand;                       // Não utilizado
		bool genL;                           // Representa se o filho esquerdo ja foi gerado
		bool genR;                           // Representa se o filho direito ja foi gerado
		bool visited;                        // Representa se o nó ja foi visitado
		Graph* g;                            // Referencia ao grafo
	public:
		TreeNode();                          // Construtpor vazio

		TreeNode(TreeNode* t, bool dir);     // Construtor dos demais nós

		TreeNode(Graph* G, int* order);      // Construtor da raiz

		virtual ~TreeNode();                 // Destrutor

		TreeNode* genLeft();                 // Gera o filho esquerdo

		TreeNode* genRight();                // Gera o filho direito

		TreeNode* genLeft(int);              // Gera o filho esquerdo utilizando alguns cortes

		TreeNode* genRight(int);             // Gera o filho direito utilizando alguns cortes

		bool hasLeft();                      // True: Filho esquerdo foi gerado, C.C False

		bool hasRight();                     // True: Filho direito foi gerado, C.C False

		bool hasChild();                     // True: Se a lista de candidatos está vazia // É uma folha

		int* getCand();                      // Retorna o array de candidatos // Esse array nunca muda
		
		int* getCurCand();                   // Retorna o array dos candidatos atuais // Esse array muda durante a enumeração

		int* getBvertices();                 // Retorna o array de bvertices

		void setBNum (short);                // Seta o numero de bvertices

		short getBNum();                     // Calcula e retorna o numero de bvertices

		short getBNum2 ();                   // Retorna o numero de bvertices

		void setCand(int*);                  // Seta o array de candidatos
 
		void setCandNum (short);             // Seta o numero de candidatos

		void setVisited(bool);               // True: Se o no ja foi visitado // Acho que não é utilizada

		short getCanNum();                   // Retorna o numero de candidatos

		bool getVisited();

		void print ();                       // Printa o bvertices e os candidatos do nó
	protected:
};

#endif /* SRC_SOLVER_TREENODE_H_ */
