#include <bits/stdc++.h>
using namespace std;

class max_tetromino_calculator{
public :
    enum class STATE {TOP_CHECK = 0, UPDATE_INFORMATION = 1, NEIGHBOR_PUSH = 2, DONE = 3};

    using pos = pair<int, int>;

    void set_map_pointer(vector<vector<int>>* mp);

    int calculate_max_tetromino_from(pos position);

    int function0(pos position);
    int function1(pos position);
    int function2(pos position);
    int function3(pos position);
    int function4(pos position);
    int function5(pos position);
    int function6(pos position);
    int function7(pos position);
    int function8(pos position);
    int function9(pos position);
    int function10(pos position);
    int function11(pos position);
    int function12(pos position);
    int function13(pos position);
    int function14(pos position);
    int function15(pos position);
    int function16(pos position);
    int function17(pos position);
    int function18(pos position);   

private :
    vector<vector<int>>* map_pointer;
    
    int answer;

    // STATE state;
};

class tetromino{
public :
    tetromino(int n, int m);

    void solve_the_max_tetromino_problem();

private :
    max_tetromino_calculator mtc;

    vector<vector<int>> map;
    int num_of_rows;
    int num_of_columns;

    int MAX_MAX_TET;
};

tetromino::tetromino(int n, int m){
    num_of_rows = n; num_of_columns = m;

    for(int i = 0; i < num_of_rows; i++){
        vector<int> a_row_of_map;

        for(int j = 0; j < num_of_columns; j++){
            int weight;
            cin >> weight;
            a_row_of_map.push_back(weight);
        }

        map.push_back(a_row_of_map);
    }

    mtc.set_map_pointer(&map);

    MAX_MAX_TET = 0;
}

void tetromino::solve_the_max_tetromino_problem(){
    for(int i = 0; i < num_of_rows; i++){
        for(int j = 0; j < num_of_columns; j++){
            int new_max_tet = mtc.calculate_max_tetromino_from({i, j});
            if(new_max_tet > MAX_MAX_TET) MAX_MAX_TET = new_max_tet;
        }
    }

    cout << MAX_MAX_TET << "\n";
}

void max_tetromino_calculator::set_map_pointer(vector<vector<int>>* mp){
    map_pointer = mp;
}

int max_tetromino_calculator::calculate_max_tetromino_from(pos position){
    // 일단 visited_positions, priority_queue, answer을 reset 해주어야함.
    // reset_by_position(position);

    // return do_the_calculation();
    int r = position.first; int c = position.second;
    int nr = (*map_pointer).size(); int nc = (*map_pointer)[0].size();

    answer = 0;

    // W
    // w
    // w
    // w
    if(((r+3) < nr)){
        int ans0 = function0(position);
        answer = (ans0 > answer) ? ans0 : answer;
    }

    // Wwww
    if(((c+3) < nc)){
        int ans1 = function1(position);
        answer = (ans1 > answer) ? ans1 : answer;
    }

    // Ww
    // ww
    if(((r+1) < nr) && ((c+1) < nc)){
        int ans2 = function2(position);
        answer = (ans2 > answer) ? ans2 : answer;
    }

    // W
    // w
    // ww
    if(((r+2) < nr) && ((c+1) < nc)){
        int ans3 = function3(position);
        answer = (ans3 > answer) ? ans3 : answer;
    }

    //   w
    // Www
    if(((r-1) >= 0) && ((c+2) < nc)){
        int ans4 = function4(position);
        answer = (ans4 > answer) ? ans4 : answer;
    }

    // Ww
    //  w
    //  w
    if(((r+2) < nr) && ((c+1) < nc)){
        int ans5 = function5(position);
        answer = (ans5 > answer) ? ans5 : answer;
    }

    // Www
    // w
    if(((r+1) < nr) && ((c+2) < nc)){
        int ans6 = function6(position);
        answer = (ans6 > answer) ? ans6 : answer;
    }

    //  w
    //  w
    // Ww
    if(((r-2) >= 0) && ((c+1) < nc)){
        int ans7 = function7(position);
        answer = (ans7 > answer) ? ans7 : answer;
    }

    // Www
    //   w
    if(((r+1) < nr) && ((c+2) < nc)){
        int ans8 = function8(position);
        answer = (ans8 > answer) ? ans8 : answer;
    }

    // Ww
    // w
    // w
    if(((r+2) < nr) && ((c+1) < nc)){
        int ans9 = function9(position);
        answer = (ans9 > answer) ? ans9 : answer;
    }

    // W
    // www
    if(((r+1) < nr) && ((c+2) < nc)){
        int ans10 = function10(position);
        answer = (ans10 > answer) ? ans10 : answer;
    }

    // W
    // ww
    //  w
    if(((r+2) < nr) && ((c+1) < nc)){
        int ans11 = function11(position);
        answer = (ans11 > answer) ? ans11 : answer;
    }

    //  ww
    // Ww
    if(((r-1) >= 0) && ((c+2) < nc)){
        int ans12 = function12(position);
        answer = (ans12 > answer) ? ans12 : answer;
    }

    //  w
    // Ww
    // w
    if(((r+1) < nr) && ((r-1) >= 0) && ((c+1) < nc)){
        int ans13 = function13(position);
        answer = (ans13 > answer) ? ans13 : answer;
    }

    // Ww
    //  ww
    if(((r+1) < nr) && ((c+2) < nc)){
        int ans14 = function14(position);
        answer = (ans14 > answer) ? ans14 : answer;
    }

    // W
    // ww
    // w
    if(((r+2) < nr) && ((c+1) < nc)){
        int ans15 = function15(position);
        answer = (ans15 > answer) ? ans15 : answer;
    }

    //  w
    // Www
    if(((r-1) >= 0) && ((c+2) < nc)){
        int ans16 = function16(position);
        answer = (ans16 > answer) ? ans16 : answer;
    }

    //  w
    // Ww
    //  w
    if(((r+1) < nr) && ((r-1) >= 0) && ((c+1) < nc)){
        int ans17 = function17(position);
        answer = (ans17 > answer) ? ans17 : answer;
    }

    // Www
    //  w
    if(((r+1) < nr) && ((c+2) < nc)){
        int ans18 = function18(position);
        answer = (ans18 > answer) ? ans18 : answer;
    }

    return answer;
}

