#pragma once

#include <algorithm> // std::reverse
#include <cstring>   // std::memcpy
#include <string>

#include <fstream>
#include <nbt/binary/Endianness.hpp>
#include <nbt/core/FileHandler.hpp>

namespace nbt {
namespace binary {
namespace detail {

template <typename T> int copyBytes(T const & t, char * buffer) {
  std::memcpy(buffer, &t, sizeof(T));

  return sizeof(T);
}

template <>
int copyBytes<std::string>(std::string const & string, char * buffer);
} // namespace detail

class FileWriter : public nbt::core::FileHandler {
public:
  FileWriter(
      std::string fileName,
      bool append = false,
      Endianness endianness = EndiannessLittle);

  ~FileWriter();

  bool isOpen() const;

  void close();

  template <typename T> void write(T const & t) {
    int numBytes = detail::copyBytes(t, &buffer_[0]);

    if (endianness_ == EndiannessBig) {
      reverseBytes(numBytes);
    }

    file_.write(buffer_, numBytes);
  }

private:
  void reverseBytes(unsigned nBytes);

  std::ofstream file_;

  Endianness endianness_;
  char buffer_[nbt::binary::BinaryBufferSize];
};
} // namespace binary
} // namespace nbt
