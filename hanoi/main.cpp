#include <bits/stdc++.h>
using namespace std;

class hanoi{
public :
    hanoi(int n);

    void solve_the_hanoi();
    void let_us_play_hanoi(int n, int from, int to);

    void move_a_ring(int n, int from, int to);

    int what_is_temporary(int from, int to);


private :
    int num_of_rings;
    vector<stack<int>> rods;

    int K;
    vector<pair<int, int>> processes;
};

hanoi::hanoi(int n){
    num_of_rings = n;
    for(int i = 0; i < 3; i++){
        stack<int> a_rod;
        rods.push_back(a_rod);
    }

    for(int i = 0; i < num_of_rings; i++){
        rods[0].push(n-i);
    }

    K = 0;
}

void hanoi::solve_the_hanoi(){
    let_us_play_hanoi(num_of_rings, 1, 3);

    cout << K << '\n';

    for(int i = 0; i < processes.size(); i++){
        cout << processes[i].first << ' ' << processes[i].second << '\n';
    }
}

void hanoi::let_us_play_hanoi(int n, int from, int to){
    if(n == 1){
        move_a_ring(n, from, to);
    }

    else{
        int tmp = what_is_temporary(from, to);

        let_us_play_hanoi(n-1, from, tmp);
        move_a_ring(n, from, to);
        let_us_play_hanoi(n-1, tmp, to);
    }
}

int hanoi::what_is_temporary(int from, int to){
    if((from * to) == 2) return 3; // (1,2) or (2,1)
    else if((from * to) == 3) return 2; // (1,3) or(3,1)
    else if((from * to) == 6) return 1; // (2,3) or (3,2)
    else return 0;
}

void hanoi::move_a_ring(int n, int from, int to){
    int ring = rods[from-1].top();
    rods[to-1].push(ring);
    rods[from-1].pop();

    auto process = make_pair(from, to);
    processes.push_back(process);
    K++;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    int N;

    cin >> N;

    hanoi h(N);

    h.solve_the_hanoi();

	return 0;
}