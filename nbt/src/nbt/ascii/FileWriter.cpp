#include <nbt/ascii/FileWriter.hpp>

nbt::ascii::FileWriter::FileWriter(std::string fileName, bool append)
    : FileHandler(fileName), fileName_(fileName) {
  if (!append) {
    fileStream_ = std::ofstream(fileName_);
  } else {
    fileStream_ = std::ofstream(fileName_, std::ios::app);
  }
}

nbt::ascii::FileWriter::~FileWriter() {
  if (fileStream_.is_open()) {
    fileStream_.close();
  }
}

bool nbt::ascii::FileWriter::isOpen() const {
  return fileStream_.is_open();
}

void nbt::ascii::FileWriter::close() {
  fileStream_.close();
}

template void nbt::ascii::FileWriter::write<std::string>(std::string, bool);
template void nbt::ascii::FileWriter::write<char const *>(char const *, bool);
template void nbt::ascii::FileWriter::write<int>(int, bool);
template void nbt::ascii::FileWriter::write<unsigned>(unsigned, bool);
template void nbt::ascii::FileWriter::write<float>(float, bool);
template void nbt::ascii::FileWriter::write<double>(double, bool);
template void nbt::ascii::FileWriter::write<bool>(bool, bool);
