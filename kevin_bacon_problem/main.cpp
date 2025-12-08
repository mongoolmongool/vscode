#include <bits/stdc++.h>
using namespace std;

class Vertice{
public :
    Vertice() {}
    Vertice(int v_index, int num_of_vertices);
    ~Vertice();

    void compute_K_B();

    vector<Vertice*>& get_connected();
    vector<int>& get_path_table();
    int get_index() { return vertice_index; }

    vector<bool>& get_is_visited() { return is_visited;}

    int& get_dist() { return dist; }

    int get_K_B() { return K_B; }

    bool is_all_visited();

private :
    int vertice_index;
    vector<Vertice*> connected;
    int K_B = 0;
    vector<int> path_table;    
    vector<bool> is_visited;
    int dist;
};

Vertice::Vertice(int v_index, int num_of_vertices) {
    vertice_index = v_index;
    is_visited.resize(num_of_vertices);

    for(int i = 0; i < num_of_vertices; i++) {
        if(v_index == i) {
            path_table.push_back(0);
        }

        else {
            path_table.push_back(-1); // -1 means infinity!!!
        }

        is_visited[i] = false;
    }
}

Vertice::~Vertice() {
    for(int i = 0; i < connected.size(); i++) {
        connected[i] = nullptr;
    }
}

void Vertice::compute_K_B() {
    for(int i = 0; i < path_table.size(); i++) {
        K_B += path_table[i];
    }
}

vector<Vertice*>& Vertice::get_connected() {
    return connected;
}

vector<int>& Vertice::get_path_table() {
    return path_table;
}

bool Vertice::is_all_visited() {
    int a = 0;
    for(int i = 0; i < is_visited.size(); i++) {
        if(is_visited[i]) {
            a++;
        }
    }

    return (a == path_table.size());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Graph{
public :
    Graph() {}
    Graph(int num_of_vertices, vector<vector<int>> vertices);
    ~Graph();

    void dijkstra();

    void dijkstra_a_vertice(Vertice* v);
    void connect_vertices(vector<int> v);
    void update_dists_of_the_connected(Vertice* standard, Vertice* current);

    vector<Vertice*>& get_g() { return g; }

private :
    vector<Vertice*> g;
};

void Graph::dijkstra() {
    for(int i = 0; i < g.size(); i++) {
        dijkstra_a_vertice(g[i]);
        g[i]->compute_K_B();
    }
}

Graph::Graph(int num_of_vertices, vector<vector<int>> connection_of_vertices) {
    for(int i = 0; i < num_of_vertices; i++) {
        g.push_back(new Vertice(i, num_of_vertices));
    }

    for(int i = 0; i < connection_of_vertices.size(); i++) {
        connect_vertices(connection_of_vertices[i]);
    }
}

Graph::~Graph() {
    for(int i = 0; i < g.size(); i++) {
        delete g[i];
    }
}

void Graph::update_dists_of_the_connected(Vertice* standard, Vertice* current) {
    vector<Vertice*> v = current->get_connected();

    vector<int>& dist = standard->get_path_table();

    for(int i = 0; i < v.size(); i++) {
        if(dist[v[i]->get_index()] == -1 || dist[v[i]->get_index()] > dist[current->get_index()] + 1) {
            dist[v[i]->get_index()] = dist[current->get_index()] + 1;
        }
    }
}

void Graph::dijkstra_a_vertice(Vertice* v) {

    vector<int>& v_pt = v->get_path_table();

    Vertice* current_v = v;

    while(!v->is_all_visited()) {
        v->get_is_visited()[current_v->get_index()] = true;

        // vector<Vertice*> connected_vector = current_v->get_connected();

        update_dists_of_the_connected(v, current_v); ///// 여기서 type name is not allowed!!!!

        int smallest = 0;
        int idx;

        for(int i = 0; i < v_pt.size(); i++) {
            if(v_pt[i] == -1 || v_pt[i] == 0) {
                continue;
            }

            if(v->get_is_visited()[i]) {
                continue;
            }

            if(smallest == 0 || v_pt[i] < smallest) {
                smallest = v_pt[i];
                idx = i;
            }
        }

        current_v = g[idx];        
    }
}

void Graph::connect_vertices(vector<int> v) {
    int index1 = v[0] - 1;
    int index2 = v[1] - 1;

    vector<Vertice*> v1 = g[index1]->get_connected();
    vector<Vertice*> v2 = g[index2]->get_connected();

    bool is_there = (find(v1.begin(), v1.end(), g[index2]) != v1.end());

    // 중복으로 들어오는 경우 처리...
    if(!is_there) {
        g[index1]->get_connected().push_back(g[index2]);
        g[index2]->get_connected().push_back(g[index1]);
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int a;
    int b;

    cin >> a >> b;

    vector<vector<int>> v1;

    for(int i = 0; i < b; i++) {
        int c, d;
        cin >> c >> d ;

        vector<int> v2;
        v2.push_back(c);
        v2.push_back(d);

        v1.push_back(v2);
    }

    Graph g1(a, v1);
    g1.dijkstra();

    int minimum_K_B = g1.get_g()[0]->get_K_B();
    int m_K_B_idx = 0;
    
    for(int i = 0; i < g1.get_g().size(); i++) {
        if(g1.get_g()[i]->get_K_B() < minimum_K_B) {
            minimum_K_B = g1.get_g()[i]->get_K_B();
            m_K_B_idx = i;
        }
    }

    cout << m_K_B_idx + 1 << '\n';
}