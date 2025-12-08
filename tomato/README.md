// 제한 시간은 1초 -> 10^8 개의 연산이 필요하고 O(N^3)까지도 가능함...

int mapping_one_dim(int x, int y, int z, int n, int m){ // n은 row 개수, m은 column 개수
    return (m + 2) * (n + 2) * z + (m + 2) * y + x;
}

class tomato{
public :
    enum class State { UNRIPE = 0, RIPE = 1, EMPTY = -1 };
    tomato(int p, State s = State::EMPTY) : pos(p), state(s), day(-1) {}
    ~tomato() {
        for(auto it = adj.begin(); it != adj.end(); it++) {
            (*it) = nullptr;
        }
    }

    void set_state(int s) { state = static_cast<State>(s); }

    
    int get_state() { return static_cast<int>(state); }
    int get_pos() { return pos; }
    int& get_day() { return day; }
    vector<tomato*>& get_adj() { return adj; }

private :  
    int pos; // one-dim
    vector<tomato*> adj; // state == RIPE일때만 adj가 존재함.
    State state;
    int day;
};

class tomato_box{
public :
    tomato_box(int m, int n, int h);
    ~tomato_box();
    int tomato_update(); // update가 되었으면 1, 아니면 0..


    int answer();

    vector<tomato*>& get_unvis() { return unvis; }
    vector<tomato*>& get_who_has_adj() { return who_has_adj; }

    int set_adj(tomato* t) {
        int pos = t->get_pos();
        int u = 0;
        if(box[pos - 1]->get_state() == 0) {
            t->get_adj().push_back(box[pos - 1]);
            u = 1;
        }
        if(box[pos + 1]->get_state() == 0) {
            t->get_adj().push_back(box[pos + 1]);
            u = 1;
        }
        if(box[pos - (M + 2)]->get_state() == 0) {
            t->get_adj().push_back(box[pos - (M + 2)]);
            u = 1;
        }
        if(box[pos + (M + 2)]->get_state() == 0) {
            t->get_adj().push_back(box[pos + (M + 2)]);
            u = 1;
        }
        if(box[pos - (M + 2) * (N + 2)]->get_state() == 0) {
            t->get_adj().push_back(box[pos - (M + 2) * (N + 2)]);
            u = 1;
        }
        if(box[pos + (M + 2) * (N + 2)]->get_state() == 0) {
            t->get_adj().push_back(box[pos + (M + 2) * (N + 2)]);
            u = 1;
        }

        return u;
    }

    void print();

private :
    int row;
    int column;
    int height;

    vector<tomato*> unvis;
    map<int, tomato*> box;
    vector<tomato*> who_has_adj;
};

