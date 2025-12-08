#include <bits/stdc++.h>
using namespace std;

class MST{
public :
    enum class STATE {TOP_CHECK = 0, UPDATE_DATAPATH = 1, ALL_VISITED_CHECK = 2, DONE = 3};

    MST(int v, int e);

    bool is_top_unvisited();

    void update_datapath();

    void select_current_from_top();

    void make_current_visited();

    void compound_length_of_MST();

    void push_edges_of_the_current();

    bool all_visited();

    void solve();

private :
    STATE state;

    pair<int, int> current; // <distance, destination>
    int MST_length;

    int how_many_visited;

    vector<vector<pair<int, int>>> edges;
    // edges[x][y].first는 x로부터 뻗은 edge중 y번째(특별한 의미는 없음)의 도착지
    // edges[x][y].second는 x로부터 뻗은 edge중 y번째(특별한 의미는 없음)의 가중치
    // 즉 edges[x]는 x로부터 뻗은 모든 edge의 정보를 담고 있음.
    // 0은 빈 값으로 냅둔다.

    unordered_map<int, bool> visit_table;

    using pii = std::pair<int, int>; // <distance, destination>
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> edge_pq;

    // min_heap을 하나 갖고 있는데 그것은 (C, DESTINATION)의 형태를 가진다.

};

MST::MST(int v, int e){ // 데이터 생성과, reset 작업
    for(int i = 1; i <= v; i++){
        visit_table[i] = false;
    }

    edges.resize(v+1);

    for(int i = 0; i < e; i++){
        int A, B, C;
        cin >> A >> B >> C;

        edges[A].push_back({C, B}); // A에서 C길이로 B에 도달할 수 있다.
        edges[B].push_back({C, A}); // B에서도 역시 C길이로 A에 도달할 수 있다.
    }

    how_many_visited = 0;
    MST_length = 0;

    edge_pq.push({0, 1});
    // min_heap에다가 {0, 1}을 넣어두고 state를 TOP_CHECK로 두면?
    // 시작점을 1로 지정하면서 MST_length에는 아무것도 안 더하게 된다.

    state = MST::STATE::TOP_CHECK;
}

void MST::solve(){
    while(state != MST::STATE::DONE){
        switch(state){
            case MST::STATE::TOP_CHECK :
                // is_top_unvisited()는 현재 min_heap의 top을 확인하고
                // unvisited이면 1을 return
                // visited이면 그걸 pop하고 0을 return
                if(is_top_unvisited()) state = MST::STATE::UPDATE_DATAPATH;
                else{
                    edge_pq.pop();
                    state = MST::STATE::TOP_CHECK;
                }
                break;

            case MST::STATE::UPDATE_DATAPATH :
                update_datapath();
                state = MST::STATE::ALL_VISITED_CHECK;
                break;

            case MST::STATE::ALL_VISITED_CHECK :
                if(!all_visited()) state = MST::STATE::TOP_CHECK; // 모두 visited가 아니면... top_check로
                else state = MST::STATE::DONE; // all_visited이면... DONE
                break;

            default :
                break;
        }
    }

    cout << MST_length << '\n';
}

bool MST::is_top_unvisited(){ // visit일 경우에 그냥 빼줘야 된다.
    return !visit_table[edge_pq.top().second];
}

void MST::update_datapath(){
    select_current_from_top();

    make_current_visited();

    compound_length_of_MST();

    push_edges_of_the_current();
}

void MST::select_current_from_top(){
    current = edge_pq.top();
    edge_pq.pop();
}

void MST::make_current_visited(){
    int current_vertice_number = current.second;
    visit_table[current_vertice_number] = true;
    how_many_visited++;
}

void MST::compound_length_of_MST(){
    int current_weight = current.first;
    MST_length += current_weight;
}

void MST::push_edges_of_the_current(){
    int current_vertice_number = current.second;
    vector<pair<int, int>> edges_of_current = edges[current_vertice_number];

    for(int i = 0; i < edges_of_current.size(); i++){
        edge_pq.push(edges_of_current[i]);
    }
}

bool MST::all_visited(){
    return (how_many_visited == edges.size() - 1); // edge는 원소가 총 vertice 개수 + 1만큼 있으므로!
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    int V, E;

    cin >> V >> E;

    MST m(V, E);

    m.solve();

	return 0;
}