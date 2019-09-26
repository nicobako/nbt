#include <algorithm>

#include <nbt/binary/FileReader.hpp>

namespace nbt {
namespace binary {
FileReader::FileReader(std::string fileName, Endianness endianness)
    : FileHandler(fileName), endianness_(endianness) {
  file_ = std::ifstream(fileName, std::ios::binary);

  file_.seekg(0, std::ios::beg);
}

FileReader::~FileReader() {
  if (file_.is_open()) {
    file_.close();
  }
}

bool FileReader::isOpen() const {
  return file_.is_open();
}

void FileReader::close() {
  if (file_.is_open()) {
    file_.close();
  }
}

void FileReader::skip(int nBytes) {
  file_.ignore(nBytes);
}

nbt::binary::Bytes FileReader::getBytes() {
  file_.seekg(0, std::ios::end);
  auto size = file_.tellg();
  file_.seekg(0, std::ios::beg);

  nbt::binary::Bytes bytes(static_cast<int>(size));
  file_.read(reinterpret_cast<char *>(&bytes[0]), size);

  return bytes;
}

template <> std::string FileReader::get_next() {
  int num_characters = this->get_next<int>();

  if (!this->file_.is_open()) {
    return std::string();
  }

  if (!file_.read(buffer_, num_characters)) {
    file_.close();
  }

  reverseBytesIfNeeded(num_characters);

  std::string str(buffer_);
  str.resize(num_characters);

  return str;
}

// Since these are built-in types that the user will have to
// read often we will define them ahead of time... will this
// increase performance??? I think so, but I'm not sure.
template void FileReader::readNext<char>(char &);
template void FileReader::readNext<int>(int &);
template void FileReader::readNext<unsigned>(unsigned &);
template void FileReader::readNext<double>(double &);
template void FileReader::readNext<float>(float &);

void FileReader::reverseBytesIfNeeded(int nBytes) {
  if (endianness_ == EndiannessBig) {
    std::reverse(&buffer_[0], &buffer_[0 + nBytes]);
  }
}
} // namespace binary
} // namespace nbt