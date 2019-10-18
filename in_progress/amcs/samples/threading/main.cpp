
#include <amcs/logging.h>
#include <amcs/threading.h>
#include <amcs/lexical_cast.h>

#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>


void print_current_thread_id()
{
	std::cout << "current amcs::threading::Thread id : " << amcs::threading::thisThread::getId() << std::endl;
}

void * f(void* args){
    int const value  = *static_cast<int*>(args);
    std::cout << "amcs::threading::Thread f parameters = " <<  value << std::endl;
    std::cout << "printing f amcs::threading::Thread id" << std::endl;;
    print_current_thread_id();
    return 0;
}

class Gbundle{
public:
        Gbundle(int x, int y) : x(x), y(y) {}
	int x, y;
};

void * g(void* args){
    Gbundle const& gb = *static_cast<Gbundle*>(args);
    std::cout << "Gbundle.x = " << gb.x << std::endl;
    std::cout << "Gbundle.y = " << gb.y << std::endl;
    return 0;
}

void * x(void* args){
  std::cout << "in function x" << std::endl;
  return 0;
}


void print_thread_id(std::string const & name, amcs::threading::Thread const& t)
{
  std::cout << "amcs::threading::Thread id " << name << " : "  << t.getId() << std::endl;
}

template<class P>
void print_pair(P & p, amcs::threading::Thread::Id const& id)
{
	std::cout << "amcs::threading::Thread name '" << p[id] << "' : amcs::threading::Thread id '" << amcs::lexical_cast<std::string>(id) << "'" << std::endl;
}

int main(){

	amcs::logging::addSink(new amcs::logging::ConsoleSink(amcs::logging::debug));

	int v = 25;
	amcs::threading::Thread tf(f, &v);
	print_thread_id("f", tf);
	Gbundle gb(10, 20);

	amcs::threading::Thread tg(g, &gb);
	print_thread_id("g", tg);

	amcs::threading::Thread tx(x);
	print_thread_id("x", tx);

	std::map<amcs::threading::Thread::Id, std::string> tnm;
	tnm[tf.getId()] = "tf";
	tnm[tg.getId()] = "tg";
	tnm[tx.getId()] = "tx";

	print_pair(tnm, tf.getId());
	print_pair(tnm, tg.getId());
	print_pair(tnm, tx.getId());

	tf.join();
	tg.join();
	tx.join();

	//amcs::threading::Thread::Id id = 5;//mainThread.id();
	LOG(amcs::logging::debug) << "amcs::threading::Thread id : " << amcs::threading::thisThread::getId();

	//std::cout << tf.id() < tg.id() << std::endl;
        //std::cout << "amcs::threading::Thread id : " << getCurrentThread().id() << std::endl;
	return 0;
}

