#include "../include/Cerium/ResourceManager.hpp"

namespace cerium
{
    Resource * ResourceManager::get(const std::string & name)
    {
        for(auto & resource : instance().resources)
        {
            if(resource.first == name)
            {
                return resource.second;
            }
        }
        return nullptr;
    }


    void ResourceManager::add(const std::string & name, Resource * resource)
    {
        if(!exist(name)) instance().resources[name] = resource;
    }


    bool ResourceManager::exist(const std::string & name)
    {
        for(auto & resource : instance().resources)
        {
            if(resource.first == name) return true;
        }
        return false;
    }


    void ResourceManager::remove(const std::string & name)
    {
        for(auto & resource : instance().resources)
        {
            if(resource.first == name) delete resource.second;
        }
    }


    void ResourceManager::clear(void)
    {
        for(auto & resource : instance().resources)
        {
            delete resource.second;
        }
    }


    ResourceManager::~ResourceManager()
    {
        clear();
    }


    ResourceManager & ResourceManager::instance()
    {
        static ResourceManager resourceManager;
        return resourceManager;
    }
}