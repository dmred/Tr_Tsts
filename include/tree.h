#include <iostream>
#include <fstream>
using namespace std;


template <class T>
	class Tree;

template <class T>
ostream & operator<<(ostream & out,Tree<T> &tree);

template <class T>
ofstream & operator<<(ofstream & fout,Tree<T> &tree);

template <class T>
ifstream & operator >> (ifstream & fin,Tree<T> &tree);


	// Исключения 
class Exceptions {
	char* err;
public:
	Exceptions(char* _err);
	char* what();
};
class File_Not_Open : public Exceptions{
public:
	File_Not_Open();
};
class Empty : public Exceptions{
public:
	Empty();
};
class Exist : public Exceptions{
public:
	Exist();
};
Exceptions::Exceptions(char* _err) : err(_err){}
char* Exceptions::what() { return err; }
Exist::Exist() : Exceptions("ERROR: It's already exist!") {}
File_Not_Open::File_Not_Open() : Exceptions("ERROR: file is not open!") {}
Empty::Empty() : Exceptions("ERROR: The Binary Tree is empty!") {}



template <class T>
class Tree{
public:
	Tree();
	bool Insert(T x);// Добавление элемента 
	bool Search(T x);// Поиск элемента 
	friend ostream & operator<< <>(ostream &out, Tree<T> &tree);
	friend ofstream & operator<< <>(ofstream &fout, Tree<T> &tree);		
	friend ifstream & operator>> <>(ifstream &fin, Tree<T> &tree);		
private:
	class Root;
	Root* root; //корень дерева
};

template <class T>
class Tree<T>::Root{
public:
	Root(T x);
	void Insert(T x);
	bool Search(T x);
	bool print_console();
	bool print_file(ofstream &fout);
	void del(T el);
	T find_min (Root* el);
private:
	T K;
	Root *l;
	Root *r;
};
