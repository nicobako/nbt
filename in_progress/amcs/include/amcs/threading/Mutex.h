#ifndef _AMCS_THREADING_MUTEX_H_
#define _AMCS_THREADING_MUTEX_H_

#include <unistd.h>
#include <pthread.h>

namespace amcs
{
   namespace threading
   {
      class Mutex
      {
      public:
         Mutex()
         {
            pthread_mutex_init(&_mutexId, NULL);
         }
         ~Mutex()
         {

         }
         void lock()
         {
            pthread_mutex_lock(&_mutexId);
         }
         void unlock()
         {
            pthread_mutex_unlock(&_mutexId);
         }
         void destroy()
         {
            pthread_mutex_destroy(&_mutexId);
         }
         bool try_lock()
         {
            bool canLock = false;

            if (pthread_mutex_trylock(&_mutexId) == 0)
            {
               canLock = true;
            }

            return canLock;
         }
      private:
         pthread_mutex_t _mutexId;
      };
   }
}

#endif /* _AMCS_THREADING_MUTEX_H_ */