int max_tetromino_calculator::function0(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r+1][c] + (*map_pointer)[r+2][c] + (*map_pointer)[r+3][c]);
}

int max_tetromino_calculator::function1(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r][c+2] + (*map_pointer)[r][c+3]);
}

int max_tetromino_calculator::function2(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r+1][c] + (*map_pointer)[r+1][c+1]);
}

int max_tetromino_calculator::function3(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r+1][c] + (*map_pointer)[r+2][c] + (*map_pointer)[r+2][c+1]);
}

int max_tetromino_calculator::function4(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r][c+2] + (*map_pointer)[r-1][c+2]);
}

int max_tetromino_calculator::function5(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r+1][c+1] + (*map_pointer)[r+2][c+1]);
}

int max_tetromino_calculator::function6(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r][c+2] + (*map_pointer)[r+1][c]);
}

int max_tetromino_calculator::function7(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r-1][c+1] + (*map_pointer)[r-2][c+1]);
}

int max_tetromino_calculator::function8(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r][c+2] + (*map_pointer)[r+1][c+2]);
}

int max_tetromino_calculator::function9(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r+1][c] + (*map_pointer)[r+2][c]);
}

int max_tetromino_calculator::function10(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r+1][c] + (*map_pointer)[r+1][c+1] + (*map_pointer)[r+1][c+2]);
}

int max_tetromino_calculator::function11(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r+1][c] + (*map_pointer)[r+1][c+1] + (*map_pointer)[r+2][c+1]);
}

int max_tetromino_calculator::function12(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r-1][c+1] + (*map_pointer)[r-1][c+2]);
}

int max_tetromino_calculator::function13(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r+1][c] + (*map_pointer)[r-1][c+1]);
}

int max_tetromino_calculator::function14(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r+1][c+1] + (*map_pointer)[r+1][c+2]);
}

int max_tetromino_calculator::function15(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r+1][c] + (*map_pointer)[r+1][c+1] + (*map_pointer)[r+2][c]);
}

int max_tetromino_calculator::function16(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r-1][c+1] + (*map_pointer)[r][c+2]);
}

int max_tetromino_calculator::function17(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r-1][c+1] + (*map_pointer)[r+1][c+1]);
}

int max_tetromino_calculator::function18(pos position){
    int r = position.first; int c = position.second;
    return ((*map_pointer)[r][c] + (*map_pointer)[r][c+1] + (*map_pointer)[r][c+2] + (*map_pointer)[r+1][c+1]);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M;

    cin >> N >> M;

    tetromino t(N, M);

    t.solve_the_max_tetromino_problem();

	return 0;
}