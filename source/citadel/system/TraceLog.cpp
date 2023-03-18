//
//  SystemTrace.cpp
//  critactics
//
//  Created by Norman van der Ploeg on 2023-03-18.
//

#include "traceLog.hpp"

#include <iostream>

namespace citadel {
TraceLog::TraceLog(std::string detail): m_detail(detail) {
    std::cout << m_detail << " - Begin\n";
}

TraceLog::~TraceLog() {
    std::cout << m_detail << " - End" << std::endl;
}

}
