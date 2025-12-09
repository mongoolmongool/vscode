#include <bits/stdc++.h>
using namespace std;

struct building{
    vector<int> before;
    priority_queue<int> max_td; // max_total_duration
    bool pushed;
    int duration;
};

class ac{
public :

    void set_T(int t);
    void receive_input();
    void main_solve();
    void sub_solve();
    

private :
    building* buildings;
    int T, N, K, W;
    int answer;
    queue<int> q;
};

void ac::set_T(int t){
    this->T = t;
}

void ac::receive_input(){
    cin >> N >> K;

    buildings = new building[N];

    int D;

    for(int i = 0; i < N; i++){
        cin >> D;
        buildings[i].duration = D;
        buildings[i].pushed = false;
    }

    int X, Y; // X means departure, Y means arrival
    for(int i = 0; i < K; i++){
        cin >> X >> Y;
        buildings[Y-1].before.push_back(X);
    }

    cin >> W;
}

void ac::main_solve(){
    for(int i = 0; i < T; i++){
        receive_input();
        sub_solve();
    }
}

void ac::sub_solve(){
    answer = 0;
    buildings[W-1].max_td.push(0);
    q.push(W);
    buildings[W-1].pushed = true;

    while(true){
        if(q.empty()) break;

        building* front = buildings + (q.front() - 1);

        int total_duration = front->duration + front->max_td.top();

        if((front->before.empty()) && (answer < total_duration)) answer = total_duration;

        building* before_of_front;
        for(auto it = front->before.begin(); it != front->before.end(); it++){
            before_of_front = &(buildings[(*it)-1]);
            before_of_front->max_td.push(total_duration);

            // q.push(*it);
            if(!before_of_front->pushed){
                 q.push(*it);
                 before_of_front->pushed = true;
            }
        }

        q.pop();
    }

    cout << answer << '\n';

    delete[] buildings;
    queue<int> new_q;
    q = new_q;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);

    ac a;

    int T;

    cin >> T;

    a.set_T(T);

    a.main_solve();

    return 0;
}