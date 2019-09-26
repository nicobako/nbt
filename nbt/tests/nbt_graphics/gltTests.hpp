#pragma once

#include <memory>
#include <string>

//#include <nbt/glt.hpp>

#if defined(_MSC_VER)
static const std::string relPathToResFiles = "res/";
#else
static const std::string relPathToResFiles = "./../tests/nbt_graphics/res/";
#endif