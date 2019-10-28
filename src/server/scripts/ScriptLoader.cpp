/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#include "ScriptLoader.h"
#include "World.h"

void AddCommandsScripts();
void AddSpellsScripts();
void AddSC_SmartScripts();

#ifdef SCRIPTS
void AddWorldScripts();
void AddEasternKingdomsScripts();
void AddKalimdorScripts();
void AddOutlandScripts();
void AddNorthrendScripts();
void AddEventsScripts();
void AddPetScripts();
void AddOutdoorPvPScripts();
void AddCustomScripts();
#endif

void AddScripts()
{
    AddCommandsScripts();
    AddSpellsScripts();
    AddSC_SmartScripts();    
#ifdef SCRIPTS
    AddWorldScripts();
    AddEasternKingdomsScripts();
    AddKalimdorScripts();
    AddOutlandScripts();
    AddNorthrendScripts();
    AddEventsScripts();
    AddPetScripts();
    AddOutdoorPvPScripts();
    AddCustomScripts();
#endif
}