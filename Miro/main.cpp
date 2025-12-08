#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> read_maze_data(int num_of_row, int num_of_col) {
    vector<vector<int>> data;
    
    vector<int> zeros(num_of_col + 1); // for indexing... index starts with 1, not 0.
    data.push_back(zeros);

    for(int i = 0; i < num_of_row; i++) {
        vector<int> row_data;
        row_data.push_back(0); // for indexing... index starts with 1, not 0;

        string s;
        cin >> s;

        for(char c : s) {
            int num = c - '0';
            row_data.push_back(num);
        }

        data.push_back(row_data);
    }

    return data;
}

void print_maze(vector<vector<int>> mz, int r, int c) {
    cout << '\n';

    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= c; j++) {
            cout << mz[i][j];
        }

        cout << '\n';
    }
}

class Vertice{
public :
    Vertice() {}
    Vertice(int a);
    ~Vertice();

    int get_pos() { return pos; }

    vector<Vertice*>& get_v_ptr() { return v_ptr; }

private :
    int pos;
    vector<Vertice*> v_ptr;
};

Vertice::Vertice(int a) {
    pos = a;
}

Vertice::~Vertice() {
    for(auto it = v_ptr.begin(); it != v_ptr.end(); it++) {
        (*it) = nullptr;
    }
}

class Graph{
public :
    Graph() {}
    Graph(vector<vector<int>> data); 
    ~Graph();  

    void update_v_ptr(Vertice* v1, Vertice* v2); 
    
    void print();

    // key function [TODO]
    int shortest_path();

private :
    unordered_map<int, Vertice*> all_vertices; // hashtable

    int destination;
};

//// TODO ////
int Graph::shortest_path() {
    // hashtable 두개 만들어
    // 거기다가 all_vertices의 <pos, int dist>
    // 그리고 all_vertices의 <pos, bool visited>로 만들고
    unordered_map<int, int> dist;
    unordered_map<int, bool> visited;

    // (1, 0), 나머지 (pos, -1)
    // (pos, false)
    for(auto it = all_vertices.begin(); it != all_vertices.end(); it++) {
        if(it->first == 1) {
            dist[it->first] = 0;
        }

        else {
            dist[it->first] = -1; // -1 means infinity!
        }

        visited[it->first] = false;
    }
    
    // 이제 dijkstra_algorithm 실행
    // 기준 vertice는 언제나 1, destination은 언제나 destination
    // current만 잘 잡아주자.
    int visit_count = 0;
    Vertice* current = all_vertices[1];
    vector<int> next_pos_candidates; // 다음 current를 고르기 위한 벡터. unvisited이나, dist != -1인 pos들의 모음.
    next_pos_candidates.push_back(1);

    while(visit_count != all_vertices.size()) {
        // av[1] = true;
        visited[current->get_pos()] = true;
        visit_count++;
        for(int i = 0; i < next_pos_candidates.size(); i++) {
            if(next_pos_candidates[i] == current->get_pos()) {
                next_pos_candidates.erase(next_pos_candidates.begin() + i);
            }
        }

        // 다음 것들 distance update(current까지의 dist + 1 < 기록된 dist인 경우)
        // 여기서 v_ptr을 이용한다.
        vector<Vertice*> neighbor = current->get_v_ptr();

        for(auto n : neighbor) {
            if(dist[n->get_pos()] == -1 || dist[current->get_pos()] + 1 < dist[n->get_pos()]){
                dist[n->get_pos()] = dist[current->get_pos()] + 1;
                next_pos_candidates.push_back(n->get_pos());
            }
        }

        // 이제 다음 current를 골라주어야 한다.
        // int min_dist = dist[next_pos_candidates[0]];
        int min_pos = next_pos_candidates[0];

        for(auto c : next_pos_candidates) {
            if(dist[c] < dist[min_pos]) {
                min_pos = c;
            }
        }

        current = all_vertices[min_pos];        
    }

    // return dist(destination)
    return dist[destination] + 1;
    // WARNING!!!
    // why + 1?? we should find the number of the blocks that we get through.
    // unordered map, dist means distances from pos(1)~pos(destination)
    // so we need +1 if we want to find blocks we get through!
}

Graph::~Graph() {
    for(auto it = all_vertices.begin(); it != all_vertices.end();) {
        delete it->second;
        it = all_vertices.erase(it);
    }
}

// all_vertices[pos - 1] 존재시 all_vertices[pos]와 connect
// all-vertices[pos - N] 존재시 all_vertices[pos]와 connect
void Graph::update_v_ptr(Vertice* v1, Vertice* v2) {
    v1->get_v_ptr().push_back(v2);
    v2->get_v_ptr().push_back(v1);
}

Graph::Graph(vector<vector<int>> data) {
    int M = data.size() - 1; // 행의 개수
    int N = data[0].size() - 1; // 열의 개수

    destination = M * N; // dijkstra용

    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {

            if(data[i][j] == 1) {
                int pos = N * (i - 1) + j; // !! very important!!!
                // position을 하나의 integer로 mapping 한 것임!

                Vertice* v = new Vertice(pos);

                all_vertices[pos] = v;

                if(data[i][j - 1] == 1) {
                    Vertice* a = all_vertices[pos];
                    Vertice* b = all_vertices[pos - 1];
                    
                    update_v_ptr(a, b); // connect
                }

                if(data[i - 1][j] == 1) {
                    Vertice* a = all_vertices[pos];
                    Vertice* b = all_vertices[pos - N];
                    
                    update_v_ptr(a, b); // connect
                }
            }
        }
    }
}


int main() {
    int M, N;
    cin >> M >> N;

    vector<vector<int>> maze;

    maze = read_maze_data(M, N);

    Graph g(maze); // maze ----> graph

    //cout << graph.shortest_path();
    cout << g.shortest_path() << '\n';

    return 0;
}