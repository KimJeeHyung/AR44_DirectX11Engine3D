#pragma once
#include <string>
#include <Windows.h>
#include <assert.h>

#include <vector>
#include <list>
#include <map>
#include <bitset>
#include <set>

#include <cmath>
#include <algorithm>
#include <limits>
#include <memory>
#include <filesystem>
#include <functional>

#include "CommonInclude.h"
#include "jhEnums.h"

#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)