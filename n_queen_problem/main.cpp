#include <bits/stdc++.h>
using namespace std;

class checkerboard{
public :
    checkerboard(int n);

    int solve_the_n_queen_problem();

    int compute_the_answer(int queen_remained, vector<pair<int, int>> possible_squares);
    vector<pair<int ,int>> next_possible_squares(vector<pair<int, int>> possible_squares, pair<int, int> a_square_to_place_a_queen);
    bool is_safe(pair<int, int> victim, pair<int, int> perpetrator);

private :
    int N;
    vector<pair<int, int>> all_squares;
};

checkerboard::checkerboard(int n){
    this->N = n;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            all_squares.push_back({i, j});
        }
    }
}

int checkerboard::solve_the_n_queen_problem(){
    return compute_the_answer(0, all_squares);
}

// 여기서 step은 현재 보아야 하는 rank를 의미한다 매우 중요함! 조합의 논리에 쓰이기 때문
int checkerboard::compute_the_answer(int step, vector<pair<int, int>> possible_squares){
    if(step == N){
        // cout << "all queens are placed!!" << "\n\n"; // for debugging
        // stack을 비우는 자리
        return 1;
    }
    else if(possible_squares.size() == 0){
        // cout << "failed to make n_queens" << "\n\n"; // for debugging
        // stack을 pop하는 자리.
        return 0;
    }
    else{
        int answer = 0;

        for(int i = 0; i < possible_squares.size(); i++){ 
            // cout << "I put the queen on " << "(" << possible_squares[i].first << ", " << possible_squares[i].second << ")\n";
            // stack에 push하는 자리.
            if(possible_squares[i].first > step) break; // 현재 보아야 하는 rank를 넘어가면 다른 rank는 보지 않는다.
            vector<pair<int, int>> next_possibles = next_possible_squares(possible_squares, possible_squares[i]);
            answer += compute_the_answer(step + 1, next_possibles);
        }

        return answer;
    }
}

vector<pair<int, int>> checkerboard::next_possible_squares(
    vector<pair<int, int>> possible_squares, 
    pair<int, int> a_square_to_place_a_queen){

    vector<pair<int, int>> next_possibles;

    for(int i = 0; i < possible_squares.size(); i++){
        if(is_safe(possible_squares[i], a_square_to_place_a_queen)) // 공격 받지 않는 다면
            next_possibles.push_back(possible_squares[i]);
    }

    return next_possibles;
}

bool checkerboard::is_safe(pair<int, int> victim, pair<int, int> perpetrator){
    int victim_rank = victim.first;
    int victim_file = victim.second;
    int perpetrator_rank = perpetrator.first;
    int perpetrator_file = perpetrator.second;

    if(victim_rank == perpetrator_rank) return 0; // 가로 r
    else if(victim_file == perpetrator_file) return 0; // 세로 f
    else if((victim_rank + victim_file) == (perpetrator_rank + perpetrator_file)) return 0; // 우상향 대각 r+f
    else if((victim_file - victim_rank) == (perpetrator_file - perpetrator_rank)) return 0; // 우하향 대각 3-r+f
    else return 1;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    int N;

    cin >> N;

    auto start = std::chrono::high_resolution_clock::now();

    checkerboard c(N);

    cout << c.solve_the_n_queen_problem() << "\n\n";

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "코드 실행 시간: " << duration.count() << "ms\n" << std::endl;

	return 0;
}