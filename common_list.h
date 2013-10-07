#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "common_node.h"

template<class T=int>
class List{
	private:
		Node<T>* first;
		Node<T>* actual;
	
	public:
		List() : first(NULL), actual(NULL){}

		~List(){
			if (this->first!=NULL)
				delete this->first;
		}
		Node<T>* getFirst(){
			return this->first;
		}	

		void addNode(Node<T>* node){
			if (this->first == NULL){
				this->first=node;
				this->actual=node;
			}else{
				(this->actual)->setNext(node);
				this->actual = node;
			}
		}
			
		Node<T>* searchNode(T data){
			if (this->first->getData()==data){
				return this->first;
			}else{
				Node<T>* aux=this->first;
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
