/*
 * logging.h
 *
 *  Created on: Aug 7, 2019
 *      Author: bakomihalisn
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <amcs/logging/globals.h>
#include <amcs/logging/Log.h>
#include <amcs/logging/Sink.h>

#include <amcs/lexical_cast.h>

#include <string>
#include <vector>
#include <stdio.h>

namespace amcs {

/** \brief Contains tools for logging.
 *
 * \todo Separate all classes into their own .h and .cpp files.
 * \todo Remove amcs::logging::Prefix class and put all
 *       of the pieces of data into their own member variable
 *       of the amcs::logging::Log class.
 * \tode Add LOG_SCOPE macro that indents the log message until it goes out of scope.
 *
 *  Logging is a very fundamental task. If you have ever had to print
 *  something to a file or to the console in order to get a better understanding
 *  of what is going on in your code, then you know how important logging is.
 *  Besides using a debugger, logging is often the only way to understand 
 *  what is going on in the code at runtime.
 *  
 *  Even though it is important and developpers have to do it all the time,
 *  most developpers are doing it inefficiently and irreproducibly by using
 *  \a printf or \a std::cout directly in their code.
 *
 *  This logging library is intended to provide the basics of logging such as
 *
 *  * allowing for multiple *sinks*
 *    *i.e. destinations for a log message to be written to
 *  * allowing for log messages to be filtered base on their *severity levels*
 *    * a sink can be configured to only accept log messages above a 
 *      threshold severity level
 *  * extracting important *source-code-level* information to facilitate tracking down bugs
 *    * this information includes *line number* and *file name* where the log was created.
 *
 */
namespace logging {

} // namespace logging
} //namespace amcs




#endif /* LOGGING_H_ */
