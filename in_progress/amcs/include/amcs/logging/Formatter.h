#ifndef _AMCS_LOGGING_FORMATTER_H_
#define _AMCS_LOGGING_FORMATTER_H_

#include <ctime>
#include <string>

#include <amcs/logging/Log.h>
#include <amcs/logging/globals.h>
#include <amcs/threading.h>
#include <amcs/lexical_cast.h>

namespace amcs {
namespace logging {

class Formatter{
public:
    virtual ~Formatter(){}
  virtual std::string operator()(Log const& log) const = 0;
  virtual std::string genTimeString() const
  {
    std::time_t const t = std::time(0);
    std::tm const time = *std::localtime(&t);
    std::string timeString;
    timeString += lexical_cast<std::string>(time.tm_year + 1900) += "/";
    timeString += lexical_cast<std::string>(time.tm_mon + 1) += "/";
    timeString += lexical_cast<std::string>(time.tm_mday) += "-";
    timeString += lexical_cast<std::string>(time.tm_hour) += ":";
    timeString += lexical_cast<std::string>(time.tm_min) += ":";
    timeString += lexical_cast<std::string>(time.tm_sec);

    return timeString;
  }
  
  virtual std::string genThreadId() const
  {
   return detail::getThreadName();
  }
};

class FixedWidthFormatter : public Formatter {
public:
  FixedWidthFormatter():
    Formatter()
  {
  }

  std::string operator()(Log const& log) const
  {
    std::string str;
    str += this->genSeverityString(log.severity());
    str += this->genFileNameString(log.fileName());
    str += this->genLineNumberString(log.lineNumber());
    str += this->genTimeString();
    str += this->genThreadId();
    str += " : ";
    str += log.message();
    return str;
  }

private:
    std::string genTimeString() const
  {
    std::string timeString = Formatter::genTimeString();
    timeString += "    ";

    return timeString;
  }
  
  std::string genThreadId() const
  {
    std::string tString = Formatter::genThreadId();
    tString.resize(20, ' ');
    return tString;
  }

  std::string genSeverityString(Severity const& severity) const
  {
    std::string severity_string = severity.asString();
    severity_string.resize(10, ' ');
    return severity_string;
  }

  std::string genFileNameString(std::string const& filename) const
  {
    std::string filename_string = filename;
    std::size_t const position_of_last_slash = filename_string.find_last_of('/');
    if(position_of_last_slash != std::string::npos){
        filename_string = filename_string.substr(position_of_last_slash);
    }
    filename_string.resize(25, ' ');
    return filename_string;
  }
    std::string genLineNumberString(int const& lineNumber) const
  {
    std::string lineNumber_string = lexical_cast<std::string>(lineNumber); 
    lineNumber_string.resize(8, ' ');
    return lineNumber_string;
  }

};

class CsvFormatter : public Formatter {
public:
  CsvFormatter() : Formatter()
  {
  }

  std::string operator()(Log const& log) const
  {
    std::string str;
    str += log.severity().asString();
    str += ", ";
    str += log.fileName();
    str += ", ";
    str += lexical_cast<std::string>(log.lineNumber());
    str += ", ";
    str += Formatter::genTimeString();
    str += ", ";
    str += Formatter::genThreadId();
    str += ", \"";
    str += log.message();
    str += "\"";
    return str;
  }
};


} // namespace logging
} // namespace amcs
#endif /* _AMCS_LOGGING_FORMATTER_H_ */
