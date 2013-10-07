#ifndef NODE_H
#define NODE_H

template<class T=int>
class Node{
	private:
		T data;
		Node<T>* next;
	
	public:
		Node(T data){
			this->data=data;
			this->next=NULL;
		}
		~Node(){
			if (next)
				delete this->next;
		}
		Node* getNext(){
			return this->next;
		}
		void setNext(Node* next){
			this->next=next;
		}
		T getData(){
			return this->data;
		}
};

#endif
