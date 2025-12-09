#include <bits/stdc++.h>
using namespace std;

struct building{
    vector<int> after;
    int accumulated_duration = 0;
    int duration;
    int indegree = 0;
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
    }

    int X, Y; // X means departure, Y means arrival
    for(int i = 0; i < K; i++){
        cin >> X >> Y;
        buildings[X-1].after.push_back(Y);
        buildings[Y-1].indegree++;
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
    for(int i = 0; i < N; i++){
        if((buildings + i)->indegree == 0){
            q.push(i+1);
        }
    }

    while(true){
        if(q.empty()) break;

        int front_building_number = q.front();
        building* front = &buildings[front_building_number-1];

        if(front_building_number == W){
            answer = front->accumulated_duration + front->duration;
            break;
        }

        building* current_after;
        int after_building_number;
        for(int i = 0; i < front->after.size(); i++){
            after_building_number = front->after[i];
            current_after = &buildings[after_building_number-1]; 
            
            int ad_candidate = front->accumulated_duration + front->duration;
            // accumulated_duration candidate of current_after
            if(ad_candidate > current_after->accumulated_duration) current_after->accumulated_duration = ad_candidate;

            current_after->indegree--;

            if(current_after->indegree == 0) q.push(after_building_number);
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