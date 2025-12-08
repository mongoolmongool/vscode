#include <bits/stdc++.h>
using namespace std;

class robovac{
public :
    enum class DIRECTION {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
    enum class STATE {CHECK_CLEANED = 0, CHECK_NEARBY = 1, CHECK_WALL = 2, NEARBY_DIRTY = 3, DONE = 4};

    robovac(int n, int m, int r, int c, int d);

    int do_clean();

    void check_cleaned();
    void check_nearby();
    void check_wall();
    void nearby_dirty(); 

    int detector(int x);

    void drive_back();
    void drive_front();

    void rotate_counterclockwise_ninty();

private :
    vector<vector<int>> room;

    DIRECTION direction;
    STATE state;

    int row; // row_of_robovac
    int column; // column_of_robovac
    int clean_count; // how many does robovac clean rooms?
};

robovac::robovac(int n, int m, int r, int c, int d){
    row = r;
    column = c;
    direction = static_cast<robovac::DIRECTION>(d);
    clean_count = 0;
    state = robovac::STATE::CHECK_CLEANED;

    for(int i = 0; i < n; i++){
        vector<int> row_of_room;
        for(int j = 0; j < m; j++){
            int row_data;
            cin >> row_data;
            row_of_room.push_back(row_data);            
        }
        room.push_back(row_of_room);
    }
    // room[n][m]으로 room에 접근할 수 있음.
}

int robovac::do_clean(){
    while(state != robovac::STATE::DONE){
        switch(state){
            case robovac::STATE::CHECK_CLEANED :
                check_cleaned();
                break;

            case robovac::STATE::CHECK_NEARBY :
                check_nearby();
                break;

            case robovac::STATE::CHECK_WALL :
                check_wall();
                break;

            case robovac::STATE::NEARBY_DIRTY :
                nearby_dirty();
                break;
        
            default :
                break;
        }
    }

    return clean_count;   
}

void robovac::check_cleaned(){
    if(room[row][column] == 0){ // not_cleaned
        room[row][column] = -1; // make it clean
        clean_count++;
    }
    state = robovac::STATE::CHECK_NEARBY;
}

void robovac::check_nearby(){
    bool cleaning_needed = false;

    for(int i = 0; i < 4; i++){
        if(detector(i) == 0) {
            cleaning_needed = true;
            break;
        }
    }

    if(cleaning_needed) state = robovac::STATE::NEARBY_DIRTY;
    else state = robovac::STATE::CHECK_WALL;
}

int robovac::detector(int i){ // 범용으로 만들 수 있을 듯, 그냥 방 한칸의 값을 받아서 0인지, 1인지, -1인지....
    // i means relative direction front = 0, right = 1, back = 2, left = 3
    int block_state;

    // clockwise
    int absolute_direction = (static_cast<int>(direction) + i) % 4; // absolute direction, north,east,south,west
    // i -> relative direction front,right,back,left

    switch(absolute_direction){
        case 0 : // north
            block_state = room[row-1][column];
            break;

        case 1 : // east
            block_state = room[row][column+1];
            break;

        case 2 : // south
            block_state = room[row+1][column];
            break;

        case 3 : // west
            block_state = room[row][column-1];
            break;
        default :
            break;    
    }

    return block_state;
}

void robovac::check_wall(){
    if(detector(2) == 1) state = robovac::STATE::DONE; // 뒤 칸이 벽
    else{
        drive_back(); // 후진
        state = robovac::STATE::CHECK_NEARBY;
    }
}

void robovac::drive_back(){
    switch(direction){
        case robovac::DIRECTION::NORTH :
            row++;
            break;
        
        case robovac::DIRECTION::EAST :
            column--;
            break;

        case robovac::DIRECTION::SOUTH :
            row--;
            break;

        case robovac::DIRECTION::WEST :
            column++;
            break;

        default :
            break;
    }
}

void robovac::drive_front(){
    switch(direction){
        case robovac::DIRECTION::NORTH :
            row--;
            break;
        
        case robovac::DIRECTION::EAST :
            column++;
            break;

        case robovac::DIRECTION::SOUTH :
            row++;
            break;

        case robovac::DIRECTION::WEST :
            column--;
            break;

        default :
            break;
    }
}

void robovac::nearby_dirty(){
    rotate_counterclockwise_ninty();
    if(detector(0) == 0){
        drive_front();
        state = robovac::STATE::CHECK_CLEANED;
    }   

    // else... 상태 유지
}

void robovac::rotate_counterclockwise_ninty(){
    int int_direction = static_cast<int>(direction);
    int_direction = (int_direction + 3) % 4;
    direction = static_cast<robovac::DIRECTION>(int_direction);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    int N, M, R, C, D;

    cin >> N >> M >> R >> C >> D;

    robovac r(N, M, R, C, D);

    cout << r.do_clean() << '\n';

	return 0;
}