#pragma once

#include <cstring> // std::memcpy
#include <string>

#include <fstream>
#include <nbt/binary/Bytes.hpp>
#include <nbt/binary/Endianness.hpp> // Endianness, bufferSize
#include <nbt/core/FileHandler.hpp>

namespace nbt {
namespace binary {
class FileReader : public nbt::core::FileHandler {
public:
  FileReader(std::string fileName, Endianness endianness = EndiannessLittle);

  ~FileReader();

  bool isOpen() const;

  void close();

  void skip(int nBytes);

  // Reads then returns built-in-types
  template <typename T> T get_next() {
    T nextValue;
    readNext<T>(nextValue);
    return nextValue;
  }

  template <> std::string get_next();

  template <typename Container_t> Container_t get_next_n(int num_elements) {
    Container_t container;
    for (int i = 0; i < num_elements; ++i) {
      typedef Container_t::value_type val_t;
      val_t val = this->get_next<val_t>();
      container.push_back(val);
    }
    return container;
  }

  // Reads and returns all bytes in file
  nbt::binary::Bytes getBytes();

private:
  template <typename T> void readNext(T & t) {
    if (!file_.read(buffer_, sizeof(T))) {
      file_.close();
    }
    reverseBytesIfNeeded(sizeof(T));
    std::memcpy(&t, buffer_, sizeof(T));
  }

  void reverseBytesIfNeeded(int nBytes);

  std::string fileName_;

  std::ifstream file_;

  char buffer_[nbt::binary::BinaryBufferSize];

  Endianness endianness_;
};
} // namespace binary
} // namespace nbt
