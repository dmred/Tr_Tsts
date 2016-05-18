#include "tree.h" 
template <class T>
Tree<T>::Root::Root(T x) : D(x), l(nullptr), r(nullptr) {}
template <class T>
Tree<T>::Tree(const std::initializer_list<T> & ilist) {

for (T element : ilist) {
Insert(element);
}
}; 

template <class T>
Tree<T>::~Tree() {
if(root){
root->destroy(root);
}
} 
template <class T>
void Tree<T>::Root::destroy(Root* root) {

if (root->l)
{
destroy(root->l);
}
if (root->r != 0)
{
destroy(root->r);
}
delete root;
root=nullptr;
}

template <class T>
T Tree<T>::Root::find_min(Root* tree) {
if (tree->l) return find_min(tree->l);
else return tree->D;
}

template <class T>
void Tree<T>::Root::del(T x) {
if ((x == D) && (!l) && (!r)) {Root* root= nullptr; throw Deleted(); }
if ((x == D) && (!l)) {
D = r->D;
if (r->l) l = r->l; else { delete l; l = nullptr; }
if (r->r) r = r->r; else { delete r; r = nullptr; }
return;
}
if ((x == D) && (!r)) {
D = l->D;
if (l->r) r = l->r; else { delete r; r = nullptr; }
if (l->l) l = l->l; else { delete l; l = nullptr; }
return;
}
if (x < D) {
if ((l->D == x) && (!(l->r)) && (!(l->l))) { delete l; l = nullptr; return; }
if ((l->D == x) && (l->l) && (l->r)) { l->D = find_min(l->r); if (l->r->D != find_min(l->r)) l->r->del(find_min(l->r)); else { delete l->r; l->r = nullptr; } return; }
else; l->del(x);
return;
}
if (x > D) {
if ((r->D == x) && (!(r->r)) && (!(r->l))) { delete r; r = nullptr; return; }
if ((r->D == x) && (r->l) && (r->r)) { r->D = find_min(r->r); if (r->r->D != find_min(r->r)) r->r->del(find_min(r->r)); else { delete r->r; r->r = nullptr; } return; }
else r->del(x);
return;
}
if ((x == D) && (l) && (r)) { D = find_min(r); if (r->D != find_min(r)) r->del(find_min(r)); else { delete r; r = nullptr; } return; }
}

template <class T>
void Tree<T>::Root::Insert(T x) {
if (x < D) {
if (l != nullptr) l->Insert(x);
if (l == nullptr) l = new Root(x);
}
if (x>D) {
if (r != nullptr) r->Insert(x);
if (r == nullptr) r = new Root(x);
}
}
template <class T>
bool Tree<T>::Root::Search(T x) {
if (x == D) { return true; }
if (x > D) if (r != nullptr) return(r->Search(x));
if (x < D) if (l != nullptr) return(l->Search(x));
return false;
}
template <class T>
bool Tree<T>::Root::print_console() {
if (this != nullptr) {
if (l != nullptr) l->print_console();
cout << D << " ";
if (r != nullptr) r->print_console();
return true;
}
else return false;
}
template <class T>
bool Tree<T>::Root::print_file(ofstream &fout) {
if (this != nullptr) {
if (fout.is_open()) {
if (l != nullptr) l->print_file(fout);
fout << D << " ";
if (r != nullptr) r->print_file(fout);
}
return true;
}
return false;
}
template <class T>
bool Tree<T>::Insert(T x) {
if (root != nullptr) if (Search(x)) throw Exist();
if (root == nullptr) { root = new Root(x); return true; }
else { root->Insert(x); return true; }
return false;
}
template <class T>
bool Tree<T>::Search(T x) {
if (root == nullptr) throw Empty();
return(root->Search(x));
}
template <class T>
bool Tree<T>::del(T x) {
if (root == nullptr) throw Empty();
if (!this->Search(x)) throw Exist();
try { root->del(x); }
catch (Deleted &) { throw Deleted(); }
return true;
}

template <class T>
ostream & operator <<(ostream & out, Tree<T> & tree) {
if (tree.root->print_console()) return out;
else throw Empty();
}
template <class T>
ifstream& operator >>(ifstream & fin, Tree<T> & tree) {
if (!fin.is_open()) throw File_Not_Open();
T x;
while (!fin.eof()){
if (fin>>x) tree.Insert(x);
else break;
}
return fin;
}
template <class T>
ofstream & operator <<(ofstream & fout, Tree<T> & tree) {
if (tree.root->print_file(fout)) return fout;else throw Empty();}

template <class T>
istream & operator >> (istream & in, Tree<T> & tree) {
size_t size;
if (in >> size) {
for (int i= 0; i < size; ++i) {
T temp;
if (in >> temp) {
tree.Insert(temp);
}
else {
throw
Error_stream();
}
}
}
else {
throw Error_stream();
}

return in;

}
