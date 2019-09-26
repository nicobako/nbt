#pragma once

#include <algorithm>
#include <iterator>
#include <vector>

#include <fstream>

namespace nbt {
namespace binary {
typedef unsigned char Byte;
typedef std::vector<Byte> Bytes;

/// \brief copies bytes of 'source' and appends to 'destination'
///
/// \param destination A container that can be passed to std::back_inserter()
/// \param source Any type
template <class C> void copy_bytes(Bytes & destination, C source) {
  std::copy(
      reinterpret_cast<unsigned char *>(&source),
      reinterpret_cast<unsigned char *>(&source) + sizeof(C),
      std::back_inserter(destination));
}

/// \brief copies bytes of 'source' and appends to 'destination'
///
/// \param destination A container that can be passed to std::back_inserter()
/// \param source A vector of any type
template <class C>
void copy_bytes(Bytes & destination, std::vector<C> const & source) {
  std::for_each(source.begin(), source.end(), [&destination](C value) {
    copy_bytes(destination, value);
  });
}

/// \brief reinterprets the \p bytes and return a vector of the bytes values
///
/// \param bytes \see nbt::binary::Bytes
/// \return A vector of type C
template <class C> std::vector<C> convert_to(Bytes const & bytes) {
  auto bytes_reinterpreted = reinterpret_cast<std::vector<C> const *>(&bytes);

  std::vector<C> bytes_converted;

  std::copy(
      bytes_reinterpreted->begin(),
      bytes_reinterpreted->end(),
      std::back_inserter(bytes_converted));

  return bytes_converted;
}

/// \brief reinterprets the \p bytes as a string
inline std::string convert_to_string(Bytes const & bytes) {
  std::string str;

  std::copy(bytes.begin(), bytes.end(), std::back_inserter(str));
  return str;
}

//// copies the byte values to an ostream object
// void dump_bytes(Bytes & bytes, std::ofstream file)
//{
//	std::for_each(
//		bytes.begin(),
//		bytes.end(),
//		[&file](Byte byte) { file << byte; });
//
//	bytes.clear();
//}

} // namespace binary
} // namespace nbt
