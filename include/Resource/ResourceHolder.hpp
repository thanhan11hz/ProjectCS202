#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    ResourceHolder(ResourceHolder& other) = delete;
    void operator=(const ResourceHolder&) = delete;
    static ResourceHolder& getInstance(std::function<Resource(const char*)> loader, std::function<void(Resource)> unloader);
    void load(Identifier id, const char* fileName);
    Resource &get(Identifier id);
    ~ResourceHolder();

protected:
    ResourceHolder(std::function<Resource(const char*)> loader, std::function<void(Resource)> unloader);
    static ResourceHolder<Resource, Identifier>* instance;

private:
    static bool isValid(const Resource &resource);
    std::unordered_map<Identifier, Resource> mResourceMap;
    std::function<Resource(const char*)> mLoader;
    std::function<void(Resource)> mUnloader;
};

#include "ResourceHolder.inl"
