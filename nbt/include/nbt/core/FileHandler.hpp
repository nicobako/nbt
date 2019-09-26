#pragma once

#include <string>

namespace nbt {
namespace core {
class FileHandler {
public:
  // A fileHandler must be initialized with the fileName
  FileHandler(std::string const & fileName);

  // It is a base class - must have virtual desctructor
  virtual ~FileHandler();

  // Will inform user if file is opened correctly
  virtual bool isOpen() const = 0;

  // Will return the fileName
  virtual std::string const getFileName() const;

  // Will close the file
  virtual void close() = 0;

private:
  std::string fileName_;
};
} // namespace core
} // namespace nbt
