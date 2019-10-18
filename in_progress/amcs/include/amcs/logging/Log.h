#ifndef _AMCS_LOGGING_LOG_H_
#define _AMCS_LOGGING_LOG_H_

#include <amcs/logging/globals.h>
#include <amcs/logging/Severity.h>
#include <amcs/lexical_cast.h>

#include <string>

namespace amcs {
namespace logging {

class Log
{
public:
  Log(SeverityLevel const& severityLevel, std::string const& fileName, int lineNumber) : 
      _lineNumber(lineNumber),
      _fileName(fileName),
      _message(),
      _severity(detail::makeSeverity(severityLevel))
  {
  }
    
  ~Log()
  {
    _message += "\n";
    detail::dump(*this);
  }

    int lineNumber() const { return this->_lineNumber; }
    std::string const& fileName() const { return this->_fileName; }
    std::string const& message() const { return this->_message; }
    Severity const& severity() const { return this->_severity; }

    template<class C>
    Log& operator<<(C const& c){
        std::string cAsString = lexical_cast<std::string>(c);
        _message += cAsString;
        return *this;
    }

private:
    int _lineNumber;
    std::string _fileName;
    std::string _message;
    Severity _severity;
};

} // namespace logging
} // namespace amcs

#define LOG(severityLevel) amcs::logging::Log(severityLevel, std::string(__FILE__), __LINE__)

#endif

