#include <nbt/ascii/FileReader.hpp>

nbt::ascii::FileReader::FileReader(const std::string & fileName)
    : FileHandler(fileName), fileStream_(fileName.c_str(), std::ios::in),
      fileOpen_(false), endOfFile_(false), previousLine_(), currentLine_(),
      currentLineNumber_(0) {
  fileOpen_ = fileStream_.is_open();

  if (!fileOpen_) {
    endOfFile_ = true;
  }
}

nbt::ascii::FileReader::~FileReader() {
  if (fileOpen_) {
    close();
  }
}

bool nbt::ascii::FileReader::isOpen() const {
  return fileOpen_;
}

bool nbt::ascii::FileReader::endOfFileReached() const {
  return endOfFile_;
}

std::string const & nbt::ascii::FileReader::getNextLine() {
  previousLine_ = currentLine_;

  if (std::getline(fileStream_, currentLine_)) {
    currentLineNumber_++;
  } else {
    endOfFile_ = true;

    close();
  }
  return currentLine_;
}

std::string const & nbt::ascii::FileReader::getCurrentLine() const {
  return currentLine_;
}

std::string const & nbt::ascii::FileReader::getPreviousLine() const {
  return previousLine_;
}

unsigned nbt::ascii::FileReader::getCurrentLineNumber() const {
  return currentLineNumber_;
}

void nbt::ascii::FileReader::close() {
  fileStream_.close();

  fileOpen_ = false;

  currentLineNumber_ = 0;
}
