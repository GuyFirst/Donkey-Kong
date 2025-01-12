#pragma once
#include <vector>
#include "Point.h"
#include "Map.h"
#include "gameConfig.h"
#include <iostream>
#include "Entity.h"

class Ghost : public Entity {
public:
    Ghost(Map* map, int m_id, Point startingPosition)
        : Entity(startingPosition, 'x', 
            (int)gameConfig::Direction::POSITIVE, (int)gameConfig::Direction::STAY, map), 
        m_id(m_id), 
        startingPosition(startingPosition) {
    } 

  
    void move(std::vector<Ghost>& Ghosts);
    void reset();
 

private:
    int m_id; 
    Point startingPosition; 
    void handleCollision(std::vector<Ghost>& Ghosts);
    void handleDirectionChange();
    bool isNearOtherGhosts(const std::vector<Ghost>& Ghosts) const;
};
