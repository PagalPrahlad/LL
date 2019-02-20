#ifndef GAURD_tests
#define GAURD_tests



void tester01() {
	// testing display functions, push_back and push_front functions, pop_back and pop_front functions.
	myList<int> L;
	for(int i(0);i<10;++i)
		L.push_back(i);
	L.display_forward (cout) <<":\n";
	L.display_backward(cout) <<":\n";
	cout<< L.size() <<"\n";
	while(L.size() > 0) {
		L.display_forward(cout) <<":\t"<< L.pop_front() <<"\n";
	}
}

void tester02() {
	// testing destructor
	while(true) {
		myList<int> L;
		for(int i(0);i<10;++i)
			L.push_back(i);
	}
}


void tester03() {
	// testing insert
	myList<int> L;
	for(int i(0);i<10;++i)
		L.push_back(i);
	cout<< "original list:\n";
	L.display_forward(cout)<<"\n";
	cout<< "L.size() = " << L.size() <<"\n";
	node<int> * P(L.head);
	const int shift(L.size());
	cout<< "\nshift = " << shift <<"\n";
	for(int i(0);i<shift;++i, P = P->next);
	P = L.insert(P, 100);
	P = L.insert(P, 110);
	P = L.insert(P, 120);
	cout<< "\nlist after insertion:\n";
	L.display_forward(cout)<<"\n";
	cout<< "L.size() = " << L.size() <<"\n";
	cout<< "P->data = " << P->data <<"\n";
	cout<< "(P == L.tail) = " <<(P == L.tail) <<"\n";
}

void tester04() {
	// testing del
	myList<int> L;
	for(int i(0);i<10;++i)
		L.push_back(i);
	cout<< "original list:\n";
	L.display_forward(cout)<<"\n";
	cout<< "L.size() = " << L.size() <<"\n";
	node<int> * P(L.head);
	const int shift(6);
	cout<< "\nshift = " << shift <<"\n";
	for(int i(0);i<shift;++i, P = P->next);
	P = L.del(P);
	cout<< "\nlist after removal:\n";
	L.display_forward(cout)<<"\n";
	cout<< "L.size() = " << L.size() <<"\n";
	cout<< "P->data = " << P->data <<"\n";
	cout<< "(P == L.tail) = " <<(P == L.tail) <<"\n";
}

void tester05() {
	// testing issorted
	myList<int> L;
	for(int i(0);i<10;++i)
		L.push_back(i);
	L.push_back(-100);
	cout<< "original list:\n";
	L.display_forward(cout)<<"\n";
	cout<< "L.size() = " << L.size() <<"\n";
	
	cout<< "L.issorted() = " << L.issorted() <<"\n";
}

void tester06() {
	// testing mergesort_aux
	myList<int> L;
	srand(clock());
	for(int i(0);i<6;++i) {
		const int val(rand()*1.0/RAND_MAX*1000);
		L.push_back(val);
	}
	cout<< "original list:\n";
	L.display_forward(cout)<<":\n";
	cout<< "L.issorted() = " << L.issorted() <<"\n";
	cout<< "L.size() = " << L.size() <<"\n\n";
	
	L.mergesort_aux(L.head, L.tail);
	
	cout<< "sorted list:\n";
	L.display_forward(cout)<<":\n";
	cout<< "L.issorted() = " << L.issorted() <<"\n";
	cout<< "L.size() = " << L.size() <<"\n\n";
}



#endif


