tomato_box::tomato_box(int m, int n, int h) { 
	row = n; column = m; height = h; 
    vector<tomato*> candidates;
	// k = 0.... 경계 처리 
	for(int j = 0; j < n + 2; j++) { 
		for(int i = 0; i < m + 2; i++) { 
			box[mapping_one_dim(i, j, 0, n, m)] = new tomato(mapping_one_dim(i, j, 0, n, m)); 
		} 
	} 
	
	// 1 <= k <= height 
	for(int k = 1; k <= height; k++) { 
		// 경계 처리
		for(int i = 0; i < m + 2; i++) { 
			box[mapping_one_dim(i, 0, k, n, m)] = new tomato(mapping_one_dim(i, 0, k, n, m)); 
		} 
		for(int j = 1; j <= n; j++) { 
			// 경계 
			box[mapping_one_dim(0, j, k, n, m)] = new tomato(mapping_one_dim(0, j, k, n, m)); 
			// 실제 tomatoes.... 
			for(int i = 1; i <= m; i++) { 
				int r; cin >> r; 
				box[mapping_one_dim(i, j, k, n, m)] = new tomato(mapping_one_dim(i, j, k, n, m), static_cast<tomato::State>(r));
                
                if(r == 0) {
                    unvis.push_back(box[mapping_one_dim(i, j, k, n, m)]);
                }

                else if(r == 1) {
                    candidates.push_back(box[mapping_one_dim(i, j, k, n, m)]);
                    box[mapping_one_dim(i, j, k, n, m)]->get_day() = 0;

                }
			} 
			// 경계 
			box[mapping_one_dim(m + 1, j, k, n, m)] = new tomato(mapping_one_dim(m + 1, j, k, n, m)); 
		} 
		// 경계 처리 
		for(int i = 0; i < m + 2; i++) { 
			box[mapping_one_dim(i, n + 1, k, n, m)] = new tomato(mapping_one_dim(i, n + 1, k, n, m)); 
		} 
	} 
	// k = height + 1.... 경계 처리 
	for(int j = 0; j < n + 2; j++) { 
		for(int i = 0; i < m + 2; i++) { 
			box[mapping_one_dim(i, j, h + 1, n, m)] = new tomato(mapping_one_dim(i, j, h + 1, n, m)); 
		} 
	}

    for(int a = 0; a < candidates.size(); a++) {
        int pos = candidates[a]->get_pos();
        // candidates[a]의 neighbor를 search하고, 있으면
        if(box[pos - 1]->get_state() == 0) {
            box[pos]->get_adj().push_back(box[pos - 1]);
            who_has_adj.push_back(box[pos]);
        }
        if(box[pos + 1]->get_state() == 0) {
            box[pos]->get_adj().push_back(box[pos + 1]);
            who_has_adj.push_back(box[pos]);
        }
        if(box[pos - (M + 2)]->get_state() == 0) {
            box[pos]->get_adj().push_back(box[pos - (M + 2)]);
            who_has_adj.push_back(box[pos]);
        }
        if(box[pos + (M + 2)]->get_state() == 0) {
            box[pos]->get_adj().push_back(box[pos + (M + 2)]);
            who_has_adj.push_back(box[pos]);
        }
        if(box[pos - (M + 2) * (N + 2)]->get_state() == 0) {
            box[pos]->get_adj().push_back(box[pos - (M + 2) * (N + 2)]);
            who_has_adj.push_back(box[pos]);
        }
        if(box[pos + (M + 2) * (N + 2)]->get_state() == 0) {
            box[pos]->get_adj().push_back(box[pos + (M + 2) * (N + 2)]);
            who_has_adj.push_back(box[pos]);
        }

        // who_has_unvis_adj에 pushback....
    }
}

tomato_box::~tomato_box() {
    for(auto it = unvis.begin(); it != unvis.end(); it++) {
        (*it) = nullptr;
    }

    for(auto it = who_has_adj.begin(); it != who_has_adj.end(); it++) {
        (*it) = nullptr;
    }

    for(auto it = box.begin(); it != box.end(); it++) {
        delete it->second;
    }
}
void tomato_box::print() {
    for(auto it = box.begin(); it != box.end(); it++) {
        cout << it->second->get_state() << " ";

        if((it->first + 1) % (column + 2) == 0) cout << '\n';
        if((it->first + 1) % ((column + 2) * (row + 2)) == 0) cout << '\n';
    }
}

int tomato_box::tomato_update() {
    int u = 0;
    vector<tomato*> new_adj;
    for(auto it = who_has_adj.begin(); it != who_has_adj.end(); it++) {

        for(int b = 0; b < (*it)->get_adj().size(); b++) {
            if((*it)->get_adj()[b]->get_state() == 0) {
                (*it)->get_adj()[b]->set_state(1);
                auto it2 = find(unvis.begin(), unvis.end(), (*it)->get_adj()[b]);
                unvis.erase(it2);
                (*it)->get_adj()[b]->get_day() = (*it)->get_day() + 1;
                if(set_adj((*it)->get_adj()[b])) new_adj.push_back((*it)->get_adj()[b]);

                u = 1;
            }
        }        
    }

    who_has_adj = new_adj;


    // for(auto it = unvis.begin(); it != unvis.end();) {
    //     int target = (*it)->get_pos();

    //     if(box[target - 1]->get_state() == 1 || box[target + 1]->get_state() == 1 || box[target - (M + 2)]->get_state() == 1
    //         || box[target + (M + 2)]->get_state() == 1 || box[target - (M + 2) * (N + 2)]->get_state() == 1 
    //         || box[target + (M + 2) * (N + 2)]->get_state() == 1) {
    //             (*it)->set_state(1);
    //             unvis.erase(it);
    //             u = 1;
    //         }

    //     else it++;
    // }

    return u;
    
}

int tomato_box::answer() {

    int update_count = 0;

    while(this->tomato_update()) {
        update_count++;
    }

    if(unvis.size() == 0) return update_count;
    else return -1;
}