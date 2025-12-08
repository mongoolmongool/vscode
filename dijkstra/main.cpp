#include <bits/stdc++.h>
using namespace std;

class dijkstra{
public :
    enum class STATE{WHERE_TO_VISIT = 0, UPDATE_INFORMATION = 1, DONE = 2};

    dijkstra(int num_of_vertices, int num_of_edges, int starting_vertice);

    void select_current();
    void update_information();
    void print_distance_table();
    void mark_visited(); // 문제에 당장은 쓰이지 않음.
    void next_distance_update();
    void update_real(int nv, int de); // 다음에 visit할 vertice를 return 해야함.

    bool is_INF(int v);
    bool can_be_updated(int nv, int de);

    void solve();

private :
    int current;

    vector<vector<pair<int, int>>> edges; // fixed_data
    vector<bool> visit_table; // can be modified
    vector<int> distance_table; // result, can be modified

    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> uv_and_no_INF; // can be modified, unvisited and no INF vertices

    STATE state;    
};

dijkstra::dijkstra(int num_of_vertices, int num_of_edges, int starting_vertice){
    for(int i = 0; i <= num_of_vertices; i++){
        visit_table.push_back(false);
        vector<pair<int, int>> a_edge;
        distance_table.push_back(-1); // -1 means INF
        edges.push_back(a_edge);
    }
    distance_table[starting_vertice] = 0;
    uv_and_no_INF.push({0, starting_vertice});

    for(int i = 1; i <= num_of_edges; i++){
        int u, v, w; // from, to, weight
        cin >> u >> v >> w; 
        pair<int, int> p = make_pair(v, w);
        edges[u].push_back(p);    
    }

    state = dijkstra::STATE::WHERE_TO_VISIT;
}

void dijkstra::solve(){

    while(state != dijkstra::STATE::DONE){

        switch(state){
            case dijkstra::STATE::WHERE_TO_VISIT :
                if(uv_and_no_INF.size() != 0){
                    select_current();
                    state = dijkstra::STATE::UPDATE_INFORMATION;
                }

                else{
                    state = dijkstra::STATE::DONE;
                }

                break;
        
            case dijkstra::STATE::UPDATE_INFORMATION :
                update_information();
                state = dijkstra::STATE::WHERE_TO_VISIT;
                break;

            default :
                break;
                
        }
    }

    print_distance_table();
}

void dijkstra::select_current(){ // 현재까지 distance 중 가장 작은 애를 pick 해야함.
    // find_left_most_uv
    // find_current
    int d = uv_and_no_INF.top().first;
    int v = uv_and_no_INF.top().second;
    uv_and_no_INF.pop();

    // 2. [중요] 이미 방문한 노드면 스킵 (더 짧은 경로가 이전에 발견된 경우)
    //    방문하지 않은 노드가 나올 때까지 반복
    while (!uv_and_no_INF.empty() && visit_table[v] == true) {
        d = uv_and_no_INF.top().first;
        v = uv_and_no_INF.top().second;
        uv_and_no_INF.pop();
    }

    current = v; // current를 설정

    // 3. 만약 d > distance_table[v] 라면, 
    //    이것은 큐에 쌓여있던 '오래된' 정보이므로 무시해야 함.
    //    (더 효율적인 구현에서는 이 검사를 포함함)
}

void dijkstra::update_information(){
    mark_visited();
    if(edges[current].size() != 0) next_distance_update();
}

void dijkstra::mark_visited(){
    visit_table[current] = true;
}

void dijkstra::next_distance_update(){
    vector<pair<int, int>> next = edges[current];

    for(int i = 0; i < next.size(); i++){
        int next_vertice = next[i].first;
        int dist_of_a_edge = next[i].second;
        update_real(next_vertice, dist_of_a_edge);
    }
}

void dijkstra::update_real(int nv, int de){
    if(can_be_updated(nv, de)){
        distance_table[nv] = distance_table[current] + de;
        uv_and_no_INF.push({distance_table[nv], nv});
    }
    // if(is_INF(nv)){
    //     distance_table[nv] = distance_table[current] + de;
    //     uv_and_no_INF.push({distance_table[nv], nv}); // 이 push가 한번만 일어나도록 해야함. INF였다가 변할때만 push 되어야함.
    // }

    // else if(((distance_table[current] + de) < distance_table[nv])){
    //     distance_table[nv] = distance_table[current] + de;
    // }
}

bool dijkstra::can_be_updated(int nv, int de){ // next_vertice, dist_of_a_edge
    return (is_INF(nv) || ((distance_table[current] + de) < distance_table[nv]));
}

bool dijkstra::is_INF(int v){
    return (distance_table[v] == -1);
}

void dijkstra::print_distance_table(){
    for(int i = 1; i <= distance_table.size() - 1; i++){
        if(distance_table[i] != -1){
            cout << distance_table[i] << '\n';
        }

        else{
            cout << "INF" << '\n';
        }
    }
}


int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    int V, E, sv;

    cin >> V >> E >> sv;

    dijkstra d(V, E, sv);

    d.solve();

	return 0;
}