#include <bits/stdc++.h>
using namespace std;

int M; // 2 <= M <= 100, 상자 가로 길이
int N; // 2 <= N <= 100, 상자 세로 길이
int H; // 1 <= H <= 100, 상자 높이

class tomato{
public :
    enum class State { UNRIPE = 0, RIPE = 1, EMPTY = -1 };

    // constructors
    tomato(int x, int y, int z, int m, int n, int h, State s) : 
        pos_x(x), pos_y(y), pos_z(z), pos_one_dim(m*n*z + m*y + x), state(s) {}

    // getter functions
    State get_state();
    int get_pos_one_dim();

    // setter functions
    void make_ripe();

    // print functions
    void print_state();
    void print_neighbors_state();

private :
    State state;
    int pos_one_dim;
    int pos_x;
    int pos_y;
    int pos_z;
};

// getter functions
tomato::State tomato::get_state() {
    return state;
}

int tomato::get_pos_one_dim() {
    return pos_one_dim;
}

// setter functions
void tomato::make_ripe() {
    state = tomato::State::RIPE;
}

// print functions for test
void tomato::print_state() {
    std::cout << static_cast<int>(state);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class tomato_box{
public :
    tomato_box(int m, int n, int h);
    ~tomato_box();

    int solve();
    int solving_algorithm();
    bool let_us_have_a_good_day();
    int update_neighbors(int pos_one_dim);

    int get_pos_x(int pos_one_dim);
    int get_pos_y(int pos_one_dim);
    int get_pos_z(int pos_one_dim);

    int cal_one_dim(int x, int y, int z);
    

private :
    vector<vector<vector<tomato*>>> tomatoes;

    int num_of_empty;
    int num_of_visited_ripe;
    queue<int> unvisited_ripe_pos_one_dim;
    int w;
    int l;
    int h;
};

tomato_box::tomato_box(int m, int n, int h){

    num_of_empty = 0;
    num_of_visited_ripe = 0;

    this->w = m;
    this->l = n;
    this->h = h;

    int state_int_type;
    
    for(int k = 0; k < h; k++) {
        vector<vector<tomato*>> v2;
        for(int j = 0; j < n; j++) {
            vector<tomato*> v1;
            for(int i = 0; i < m; i++) {
                cin >> state_int_type;
                tomato::State state = static_cast<tomato::State>(state_int_type);
                v1.push_back(new tomato(i, j, k, m, n, h, state));
                if(state == tomato::State::EMPTY) num_of_empty++;
                if(state == tomato::State::RIPE) unvisited_ripe_pos_one_dim.push(v1.back()->get_pos_one_dim());
            }
            v2.push_back(v1);
        }
        tomatoes.push_back(v2);
    }
}

tomato_box::~tomato_box() {
    for(int k = 0; k < h; k++) {
        for(int j = 0; j < l; j++) {
            for(int i = 0; i < w; i++) {
                delete tomatoes[k][j][i];
            }
        }
    }
}

int tomato_box::solve() {
    int total_num_of_tomatoes = w * l * h;
    int num_of_unripen = total_num_of_tomatoes - num_of_empty - unvisited_ripe_pos_one_dim.size();

    if(num_of_unripen == 0) return 0;
    else return solving_algorithm();
}

int tomato_box::solving_algorithm() {
    int day = 0;
    while(let_us_have_a_good_day()) {
        day++;
    }

    int total_num_of_tomatoes = w * l * h;
    int num_of_unripen = total_num_of_tomatoes - num_of_empty - unvisited_ripe_pos_one_dim.size() - num_of_visited_ripe;

    if(num_of_unripen == 0) return day;
    else return -1;
}

bool tomato_box::let_us_have_a_good_day() {
    bool IS_UPDATED = 0;

    int num_of_process = unvisited_ripe_pos_one_dim.size();

    for(int i = 0; i < num_of_process; i++) {
        // int x = this->get_pos_x(unvisited_ripe_pos_one_dim[i]);
        // int y = this->get_pos_x(unvisited_ripe_pos_one_dim[i]);
        // int z = this->get_pos_x(unvisited_ripe_pos_one_dim[i]); 
        
        IS_UPDATED = (update_neighbors(unvisited_ripe_pos_one_dim.front()) | IS_UPDATED);
        unvisited_ripe_pos_one_dim.pop();
        num_of_visited_ripe++;
    }

    return IS_UPDATED;
}

int tomato_box::update_neighbors(int pos_one_dim) {
    // {x-1, y, z}, {x+1, y, z}, {x, y-1, z}, {x, y+1 ,z}, {x, y, z-1}, {x, y, z+1}을 update
    int x = this->get_pos_x(pos_one_dim);
    int y = this->get_pos_y(pos_one_dim);
    int z = this->get_pos_z(pos_one_dim); 

    int updated = 0;

    if(((x-1) >= 0) && (tomatoes[z][y][x-1]->get_state() == tomato::State::UNRIPE)){
        tomatoes[z][y][x-1]->make_ripe();
        unvisited_ripe_pos_one_dim.push(cal_one_dim(x-1, y, z));
        updated = 1;
    }

    if(((x+1) <= (w-1)) && (tomatoes[z][y][x+1]->get_state() == tomato::State::UNRIPE)) {
        tomatoes[z][y][x+1]->make_ripe();
        unvisited_ripe_pos_one_dim.push(cal_one_dim(x+1, y, z));
        updated = 1;
    }
    if(((y-1) >= 0) && (tomatoes[z][y-1][x]->get_state() == tomato::State::UNRIPE)){
        tomatoes[z][y-1][x]->make_ripe();
        unvisited_ripe_pos_one_dim.push(cal_one_dim(x, y-1, z));
        updated = 1;
    }
    if(((y+1) <= (l-1)) && (tomatoes[z][y+1][x]->get_state() == tomato::State::UNRIPE)){
        tomatoes[z][y+1][x]->make_ripe();
        unvisited_ripe_pos_one_dim.push(cal_one_dim(x, y+1, z));
        updated = 1;
    }
    if(((z-1) >= 0) && (tomatoes[z-1][y][x]->get_state() == tomato::State::UNRIPE)){ 
        tomatoes[z-1][y][x]->make_ripe();
        unvisited_ripe_pos_one_dim.push(cal_one_dim(x, y, z-1));
        updated = 1;
    }
    if(((z+1) <= (h-1)) && (tomatoes[z+1][y][x]->get_state() == tomato::State::UNRIPE)){
        tomatoes[z+1][y][x]->make_ripe();
        unvisited_ripe_pos_one_dim.push(cal_one_dim(x, y, z+1));
        updated = 1;
    }    

    return updated;
}

int tomato_box::get_pos_x(int pos_one_dim){
    return (pos_one_dim % (w * l)) % w;
}

int tomato_box::get_pos_y(int pos_one_dim){
    return (pos_one_dim % (w * l)) / w;
}

int tomato_box::get_pos_z(int pos_one_dim){
    return pos_one_dim / (w * l); 
}

int tomato_box::cal_one_dim(int x, int y, int z){
    return w*l*z + w*y + x;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);

    cin >> M >> N >> H;   

    tomato_box t(M, N, H);

    cout << t.solve() << '\n';  

    return 0;
}

