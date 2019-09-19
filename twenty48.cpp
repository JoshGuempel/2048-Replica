//Create the 2048 game with i/o and arrays.
//Josh Guempel
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int GRID_SIZE = 4;
const int MAX_MOVES = GRID_SIZE - 1;

//Prints 4x4 array of ints
void print_g(int a[GRID_SIZE][GRID_SIZE]);

//Initialize 4x4 grid
void init_g(int a[GRID_SIZE][GRID_SIZE]);

//Various movements. May or may not be neccesary, wait and see.
void move_left(int a[GRID_SIZE][GRID_SIZE]);
void move_up(int a[GRID_SIZE][GRID_SIZE]);
void move_right(int a[GRID_SIZE][GRID_SIZE]);
void move_down(int a[GRID_SIZE][GRID_SIZE]);

//Subroutine of left, up, right, down (shift)
void shift_left(int a[GRID_SIZE][GRID_SIZE], int i);
void shift_up(int a[GRID_SIZE][GRID_SIZE], int i);
void shift_right(int a[GRID_SIZE][GRID_SIZE], int i);
void shift_down(int a[GRID_SIZE][GRID_SIZE], int i);

void random_spawn(int a[GRID_SIZE][GRID_SIZE]);

bool grid_filled(int a[GRID_SIZE][GRID_SIZE]);


int main() {
    srand(time(NULL));
    string move;
    int grid[GRID_SIZE][GRID_SIZE];
    bool lost = false;

    //Initialize the grid
    for(int row = 0; row < GRID_SIZE; row++) {
        for(int column = 0; column < GRID_SIZE; column++) {
            grid[row][column] = 0;
        }
    }
    random_spawn(grid);
    print_g(grid);

    while(!lost) {
        cin >> move;
        for(int i = 0; i < 10; i++)
            cout << "\n\n\n\n";
        if(move == "a") {
            move_left(grid);
            print_g(grid);
        } else if(move == "w") {
            move_up(grid);
            print_g(grid);
        } else if(move == "d") {
            move_right(grid);
            print_g(grid);
        } else if(move == "s") {
            move_down(grid);
            print_g(grid);
        }
        if(grid_filled(grid)) {
            lost = true;
            cout << "YOU LOSE, HA" << endl;
        }
        random_spawn(grid);
        
    }
    return 0;
}

void print_g(int a[GRID_SIZE][GRID_SIZE]) {
    for(int row = 0; row < GRID_SIZE; row++) {
        for(int column = 0; column < GRID_SIZE; column++) {
            cout<<a[row][column]<<" ";
        }
        cout<<endl;
    }
}

void init_g(int a[GRID_SIZE][GRID_SIZE]) {
    for(int row = 0; row < GRID_SIZE; row++) {
        for(int column = 0; column < GRID_SIZE; column++) {
            cin>>a[row][column];
        }
    }
}

void move_left(int a[GRID_SIZE][GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++) {
        //Shift left
        shift_left(a, i);

        //Merge, walking left to right
        for(int j = 0; j < GRID_SIZE - 1; j++) {
            if(a[i][j]==a[i][j+1]) {
                a[i][j] += a[i][j+1];
                a[i][j+1] = 0;
            }
        }

        //shift left again
        shift_left(a, i);
    }
}

void move_up(int a[GRID_SIZE][GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++) {
        //Shift up
        shift_up(a, i);

        //Merge, walking top to bottom
        for(int j = 0; j < GRID_SIZE - 1; j++) {
            if(a[j][i]==a[j+1][i]) {
                a[j][i] += a[j+1][i];
                a[j+1][i] = 0;
            }
        }

        //shift up again
        shift_up(a, i);
    }
}

void move_right(int a[GRID_SIZE][GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++) {
        //Shift right
        shift_right(a, i);

        //Merge, walking right to left
        for(int j = GRID_SIZE - 1; j >= 1; j--) {
            if(a[i][j]==a[i][j-1]) {
                a[i][j] += a[i][j-1];
                a[i][j-1] = 0;
            }
        }

        //Shift right again
        shift_right(a, i);
    }
}

void move_down(int a[GRID_SIZE][GRID_SIZE]) {
    for(int i = 0; i < GRID_SIZE; i++) {
        //Shift down
        shift_down(a, i);

        //Merge, walking bottom to top
        for(int j = GRID_SIZE - 1; j >= 1; j--) {
            if(a[j][i]==a[j-1][i]) {
                a[j][i] += a[j-1][i];
                a[j-1][i] = 0;
            }
        }

        //Shift down again
        shift_down(a, i);
    }
}

//Shift array left
void shift_left(int a[GRID_SIZE][GRID_SIZE], int i) {
    for(int m = 0; m < MAX_MOVES; m++) {
        for(int l = 0; l < GRID_SIZE-1; l++) {
            if(a[i][l]==0) {
                a[i][l] += a[i][l+1];
                a[i][l+1] = 0;
            }
        }
    }
}

//shift array up
void shift_up(int a[GRID_SIZE][GRID_SIZE], int i) {
    for(int m = 0; m < MAX_MOVES; m++) {
        for(int l = 0; l < GRID_SIZE-1; l++) {
            if(a[l][i]==0) {
                a[l][i] += a[l+1][i];
                a[l+1][i] = 0;
            }
        }
    }
}

//Shift array right
void shift_right(int a[GRID_SIZE][GRID_SIZE], int i) {
    for(int m = 0; m < MAX_MOVES; m++) {
        for(int l = 0; l < GRID_SIZE-1; l++) {
            if(a[i][l+1]==0) {
                a[i][l+1] += a[i][l];
                a[i][l] = 0;
            }
        }
    }
}

//Shift array down
void shift_down(int a[GRID_SIZE][GRID_SIZE], int i) {
    for(int m = 0; m < MAX_MOVES; m++) {
        for(int l = 0; l < GRID_SIZE-1; l++) {
            if(a[l+1][i]==0) {
                a[l+1][i] += a[l][i];
                a[l][i] = 0;
            }
        }
    }
}


void random_spawn(int a[GRID_SIZE][GRID_SIZE]) {
    for(int row = 0; row < GRID_SIZE; row++) {
        for(int column = 0; column < GRID_SIZE; column++) {
            if(a[row][column] == 0 && !(rand()%8)) {
                a[row][column] = 2;
            }
        }
    }
}

bool grid_filled(int a[GRID_SIZE][GRID_SIZE]) {
    for(int row = 0; row < GRID_SIZE; row++) {
        for(int column = 0; column < GRID_SIZE; column++) {
            if(a[row][column] == 0) {
                return false;
            }
        }
    }
    return true;
}