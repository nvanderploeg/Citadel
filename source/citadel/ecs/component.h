#pragma once

#include <string>
#include <memory>

namespace citadel
{

    class Entity;

    struct Component
    {
        //We hold a backreference to the entity we are attached to
        //Component may not be attached to more than one entity.
        //As a weak pointer, if the owner deallocates, then this component is no longer valid
        //so owner may used for validation
        std::weak_ptr<Entity> owner;
        virtual ~Component() = default;
        virtual std::string getType() const = 0;
    };

} // namespace citadel

