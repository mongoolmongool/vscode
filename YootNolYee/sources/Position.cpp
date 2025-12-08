#include "Position.hpp"
#include <algorithm>

Position::Position(float x, float y, POS_TYPE type) {
    center[0] = x; center[1] = y; pos_type = type; deleted = false;
    if(pos_type == POS_TYPE::SENTINEL || pos_type == POS_TYPE::TWO_WAY) {
        size = 70.f;
        color[0] = 0.0f; color[1] = 1.0f; color[2] = 0.0f;
    }

    else if(pos_type == POS_TYPE::TAIL) {
        size = 50.f;
        color[0] = 1.0f, color[1] = 0.75f, color[2] = 0.8f;
        nexts.push_back(this);
        prevs.push_back(this);
    }

    else {
        size = 50.f;
        color[0] = 1.0f; color[1] = 1.0f; color[2] = 0.0f;
    }
}

Position::~Position() {
    // deleted = true;
    for(int i = 0; i < nexts.size(); i++) {
        nexts[i] = nullptr;
    }

    for(int i = 0; i < prevs.size(); i++) {
        prevs[i] = nullptr;
    }

    for(auto it = current_pieces.begin(); it != current_pieces.end(); it++) {
        delete (*it);
    }
    // // std::cout << "A Position Deleted" << '\n'; // ONLY FOR DEBUGGING!!
    // if(nexts[0] && nexts[0]->pos_type != POS_TYPE::SENTINEL) { // 다음 POSITION이 SENTINEL TYPE이 아니면
    //     for(int i = 0; i < nexts.size(); i++) {   // RECURSIVE하게 다음 POSITION도 delete
    //         if(!nexts[i]->Is_deleted()) {
    //             delete nexts[i];
    //         }
    //     }
    // }
}

void Position::set_center(float x, float y) {
    center[0] = x; center[2] = y;
}

float& Position::get_center() {
    return center[2];
}
    
float& Position::operator[](const int i) {
    return center[i];
}

std::vector<Position*>& Position::get_prevs() {
    return prevs;
}
    
std::vector<Position*>& Position::get_nexts() {
    return nexts;
}

std::list<Piece*>& Position::get_current_pieces() {
    return current_pieces;
}

bool Position::Is_deleted() {
    return deleted;
}

Position* Position::search(float x, float y) {
    if(center[0] + size / 2.f >= x && center[0] - size / 2.f <= x &&
        center[1] + size / 2.f >= y && center[1] - size / 2.f <= y) {
        return this;
    }
    
    for(int i = 0; i < nexts.size(); i++) {
        return nexts[i]->search(x, y);
    }    

    return this;
}

float Position::get_size() {
    return size;
}

void Position::toss_a_piece(Position* destination) {
    // 아주 중대한 예외처리!!! piece_type과 team_number가 고려되어야 한다.
    // 근데 아래 처럼 하면 sentinel의 ongoing piece들이 tail로 들어오지 못하는 경우가 발생했다.

    // 하나라도 initial이 있으면 initial만 움직이고
    // 모두 on_going이라면 원래대로 움직일 수 있게 하면 될것!
    bool is_there_initial_piece = false;
    
    for(auto it = current_pieces.begin(); it != current_pieces.end(); it++) {
        if((*it)->piece_type == Piece::PIECE_TYPE::INITIAL) {
            is_there_initial_piece = true;
        }
    }

    if(is_there_initial_piece) {
        for(auto it = current_pieces.begin(); it != current_pieces.end();) {
            if((*it)->piece_type == Piece::PIECE_TYPE::INITIAL) {
                destination->get_current_pieces().push_back(*it);
                (*it)->get_current_position() = destination;
                it = current_pieces.erase(it);
            }

            else{
                it++;
            }
        }
    }

    else {
        while(!current_pieces.empty()) {
            Piece* front_piece = this->current_pieces.front();
            this->current_pieces.pop_front();
            destination->get_current_pieces().push_back(front_piece);
            front_piece->get_current_position() = destination;
        }   
    }



    // if(pos_type == POS_TYPE::SENTINEL) {
    //     for(auto it = current_pieces.begin(); it != current_pieces.end();) {
    //         if((*it)->piece_type == Piece::PIECE_TYPE::INITIAL) {
    //             destination->get_current_pieces().push_back(*it);
    //             (*it)->get_current_position() = destination;
    //             it = current_pieces.erase(it);
    //         }

    //         else{
    //             it++;
    //         }
    //     }
    // }

    // else {
    //     while(!current_pieces.empty()) {
    //         Piece* front_piece = this->current_pieces.front();
    //         this->current_pieces.pop_front();
    //         destination->get_current_pieces().push_back(front_piece);
    //         front_piece->get_current_position() = destination;
    //     }
    // }
}

void Position::give_pieces_to_team(Team* destination) {
    while(!current_pieces.empty()) {
        Piece* front_piece = this->current_pieces.front();
        this->current_pieces.pop_front();
        destination->get_current_pieces().push_back(front_piece);
        front_piece->piece_type = Piece::PIECE_TYPE::INITIAL;
    }
}

void Position::draw() {

	glPushMatrix();

    // glColor3f(color[0], color[1], color[2]);

	// glBegin(GL_QUADS);
	// glVertex2d(center[0] - size / 2.0f, center[1] + size / 2.0f);
	// glVertex2d(center[0] + size / 2.0f, center[1] + size / 2.0f);
	// glVertex2d(center[0] + size / 2.0f, center[1] - size / 2.0f);
	// glVertex2d(center[0] - size / 2.0f, center[1] - size / 2.0f);
    // glEnd();

    glColor3f(0.f, 0.f, 0.f);
    glBegin(GL_LINE_LOOP);
	glVertex2d(center[0] - size / 2.0f, center[1] + size / 2.0f);
	glVertex2d(center[0] + size / 2.0f, center[1] + size / 2.0f);
	glVertex2d(center[0] + size / 2.0f, center[1] - size / 2.0f);
	glVertex2d(center[0] - size / 2.0f, center[1] - size / 2.0f);
    glEnd();



    glPopMatrix();

    if(pos_type == POS_TYPE::TAIL) {
        float dist = (MAP_HEIGHT / (current_pieces.size() + 1));
        float centerX = center[0];
        int i = 1;
        for(auto it = current_pieces.begin(); it != current_pieces.end(); it++) {
            float centerY = MAP_boundaryY - dist * i;
            (*it)->draw(centerX, centerY);
            i++;
        }
    }

    else{
        for (auto it = current_pieces.begin(); it != current_pieces.end(); it++) {
            (*it)->draw();
        }
    }
}

void make_relationship(Position* prev, Position* next) {
    prev->get_nexts().push_back(next);
    next->get_prevs().push_back(prev);
}