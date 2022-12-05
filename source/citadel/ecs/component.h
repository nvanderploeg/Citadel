#pragma once

#include <string>

namespace citadel {

struct Component {
    virtual ~Component() = default;
    virtual std::string getType() const = 0;
};


}

