/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#include "Config.h"
#include "Errors.h"
#include "Log.h"
#include <Poco/AutoPtr.h>
#include <Poco/Util/PropertyFileConfiguration.h>
#include <Poco/Util/LayeredConfiguration.h>
#include <memory>

using Poco::AutoPtr;
using Poco::Util::LayeredConfiguration;

AutoPtr<LayeredConfiguration> _configs;

ConfigMgr* ConfigMgr::instance()
{
    static ConfigMgr instance;
    return &instance;
}

void ConfigMgr::AddConfigFile(std::string const& file, bool enableDist /*= true*/)
{
    auto const itr = _configFiles.find(file);
    if (itr != _configFiles.end())
    {
        SYS_LOG_ERROR("Config file (%s) is exist", file.c_str());
        return;
    }

    _configFiles.insert(std::make_pair(file, enableDist));
}

bool ConfigMgr::Load()
{
    std::lock_guard<std::mutex> lock(_configLock);

    if (_configFiles.empty())
    {
        SYS_LOG_ERROR("Config files is empty");
        return false;
    }

    _configs = new LayeredConfiguration();   

    for (auto const& itr : _configFiles)
    {
        try
        {
            if (itr.second)
                _configs->addFront(new Poco::Util::PropertyFileConfiguration(itr.first + ".dist"));

            _configs->addFront(new Poco::Util::PropertyFileConfiguration(itr.first));
        }
        catch (const Poco::Exception& e)
        {
            SYS_LOG_ERROR("Error at loading config - %s", e.displayText().c_str());
            return false;
        }
    }

    return true;
}

bool ConfigMgr::Reload()
{
    _configs.reset();

    if (Load())
        return true;

    return false;
}

std::string ConfigMgr::GetStringDefault(std::string const& name, const std::string& def) const
{
    auto key = def;

    try
    {
        key = _configs->getString(name);
    }
    catch (const Poco::Exception& e)
    {
        SYS_LOG_ERROR("Error at get config option - %s", e.displayText().c_str());
    }

    return key;
}

bool ConfigMgr::GetBoolDefault(std::string const& name, bool def) const
{
    auto key = def;

    try
    {
        key = _configs->getBool(name);
    }
    catch (const Poco::Exception& e)
    {
        SYS_LOG_ERROR("Error at get config option - %s", e.displayText().c_str());
    }

    return key;
}

int ConfigMgr::GetIntDefault(std::string const& name, int def) const
{
    auto key = def;

    try
    {
        key = _configs->getInt(name);
    }
    catch (const Poco::Exception& e)
    {
        SYS_LOG_ERROR("Error at get config option - %s", e.displayText().c_str());
    }

    return key;
}

float ConfigMgr::GetFloatDefault(std::string const& name, float def) const
{
    auto key = def;

    try
    {
        key = static_cast<float>(_configs->getDouble(name));
    }
    catch (const Poco::Exception& e)
    {
        SYS_LOG_ERROR("Error at get config option - %s", e.displayText().c_str());
    }

    return key;
}

std::set<std::string> ConfigMgr::GetKeysByString(std::string const& name)
{
    std::lock_guard<std::mutex> lock(_configLock);

    std::set<std::string> keys;
    Poco::Util::AbstractConfiguration::Keys __Range;

    _configs->keys(name, __Range);

    for (auto const& itr : __Range)
    {
        keys.insert(itr);
        SYS_LOG_INFO("itr - %s", itr.c_str());
    }

    return keys;
}
