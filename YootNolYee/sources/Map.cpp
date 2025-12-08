#include "Map.hpp"
#include "Constants.hpp"

Map::Map() {
    // 총 27개의 Node를 모두 생성해 주어야함...
    position_0 = new Position(MAP_boundaryX * 5 / 7, -MAP_boundaryY * 5 / 7, Position::POS_TYPE::SENTINEL);

    tail = new Position(MAP_boundaryX + (boundaryX - MAP_boundaryX) / 2, MAP_boundaryY, Position::POS_TYPE::TAIL);
    position_0->get_nexts().push_back(tail);

    Position* position_1 = new Position(MAP_boundaryX * 5 / 7, -MAP_boundaryY * 3 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_0, position_1);

    Position* position_2 = new Position(MAP_boundaryX * 5 / 7, -MAP_boundaryY * 1 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_1, position_2);

    Position* position_3 = new Position(MAP_boundaryX * 5 / 7, MAP_boundaryY * 1 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_2, position_3);

    Position* position_4 = new Position(MAP_boundaryX * 5 / 7, MAP_boundaryY * 3 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_3, position_4);

    Position* position_5 = new Position(MAP_boundaryX * 5 / 7, MAP_boundaryY * 5 / 7, Position::POS_TYPE::TWO_WAY);
    make_relationship(position_4, position_5);

    Position* position_6 = new Position(MAP_boundaryX * 3 / 7, MAP_boundaryY * 5 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_5, position_6);

    Position* position_7 = new Position(MAP_boundaryX * 1 / 7, MAP_boundaryY * 5 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_6, position_7);

    Position* position_8 = new Position(-MAP_boundaryX * 1 / 7, MAP_boundaryY * 5 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_7, position_8);

    Position* position_9 = new Position(-MAP_boundaryX * 3 / 7, MAP_boundaryY * 5 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_8, position_9);

    Position* position_10 = new Position(-MAP_boundaryX * 5 / 7, MAP_boundaryY * 5 / 7, Position::POS_TYPE::TWO_WAY);
    make_relationship(position_9, position_10);

    Position* position_11 = new Position(-MAP_boundaryX * 5 / 7, MAP_boundaryY * 3 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_10, position_11);

    Position* position_12 = new Position(-MAP_boundaryX * 5 / 7, MAP_boundaryY * 1 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_11, position_12);

    Position* position_13 = new Position(-MAP_boundaryX * 5 / 7, -MAP_boundaryY * 1 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_12, position_13);

    Position* position_14 = new Position(-MAP_boundaryX * 5 / 7, -MAP_boundaryY * 3 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_13, position_14);

    Position* position_15 = new Position(-MAP_boundaryX * 5 / 7, -MAP_boundaryY * 5 / 7, Position::POS_TYPE::TWO_WAY);
    make_relationship(position_14, position_15);

    Position* position_16 = new Position(-MAP_boundaryX * 3 / 7, -MAP_boundaryY * 5 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_15, position_16);

    Position* position_17 = new Position(-MAP_boundaryX * 1 / 7, -MAP_boundaryY * 5 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_16, position_17);

    Position* position_18 = new Position(MAP_boundaryX * 1 / 7, -MAP_boundaryY * 5 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_17, position_18);

    Position* position_19 = new Position(MAP_boundaryX * 3 / 7, -MAP_boundaryY * 5 / 7, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_18, position_19);
    make_relationship(position_19, position_0);

    Position* position_20 = new Position(MAP_boundaryX * 10 / 21, MAP_boundaryY * 10 / 21, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_5, position_20);

    Position* position_21 = new Position(MAP_boundaryX * 5 / 21, MAP_boundaryY * 5 / 21, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_20, position_21); 

    Position* position_22 = new Position(0, 0, Position::POS_TYPE::TWO_WAY);
    make_relationship(position_21, position_22);

    Position* position_23 = new Position(-MAP_boundaryX * 5 / 21, MAP_boundaryY * 5 / 21, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_23, position_22);  

    Position* position_24 = new Position(-MAP_boundaryX * 10 / 21, MAP_boundaryY * 10 / 21, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_24, position_23);
    make_relationship(position_10, position_24);

    Position* position_25 = new Position(-MAP_boundaryX * 5 / 21, -MAP_boundaryY * 5 / 21, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_22, position_25);

    Position* position_26 = new Position(-MAP_boundaryX * 10 / 21, -MAP_boundaryY * 10 / 21, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_25, position_26);
    make_relationship(position_26, position_15);

    Position* position_27 = new Position(MAP_boundaryX * 5 / 21, -MAP_boundaryY * 5 / 21, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_22, position_27);
    
    Position* position_28 = new Position(MAP_boundaryX * 10 / 21, -MAP_boundaryY * 10 / 21, Position::POS_TYPE::ONE_WAY);
    make_relationship(position_27, position_28);
    make_relationship(position_28, position_0);

    // 얘네가 올바르게 연결되어 있는지에 대한 확인이 필요함

    positions.push_back(position_0);
    positions.push_back(position_1);
    positions.push_back(position_2);
    positions.push_back(position_3);
    positions.push_back(position_4);
    positions.push_back(position_5);
    positions.push_back(position_6);
    positions.push_back(position_7);
    positions.push_back(position_8);
    positions.push_back(position_9);
    positions.push_back(position_10);
    positions.push_back(position_11);
    positions.push_back(position_12);
    positions.push_back(position_13);
    positions.push_back(position_14);
    positions.push_back(position_15);
    positions.push_back(position_16);
    positions.push_back(position_17);
    positions.push_back(position_18);
    positions.push_back(position_19);
    positions.push_back(position_20);
    positions.push_back(position_21);
    positions.push_back(position_22);
    positions.push_back(position_23);
    positions.push_back(position_24);
    positions.push_back(position_25);
    positions.push_back(position_26);
    positions.push_back(position_27);
    positions.push_back(position_28);
    positions.push_back(tail);
}
    
Map::~Map() {
    for(int i = 0; i < positions.size(); i++) {
        delete positions[i];
    }
}

std::vector<Position*> Map::get_positions() {
    return positions;
}

void Map::draw() {

    glPushMatrix();
    glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_POLYGON);
	glVertex2f(MAP_boundaryX, MAP_boundaryY);
	glVertex2f(-MAP_boundaryX, MAP_boundaryY);
	glVertex2f(-MAP_boundaryX, -MAP_boundaryY);
	glVertex2f(MAP_boundaryX, -MAP_boundaryY);
	glEnd();
    glPopMatrix();

    for(int i = 0; i < positions.size(); i++) {
        positions[i]->draw();
    }



    // position_0->draw(); // recursively called..
}