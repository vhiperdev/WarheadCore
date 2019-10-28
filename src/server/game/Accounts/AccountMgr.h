/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef _ACCMGR_H
#define _ACCMGR_H

#include "Define.h"
#include <string>

enum AccountOpResult
{
    AOR_OK,
    AOR_NAME_TOO_LONG,
    AOR_PASS_TOO_LONG,
    AOR_NAME_ALREDY_EXIST,
    AOR_NAME_NOT_EXIST,
    AOR_DB_INTERNAL_ERROR
};

#define MAX_ACCOUNT_STR 20
#define MAX_PASS_STR 16

namespace AccountMgr
{
    AC_GAME_API AccountOpResult CreateAccount(std::string username, std::string password);
    AC_GAME_API AccountOpResult DeleteAccount(uint32 accountId);
    AC_GAME_API AccountOpResult ChangeUsername(uint32 accountId, std::string newUsername, std::string newPassword);
    AC_GAME_API AccountOpResult ChangePassword(uint32 accountId, std::string newPassword);
    AC_GAME_API bool CheckPassword(uint32 accountId, std::string password);

    AC_GAME_API uint32 GetId(std::string const& username);
    AC_GAME_API uint32 GetSecurity(uint32 accountId);
    AC_GAME_API uint32 GetSecurity(uint32 accountId, int32 realmId);
    AC_GAME_API bool GetName(uint32 accountId, std::string& name);
    AC_GAME_API uint32 GetCharactersCount(uint32 accountId);
    AC_GAME_API std::string CalculateShaPassHash(std::string const& name, std::string const& password);

    AC_GAME_API bool normalizeString(std::string& utf8String);
    AC_GAME_API bool IsPlayerAccount(uint32 gmlevel);
    AC_GAME_API bool IsGMAccount(uint32 gmlevel);
    AC_GAME_API bool IsAdminAccount(uint32 gmlevel);
    AC_GAME_API bool IsConsoleAccount(uint32 gmlevel);
};

#endif
