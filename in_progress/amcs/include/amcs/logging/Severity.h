#ifndef _AMCS_LOGGING_SEVERITY_H_
#define _AMCS_LOGGING_SEVERITY_H_

#include <string>

namespace amcs {
namespace logging {

/** \brief The available *severity levels of logs.
 *
 *  When a Sink is created it is assigned a SeverityLevel.
 *  Likewise, when a Log is created (via the LOG macro) it is assigned a SeverityLevel.
 *  A Log will be dumped to the Sink if the Log's SeverityLevel is greater or equal to
 *  the SeverityLevel of the Sink.
 */
enum SeverityLevel{
    debug,
    info,
    warning,
    error,
    undefined
};

/** \brief Pairs a SeverityLevel with a \a name.
 */
class Severity{
public:
    Severity(std::string const& severityString, SeverityLevel const& severityLevel):
    _severityString(severityString),
    _severityLevel(severityLevel)
  {
  }

  Severity(Severity const& rhs) :
    _severityString(rhs.asString()),
    _severityLevel(rhs.asLevel())
  {
  }

  SeverityLevel const& asLevel() const { return this->_severityLevel; }
    
  std::string const& asString() const { return this->_severityString; }

  bool operator>=(Severity const& other) const {  
    return this->asLevel() >= other.asLevel();
  }
    
private:
    std::string _severityString;
    SeverityLevel _severityLevel;
};

namespace detail {
/** \brief Helper function for creating a Severity
 */
inline Severity makeSeverity(SeverityLevel const severityLevel)
{
    switch(severityLevel)
    {
        case debug :
            return Severity("DEBUG", debug);
        case info :
            return Severity("INFO", info);
        case warning :
            return Severity("WARNING", warning);
        case error :
            return Severity("ERROR", error);
        case undefined :
            return Severity("UNDEFINED", undefined);
        default :
            return Severity("UNDEFINED", undefined);
    }
}

} // namespace detail

} // namespace logging
} // namespace amcs

#endif /* _AMCS_LOGGING_SEVERITY_H_ */

