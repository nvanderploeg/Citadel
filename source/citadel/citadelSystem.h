//
//  citadelSystem.h
//  CitadelEngine
//
//  Created by Norman van der Ploeg.
//  Copyright � 2020 Floating Citadel Games. All rights reserved.
//
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <iostream>
#include <filesystem>

// externals
#include "json/json.h"

//Citadel System
#include "system/resourcePath.h"
#include "system/JSONSerializable.h"
#include "system/serializer.h"
#include "system/cTime.h"
#include "system/tickable.h"
#include "system/traceLog.hpp"
#include "system/clock.h"
#include "system/errorCodes.h"
