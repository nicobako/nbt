#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <typeinfo>
#include <amcs/variant.h>
#include <amcs/lexical_cast.h>

namespace var = amcs::variant;

template<class T, class Var>
void print(Var const& v)
{
  std::cout << "typeid name : " << typeid(T).name() << std::endl;
  std::cout << "v.index() : " << v.index() << std::endl;
  if(T const* t = var::getIf<T>(&v))
  {
    std::cout << "value : " <<  *t << std::endl;
  }
  else
  {
    std::cout << "NO VALUE : requested type not in variant" << std::endl;
  }
  std::cout << std::endl;

}

class C
{
public:
  explicit C(int a) : x(a) {};
  int x;
};

struct Person{
  std::string name;
  int age;
};

std::ostream & operator << (std::ostream & os, C const& c) 
{
  os << "c.x = " << c.x << std::endl;
  return os;
}

std::ostream & operator << (std::ostream & os, std::vector<int> const& v)
{
  for(int i = 0; i < (int)v.size(); ++i)
  {
    os << v.at(i) << ", ";
  }
  os << std::endl;
  return os;
}

std::ostream & operator << (std::ostream & os, std::map<std::string, int> const& map)
{
  typedef std::map<std::string, int>::const_iterator map_iterator;
  
  os << "map values" << std::endl;
  map_iterator const e = map.end();
  for(map_iterator b = map.begin(); b != e; ++b)
  {
    os << "  " << b->first << " : " << b->second << std::endl;
  }
  return os;
}

std::ostream & operator << (std::ostream & os, Person const& p)
{
  os << "Hello, my name is " << p.name << " and I am " << p.age << " years old." << std::endl;
  return os;
}

class Printer : public var::Visitor<void, Printer>
{
public:
  void operator()(int const& num) const
  {
    std::cout << "printing an int : " << num << std::endl;
  }
  void operator()(double const& num) const
  {
    std::cout << "printing a double : " << num << std::endl;
  }
  void operator()(std::string const& num) const
  {
    std::cout << "printing a string : " << num << std::endl;
  }
};

class ToDouble : public var::Visitor<double, ToDouble>
{
public:
  double operator()(int const& num) const
  {
    std::cout << "int to double : " << num << std::endl;
    return static_cast<double>(num);
  }
  double operator()(double const& num) const
  {
    std::cout << "double to double : " << num << std::endl;
    return num;
  }
  double operator()(std::string const& num) const
  {
    std::cout << "std::string to double : " << num << std::endl;
    return amcs::lexical_cast<double>(num);
  }
};

int main()
{

  C c(5);
  std::cout << c;
  std::cout << "variant app" << std::endl;
  
  var::Variant<var::MonoState<>, C, double, std::string> v4;

  v4 = C(10);
  print<C>(v4);
  print<double>(v4);

  v4 = 1.0;
  print<double>(v4);

  v4 = 2.0;
  print<double>(v4);

  v4 = "hello";
  print<std::string>(v4);

  v4 = 10.0005f;
  print<double>(v4);

  var::Variant<
    int,
    double,
    std::string,
    std::vector<int>,
    float,
    unsigned,
    C,
    char,
    std::map<std::string, int>,
    Person > myV;

  myV = 5;
  print<int>(myV);
  myV = 10.55;
  print<double>(myV);
  myV = "hello, I am a string";
  print<std::string>(myV);
  myV = std::vector<int>();
  if(std::vector<int> * vect = var::getIf< std::vector<int> >(&myV))
  {
    for(int i = 0; i < 10; ++i)  
    { 
      vect->push_back(i);
    }
    print< std::vector<int> >(myV);
  }
  else
  {
    std::cout << "ERROR : NO VECTOR\n" << std::endl;
  }

  myV = 5.0f;
  print<float>(myV);
  print<unsigned>(myV);
  myV = static_cast<unsigned>(-1);
  print<unsigned>(myV);
  
  myV = 'c'; 
  print<char>(myV);
  
  myV = std::map<std::string, int>();
  if(std::map<std::string, int> * map = var::getIf< std::map<std::string, int> >(&myV))
  {
    (*map)["hello"] = 5;
    (*map)["goodbye"] = 100;
  }


  print<std::map<std::string, int> >(myV);

  Person p;
  p.name = "Bob";
  p.age = 5;
  myV = p;
  print<Person>(myV);

  var::Variant<int, double, std::string> num;

  Printer printer;
  ToDouble toDouble;
  
  num = 5;
  var::visit<void>(printer, num);
  num = 3.14159;
  var::visit<void>(printer, num);
  num = "6.20";
  var::visit<void>(printer, num);

  typedef var::Variant<int, double, std::string> Number;
  std::vector< Number > vectOfVariants;

  vectOfVariants.push_back(5);
  vectOfVariants.push_back(3.14159);
  vectOfVariants.push_back(std::string("6.20"));
  
  std::vector<double> vectOfDoubles;
  for(int i = 0; i < static_cast<int>(vectOfVariants.size()); ++i)
  {
    std::cout << "variant index : " << vectOfVariants[i].index() << std::endl;
    double d = var::visit<double>(toDouble, vectOfVariants[i]);
    std::cout << "converted double : " << d << std::endl;
    vectOfDoubles.push_back(d);
    std::cout << "double in vector : " << vectOfDoubles.back() << std::endl;
  }
  /*
  std::cout << std::endl;

  std::transform(
    vectOfVariants.begin(),
    vectOfVariants.end(),
    std::back_inserter(vectOfDoubles),
    var::visit(toDouble));
  */
  return 0;

}
