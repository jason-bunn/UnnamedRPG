#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

public:
    void                    Load(Identifier id, const std::string& filename);

    template<typename Parameter>
    void                    Load(Identifier id, const std::string& filename, const Parameter& secondParam);

    Resource&               Get(Identifier id);
    const Resource&         Get(Identifier id) const;

private:
    void                    InsertResource(Identifier id, std::unique_ptr<Resource> resource);

};

#include "ResourceHolder.inl"

#endif // RESOURCEHOLDER_HPP
