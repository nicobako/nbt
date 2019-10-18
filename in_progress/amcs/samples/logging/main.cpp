/*
 * main.cpp
 *
 *  Created on: Aug 6, 2019
 *      Author: bakomihalisn
 */

#include <amcs/lexical_cast.h>
#include <amcs/logging.h>
#include <amcs/threading.h>

#include <fstream>

class FileSink : public amcs::logging::Sink {
public:
    FileSink(amcs::logging::SeverityLevel const& severityLevel, const char* filename) : 
        amcs::logging::Sink(severityLevel, new amcs::logging::CsvFormatter()),
        file(filename)
    {
        
    }

  ~FileSink(){
    delete this->_formatter; 
  }
    
    void dump(amcs::logging::Log const& log){
        file << (*this->_formatter)(log);
        file.flush();
    }
    
private:
    std::ofstream file;
};

void * f(void * args)
{
  LOG(amcs::logging::debug) << "message from unregistered thread";
  return 0;
}

void * g(void * args)
{
    int const& x = *reinterpret_cast<int*>(args);
    
    amcs::logging::registerThisThread(amcs::lexical_cast<std::string>(x));
    LOG(amcs::logging::debug) << "message from registered thread";
  return 0;
}

int main() {
    // add sinks
    namespace log = amcs::logging;
    namespace thread = amcs::threading;

    log::addSink(new log::ConsoleSink(log::debug));
    log::addSink(new log::ConsoleSink(log::info));
    log::addSink(new log::ConsoleSink(log::warning));

    log::registerThisThread("main");

    // // adding a user-defined sink
    log::addSink(new FileSink(log::debug, "log.txt"));

    // add some log  messages
    LOG(log::debug) << "debug message using the macro 'LOG'";
    LOG(log::info) << "info message" << " with int at the end " << 5;
    LOG(log::warning) << "warning message "<< "with extra stuff";
    LOG(log::error) << "an error!!!";

    amcs::threading::Thread tf(f);

    int x = 5;
    thread::Thread tg(g, &x);
    int hundred = 100;
    thread::Thread tg100(g, &hundred);
    tf.join();
    tg.join();
    tg100.join();
    
    return 0;
}



