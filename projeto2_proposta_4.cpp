#include <iostream>
#include <string>

#define N 100
int posU = 0;
int posL = 0;
int posG = 0;

using namespace std;

struct Usuario {
string matricula;
string nome;
string tipo;
};

struct Genero {
string generoDoL;
};

struct Livro {
string codigo;
string tituloDoLivro;
string autor;
string edicao;
string matriculaUsuario;
string generoDoLGenero;
};

void cadastrarGenero(Genero vet[]) {
cout << "Digite o genero: ";
cin.ignore();
getline(cin, vet[posG].generoDoL);
posG++;
}

void mostrarGeneros(Genero vet[]) {
cout << "Generos Cadastrados.\n";
    for (int i = 0; i < posG; i++) {
        cout << "ID: " << i << " - " << vet[i].generoDoL << endl;
}
}

void mostrarMenu() {
cout << "---------- MENU DE OPCOES -----------\n";
cout << "1 - para cadastrar um usuario.\n";
cout << "2 - para cadastrar um livro.\n";
cout << "3 - para cadastrar um genero e relacionar a um livro.\n";
cout << "4 - para listar os usuarios.\n";
cout << "5 - para listar os livros.\n";
cout << "6 - para buscar livros por usuarios.\n";
cout << "7 - para relatorio geral.\n";
cout << "8 - para sair.\n";
cout << "Digite sua opcao: " << endl;
}

void mostrar(Usuario vet[]) {
for(int i = 0; i < posU; i++) {
cout << "Informacoes do Usuario. ID: " << i+1 << endl;
cout << "Matricula: " << vet[i].matricula << endl;
cout << "Nome: " << vet[i].nome << endl;
cout << "Tipo: " << vet[i].tipo << endl;
}
}

void mostrarLivros(Livro liv[], Usuario vet[]) {
for(int i = 0; i < posL; i++) {
cout << "Informacoes do Livro. ID: " << i+1 << endl;
cout << "Codigo: " << liv[i].codigo << endl;
cout << "Titulo: " << liv[i].tituloDoLivro << endl;
cout << "Autor: " << liv[i].autor << endl;
cout << "Edicao: " << liv[i].edicao << endl;
cout << "Genero: " << liv[i].generoDoLGenero << endl;

if (liv[i].matriculaUsuario == "-1") {
cout << "Emprestado para: Ninguem" << endl;
} else {
bool achou = false;
for (int j = 0; j < posU; j++) {
if (liv[i].matriculaUsuario == vet[j].matricula) {
cout << "Emprestado para: " << vet[j].nome << endl;
achou = true;
}
}
if (!achou)
cout << "Emprestado para: Usuario nao encontrado" << endl;
}
}
}

void buscarLivrosPorUsuario(Livro liv[], Usuario vet[]) {
string mat;
cout << "Digite a matricula do usuario: ";
cin >> mat;

cout << "Livros emprestados: " << endl;

bool encontrou = false;
for (int i = 0; i < posL; i++) {
if (liv[i].matriculaUsuario == mat) {
cout << liv[i].tituloDoLivro << endl;
encontrou = true;
}
}

if (!encontrou)
cout << "Nenhum livro encontrado para esta matricula." << endl;
}

void relatorioGeral(Livro liv[], Usuario vet[]) {
for (int i = 0; i < posU; i++) {
int cont = 0;
for (int j = 0; j < posL; j++) {
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

for (int i = 0; i < posU; i++) {
if (vet[i].matricula == u->matricula) {
cout << "Matricula ja existe. Usuario nao cadastrado.\n";
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

cout << "Digite a matricula do usuario que pegou o livro (ou -1): ";
cin >> l->matriculaUsuario;

l->generoDoLGenero = "Nao definido";

bool achou = false;
if (l->matriculaUsuario != "-1") {
for (int i = 0; i < posU; i++) {
if (vet[i].matricula == l->matriculaUsuario) {
achou = true;
{
    cout << "Usuario nao encontrado! Livro cadastrado como disponivel.\n"; l->matriculaUsuario = "-1";
}
}
posL++;
}
}
}
int main() {

Usuario esteUsuario;
Usuario vetorUsuario[N];
Livro vetorLivro[N];
Livro esteLivro;
Genero vetorGenero[N];

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
        cout << "A lista esta cheia. O usuario nao foi adicionado.\n";
}
break;

case 2:
    if (posL < N) {
    cadastrar(&esteLivro, vetorUsuario); vetorLivro[posL-1] = esteLivro;
}
else {
    cout << "Lista cheia. Livro nao adicionado.\n";
}
break;

case 3:
    if (posG < N) {
    cadastrarGenero(vetorGenero);
}
    else {
        cout << "Lista de generos cheia.\n";
}
    if (posL == 0){
        cout << "Nenhum livro cadastrado para relacionar ao genero.\n";
}
break;

    cout << "Escolha o ID do livro para adicionar ao genero:\n";
    for (int i = 0; i < posL; i++)
    cout << i << " - " << vetorLivro[i].tituloDoLivro << endl;

    int idLivro;
    cin >> idLivro;

    cout << "Escolha o ID do genero:\n";

    mostrarGeneros(vetorGenero);
    int idGenero;
    cin >> idGenero;

    vetorLivro[idLivro].generoDoLGenero = vetorGenero[idGenero].generoDoL;
    cout << "Genero adicionado ao livro com sucesso!\n";
break;

case 4:
    mostrar(vetorUsuario);
break;

case 5:
    mostrarLivros(vetorLivro, vetorUsuario);
    break;

case 6:
    buscarLivrosPorUsuario(vetorLivro, vetorUsuario);
    break;

case 7:
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
