//
//  SystemTrace.hpp
//  citadel
//
//  Created by Norman van der Ploeg on 2023-03-18.
//

#pragma once

#include <string>

namespace citadel {

class TraceLog {
    std::string m_detail;
public:
    TraceLog() = delete;
    TraceLog(std::string detail);
    virtual ~TraceLog();
};

#define CITADEL_TRACEFUNCTION() citadel::TraceLog trace = citadel::TraceLog(__PRETTY_FUNCTION__);

}
