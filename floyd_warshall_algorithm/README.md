https://www.acmicpc.net/problem/11404

N * dijkstra method

#include <bits/stdc++.h>
using namespace std;

using cap = pair<int, int>; // {cost, arrival}

const int INF = 0x1f1f1f1f;

// 1word = 4bytes = 32bits
// hexademical = 4bits = 1bytes
// memset은 hexademical, byte 단위로 값을 채움.

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    int N, M;

    cin >> N >> M;

    int* edges = new int[N*N]; // edges[r*N + c] = (r+1에서 c+1로 향하는 버스의 cost)
    memset(edges, 0x1f, sizeof(int)*N*N);
    // 인덱스 계산 -> [r*N + c] = [r][c] (departure : r+1, arrival : c+1, total_cost = ans[r][c])

    for(int i = 0; i < N; i++){
        edges[i*N + i] = 0;
    }

    int a, b, c; // (a,b,c) = (DEPARTURE, ARRIVAL, COST)
    for(int m = 0; m < M; m++){
        cin >> a >> b >> c;
        int* e = &edges[(a-1)*N + (b-1)];
        if(c < *e){
            *e = c; // cost가 작은 것만 저장함!
        }  
    }

    int* ans = new int[N*N];
    memset(ans, 0x1f, sizeof(int)*N*N);

    bool* vt = new bool[N]; // visit_table

    cap current;
    int visit_count;

    for(int i = 0; i < N; i++){
        priority_queue<cap, vector<cap>, greater<cap>> min_heap; // {cost, arrival}

        memset(vt, 0, N * sizeof(bool));
        visit_count = 0;
        
        min_heap.push({0, i});
        ans[i*N + i] = 0;

        while((!min_heap.empty())){ // worst case : O(N)
            if(visit_count == N) break; // unconnected graph라는 edge case 때문에 visit_count가 절대적인 종료조건이 되어서는 안됨.

            if(vt[min_heap.top().second]){ // if arrival point is visited....
                min_heap.pop();
                continue;
            }

            else{
                current = min_heap.top();
                min_heap.pop();
            }

            vt[current.second] = true;
            visit_count++;

            // edge_current_to_neighbor != INF인 상황을 갖고 있어야 한다.
            for(int c = 0; c < N; c++){
                int* edge_current_to_neighbor = &edges[current.second*N + c];
                if((*edge_current_to_neighbor) == INF) continue;

                int* neighbor_dist = &ans[i*N + c];
                int* current_dist = &ans[i*N + current.second];

                // edge가 INF인 경우 = 도달할 수 없는 경우 jump
                // current_dist가 INF일 수는 없음.
                if((*neighbor_dist) > (*current_dist) + (*edge_current_to_neighbor)){ 
                    (*neighbor_dist) = ((*current_dist) + (*edge_current_to_neighbor));
                    min_heap.push({(*neighbor_dist), c});
                }
            }
        }
    }

    // print_the_output! but we should print '0' even if total_cost == INF!
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            if(ans[r*N + c] != INF) cout << ans[r*N + c] << ' '; 
            else cout << 0 << ' ';
        }
        cout << '\n';
    }

    // prevent from memory leak!
    delete[] edges;
    delete[] ans;
    delete[] vt;
	
	return 0;
}