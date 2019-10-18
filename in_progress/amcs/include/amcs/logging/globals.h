#ifndef _AMCS_LOGGING_GLOBALS_H_
#define _AMCS_LOGGING_GLOBALS_H_


#include <string>


namespace amcs {
namespace logging {

class Sink;
void addSink(Sink * sink);

void registerThisThread(std::string const& name);

class Log;
namespace detail {
void dump(Log const& log);

std::string getThreadName();

} // namespace detail

} //namespace logging
} //namespace amcs


#endif /* _AMCS_LOGGING_GLOBALS_H_ */

