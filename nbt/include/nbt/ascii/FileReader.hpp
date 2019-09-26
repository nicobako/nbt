#pragma once

#include <string>

#include <fstream>
#include <nbt/core/FileHandler.hpp>

namespace nbt {
namespace ascii {
class FileReader : public nbt::core::FileHandler {
  // AsciiReader is a class to help you load ASCII files
  // AsciiReader does not support line parsing
  //     To parse a line use the LineParser class (file/LineParser)
public:
  // A AsciiReader object must be instantiated with the name
  // of the file which it will load.
  // Yes, this means that you will need to create a new
  // AsciiReader object for every file you want to open
  FileReader(std::string const & fileName);

  // This destructor will call the function AsciiReader::close()
  // iff the user forgets to do it.
  virtual ~FileReader();

  // Return a boolean indicating whether the file was opened
  // correctly or not
  bool isOpen() const override;

  // Returns a boolean indicating whether the end of the file
  // has been reached
  bool endOfFileReached() const;

  // Reads the next line of the file and returns it as a std::string
  std::string const & getNextLine();

  // Returns the line that the AsciiReader object is currently on
  std::string const & getCurrentLine() const;

  // Returns the previous line that the AsciiReader object has read
  std::string const & getPreviousLine() const;

  // Returns the line number that the AsciiReader object is on
  //     Note that this returns a 1-indexed number
  //         i.e. the first line of a file always = 1
  unsigned getCurrentLineNumber() const;

  // Closes the file
  void close() override;

private:
  std::ifstream fileStream_;
  bool fileOpen_;
  bool endOfFile_;
  std::string previousLine_;
  std::string currentLine_;
  unsigned currentLineNumber_;
};
} // namespace ascii
} // namespace nbt
