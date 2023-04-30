#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define CELL_MAX (3 * 3 - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[3][3])
{
    int cell = 0;

    print_sep(3);
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(3);
    }
}

char row_winner(char board[3][3]){
    char winner;
    for (int row = 0; row < 3; ++row){
        bool aux=true;
        winner = board[row][0];
        for (int column = 0; column < 3; ++column) {
            if (board[row][column]!=winner){
                aux=false;
            }
        }
        if(aux==true){
            return winner;
        }
    }
    winner = '-';
    return winner;
}

char column_winner(char board[3][3]){
    char winner;
    for (int column = 0; column < 3; ++column){
        bool aux=true;
        winner = board[0][column];
        for (int row = 0; row < 3; ++row) {
            if (board[row][column]!=winner){
                aux=false;
            }
        }
        if(aux==true){
            return winner;
        }
    }
    winner = '-';
    return winner;
}

char diag_winner(char board[3][3]){
    char winner;
    bool aux=true;
    for (int cow = 0; cow < 3; ++cow){
        winner = board[0][0];
        if (board[cow][cow]!=winner){
            aux=false;
        }
    }
    if(aux==true){
            return winner;
    }
    winner = '-';
    return winner;
}

char diaginverse_winner(char board[3][3]){
    char winner;
    int i = 0;
    int j = 3-1;
    bool aux=true;
    for (int cow = 0; cow < 3; ++cow){
        winner = board[0][3-1];
        if (board[i][j]!=winner){
            aux=false;
        }
        i = i+1;
        j = j-1;
    }
    if(aux==true){
            return winner;
    }
    winner = '-';
    return winner;
}

char get_winner(char board[3][3])
{
    char winner='-';
    if (winner=='-'){
        winner = column_winner(board);
    }
    if (winner=='-'){
        winner = row_winner(board);
    }
    if (winner=='-'){
        winner = diag_winner(board);
    }
    if (winner=='-'){
        winner = diaginverse_winner(board);
    }

    return winner;
}

bool has_free_cell(char board[3][3])
{
    bool free_cell=false;
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            if (board[row][column]=='-'){
                free_cell=true;
            }
        }
    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[3][3] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / 3;
            int colum = cell % 3;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
