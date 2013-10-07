#ifndef NODE_H
#define NODE_H

class Node{
	private:
		unsigned data;
		Node* next;
	
	public:
		Node(int data){
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
		int getData(){
			return this->data;
		}
};

#endif
