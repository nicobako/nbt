#pragma once

#include <memory>
#include <string>

#if defined(_MSC_VER)
std::string static const relativePath = "res/";
#else
std::string static const relativePath = "./../tests/nbt_ascii/res/";
#endif