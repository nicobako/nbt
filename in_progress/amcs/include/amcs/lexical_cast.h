#ifndef _AMCS_LEXICAL_CAST_H_
#define _AMCS_LEXICAL_CAST_H_

/** \file lexical_cast.h
 *  
 *  \brief This file contains the function
 *         declaration for the amcs::lexical_cast function.
 */

namespace amcs {

/** \brief Casts ValueType into ReturnType.
 *  
 *  This function provides a simple interface for performing
 *  casts. It is specifically intended for StringType <-> ValueType
 *  conversions.
 *
 *  It may be used as follows:
 *
 *  ```cpp
 *  // convert std::string to int
 *  std::string s = "5";
 *  int i = amcs::lexical_cast<int>(s);
 *  
 *  // convert double to std::string
 *  double pi = 3.14159;
 *  std::string pi_string = amcs::lexical_cast<std::string>(pi);
 *  ```
 */
template<class ReturnType, class ValueType>
ReturnType lexical_cast(ValueType value);

} // namespace amcs

#endif /*_AMCS_LEXICAL_CAST_H_*/
