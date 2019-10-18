#include <amcs/optional.h>

#include <iostream>
#include <string>
#include <algorithm>

namespace opt = amcs::optional;

// if seed is valid, returns a value,
// else returns none
opt::Optional<int> getValue(int seed)
{
  int const myFavouriteNumber = 2;
  if(seed == myFavouriteNumber) {
    return 2;
  } else {
    return opt::nullOptional;
  }
  
}

struct Point
{
  Point(int x, int y) : _x(x), _y(y) {}

  int & x() {return _x;}
  int const& x() const {return _x;}

  int & y() {return _y;}
  int const& y() const {return _y;}

private:
  int _x;
  int _y;
};


void printPoint(Point const& p)
{
  std::cout << "p.x : " << p.x() << std::endl;
  std::cout << "p.y : " << p.y() << std::endl;
}


int main()
{
  std::cout << "starting 'optional' app" << std::endl;

  
  // we start with an uninitialized optional int
  opt::Optional<int> oi;
  if(!oi) {
    std::cout << "oi is empty ... as it should be" << std::endl;
  } else {
    std::cout << "oi is not empty ... problem!" << std::endl;
  }

  // we now set its value
  oi = 5;
  if(oi) {
    std::cout << "oi is not empty ... Yay!" << std::endl;
    // we can now access the value
    std::cout << "oi has value : " << oi.value() << std::endl;
  } else {
    std::cout << "oi is empty... problem!" << std::endl;
  }

  // we can reset its value
  oi = 10;
  std::cout << "oi now has value : " << oi.value() << std::endl;
  std::cout << "*oi : " << *oi << std::endl;

  // we can also reset its value to uninitialized
  oi = opt::nullOptional;

  std::cout << "set to null" << std::endl;
  if(!oi) {
    std::cout << "oi is empty again ... as it should be" << std::endl;
  } else {
    std::cout << "oi is not empty ... problem!" << std::endl;
  }
  
  // constructing an optional with an initial value
  opt::Optional<double> od(100.505);
  if(od) {
    std::cout << "od has value : " << od.value() << std::endl;
  } else {
    std::cout << "od is not initialized ... problem!" << std::endl;
  }

  // constructing an optional with nullOptional
  opt::Optional<float> no = opt::nullOptional;
  if(!no) {
    std::cout << "no is not initialized ... Yay" << std::endl;
  } else {
    std::cout << "no is initialized ... problem!" << std::endl;
  }
  
  opt::Optional<int> gv0 = getValue(0);
  if(!gv0) {
    std::cout << "gv0 is not initialized ... yay" << std::endl;
  } else {
    std::cout << "gv0 is initialized ... problem!" << std::endl;
  }

  opt::Optional<int> gv2 = getValue(2);
  if(gv2) {
    std::cout << "gv2 is initialized ... yay" << std::endl;
    std::cout << "gv2 value : " << gv2.value() << std::endl;
  } else {
    std::cout << "gv2 is not initialized ... problem!" << std::endl;
  }
  
  // can it handle strings ?
  opt::Optional<std::string> os("hello world");
  if(os) {
    std::cout << "can it have a string value? " << sizeof(std::string) <<  std::endl;
    std::cout << "os has value " << os.value() << std::endl;
    std::cout << "os length : " << os->size() << std::endl;
  } else {
    std::cout << "os not initialized ... problem!" << std::endl;
  }

  // can it handle non-default-constructible types ?
  opt::Optional<Point> p;
  std::cout << std::boolalpha;
  std::cout << p << std::endl;
  p = Point(0, 1);
  std::cout << p << std::endl;  
  printPoint(*p);
  p.reset();
  std::cout << p << std::endl;
  return 0;
}


