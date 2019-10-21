/*
* Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
* Copyright (C) 2008-2018 TrinityCore <http://www.trinitycore.org/>
*/

#ifndef __GITREVISION_H__
#define __GITREVISION_H__

#include "Define.h"

namespace GitRevision
{
    AC_COMMON_API char const* GetHash();
    AC_COMMON_API char const* GetDate();
    AC_COMMON_API char const* GetBranch();
    AC_COMMON_API char const* GetFullVersion();
    AC_COMMON_API char const* GetCompanyNameStr();
    AC_COMMON_API char const* GetLegalCopyrightStr();
    AC_COMMON_API char const* GetFileVersionStr();
    AC_COMMON_API char const* GetProductVersionStr();
}

#endif
