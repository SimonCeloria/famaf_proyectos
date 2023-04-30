#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define N (5)
#define CELL_MAX (N * N - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[N][N])
{
    int cell = 0;

    print_sep(N);
    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(N);
    }
}

char row_winner(char board[N][N]){
    char winner;
    for (int row = 0; row < N; ++row){
        bool aux=true;
        winner = board[row][0];
        for (int column = 0; column < N; ++column) {
            if (board[row][column]!=winner){
                aux=false;
            }
        }
        if(aux==true && winner!='-'){
            return winner;
        }
    }
    winner = '-';
    return winner;
}

char column_winner(char board[N][N]){
    char winner;
    for (int column = 0; column < N; ++column){
        bool aux=true;
        winner = board[0][column];
        for (int row = 0; row < N; ++row) {
            if (board[row][column]!=winner){
                aux=false;
            }
        }
        if(aux==true && winner!='-'){
            return winner;
        }
    }
    winner = '-';
    return winner;
}

char diag_winner(char board[N][N]){
    char winner;
    bool aux=true;
    for (int cow = 0; cow < N; ++cow){
        winner = board[0][0];
        if (board[cow][cow]!=winner){
            aux=false;
        }
    }
    if(aux==true && winner!='-'){
            return winner;
    }
    winner = '-';
    return winner;
}

char diaginverse_winner(char board[N][N]){
    char winner;
    int i = 0;
    int j = N-1;
    bool aux=true;
    for (int cow = 0; cow < N; ++cow){
        winner = board[0][N-1];
        if (board[i][j]!=winner){
            aux=false;
        }
        i = i+1;
        j = j-1;
    }
    if(aux==true && winner!='-'){
            return winner;
    }
    winner = '-';
    return winner;
}

char get_winner(char board[N][N])
{
    char winner='-';
    if (winner=='-'){
        winner = diag_winner(board);
    }
    if (winner=='-'){
        winner = diaginverse_winner(board);
    }
    if (winner=='-'){
        winner = column_winner(board);
    }
    if (winner=='-'){
        winner = row_winner(board);
    }

    return winner;
}

bool has_free_cell(char board[N][N])
{
    bool free_cell=false;
    for (int row = 0; row < N; ++row) {
        for (int column = 0; column < N; ++column) {
            if (board[row][column]=='-'){
                free_cell=true;
            }
        }
    }
    return free_cell;
}

void fill_with_dash(char board[N][N]){
    for (int i=0; i<N; ++i){
        for (int j=0; j<N; ++j){
            board[i][j] = '-';
        }
    }
}

int main(void)
{
    printf("TicTacToe\n");

    char board[N][N];

    fill_with_dash(board);

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posicion (numero del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un numero desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / N;
            int colum = cell % N;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda invalida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Gano %c\n", winner);
    }
    return 0;
}
