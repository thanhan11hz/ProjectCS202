#pragma once
#include <iostream>
template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>*  ResourceHolder<Resource, Identifier>::instance = nullptr;

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder(std::function<Resource(const char*)> loader,std::function<void(Resource)> unloader)
: mLoader(loader), mUnloader(unloader)
{}

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>& ResourceHolder<Resource, Identifier>::getInstance(std::function<Resource(const char*)> loader, std::function<void(Resource)> unloader) {
    if (!instance) {
        instance = new ResourceHolder(loader, unloader);
    }
    return *instance;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const char* fileName) {
    Resource resource = mLoader(fileName);
    //assert(isValid(resource) && "Failed to load resource");
    auto result = mResourceMap.emplace(id, resource);
    assert(result.second && "Duplicated resource ID");
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
    // std::cout << "Trying to get resource with ID: " << static_cast<int>(id) << std::endl;
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end() && "Resource not found" );
    return found->second;
}

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder() {
    for (auto& pair : mResourceMap)
        mUnloader(pair.second);
}

// template <typename Resource, typename Identifier>
// bool ResourceHolder<Resource, Identifier>::isValid(const Resource& resource) {
//     return (resource.id != 0);
// }