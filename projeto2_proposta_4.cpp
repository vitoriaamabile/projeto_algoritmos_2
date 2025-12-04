#include <iostream>
#include <fstream>
#include <cstring>

#define N 100
int posU = 0;
int posL = 0;
int posG = 0;

using namespace std;

struct Usuario {
    char matricula[100];
    char nome[100];
    char tipo[100];
};

struct Genero {
    char generoDoL[100];
};

struct Livro {
    char codigo[100];
    char tituloDoLivro[100];
    char autor[100];
    char edicao[100];
    char matriculaUsuario[100];
    char generoDoLGenero[100];
};

void cadastrarGenero(Genero vet[]) {
    cout << "Digite o genero: ";
    cin.ignore();
    cin.getline(vet[posG].generoDoL, 100);
    posG++;
}

void cadastrar(Usuario *u, Usuario vet[]) {
    cout << "Digite o nome: ";
    cin.ignore();
    cin.getline(u->nome, 100);

    cout << "Digite a matricula: ";
    cin.getline(u->matricula, 100);

    for (int i = 0; i < posU; i++) {
        if (strcmp(vet[i].matricula, u->matricula) == 0) {
            cout << "Matricula ja existe. Usuario nao cadastrado.\n";
            return;
        }
    }

    cout << "Digite o tipo: ";
    cin.getline(u->tipo, 100);

    vet[posU++] = *u;
}

void cadastrar(Livro *l, Usuario vet[]) {
    cout << "Digite o codigo do livro: ";
    cin.ignore();
    cin.getline(l->codigo, 100);

    cout << "Digite o titulo do livro: ";
    cin.getline(l->tituloDoLivro, 100);

    cout << "Digite o autor do livro: ";
    cin.getline(l->autor, 100);

    cout << "Digite a edicao do livro: ";
    cin.getline(l->edicao, 100);

    cout << "Digite a matricula do usuario que pegou o livro (ou -1): ";
    cin.getline(l->matriculaUsuario, 100);

    strcpy(l->generoDoLGenero, "Nao definido");

    if (strcmp(l->matriculaUsuario, "-1") != 0) {
        bool achou = false;
        for (int i = 0; i < posU; i++) {
            if (strcmp(vet[i].matricula, l->matriculaUsuario) == 0) {
                achou = true;
                break;
            }
        }
        if (!achou) {
            cout << "Usuario nao encontrado! Livro cadastrado como disponivel.\n";
            strcpy(l->matriculaUsuario, "-1");
        }
    }
    posL++;
}

void mostrar(Usuario vet[]) {
    for(int i = 0; i < posU; i++) {
        cout << "Informacoes do Usuario. ID: " << i+1 << endl;
        cout << "Matricula: " << vet[i].matricula << endl;
        cout << "Nome: " << vet[i].nome << endl;
        cout << "Tipo: " << vet[i].tipo << endl;
    }
}

void mostrarGeneros(Genero vet[]) {
    cout << "Generos Cadastrados:\n";
    for(int i = 0; i < posG; i++) {
        cout << "ID: " << i << " - " << vet[i].generoDoL << endl;
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

        if (strcmp(liv[i].matriculaUsuario, "-1") == 0)
            cout << "Emprestado para: Ninguem" << endl;
        else {
            bool achou = false;
            for(int j = 0; j < posU; j++) {
                if(strcmp(liv[i].matriculaUsuario, vet[j].matricula) == 0) {
                    cout << "Emprestado para: " << vet[j].nome << endl;
                    achou = true;
                    break;
                }
            }
            if(!achou)
                cout << "Emprestado para: Usuario nao encontrado" << endl;
        }
    }
}

void buscarLivrosPorUsuario(Livro liv[], Usuario vet[]) {
    char mat[100];
    cout << "Digite a matricula do usuario: ";
    cin.ignore();
    cin.getline(mat, 100);

    cout << "Livros emprestados: " << endl;
    bool encontrou = false;
    for(int i = 0; i < posL; i++) {
        if(strcmp(liv[i].matriculaUsuario, mat) == 0) {
            cout << liv[i].tituloDoLivro << endl;
            encontrou = true;
        }
    }
    if(!encontrou)
        cout << "Nenhum livro encontrado para esta matricula." << endl;
}

void relatorioGeral(Livro liv[], Usuario vet[]) {
    for(int i = 0; i < posU; i++) {
        int cont = 0;
        for(int j = 0; j < posL; j++) {
            if(strcmp(liv[j].matriculaUsuario, vet[i].matricula) == 0)
                cont++;
        }
        cout << vet[i].nome << " possui " << cont << " livro(s) emprestado(s)." << endl;
    }
}

void salvar(Usuario vetU[], Livro vetL[], Genero vetG[]) {
    ofstream arquivo("usuario.bin", ios::out | ios::binary);
    if(arquivo.is_open()) {
        arquivo.write((char*)&posU, sizeof(posU));
        arquivo.write((char*)vetU, sizeof(Usuario) * N);
        arquivo.write((char*)vetL, sizeof(Livro) * N);
        arquivo.write((char*)&posL, sizeof(posL));
        arquivo.write((char*)vetG, sizeof(Genero) * N);
        arquivo.write((char*)&posG, sizeof(posG));
        arquivo.close();
        cout << "Informacoes salvas com sucesso!\n";
    } else {
        cout << "Falha ao salvar informacoes.\n";
    }
}

void carregar(Usuario vetU[], Livro vetL[], Genero vetG[]) {
    ifstream arquivo("usuario.bin", ios::in | ios::binary);
    if(arquivo.is_open()) {
        arquivo.read((char*)&posU, sizeof(posU));
        arquivo.read((char*)vetU, sizeof(Usuario) * N);
        arquivo.read((char*)vetL, sizeof(Livro) * N);
        arquivo.read((char*)&posL, sizeof(posL));
        arquivo.read((char*)vetG, sizeof(Genero) * N);
        arquivo.read((char*)&posG, sizeof(posG));
        arquivo.close();
        cout << "Informacoes carregadas com sucesso!\n";
    } else {
        cout << "Falha ao carregar informacoes.\n";
    }
}

void mostrarMenu() {
    cout << "---------- MENU DE OPCOES -----------\n";
    cout << "1 - Cadastrar usuario\n";
    cout << "2 - Cadastrar livro\n";
    cout << "3 - Cadastrar genero\n";
    cout << "4 - Listar usuarios\n";
    cout << "5 - Listar livros\n";
    cout << "6 - Listar generos\n";
    cout << "7 - Buscar livros por usuario\n";
    cout << "8 - Relatorio geral\n";
    cout << "9 - Salvar informacoes\n";
    cout << "10 - Carregar informacoes\n";
    cout << "11 - Sair\n";
    cout << "Digite sua opcao: ";
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
    while (opcao != 11) {
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
            break;

        case 3:
            if (posG < N) {
                cadastrarGenero(vetorGenero);
            }
            if (posL == 0){
                cout << "Nenhum livro cadastrado para relacionar ao genero.\n";
            }
            break;

        case 4:
            mostrar(vetorUsuario);
            break;

        case 5:
            mostrarLivros(vetorLivro, vetorUsuario);
            break;

        case 6:
            mostrarGeneros(vetorGenero);
            break;

        case 7:
            buscarLivrosPorUsuario(vetorLivro, vetorUsuario);
            break;

        case 8:
            relatorioGeral(vetorLivro, vetorUsuario);
            break;
        case 9:
            salvar(vetorUsuario,vetorLivro,vetorGenero);

            break;
        case 10:
            carregar(vetorUsuario, vetorLivro, vetorGenero);
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
