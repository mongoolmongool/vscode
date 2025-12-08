#include <bits/stdc++.h>
using namespace std;

class danger_detector{
public :
    void set_exp_string(string s);

    void operate(const bool& shift_ena, const bool& load_ena, const char* data);
    void shift(const char* data);
    void load(const char* data);

    bool is_dangerous_zone_equals_exp_string();

    // outputs
    bool is_detected;
    bool is_ready;
    bool is_completed;
    char front;
    // outputs

private :
    string exp_string;

    deque<char> dangerous_zone;
};

void danger_detector::set_exp_string(string s){
    exp_string = s;
}

void danger_detector::operate(const bool& shift_ena, const bool& load_ena, const char* data){
    if(shift_ena && !load_ena){
        shift(data);
    }

    else if(!shift_ena && load_ena){
        load(data);
    }

    else{
        is_detected = 0;
        is_ready = 0;
        is_completed = 0;
        front = '\0'; // null값, ASCII CODE로는 0
    }    
}

void danger_detector::shift(const char* data){
    is_detected = 0;
    is_ready = 0;
    is_completed = 0;

    // 받은 data가 없으면 completed 결정 시도, 있으면 바로 dz에 push_back
    if(!data) is_completed = (dangerous_zone.size() == 0); // data = nullptr
    else dangerous_zone.push_back(*data);
    ///////////////////////////////////////////////////////////////////

    // dz와 es의 size가 같으면 detected 되었는지 볼 가치가 있음.
    if(dangerous_zone.size() == exp_string.size()) is_detected = is_dangerous_zone_equals_exp_string(); // time complexity : O(M);
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // 이제 front를 결정할 차례
    if((dangerous_zone.size() == exp_string.size()) || (!(dangerous_zone.size() == 0) && (!data))){
        front = dangerous_zone.front();
        dangerous_zone.pop_front();
    }

    else front = '\0';
    // dz의 pop_front는 dangerous_zone.size == exp_string.size일때만 일어나야 한다.
}

bool danger_detector::is_dangerous_zone_equals_exp_string(){
    bool bomb = true;

    int i = 0;
    for(auto it = dangerous_zone.begin(); it != dangerous_zone.end(); it++){
        if((*it) != exp_string[i]) {
            bomb = false;
            break;
        }

        else i++;
    }

    if(bomb) dangerous_zone.clear();

    return bomb;
}

void danger_detector::load(const char* data){
    is_detected = 0;
    is_ready = 0;
    is_completed = 0;
    front = '\0';

    if(!data) is_ready = 1;

    else dangerous_zone.push_front(*data);

    if(dangerous_zone.size() == (exp_string.size() - 1)) is_ready = 1;
}

class string_after_explosion{
public :
    enum class STATE {IDLE = 0, DETECTING = 1, MOVE_SOME_CHARACTERS_TO_DD = 2, DONE = 3};
    string_after_explosion();

    void make_explosion();

    void controller();

private :
    string original_string;
    string safe_zone;

    STATE state;

    bool shift_ena;
    bool load_ena;
    bool done;

    danger_detector DD;

    char* current_character;
};

string_after_explosion::string_after_explosion(){    
    cin >> original_string;

    string es;
    cin >> es;
    DD.set_exp_string(es);

    shift_ena = false;
    load_ena = false;
    done = false;

    current_character = &original_string[0];

    state == STATE::IDLE;
}

void string_after_explosion::make_explosion(){
    controller(); // controller operation start!

    cout << safe_zone << '\n';
}

void string_after_explosion::controller(){
    // next_state and next_output logics
    while(!done){

        // 코드 정리할 때 control_dd 함수로 바꿀 block
        if(state == STATE::DETECTING){
            if(current_character != &(*original_string.end())){
                DD.operate(shift_ena, load_ena, current_character++); // current character가 end인 경우도 고려해야함.
                // current_character++;
            }

            else DD.operate(shift_ena, load_ena, nullptr);
        }

        // 아래 작업은 safe_zone.size가 0이거나, exp_string.size-1만큼 dangerous_zone이 채워질때까지
        // 후자는 dd에서 ready라는 신호로 가해지고, 전자는 control에서 처리. 아래 state transition에서 처리함.
        else if(state == STATE::MOVE_SOME_CHARACTERS_TO_DD){
            if(safe_zone.size() == 0) DD.operate(shift_ena, load_ena, nullptr);
            else{
                DD.operate(shift_ena, load_ena, &safe_zone.back()); // 처음부터 터져서 없는 경우도 생각해야함.
                safe_zone.pop_back();
            }
        }

        // front가 빈값이 아니면...
        if(DD.front != '\0') safe_zone += DD.front;

        // 코드 정리할 때 control_dd 함수로 바꿀 block

        // state_transition logic
        switch(state){
            case STATE::IDLE :
                state = STATE::DETECTING;
                shift_ena = true;
                break;

            case STATE::DETECTING :
                if(DD.is_completed){ // is_completed
                    state = STATE::DONE;
                    shift_ena = false;
                    load_ena = false;
                }

                else if(DD.is_detected){ // is_detected
                    state = STATE::MOVE_SOME_CHARACTERS_TO_DD;
                    shift_ena = false;
                    load_ena = true;
                }

                else state = STATE::DETECTING; // for readability!

                break;

            case STATE::MOVE_SOME_CHARACTERS_TO_DD :
                if(DD.is_ready){ // is_ready
                    state = STATE::DETECTING;
                    shift_ena = true;
                    load_ena = false;
                }

                else state = STATE::MOVE_SOME_CHARACTERS_TO_DD; // for readability!

                break;

            case STATE::DONE :
                if(safe_zone.empty()) safe_zone = "FRULA";
                done = true;
                break;

            default :
                break;
        }
    }
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    string_after_explosion sae;

    sae.make_explosion();

	return 0;
}