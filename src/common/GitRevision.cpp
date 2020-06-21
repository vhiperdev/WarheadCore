/*
* Copyright (C) 2016+     WarheadCore <www.Warheadcore.org>
* Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
*/

#include "GitRevision.h"
#include "revision.h"

char const* GitRevision::GetHash()
{
    return _HASH;
}

char const* GitRevision::GetDate()
{
    return _DATE;
}

char const* GitRevision::GetBranch()
{
    return _BRANCH;
}

char const* GitRevision::GetCMakeCommand()
{
    return _CMAKE_COMMAND;
}

char const* GitRevision::GetCMakeVersion()
{
    return _CMAKE_VERSION;
}

char const* GitRevision::GetHostOSVersion()
{
    return _CMAKE_HOST_SYSTEM;
}

char const* GitRevision::GetBuildDirectory()
{
    return _BUILD_DIRECTORY;
}

char const* GitRevision::GetSourceDirectory()
{
    return _SOURCE_DIRECTORY;
}

char const* GitRevision::GetMySQLExecutable()
{
    return _MYSQL_EXECUTABLE;
}

#if WH_PLATFORM == WH_PLATFORM_WINDOWS
#  ifdef _WIN64
#    define Warhead_PLATFORM_STR "Win64"
#  else
#    define Warhead_PLATFORM_STR "Win32"
#  endif
#else // WH_PLATFORM
#  define Warhead_PLATFORM_STR "Unix"
#endif

char const* GitRevision::GetFullVersion()
{
    return VER_COMPANYNAME_STR " rev. " VER_PRODUCTVERSION_STR " (" Warhead_PLATFORM_STR ", " _BUILD_DIRECTIVE ")";
}

char const* GitRevision::GetCompanyNameStr()
{
    return VER_COMPANYNAME_STR;
}

char const* GitRevision::GetLegalCopyrightStr()
{
    return VER_LEGALCOPYRIGHT_STR;
}

char const* GitRevision::GetFileVersionStr()
{
    return VER_FILEVERSION_STR;
}

char const* GitRevision::GetProductVersionStr()
{
    return VER_PRODUCTVERSION_STR;
}
