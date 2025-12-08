    #include <bits/stdc++.h>

    using namespace std;

    using pos = pair<int, int>;

    pair<int, int> LUT_drdc[4] = {{-1,0}, {0,-1}, {0,1}, {1,0}}; // 상, 좌, 우, 하

    const int power_INF = 9;
    const int dist_INF = 0x3f3f3f3f;

    int fish_power[20][20];
    int dist[20][20];
    bool mark[20][20];
    int number_of_each_power[6];

    int main(){
        ios::sync_with_stdio(false); cin.tie(NULL);

        int N;

        int shark_power = 2;
        
        memset(number_of_each_power, 0, sizeof(number_of_each_power));

        cin >> N;

        pos shark_pos;
        queue<pos> pp;

        int fp;
        for(int r = 0; r < N; r++){
            for(int c = 0; c < N; c++){
                cin >> fp;
                if(fp == 0) fish_power[r][c] = 0;
                else if(fp != 9){
                    fish_power[r][c] = fp;
                    number_of_each_power[fp-1]++;
                }
                else{
                    fish_power[r][c] = 0;
                    shark_pos = {r, c};
                    pp.push(shark_pos);
                }
            }
        }

        auto start = chrono::high_resolution_clock::now();
        int answer = 0;
        int eat_count = 0;

        memset(dist, dist_INF, sizeof(dist));
        dist[shark_pos.first][shark_pos.second] = 0;
        memset(mark, false, sizeof(mark));

        while(true){
            bool is_there_edible = 0;
            for(int i = 0; i < (shark_power - 1); i++){
                if(number_of_each_power[i] != 0){
                    is_there_edible = 1;
                    break;
                }
            }

            if(!is_there_edible) break;
            if(pp.empty()) break;

            shark_pos = pp.front();
            int shark_r = shark_pos.first;
            int shark_c = shark_pos.second;
            mark[shark_r][shark_c] = true;
            pp.pop();

            int current_dist = dist[shark_r][shark_c];

            int* current_fp = &fish_power[shark_r][shark_c];

            if((*current_fp >= 1) && (*current_fp < shark_power)){
                number_of_each_power[*current_fp-1]--;
                *current_fp = 0;
                eat_count++;
                queue<pos> p;
                pp = p;
                pp.push(shark_pos);

                if(eat_count == shark_power){
                    shark_power++;
                    eat_count = 0;
                }

                answer += current_dist;
                memset(mark, false, sizeof(mark));
                memset(dist, dist_INF, sizeof(dist));
                dist[shark_r][shark_c] = 0;
                mark[shark_r][shark_c] = true;
                current_dist = 0;
            }

            for(int i = 0; i < 4; i++){
                int neighbor_r = shark_r + LUT_drdc[i].first;
                int neighbor_c = shark_c + LUT_drdc[i].second;

                if(((neighbor_r) >= 0) && ((neighbor_r) < N) && 
                    ((neighbor_c) >= 0) && ((neighbor_c < N))){
                    if((fish_power[neighbor_r][neighbor_c] <= shark_power) &&
                        (!mark[neighbor_r][neighbor_c])){
                        dist[neighbor_r][neighbor_c] = current_dist + 1;
                        pp.push({neighbor_r, neighbor_c});
                    }
                }
            }
        }

        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        cout << "DURATION : " << duration.count() << "ms\n";

        cout << answer << '\n';

        return 0;
    }