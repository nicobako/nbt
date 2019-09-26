#pragma once

#include <string>

#include <fstream>
#include <nbt/core/FileHandler.hpp>

namespace nbt {
namespace ascii {
/// AsciiWriter is a class to help you write ASCII files

/// Its interface is very simple
/// The destructor of AsciiWriter (~AsciiWriter) call ofstream::close
/// in the case that the user forgets to close the file
class FileWriter : public nbt::core::FileHandler {

public:
  // The constructor for AsciiWriter
  FileWriter(std::string fileName, bool append = false);

  /// The destructor for AsciiWriter
  virtual ~FileWriter();

  /// Returns a boolean indicating whether the file is open
  bool isOpen() const;

  /// Closes the file
  void close();

  /// The crucial function that writes a Writeable object to a file.
  ///
  /// \todo
  /// If you wish to pass your own class as a Printable object
  /// you must define operator << for your class
  template <typename Writeable>
  void write(Writeable writeable, bool endLine = false) {
    if (fileStream_.is_open()) {
      fileStream_ << writeable;
    }
    if (endLine) {
      fileStream_ << std::endl;
    }
  }

private:
  std::string fileName_;
  std::ofstream fileStream_;
};
} // namespace ascii
} // namespace nbt
