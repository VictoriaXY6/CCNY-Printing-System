#include <iostream>

using namespace std;

struct node {
	int id;
	node *next;

	node(userID) {
		this->id=userID;
		this->next=NULL;
	}
}; 

class printer {
	node *head = NULL;
	node *tail = NULL;

	int length;

	void enqueue(int userID) {
		node *temp = new node(userID);

		if (head==NULL) {
			head=temp;
			tail=temp;
		}
		else {
			tail->next=temp;
			tail=temp;
		}
	}

	int dequeue() {
		if (head!=NULL) {
			node *temp = head;
			head = head->next;
			int id_to_remove = temp->id;
			del(temp);
			return id_to_remove;
		}
		else {
			return 0;
		}
	}


	void display() {
		Node *curr = head;
		while(curr != NULL) {
			cout<<curr->id;
		}
	}
};