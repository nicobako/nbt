#include <iostream>

#include <nbt/core/NamedType.hpp>
#include <nbt/core/ValueRange.hpp>
#include <nbt/core/random.hpp>

// The nbt::core::NamedType class is truly designed to be derived from.
// It provides a nice safe way to ensure that the value will not
// be altered by clients.
class Age : public nbt::core::NamedType<int> {
public:
  Age(int age) : nbt::core::NamedType<int>(age) {}
  bool isMinor() const {
    return this->get() < 18;
  }
  bool isMiddleAged() const {
    // Example of how to use the nbt::core::Range class
    return nbt::core::isInRange(*this, nbt::core::ValueRange<int>(35, 55));
  }
  bool isSenior() const {
    return this->get() >= 65;
  }
};

void printDetails(Age const & age) {
  std::cout << "Age : " << age.get() << std::endl;
  std::cout << "Is minor ? : " << age.isMinor() << std::endl;
  std::cout << "Is middle-aged ? : " << age.isMiddleAged() << std::endl;
  std::cout << "Is senior ? : " << age.isSenior() << std::endl << std::endl;
}
int main() {
  Age age0(0);
  printDetails(age0);

  Age age15(15);
  printDetails(age15);

  Age age40(40);
  printDetails(age40);

  Age age75(75);
  printDetails(age75);

  std::cout << "Any age\n\n";

  // Example of how to use the nbt::core::random functions in conjuction
  // with the nbt::core::Range class
  Age anyAge1(nbt::core::random<int>(nbt::core::ValueRange<int>(0, 100)));
  printDetails(anyAge1);

  Age anyAge2(nbt::core::random<int>(nbt::core::ValueRange<int>(0, 100)));
  printDetails(anyAge2);

  Age anyAge3(nbt::core::random<int>(nbt::core::ValueRange<int>(0, 100)));
  printDetails(anyAge3);

  return 0;
}