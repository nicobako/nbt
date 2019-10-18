#include <amcs/lexical_cast.h>

#include <stdio.h>
#include <string>
#include <cstdlib>

namespace amcs{

/** \brief Converts \a int to \a std::string.
 */
template<>
std::string lexical_cast(int const value){
    char s[100];
    snprintf(s, 100, "%i", value);
    return std::string(s);
}

/** \brief Converts \a char* to \a std::string.
 */
template<>
std::string lexical_cast(const char * value){
    return std::string(value);
}

/** \brief Converts \a std::string to \a std::string.
 */
template<>
std::string lexical_cast(std::string const value){
    return value;
}

/** \brief Converts \a unsigned \a long \a int to \a std::string.
*/
template<>
std::string lexical_cast(unsigned long int const value)
{
    char s[100];
    snprintf(s, 100, "%lu", value);
    return std::string(s);
}

/** \brief Converts \a char* to double.
*/
template<>
double lexical_cast(const char* value){
  return atof(value);
}

/** \brief converts std::string to double.
*/
template<>
double lexical_cast(std::string const value){
  return lexical_cast<double>(value.c_str());
}

} // namespace amcs

