#include <bits/stdc++.h>
using namespace std;

const int INF = 0x1f1f1f1f;

class sea{
public :
    sea(int n);

    void solve();

    bool no_target_possible();
    void find_nearest();
    bool no_target_reachable();

    void eat(); // power_up과 sea_update를 포함함.

private :
    int N;

    using pos = pair<int, int>; // row, column
    using dp = pair<int, pos>;
    std::priority_queue<dp, std::vector<dp>, std::greater<dp>> reachables;

    queue<pos> bfs_data;

    int answer;

    int fish_power[20][20];
    bool visited[20][20];
    int dist[20][20];
    int number_of_fish_of_each_power[7]; // 1,2,3,4,5,6을 index 입력으로 그 power에 해당하는 fish 수를 출력으로 내는 함수라고 생각.

    pos shark_pos;
    int shark_power;
    int shark_eat_count;
};

sea::sea(int n){
    memset(fish_power, 0x1f, sizeof(fish_power));
    memset(visited, true, sizeof(visited));
    memset(dist, 0x1f, sizeof(dist));
    memset(number_of_fish_of_each_power, 0, sizeof(number_of_fish_of_each_power));

    N = n;

    int p;
    
    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
            cin >> p;
            if(p == 0) fish_power[r][c] = 0;

            else if(p != 9){
                fish_power[r][c] = p;
                number_of_fish_of_each_power[p]++;
            }

            else{
                fish_power[r][c] = 0;
                shark_pos = {r, c};
            }

            visited[r][c] = false;
        }
    }

    shark_power = 2;
    shark_eat_count = 0;

    answer = 0;
}

void sea::solve(){
    while(true){
        if(no_target_possible()) break;
        
        find_nearest(); // BFS 끝날때 queue를 reset 시켜주면 될 것.

        if(no_target_reachable()) break;

        eat();
    }

    cout << answer << '\n';
}

bool sea::no_target_possible(){
    for(int i = shark_power-1; i > 0; i--){
        if(number_of_fish_of_each_power[i] != 0) return false;
    }

    return true;
}

bool sea::no_target_reachable(){
    return reachables.empty();
}

void sea::eat(){
    shark_pos = reachables.top().second;
    answer += reachables.top().first;

    int fp = fish_power[shark_pos.first][shark_pos.second];

    std::priority_queue<dp, std::vector<dp>, std::greater<dp>> new_reachables;
    reachables = new_reachables;

    shark_eat_count++;
    number_of_fish_of_each_power[fp]--;

    if(shark_eat_count == shark_power){
        shark_power++;
        shark_eat_count = 0;
    }

    int r = shark_pos.first;
    int c = shark_pos.second;

    fish_power[r][c] = 0;
}

void sea::find_nearest(){
    int original_r = shark_pos.first;
    int original_c = shark_pos.second;
    dist[original_r][original_c] = 0;

    bfs_data.push(shark_pos);
    visited[original_r][original_c] = true;

    pos ghost_pos;

    while(true){
        if(bfs_data.empty()) break;

        ghost_pos = bfs_data.front();
        bfs_data.pop();
        
        int r = ghost_pos.first;
        int c = ghost_pos.second;

        // visited[r][c] = true;

        if((fish_power[r][c] != 0) && (fish_power[r][c] < shark_power)){ // eat이 가능한 곳.
            reachables.push({dist[r][c], ghost_pos});
            continue;
        }

        if(((r-1) >= 0) && !visited[r-1][c] && (fish_power[r-1][c] <= shark_power)){
            bfs_data.push({r-1, c});
            dist[r-1][c] = dist[r][c] + 1;
            visited[r-1][c] = true;
        }

        if(((c-1) >= 0) && !visited[r][c-1] && (fish_power[r][c-1] <= shark_power)){
            bfs_data.push({r, c-1});
            dist[r][c-1] = dist[r][c] + 1;
            visited[r][c-1] = true;
        }

        if(((c+1) < N) && !visited[r][c+1] && (fish_power[r][c+1] <= shark_power)){
            bfs_data.push({r, c+1});
            dist[r][c+1] = dist[r][c] + 1;
            visited[r][c+1] = true;
        }

        if(((r+1) < N) && !visited[r+1][c] && (fish_power[r+1][c] <= shark_power)){
            bfs_data.push({r+1, c});
            dist[r+1][c] = dist[r][c] + 1;
            visited[r+1][c] = true;
        }
    }

    memset(dist, 0x1f, sizeof(dist));
    memset(visited, false, sizeof(visited));
}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);

    int N;

    cin >> N;

    sea s(N);

    // auto start = chrono::high_resolution_clock::now();
    
    s.solve();

    // auto end = chrono::high_resolution_clock::now();

    // auto duration = chrono::duration_cast<chrono::milliseconds>(end-start);

    // cout << "DURATION : " << duration.count() << "ms\n";

    return 0;
}