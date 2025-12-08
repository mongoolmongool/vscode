#pragma GCC optimize("O3")
#pragma GCC target("avx512f,avx512bw,avx512dq,avx512vl,avx512cd")

#include <bits/stdc++.h>
#include <immintrin.h>
using namespace std;

using cap = pair<int, int>; // {cost, arrival}

const int INF = 0x1f1f1f1f;

// 1word = 4bytes = 32bits
// hexademical = 4bits = 1bytes
// memset은 hexademical, byte 단위로 값을 채움.

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    ////////// DATA //////////
    int N, M;

    cin >> N >> M;

    int* dist = new int[N*N]; // edges[r*N + c] = (r+1에서 c+1로 향하는 버스의 cost)
    memset(dist, 0x1f, sizeof(int)*N*N);
    // 인덱스 계산 -> [r*N + c] = [r][c] (departure : r+1, arrival : c+1, total_cost = ans[r][c])

    for(int i = 0; i < N; i++) dist[i*N + i] = 0;    

    int a, b, c; // (a,b,c) = (DEPARTURE, ARRIVAL, COST)

    for(int m = 0; m < M; m++){
        cin >> a >> b >> c;
        int* e = &dist[(a-1)*N + (b-1)];
        if(c < *e){
            *e = c; // cost가 작은 것만 저장함!
        }  
    }
    ////////// DATA //////////

    auto start = chrono::high_resolution_clock::now();
    ////////// ALGORITHM //////////
    for(int tmp = 0; tmp < N; tmp++){
        for(int dep = 0; dep < N; dep++){
            if(dist[dep*N + tmp] == INF) continue;

            __m512i d_dt = _mm512_set1_epi32(dist[dep*N + tmp]);

            int arr = 0;
            for(; arr <= (N-16); arr += 16){
                __m512i d_ta = _mm512_loadu_si512((__m512i*)&dist[tmp*N + arr]);
                __m512i d_da = _mm512_loadu_si512((__m512i*)&dist[dep*N + arr]);

                __m512i new_dist = _mm512_add_epi32(d_dt, d_ta);
                __m512i result = _mm512_min_epi32(d_da, new_dist);

                _mm512_storeu_si512((__m512i*)&dist[dep*N + arr], result);
            }

            for(; arr < N; arr++){
                if(dist[dep*N + arr] > (dist[dep*N + tmp] + dist[tmp*N + arr])){
                    dist[dep*N + arr] = (dist[dep*N + tmp] + dist[tmp*N + arr]);
                }
            }
        }
    }
    ////////// ALGORITHM ///////////
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

    ///////// OUTPUT //////////
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            if(dist[r*N + c] != INF) cout << dist[r*N + c] << ' '; 
            else cout << 0 << ' ';
        }
        cout << '\n';
    }
    ////////// OUTPUT //////////

    ////////// DURATION //////////
    cout << "DURATION : " << duration.count() << "ns\n";
    ////////// DURATION //////////

    ////////// MEMORY LEAK CHECK //////////
    delete[] dist;
    ////////// MEMORY LEAK CHECK //////////
	
	return 0;
}