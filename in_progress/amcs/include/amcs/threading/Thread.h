#ifndef _AMCS_THREADING_THREAD_H_
#define _AMCS_THREADING_THREAD_H_

#include <pthread.h>

namespace amcs {
namespace threading {

/** \brief Allows users to customize properties of the thread.
 *
 *  \param stackSize The stack size of the thread.
 *  \param priority The thread's priority.
 */
struct ThreadParameters{
	ThreadParameters(int const stackSize, int const priority);
	int stackSize;
	int priority;
};

/** \brief The argument to a function that will run in its own thread.
 */
typedef void* ArgPtr;

/** \brief The function that will run in its own thread.
 */
typedef void* Function(ArgPtr arg);


/** \brief An individual thread.
 *
 *  The Thread class encapsulates the concept of a thread.
 *  A thread is created by providing it with a \p function,
 *  and an optional \p argument to that function. 
 *  The thread begins to *run* once it is instantiated (i.e. created).
 *  Once the thread starts, the thread from which the thread object was created
 *  has control of the thread and can *join* it or *destroy* it.
 *
 *  It may be used as follows:
 *
 * ```cpp
 * 
 * ```
 * \todo Add a *destroy()* member function.
 * \todo Add a *detach()* member function.
 */
class Thread{
public:

	typedef pthread_t Id;

	Thread(Function function, ArgPtr arg, ThreadParameters threadParameters = ThreadParameters(256, 0));

	Thread(Function function, ThreadParameters threadParameters = ThreadParameters(256, 0));

	void join();

	Id getId() const;

private:
  void setName();
	void start(Function function, ArgPtr arg, ThreadParameters threadParameters);

	Id _thread;
};

/** \brief Contains functionality that may be accessed from the current thread.
 */
namespace thisThread{

/** \brief Get the ID of the current thread.
 */
Thread::Id getId();

}
#endif

} // namespace threading
} // namespace amcs

