#include <amcs/messaging.h>
#include <amcs/threading.h>

#include <iostream>


typedef amcs::messaging::MessageQueue<256,5> MyMessageQueue;

void* func(void* messageQueue)
{
  MyMessageQueue const& mainMq = *reinterpret_cast<MyMessageQueue*>(messageQueue);  
  MyMessageQueue mq(mainMq);

  while(true)
  {
    std::string const message = mq.receive();
    std::cout << "thread received from main : " << message << std::endl;
    if(message == "exit")
    {
      break;
    }
    else
    {
      mq.send("finished processing : " + message);
    }
  }
  return 0;
}

int main()
{
  namespace msg = amcs::messaging;
  namespace thread = amcs::threading;
  
  MyMessageQueue mq;

  thread::Thread t(func, &mq);
  while(true)
  {
    std::cout << "enter message (type 'exit' to exit app) : ";
    std::string input;
    std::cin >> input;
    if(input == "exit")
    {
      break;
    }
    else
    {
      mq.send(input);
      std::string const messageFromThread = mq.receive();
      std::cout << "main received from thread : " << messageFromThread << std::endl;
    }
  }
  
  return 0;
}
