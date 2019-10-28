/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef CHARACTERDATABASECLEANER_H
#define CHARACTERDATABASECLEANER_H

namespace CharacterDatabaseCleaner
{
    enum CleaningFlags
    {
        CLEANING_FLAG_ACHIEVEMENT_PROGRESS  = 0x1,
        CLEANING_FLAG_SKILLS                = 0x2,
        CLEANING_FLAG_SPELLS                = 0x4,
        CLEANING_FLAG_TALENTS               = 0x8,
        CLEANING_FLAG_QUESTSTATUS           = 0x10
    };

    AC_GAME_API void CleanDatabase();

    AC_GAME_API void CheckUnique(const char* column, const char* table, bool (*check)(uint32));

    AC_GAME_API bool AchievementProgressCheck(uint32 criteria);
    AC_GAME_API bool SkillCheck(uint32 skill);
    AC_GAME_API bool SpellCheck(uint32 spell_id);
    AC_GAME_API bool TalentCheck(uint32 talent_id);

    AC_GAME_API void CleanCharacterAchievementProgress();
    AC_GAME_API void CleanCharacterSkills();
    AC_GAME_API void CleanCharacterSpell();
    AC_GAME_API void CleanCharacterTalent();
    AC_GAME_API void CleanCharacterQuestStatus();
}

#endif
