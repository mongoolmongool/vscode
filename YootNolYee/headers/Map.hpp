#pragma once

#include "Position.hpp"
#include <memory>

class Map{
public :
    Map();
    ~Map();

    void draw();

    Position* position_0 = nullptr;
    Position* tail = nullptr;

    std::vector<Position*> get_positions();  

private :
    std::vector<Position*> positions; // 이렇게 안하고 싶었는데...
};