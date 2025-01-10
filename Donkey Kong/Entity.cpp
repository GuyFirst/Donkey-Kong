#include "Entity.h"
#include "gameConfig.h"
#include "Map.h"

bool Entity::isNearBoundry()
{
	if (m_diff_x == (int)gameConfig::Direction::POSITIVE)
		return map->originalMap[getPoint().getY()][getPoint().getX() + 1] == 'Q' || position.getX() >= gameConfig::GAME_WIDTH - 2;
	else
		return map->originalMap[getPoint().getY()][getPoint().getX() - 1] == 'Q' || (position.getX() <= 0);
}
