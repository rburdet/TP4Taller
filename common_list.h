#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "common_node.h"

class List{
	private:
		Node* first;
		Node* actual;
	
	public:
		List() : first(NULL), actual(NULL){}

		~List(){
			if (this->first!=NULL)
				delete this->first;
		}
		Node* getFirst(){
			return this->first;
		}	

		void addNode(Node* node){
			if (this->first == NULL){
				this->first=node;
				this->actual=node;
			}else{
				(this->actual)->setNext(node);
				this->actual = node;
			}
		}
			
		Node* searchNode(int data){
			if (this->first->getData()==data){
				return this->first;
			}else{
				Node* aux=this->first;
				while (aux != NULL){
					if (aux->getData() == data)
						return aux;
					aux=aux->getNext();
				}
			return aux;
			}
		}

};

#endif
