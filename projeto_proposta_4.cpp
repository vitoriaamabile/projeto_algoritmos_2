#include <iostream>
#include <string>

#define N 100
int posU = 0;
int posL = 0;


using namespace std;

struct Usuario {
string matricula;
string nome;
string tipo;
};

struct Livro {
string codigo;
string tituloDoLivro;
string autor;
string edicao;
string matriculaUsuario;
string generoDoLGenero;
};


void mostrarMenu() {
cout << "---------- MENU DE OPCOES -----------\n";
cout << "1 - para cadastrar um usuario.\n";
cout << "2 - para cadastrar um livro.\n";
cout << "3 - para listar os usuarios.\n";
cout << "4 - para listar os livros.\n";
cout << "5 - para buscar livros por usuarios.\n";
cout << "6 - para relatorio geral.\n";
cout << "7 - para sair.\n";
cout << "Digite sua opcao: " << endl;
}

void mostrar(Usuario vet[]) {
for(int i=0; i<posU; i++) {
cout << "Informacoes do Usuario. ID: " << i+1 << endl;
cout << "Matricula: " << vet[i].matricula << endl;
cout << "Nome: " << vet[i].nome << endl;
cout << "Tipo: " << vet[i].tipo << endl;
}
}

void mostrarLivros(Livro liv[], Usuario vet[]) {
for(int i=0; i<posL; i++) {
cout << "Informacoes do Livro. ID: " << i+1 << endl;
cout << "Codigo: " << liv[i].codigo << endl;
cout << "Titulo: " << liv[i].tituloDoLivro << endl;
cout << "Autor: " << liv[i].autor << endl;
cout << "Edicao: " << liv[i].edicao << endl;

if (liv[i].matriculaUsuario == "-1") {
cout << "Emprestado para: ninguem" << endl;
}
else {
bool achou = false;
for (int j=0; j<posU; j++) {
if (liv[i].matriculaUsuario == vet[j].matricula) {
cout << "Emprestado para: " << vet[j].nome << endl;
achou = true;
}
}
if (!achou)
cout << "Emprestado para: usuario nao encontrado" << endl;
}
}
}

void buscarLivrosPorUsuario(Livro liv[], Usuario vet[]) {
string mat;
cout << "Digite a matricula do usuario: ";
cin >> mat;

cout << "Livros emprestados: " << endl;

bool encontrou = false;
for (int i=0; i<posL; i++) {
if (liv[i].matriculaUsuario == mat) {
cout << liv[i].tituloDoLivro << endl;
encontrou = true;
}
}

if (!encontrou)
cout << "Nenhum livro foi encontrado para esta matricula." << endl;
}

void relatorioGeral(Livro liv[], Usuario vet[]) {
for (int i=0; i<posU; i++) {
int cont = 0;
for (int j=0; j<posL; j++) {
int cont = 0;
if (liv[j].matriculaUsuario == vet[i].matricula) {
cont++;
}
}
cout << vet[i].nome << " possui " << cont << " livro(s) emprestado(s)." << endl;
}
}

void cadastrar(Usuario *u, Usuario vet[]) {
cout << "Digite o nome: ";
cin.ignore();
getline(cin, u->nome);

cout << "Digite a matricula: ";
getline(cin, u->matricula);

for (int i=0; i<posU; i++) {
if (vet[i].matricula == u->matricula) {
cout << "A matricula ja existe o usuario nao foi cadastrado!.\n";
return;
}
}

cout << "Digite o tipo: ";
cin >> u->tipo;

vet[posU++] = *u;
}

void cadastrar(Livro *l, Usuario vet[]) {
cout << "Digite o codigo do livro: ";
cin.ignore();
getline(cin, l->codigo);

cout << "Digite o titulo do livro: ";
getline(cin, l->tituloDoLivro);

cout << "Digite o autor do livro: ";
getline(cin, l->autor);

cout << "Digite a edicao do livro: ";
getline(cin, l->edicao);

cout << "Digite a matricula do usuario que pegou o livro (caso não esteja com nenhum usuario digite -1): ";
cin >> l->matriculaUsuario;


bool achou = false;

if (l->matriculaUsuario != "-1") {
for (int i=0; i<posU; i++) {
if (vet[i].matricula == l->matriculaUsuario) {
achou = true;
break;
}
}
if (!achou) {
cout << "Usuario nao encontrado! Livro cadastrado como disponivel.\n";
l->matriculaUsuario = "-1";
}
}

posL++;
}

int main() {
Usuario esteUsuario;
Usuario vetorUsuario[N];
Livro vetorLivro[N];
Livro esteLivro;

int opcao;

mostrarMenu();
cin >> opcao;
while (opcao != 8) {
switch(opcao) {

case 1:
if (posU < N) {
cadastrar(&esteUsuario, vetorUsuario);
}
else {
cout << "A lista esta cheia, o usuario nao foi adicionado.\n";
}
break;

case 2:
if (posL < N) {
cadastrar(&esteLivro, vetorUsuario);
vetorLivro[posL-1] = esteLivro;
}
else {
cout << "A lista esta cheia, o livro nao foi adicionado.\n";
}
break;

case 3:
mostrar(vetorUsuario);
break;

case 4:
mostrarLivros(vetorLivro, vetorUsuario);
break;

case 5:
buscarLivrosPorUsuario(vetorLivro, vetorUsuario);
break;

case 6:
relatorioGeral(vetorLivro, vetorUsuario);
break;

default:
cout << "Opcao invalida. Digite novamente...\n";
break;
}

mostrarMenu();
cin >> opcao;
}

return 0;
}
