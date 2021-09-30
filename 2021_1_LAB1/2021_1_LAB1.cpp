#include "pch.h"
#include "stdlib.h"

using namespace System;
const int ROW_MAX = 60;
const int COLS_MAX = 60;
const int POKE_STOPS = 30;
const int POKE_NUM = 13;
const int POKEDEX_MAX = 12;

void Leer_Dato_int(String^ aux_var, int *var);
void init_board(int board[ROW_MAX][COLS_MAX], int rows, int cols, int number_of_pokemons);
void start_game(int board[ROW_MAX][COLS_MAX], int rows, int cols, int number_of_pokemons, int radius , int experience , int pokeballs);

int main(array<System::String^>^ args) {

    String^ aux_var;// lo utilizo para la funcion de entrada de datos "Leer_Dato_int"
    int init_centinel=0;
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
    //variables del jugador
    int player_x, player_y;

    Console::WriteLine("Bienvenido a POKE LPOO");  
   
    
    for (;init_centinel == 0;) {

        Console::WriteLine("Ingrese nivel de juego (1-Principiante,2-Intermedio,3-Avanzado)");
        Leer_Dato_int(aux_var, &player_level);

        if (player_level == 1 || player_level == 2 || player_level == 3) {
            Console::WriteLine("Nivel de jugador: " + player_level);
            Console::WriteLine("Puntos de experiencia : " + experience);
            Console::WriteLine("Numero de Pokebolas : " + pokeballs);
            init_centinel = 1;
        }
        else {
            Console::WriteLine("ERROR ingrese de nuevo el nivel de jugador");
        }
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

    init_board(board2,rows,cols,number_of_pokemons,&player_x,&player_y);

    start_game(board2,rows,cols,number_of_pokemons,radius,experience, pokeballs);

    
    return 0;
}

void Leer_Dato_int (String^  aux_var, int *var) {
    aux_var = Console::ReadLine();
    *var = Int32::Parse(aux_var);
}

void init_board(int board[ROW_MAX][COLS_MAX], int rows, int cols, int number_of_pokemons ,int *player_x,int *player_y ) {
    int i , j;

    //Se llena el tablero con '+'
    for (i = 0; i < rows; i++) {

        for (j = 0; j < cols; j++) {
            board[i][j] = '+';
        }
    }

    //llenando las pokeparadas
    int rand_num,row,col;
    int total_elements = rows * cols;
    for (i = 0; i < POKE_STOPS; ) {
        rand_num = rand() % total_elements;//SE GENERA EL NUMERO ALEATORIO
        row = rand_num / cols;//FILA ALEATORIA
        col = rand_num - row * cols;//COLUMNA ALEATORIA

        if (board[row][col] == '+') {
            board[row][col] = 'W';
            i++;
        }
    }

    //Colocamos al jugador
    int centinel_player=0;
    for (; centinel_player == 0;) {
        rand_num = rand() % total_elements;//SE GENERA EL NUMERO ALEATORIO
        row = rand_num / cols;//FILA ALAEATORIA
        col = rand_num - row * cols;//COLUMNA ALEATORIA

        if (board[row][col] == '+') {
            board[row][col] = 'J';
            *player_x = row;//posicion en x del jugador
            *player_y = col;//posicion en y del jugador
            centinel_player = 1;
        }
    }

    //colocamos a los pokemones
    char pokemons[POKE_NUM] = {'A','B','C','D','E','F','N','O','P','Q','R','S','T'};
    char pokemon;
    for (int pokemon_counter=0; pokemon_counter < number_of_pokemons;) {
        rand_num = rand() % total_elements;//SE GENERA EL NUMERO ALEATORIO
        row = rand_num / cols;//FILA ALEATORIA
        col = rand_num - row * cols;//COLUMNA ALEATORIA
        pokemon = pokemons[rand() % POKE_NUM];//"[rand() % POKE_NUM]" me da un numero aleatorio entre 0 y 13

        if (board[row][col] == '+') {
            board[row][col] = pokemon;
            pokemon_counter++;//aumenta en 1 el numero de pokemones 
        }
    }

}

void throw_pokeball(int board[ROW_MAX][COLS_MAX], int rows , int cols , int x,int y,int *experience,char pokedex[POKEDEX_MAX],int number_of_pokemons,int radius, int player_x,int player_y, int *pokeball) {
    int centinel_of_coordinates=0;

    int prob;
    char pokemon;
    bool is_found = false;
    if (in_in_visio_range(x, y)) {
        if (board[x][y] != 'W' && board[x][y] != 'J' && board[x][y] != '+') { 
            prob = rand() % 10;//probabilidad de atrapar un pokemon
            if (prob<5) {
                pokemon = board[x][y];
                *experience += 100;
                board[x][y] = '+';
                Console::WriteLine("El pokemon ha sido atrapado");
                for (int i = 0; i < POKEDEX_MAX;i++){
                    if (pokemon == pokedex[i]) {
                        is_found = true;
                    }
                }
                if (!is_found) {
                    Console::WriteLine("Pokemon nuevo registrado en la pokedex");
                    *experience += 100;
                    for (int i; i < POKEDEX_MAX;i++) {
                        if (pokedex[i]=='X') {
                            pokedex[i] = pokemon;
                            break;
                        }
                    }
                }
                (*pokeball)--;
            }
        }
    }

}
void start_game(int board[ROW_MAX][COLS_MAX], int rows, int cols, int number_of_pokemons, int radius,int player_level, int experience , int pokeballs , int player_x , int player_y ) {
    String^ command;
    //Para las coordenadas
    String^ aux_vector;
    int x, y,dir,i,j;
    char pokedex[POKEDEX_MAX];

    for (; player_level != 5;) {
        Console::WriteLine("Ingrese su comando: ");
        command = Console::ReadLine();

        if (command->Equals("L") || command->Equals("G") || command->Equals("M")) {

            //Comando para lanzar la pokebola
            if (command->Equals("L")) {
                Console::WriteLine("Ingrese la fila del pokemon : ");
                Leer_Dato_int(aux_vector,&x);
                x--;//se reduce el valor en 1 pues en la programacion se trabaja desde el 0 en adelante
                Console::WriteLine("Ingrese la columna del pokemon: ");
                Leer_Dato_int(aux_vector, &y);
                y--;//se reduce en 1 pues en la programacion se trabaja desde el 0 en adelante
                throw_pokeball(board,rows,cols,x,y,&experience,pokedex,number_of_pokemons,radius,player_x,player_y, &pokeballs);
            }

            //comando para girar la pokeparada
            if (command->Equals("G")) {
                Console::WriteLine("Ingrese la fila de la pokeparada:   ");
                x--;//se reduce el valor en 1 pues en la programacion se trabaja desde el 0 en adelante
                Console::WriteLine("Ingrese la columna de la pokeparada: ");
                Leer_Dato_int(aux_vector, &y);
                y--;//se reduce en 1 pues en la programacion se trabaja desde el 0 en adelante
                rotate_pokestop(x, y, experience, pokedex, number_of_pokemons, radius);
            }

            //comando para moverse
            if (command->Equals("M")) {
                Console::WriteLine("Ingrese la direccion;   ");
                Leer_Dato_int(aux_vector, &dir);
                move_player(dir, experience, pokedex, number_of_pokemons, radius);
            }       

            //aumento de nivel
            if (experience >= 500) {
                player_level++;
                experience -= 500;
            }

            Console::WriteLine("Nivel de jugador: " + player_level);
            Console::WriteLine("Puntos de experiencia : " + experience);
            Console::WriteLine("Numero de Pokebolas : " + pokeballs);
            
            for (i = 0;i<rows;i++) {
                for (j = 0; j < cols; j++){
                    if (board[i][j]=='J' || board[i][j]=='W' || board[i][j]=='+') {
                        Console::Write(board[i][j]);
                    }
                    else{
                        if (is_vision_range(i,j)) {
                            Console::WriteLine(board[i][j]);
                        }
                        else {
                            Console::Write('+');
                        }
                    }
                }
            }
        }
        else {
            Console::WriteLine("Ingrese comando valido");
        }
    }
    Console::WriteLine("Ha finalizado el juego.");
}