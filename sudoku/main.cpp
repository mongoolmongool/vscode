#include <bits/stdc++.h>
using namespace std;

using pos = pair<int, int>;

char board[9][9]; // sudoku board, 숫자의 범위가 1~9이므로 1byte만 써서 최적화.
pos unfilled[81];
pos* unfilled_sp = unfilled - 1; // stack pointer of the unfilled positions

inline void print_board(){ // for debugging
    for(int r = 0; r < 9; r++){
        for(int c = 0; c < 9; c++){
            cout << board[r][c] << ' ';
        }
        cout << '\n';
    }
}

bool solve(){
    if(unfilled_sp < unfilled) return true;

    else{
        int R = (*unfilled_sp).first;
        int C = (*unfilled_sp).second;

        bool is_possible[10];
        memset(&is_possible, true, sizeof(bool)*10);

        for(int r = 0; r < 9; r++){
            if(board[r][C] != '0') is_possible[board[r][C] - '0'] = false;
        }

        for(int c = 0; c < 9; c++){
            if(board[R][c] != '0') is_possible[board[R][c] - '0'] = false;
        }

        if((R >= 0) && (R <= 2) && (C >= 0) && (C <= 2)){
            for(int r = 0; r <= 2; r++){
                for(int c = 0; c <= 2; c++){
                    if(board[r][c] != '0') is_possible[board[r][c] - '0'] = false;
                }
            }
        }

        else if((R >= 0) && (R <= 2) && (C >= 3) && (C <= 5)){
            for(int r = 0; r <= 2; r++){
                for(int c = 3; c <= 5; c++){
                    if(board[r][c] != '0') is_possible[board[r][c] - '0'] = false;
                }
            }
        }
        else if((R >= 0) && (R <= 2) && (C >= 6) && (C <= 8)){
            for(int r = 0; r <= 2; r++){
                for(int c = 6; c <= 8; c++){
                    if(board[r][c] != '0') is_possible[board[r][c] - '0'] = false;
                }
            }
        }
        else if((R >= 3) && (R <= 5) && (C >= 0) && (C <= 2)){
            for(int r = 3; r <= 5; r++){
                for(int c = 0; c <= 2; c++){
                    if(board[r][c] != '0') is_possible[board[r][c] - '0'] = false;
                }
            }
        }
        else if((R >= 3) && (R <= 5) && (C >= 3) && (C <= 5)){
            for(int r = 3; r <= 5; r++){
                for(int c = 3; c <= 5; c++){
                    if(board[r][c] != '0') is_possible[board[r][c] - '0'] = false;
                }
            }
        }
        else if((R >= 3) && (R <= 5) && (C >= 6) && (C <= 8)){
            for(int r = 3; r <= 5; r++){
                for(int c = 6; c <= 8; c++){
                    if(board[r][c] != '0') is_possible[board[r][c] - '0'] = false;
                }
            }
        }
        else if((R >= 6) && (R <= 8) && (C >= 0) && (C <= 2)){
            for(int r = 6; r <= 8; r++){
                for(int c = 0; c <= 2; c++){
                    if(board[r][c] != '0') is_possible[board[r][c] - '0'] = false;
                }
            }
        }
        else if((R >= 6) && (R <= 8) && (C >= 3) && (C <= 5)){
            for(int r = 6; r <= 8; r++){
                for(int c = 3; c <= 5; c++){
                    if(board[r][c] != '0') is_possible[board[r][c] - '0'] = false;
                }
            }
        }
        else if((R >= 6) && (R <= 8) && (C >= 6) && (C <= 8)){
            for(int r = 6; r <= 8; r++){
                for(int c = 6; c <= 8; c++){
                    if(board[r][c] != '0') is_possible[board[r][c] - '0'] = false;
                }
            }
        }

        for(int i = 1; i <= 9; i++){
            if(is_possible[i]){
                board[R][C] = i + '0';
                unfilled_sp--;

                if(solve()) return true;

                unfilled_sp++;
                *unfilled_sp = {R, C};
                board[R][C] = '0';
            }
        }
        return false;
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);

    // INPUT //
    char input;

    for(int r = 0; r < 9; r++){
        for(int c = 0; c < 9; c++){
            cin >> input;
            if(input == '0'){
                unfilled_sp++;
                *unfilled_sp = {r, c};
            }
            board[r][c] = input;
        }
    }

    // ALGORITHM //
    auto start = chrono::high_resolution_clock::now();

    bool valid = solve();

    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end-start);

    cout << "DURATION : " << duration.count() << "ns\n";

    // OUTPUT //
    if(valid) print_board();

    return 0;
}