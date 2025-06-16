#pragma once

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::ResourceHolder(std::function<Resource(const char*)> loader,std::function<void(Resource)> unloader)
: mLoader(loader), mUnloader(unloader)
{}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const char* fileName) {
    Resource resource = mLoader(fileName);
    assert(isValid(resource) && "Failed to load resource");
    auto result = mResourceMap.emplace(id, resource);
    assert(result.second && "Duplicated resource ID");
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end() && "Resource not found");
    return found->second;
}

template <typename Resource, typename Identifier>
ResourceHolder<Resource, Identifier>::~ResourceHolder() {
    for (auto& pair : mResourceMap)
        mUnloader(pair.second);
}

template <typename Resource, typename Identifier>
bool ResourceHolder<Resource, Identifier>::isValid(const Resource& resource) {
    return (resource.id != 0);
}
