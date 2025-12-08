#include <bits/stdc++.h>
using namespace std;

using pos = pair<int, int>;

int R, C;

vector<vector<char>> alphabet_paper;
// map<char, bool> vt // 느리다.
vector<bool> vt; // 빠르다.

vector<pair<int, int>> neighbor = {{-1,0}, {0,1}, {1,0}, {0,-1}}; // clockwise {up, right, down, left}

bool boundary_and_unvisit_check(int& r, int& c, int& i){
    bool return_value;
    switch(i){
        case 0 :
            return_value = (((r-1) >= 0) && (!vt[alphabet_paper[r-1][c] - static_cast<int>('A')]));
            break;

        case 1 :
            return_value = (((c+1) < C) && (!vt[alphabet_paper[r][c+1] - static_cast<int>('A')]));
            break;

        case 2 :
            return_value = (((r+1) < R) && (!vt[alphabet_paper[r+1][c] - static_cast<int>('A')]));
            break;

        case 3 :
            return_value = (((c-1) >= 0) && (!vt[alphabet_paper[r][c-1] - static_cast<int>('A')]));
            break;

        default :
            break;
    }

    return return_value;
}

bool boundary_up(pos& p){
    return ((p.first-1) >= 0);
}

bool boundary_right(pos& p){
    return ((p.second+1) < C);
}

bool boundary_down(pos& p){
    return ((p.first+1) < R);
}

bool boundary_left(pos& p){
    return ((p.second-1) >= 0);
}

bool are_all_neighbors_visited(pos& p){
    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;

    if(boundary_up(p)) up = (vt[static_cast<int>(alphabet_paper[p.first-1][p.second]) - static_cast<int>('A')]);
    else up = true;
    if(boundary_right(p)) right = (vt[static_cast<int>(alphabet_paper[p.first][p.second+1]) - static_cast<int>('A')]);
    else right = true;
    if(boundary_down(p)) down = (vt[static_cast<int>(alphabet_paper[p.first+1][p.second]) - static_cast<int>('A')]);
    else down = true;
    if(boundary_left(p)) left = (vt[static_cast<int>(alphabet_paper[p.first][p.second-1]) - static_cast<int>('A')]);
    else left = true;

    return (up && right && down && left);
}

int let_us_move_a_horse(pos p, int step){
    int r = p.first; int c = p.second;
    char alphabet = alphabet_paper[r][c];

    // 현재 p를 visit 표시 하고
    vt[static_cast<int>(alphabet) - static_cast<int>('A')] = true;

    // neighbor들이 모두 visited이면
    // return step
    if(are_all_neighbors_visited(p)){
        vt[static_cast<int>(alphabet) - static_cast<int>('A')] = false;
        return step;
    }

    // 아니라면
    // boundary 조건 확인 후
    // return function(neighbor 좌표, step + 1);

    // neighbor_call

    int max = step;

    for(int i = 0; i < neighbor.size(); i++){
        int dr = neighbor[i].first; // 행 변화
        int dc = neighbor[i].second; // 열 변화

        if(boundary_and_unvisit_check(r, c, i)){
            int new_max = let_us_move_a_horse({r + dr, c + dc}, step+1);
            max = (new_max > max) ? new_max : max;
        }
    }

    vt[static_cast<int>(alphabet) - static_cast<int>('A')] = false;

    return max;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    cin >> R >> C;

    vt.resize(26);

    for(int i = 0; i < R; i++){
        vector<char> a_row;

        for(int j = 0; j < C; j++){
            char a;
            cin >> a;
            a_row.push_back(a);
            vt[static_cast<int>(a) - static_cast<int>('A')] = false;
        }

        alphabet_paper.push_back(a_row);
    }

    cout << let_us_move_a_horse({0, 0}, 1) << '\n';

	return 0;
}