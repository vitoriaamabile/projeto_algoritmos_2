#include <iostream>
#include <string>

#define N 5
int pos = 0;

using namespace std;

struct Usuario {
    string matricula;
    string nome;
    string tipo;
};

struct Livro {
    string codigo;
    int tituloDoLivro;
    int autor;
    int edicao;
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
    for(int i=0; i<pos; i++) {
    cout << "Informacoes do Usuario. ID: " << i+1 << endl;;
    cout << "Matricula: " << vet[i].matricula << endl;
    cout << "Nome: " << vet[i].nome << endl;
    cout << "Tipo: " << vet[i].tipo << endl;
    }
}


void cadastrar(Usuario *u){
    cout << "Digite o nome: ";
    cin.ignore();
    getline(cin, u->nome);
    cout << "Digite a matricula: ";
    getline(cin, u->matricula);
    cout << "Digite o tipo: ";
    cin >> u->tipo;
}

void cadastrar(Livro l){
    cout << "Digite o codigo do livro: ";
    cin >> l.codigo;
    cout << "Digite o titulo do livro: ";
    cin >> l.tituloDoLivro;
    cout << "Digite o autor do livro: ";
    cin >> l.autor;
    cout << "Digite a edicao do livro: ";
    cin >> l.edicao;
}

void adicionarUsuario(Usuario vet[], Usuario u) {
    if(pos < N)
        vet[pos++] = u;
    else
        cout << "Lista cheia. Usuario nao adicionado.\n";
}


int main() {
    Usuario esteUsuario;
    Usuario vetorUsuario[N];

    int opcao;

    mostrarMenu();
    cin >> opcao;
    while (opcao != 0) {
        switch(opcao) {
            case 1:
                cadastrar(&esteUsuario);
                adicionarUsuario(vetorUsuario, esteUsuario);
                break;
            case 3:
                mostrar(vetorUsuario);
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
