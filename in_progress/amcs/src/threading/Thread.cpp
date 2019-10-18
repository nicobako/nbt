#include <amcs/threading/Thread.h>
#include <amcs/lexical_cast.h>
#include <sys/types.h>
#include <pthread.h>

namespace amcs {
namespace threading {

ThreadParameters::ThreadParameters(int const stackSize, int const priority) :
	stackSize(stackSize), 
	priority(priority)
{
}

Thread::Thread(Function function, ArgPtr arg, ThreadParameters threadParameters) :
	_thread(0)
{
	start(function, arg, threadParameters);
}

Thread::Thread(Function function, ThreadParameters threadParameters) :
	_thread(0)
{
	start(function, (void*)(0), threadParameters);
}

void Thread::join()
{
	pthread_join(_thread, NULL);
}


Thread::Id Thread::getId() const
{
    return this->_thread;
}

void Thread::start(Function function, ArgPtr arg, ThreadParameters threadParameters)
{
	// initialize the attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	// create the priority struct
	sched_param priority_struct;
	priority_struct.sched_priority = threadParameters.priority;
	pthread_attr_setschedparam(&attr, &priority_struct);
	// set the stack size
	pthread_attr_setstacksize(&attr, threadParameters.stackSize);
	// create the thread
	pthread_create(&_thread, &attr, function, arg);
}

namespace thisThread {

Thread::Id getId()
{
	pthread_t thread = pthread_self();
	return Thread::Id(thread);
}

} // namespace thisThread
} // namespace threading
} // namespace amcs

