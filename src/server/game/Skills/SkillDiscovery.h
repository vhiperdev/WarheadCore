/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef TRINITY_SKILLDISCOVERY_H
#define TRINITY_SKILLDISCOVERY_H

#include "Common.h"

class Player;

AC_GAME_API void LoadSkillDiscoveryTable();
AC_GAME_API uint32 GetSkillDiscoverySpell(uint32 skillId, uint32 spellId, Player* player);
AC_GAME_API bool HasDiscoveredAllSpells(uint32 spellId, Player* player);
AC_GAME_API uint32 GetExplicitDiscoverySpell(uint32 spellId, Player* player);

#endif
