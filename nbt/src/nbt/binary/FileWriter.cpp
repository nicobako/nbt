#include <nbt/binary/FileWriter.hpp>

template <>
int nbt::binary::detail::copyBytes<std::string>(
    std::string const & string,
    char * buffer) {
  for (unsigned i = 0; i < string.size(); i++) {
    buffer[i] = string[i];
  }
  return string.size();
}

nbt::binary::FileWriter::FileWriter(
    std::string fileName,
    bool append,
    Endianness endianness)
    : FileHandler(fileName),
      // file_(fileName_, std::ios::binary | std::ios::trunc),
      endianness_(endianness) {
  if (append) {
    file_ = std::ofstream(fileName, std::ios::binary | std::ios::app);
  } else {
    file_ = std::ofstream(fileName, std::ios::binary | std::ios::trunc);
  }
}

nbt::binary::FileWriter::~FileWriter() {
  if (file_.is_open()) {
    file_.close();
  }
}

bool nbt::binary::FileWriter::isOpen() const {
  return file_.is_open();
}

void nbt::binary::FileWriter::close() {
  if (file_.is_open()) {
    file_.close();
  }
}

template void nbt::binary::FileWriter::write<int>(int const &);
template void nbt::binary::FileWriter::write<unsigned>(unsigned const &);
template void nbt::binary::FileWriter::write<double>(double const &);
template void nbt::binary::FileWriter::write<float>(float const &);

void nbt::binary::FileWriter::reverseBytes(unsigned nBytes) {
  std::reverse(&buffer_[0], &buffer_[0 + nBytes]);
}