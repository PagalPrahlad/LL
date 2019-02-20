#include <iostream>
#include <cstdlib>
#include <cmath>


using namespace std;

template<class T>
struct node {
	T data;
	node<T> *next, *prev;
	
	node(const T _data): data(_data), next(NULL), prev(NULL) {}
	node(): next(NULL), prev(NULL) {}
};


template<class T>
struct myList {
	node<T> *head, *tail;
	size_t length;
	
	myList();
	~myList();
	
	void push_back (const T &);
	void push_front(const T &);
	
	T pop_back();
	T pop_front();
	
	ostream & display_forward (ostream &) const;
	ostream & display_backward(ostream &) const;
	size_t size() const { return length; }
	
	
	node<T> * insert(node<T> *, const T &);
	node<T> * del(node<T> *);
	
	bool issorted() const;
	
	void mergesort_aux(node<T> * &, node<T> * &);
	void mergesort() { mergesort_aux(head, tail); }
};

template<class T>
void myList<T>::mergesort_aux(node<T> * & P1, node<T> * & P2) {
	if(P1->next == P2 or length <= 1)
		return;
	
	node<T> * temp(P1);
	size_t count(0);
	while(temp != P2) {
		count += 1;
		temp = temp->next;
	}
	
	const size_t half_length(count / 2);
	temp = P1;
	count = 0;
	while(count != half_length) {
		count += 1;
		temp = temp->next;
	}
	node<T> * Pmid(temp);
	mergesort_aux(P1, Pmid);
	mergesort_aux(Pmid, P2);
	
	node<T> *T1(P1), *Tmid(Pmid);
	bool mark(true);
	while(T1 != Tmid and Tmid != P2) {
		if(T1->data < Tmid->data)
			T1 = T1->next;
		else {
			T1 = insert(T1, Tmid->data);
			if(mark)
				P1 = T1->prev;
			Tmid = del(Tmid);
		}
		mark = false;
	}
}


template<class T>
bool myList<T>::issorted() const {
	if(length <= 1)
		return true;
	
	node<T> * temp(head);
	while(temp->next != tail) {
		if(temp->data > temp->next->data)
			return false;
		temp = temp->next;
	}
	return true;
}


template<class T>
node<T> * myList<T>::del(node<T> * P) {
	// deletes the node P points to
	// returns a pointer to the next node
	if(length == 0 or P == tail)
		throw(domain_error("ERROR in del"));
	
	if(P == head) {
		pop_front();
		return head;
	}
	
	if(P == tail->prev) {
		pop_back();
		return tail;
	}
	
	node<T> * ans(P->next);
	P->prev->next = P->next;
	P->next->prev = P->prev;
	delete P;
	length -= 1;
	return ans;
}


template<class T>
node<T> * myList<T>::insert(node<T> * P, const T & data) {
	// inserts a new node with the data at the location pointed to by P.
	// returns a pointer to the location just following the newly created location.
	if(P == head) {
		push_front(data);
		return head->next;
	}
	
	if(P == tail) {
		push_back(data);
		return tail;
	}
	
	node<T> * temp( new node<T>(data) );
	temp->prev = P->prev;
	temp->next = P;
	P->prev->next = temp;
	P->prev = temp;
	length += 1;
	return P;
}


template<class T>
myList<T>::~myList() {
	while(size() > 0)
		pop_front();
	delete head;
}


template<class T>
T myList<T>::pop_front() {
	if(length == 0)
		throw(domain_error("ERROR in pop_front"));
	
	const T ans( head->data );
	head = head->next;
	delete head->prev;
	head->prev = NULL;
	length -= 1;
	return ans;
}


template<class T>
T myList<T>::pop_back() {
	if(length == 0)
		throw(domain_error("ERROR in pop_back"));
	
	const T ans( tail->prev->data );
	tail = tail->prev;
	delete tail->next;
	tail->next = NULL;
	length -= 1;
	return ans;
}


template<class T>
ostream & myList<T>::display_backward(ostream & out) const {
	if(length > 0) {
		node<T> *temp(tail);
		while(temp->prev != head) {
			out<< temp->prev->data <<"\t";
			temp = temp->prev;
		}
		out<< temp->prev->data;
	}
	return out;
};

template<class T>
ostream & myList<T>::display_forward(ostream & out) const {
	if(length > 0) {
		node<T> *temp(head);
		while(temp->next != tail) {
			out<< temp->data <<"\t";
			temp = temp->next;
		}
		out<< temp->data;
	}
	return out;
}


template<class T>
void myList<T>::push_front(const T & data) {
	head->prev = new node<T>(data);
	head->prev->next = head;
	head = head->prev;
	length += 1;
}


template<class T>
void myList<T>::push_back(const T & data) {
	tail->data = data;
	tail->next = new node<T>;
	tail->next->prev = tail;
	tail = tail->next;
	length += 1;
}


template<class T>
myList<T>::myList() {
	head = new node<T>;
	tail = head;
	length = 0;
}

/////////////////////////

#include "tests.h"

/////////////////////////


void worker(const int base, const int N) {
	double first_time;
	for(int val(base);val <= N*base; val += base) {
		myList<int> L;
		for(int i(val) ; i > 0 ; i-= 1)
			L.push_back(i);
		if(L.issorted())
			throw(domain_error("ERROR01 in worker"));
		
		const clock_t T1( clock() );
		L.mergesort();
		const clock_t T2( clock() );
		
		const double time_taken( double(T2 - T1)/CLOCKS_PER_SEC );
		if(val == base)
			first_time  = time_taken;
		
		const int mult(val / base);
		cout<< mult <<"\t"<< time_taken <<"\t"<< time_taken / first_time <<"\t"<< mult*(1.0 + log(mult) / log(base)) <<"\t"<< mult <<"\n";
		
		if(not L.issorted())
			throw(domain_error("ERROR02 in worker"));
	}
}


int main(int argc, char *argv[]) {
	if(argc == 3) {
		const int base( atoi(argv[1]) ), N( atoi(argv[2]) );
		worker(base, N);
	}
	return 0;
}











