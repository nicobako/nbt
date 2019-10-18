#include <amcs/lexical_cast.h>

#include <iostream>
#include <string>

int main(){
    std::cout << amcs::lexical_cast<std::string>(5) << std::endl;
    std::cout << amcs::lexical_cast<std::string>("hello") << std::endl;
    std::string s = "hi, I'm a std::string";
    std::cout << amcs::lexical_cast<std::string>(s) << std::endl;
    return 0;
}
