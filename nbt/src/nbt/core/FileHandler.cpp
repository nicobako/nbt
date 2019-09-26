#include <nbt/core/FileHandler.hpp>

nbt::core::FileHandler::FileHandler(std::string const & fileName)
    : fileName_(fileName) {}

nbt::core::FileHandler::~FileHandler() {}

std::string const nbt::core::FileHandler::getFileName() const {
  return fileName_;
}