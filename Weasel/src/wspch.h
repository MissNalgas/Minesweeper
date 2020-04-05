#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

#include "Weasel/Core/Log.h"
#include "Weasel/Debug/Instrumentor.h"

#ifdef WS_PLATFORM_WINDOWS
#include <Windows.h>

#endif