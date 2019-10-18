#include <amcs/logging.h>
#include <amcs/threading.h>

#include <map>
#include <vector>
#include <string>

namespace amcs{
namespace logging{


class Logger
{
private:
  Logger() :
    _sinks(),
    _threadNames()
  {
  }

public:
  static Logger & instance()
  {
    static Logger instance;
    return instance;
  }

  ~Logger()
  {
    for(unsigned int i = 0; i < this->_sinks.size(); ++i)
    {
      delete this->_sinks[i];
    }
  }

  void dump(Log const& log)
  {
    for(unsigned int i = 0; i < this->_sinks.size(); ++i)
    {
      Sink & sink = *this->_sinks.at(i);
      if(log.severity() >= sink.severity()){
          sink.dump(log);
      }
    }
  }

  void addSink(Sink * sink)
  {
    _sinks.push_back(sink);
  }

  void registerThread(amcs::threading::Thread::Id id, std::string const& name)
  {
    this->_threadNames[id] = name;
  }

  std::string getThreadName()
  {
    amcs::threading::Thread::Id const threadId =
      amcs::threading::thisThread::getId();
    ThreadNamesMap::iterator threadNamePos =
      this->_threadNames.find(threadId);
   
    if(threadNamePos == _threadNames.end())
    {
      return amcs::lexical_cast<std::string>(threadId);
    }

    return threadNamePos->second;
  }

private:
  std::vector<Sink*> _sinks;

  typedef std::map<amcs::threading::Thread::Id, std::string> ThreadNamesMap;
  ThreadNamesMap _threadNames;

};



void addSink(Sink * sink)
{
    Logger::instance().addSink(sink);
}

void registerThisThread(std::string const& name)
{
  amcs::threading::Thread::Id threadId = amcs::threading::thisThread::getId();
  Logger::instance().registerThread(threadId, name);
}

namespace detail {
void dump(Log const& log)
{
  Logger::instance().dump(log);
}

std::string getThreadName()
{
  return Logger::instance().getThreadName();

}

} // namespace detail

} // namespace logging
} // namespace amcs

