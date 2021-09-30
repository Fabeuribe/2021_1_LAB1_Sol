#include "pch.h"
#include "stdlib.h"

using namespace System;
const int ROW_MAX = 60;
const int COLS_MAX = 60;
const int POKE_STOPS = 30;
const int POKE_NUM = 13;

void Leer_Dato_int(String^ aux_var, int *var);
void init_board(int board[ROW_MAX][COLS_MAX], int rows, int cols, int number_of_pokemons);

int main(array<System::String^>^ args) {

    String^ aux_var;// lo utilizo para la funcion de entrada de datos "Leer_Dato_int"
    int level_centinel=0;
    int player_level=0 ;
    int experience = 0;
    int pokeballs = 20; 
    //variables para el tablero
    int rows = 0;
    int cols = 0;
    int number_of_pokemons = 0;
    int radius = 0;
    int i;
    int j;

    Console::WriteLine("Bienvenido a POKE LPOO");  
   
    
    for (;level_centinel==0;) {

        Console::WriteLine("Ingrese nivel de juego (1-Principiante,2-Intermedio,3-Avanzado)");
        Leer_Dato_int (aux_var, &player_level);

        if (player_level == 1 || player_level == 2 || player_level == 3) {
            Console::WriteLine("Nivel de jugador: "+ player_level);
            Console::WriteLine("Puntos de experiencia : "+ experience);
            Console::WriteLine("Numero de Pokebolas : "+ pokeballs);
            level_centinel = 1;
        }
        else {
            Console::WriteLine("ERROR ingrese de nuevo el nivel de jugador");
        }

        //definiendo las  variables que dependen de la dificultad (player_level) del juego

        if (player_level == 1) {
            rows = 4;
            cols = 24;
            number_of_pokemons = 10;
            radius = 3;
        }
        else if (player_level == 2) {
            rows = 40;
            cols = 40;
            number_of_pokemons = 120;
            radius = 2;
        }
        else {
            rows = 60;
            cols = 60;
            number_of_pokemons = 120;
            radius = 1;
        }
        /*
        int** board;//board es una variable puntero a puntero entero
        board = (int**)malloc(sizeof(int*) * rows);
                      //malloc memory allocation "reservar memoria" 
                      // busca la direccion de memoria dentro de la memoria fisica
                      //para reotrnar ese espacio disponible
                      //que se indica dentro del parentesis de malloc
                      //eso me devuelve una direccion de memoria que asigno a "board"
                      //resumen(? board es un puntero a una direccion de memoria que permite apuntar a un entero

        for (i = 0; i < rows; i++) {
            *(board+i) =(int *)malloc(sizeof(int)*cols);
        }
        */
        int board2[ROW_MAX][COLS_MAX];
        init_board(board2,rows,cols,number_of_pokemons);
    }
    return 0;
}

void Leer_Dato_int (String^  aux_var, int *var) {
    aux_var = Console::ReadLine();
    *var = Int32::Parse(aux_var);
}

void init_board(int board[ROW_MAX][COLS_MAX], int rows, int cols, int number_of_pokemons) {
    int i , j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            board[i][j] = '+';//se llena el tablero con '+' 
        }
    }

    //llenando las pokeparadas
    int rand_num,row,col;
    int total_elements = rows * cols;
    for (i = 0; i < POKE_STOPS; ) {
        rand_num = rand() % total_elements;
        row = rand_num / cols;
        col = rand_num - row * cols;
        if (board[row][col] == '*') {
            board[row][col] = 'W';
            i++;
        }
    }

    //Colocamos al jugador
    int centinel_player=0;
    for (; centinel_player == 0;) {
        rand_num = rand() % total_elements;
        row = rand_num / cols;
        col = rand_num - row * cols;
        if (board[row][col] == '*') {
            board[row][col] = 'J';
            centinel_player = 1;
        }
        /*
        if (board[row][col] == 'J') {
            centinel_player = 1;
        }
        */
    }

    //colocamos a los pokemones
    char pokemons[13] = {'A','B','C','D','E','F','N','O','P','Q','R','S','T'};
    char pokemon;
    int centinel_pokemons = 0;
    for (; centinel_pokemons == 0;) {
        rand_num = rand() % total_elements;
        row = rand_num / cols;
        col = rand_num - row * cols;
        if (board[row][col] == '*') {
            board[row][col] = 'J';
            centinel_pokemons = 1;
        }
        /*
        if (board[row][col] == 'J') {
            centinel_player = 1;
        }
        */
    }

}

