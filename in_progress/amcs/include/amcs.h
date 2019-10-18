#ifndef _AMCS_H_
#define _AMCS_H_

/** \file amcs.h
 *  
 *  \brief The root header file for the amcs C++ libraries.
 *
 *  Including this file #includes all of the amcs C++ libraries.
 *  This is rarely necessary, but is provided as a facility.
 */


#include <amcs/lexical_cast.h>
#include <amcs/logging.h>
#include <amcs/messaging.h>
#include <amcs/optional.h>

/** \brief The root namespace for the amcs C++ libraries.
 *
 *  All of the different libraries reside within the \a amcs namespace.
 *  Each library then resides within its own namespace named after the
 *  functionality that it is intended to provide.
 *
 * \todo Create a template metaprogramming library called amcs::mpl.
 */
namespace amcs {

}

#endif // !_AMCS_H_
