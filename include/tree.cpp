#include "tree.h"  
template <class T>
Tree<T>::Root::Root(T x) : K(x), l(nullptr), r(nullptr){}
template <class T>
void Tree<T>::Root::Insert(T x){
	if (x < K){
		if (l != nullptr) l->Insert(x);
		if (l == nullptr) l = new Root(x);
	}
	if (x>K){
		if (r != nullptr) r->Insert(x);
		if (r == nullptr) r = new Root(x);
	}
}
template <class T>
bool Tree<T>::Root::Search(T x){
	if (x == K) { return true; }
	if (x > K) if (r != nullptr) return(r->Search(x));
	if (x < K) if (l != nullptr) return(l->Search(x));
	return false;
}
template <class T>
bool Tree<T>::Root::print_console(){
	if (this != nullptr){
		if (l != nullptr) l->print_console();
		cout << K << " ";
		if (r != nullptr) r->print_console();
		return true;
	}
	else return false;
}
template <class T>
bool Tree<T>::Root::print_file(ofstream &fout){
	if (this != nullptr){
		if (fout.is_open()){
			if (l != nullptr) l->print_file(fout);
			fout << K << " ";
			if (r != nullptr) r->print_file(fout);
		}
		return true;
	}
	return false;
}

template <class T>
Tree<T>::Tree() : root(nullptr){}
template <class T>
bool Tree<T>::Insert(T x){
	if (root != nullptr) if (Search(x)) throw Exist();
	if (root == nullptr) { root = new Root(x); return true; }
	else { root->Insert(x); return true; }
	return false;
}
template <class T>
bool Tree<T>::Search(T x){
	if (root == nullptr) throw Empty();
	return(root->Search(x));
}


template <class T>
ostream & operator <<(ostream & out, Tree<T> & tree) {
	if (tree.root->print_console()) return out;
	else throw Empty();
}
template <class T>
ifstream & operator >>(ifstream & fin, Tree<T> & tree) {
	if (!fin.is_open()) throw File_Not_Open();
	T x;
	while (!fin.eof()){
		fin >> x;
		if(x!=-1)tree.Insert(x);
		else break;
	}
	return fin;
}
template <class T>
ofstream & operator <<(ofstream & fout, Tree<T> & tree) {
	if (tree.root->print_file(fout)) return fout;
	else throw Empty();
}
