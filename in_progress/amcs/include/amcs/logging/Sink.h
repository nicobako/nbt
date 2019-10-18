#ifndef _AMCS_LOGGING_SINK_H_
#define _AMCS_LOGGING_SINK_H_


#include <amcs/logging/Formatter.h>
#include <amcs/logging/Severity.h>
#include <stdio.h>

namespace amcs {
namespace logging {

class Sink{
public:
    Sink(SeverityLevel const& severityLevel, Formatter* formatter):
        _formatter(formatter),
        _severity(detail::makeSeverity(severityLevel))
{
}
    virtual ~Sink() {};
    virtual void dump(Log const& log) = 0;
    Severity const& severity() const { return this->_severity; }
protected:
    Formatter * _formatter;
private:
    Severity _severity;
};


class ConsoleSink : public Sink{
public:
  ConsoleSink(SeverityLevel const& severityLevel):
    Sink(severityLevel, new FixedWidthFormatter())
  {
  }
  
  ~ConsoleSink()
  {
    delete _formatter;
  }
  
  void dump(Log const& log)
  {
    printf("%s", (*this->_formatter)(log).c_str());
  }
};


} // namespace logging
} // namespace amcs

#endif /* _AMCS_LOGGING_SINK_H_ */
