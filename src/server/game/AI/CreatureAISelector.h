/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef ACORE_CREATUREAISELECTOR_H
#define ACORE_CREATUREAISELECTOR_H

#include "Define.h"

class CreatureAI;
class Creature;
class MovementGenerator;
class GameObjectAI;
class GameObject;

namespace FactorySelector
{
    AC_GAME_API CreatureAI* selectAI(Creature*);
    AC_GAME_API MovementGenerator* selectMovementGenerator(Creature*);
    AC_GAME_API GameObjectAI* SelectGameObjectAI(GameObject*);
}
#endif

