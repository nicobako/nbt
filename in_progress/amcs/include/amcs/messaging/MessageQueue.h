/*
 * MessageQueue.h
 *
 *  Created on: Aug 8, 2019
 *      Author: wynnj
 */

#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include <amcs/lexical_cast.h>

#include <unistd.h>
#include <mqueue.h>
#include <string>
#include <errno.h>
#include <cstring>

namespace amcs {
namespace messaging {

static int messageQueueCounter;

template<int bufferSize = 256, int numMessages = 10>
class MessageQueue{
public:
	typedef mqd_t MessageQueueId;
	typedef mq_attr MessageQueueAttributes;

	MessageQueue() :
		_messageSize(bufferSize),
		_numMessages(numMessages),
		_buffer(),
		_name(std::string("/mq-") + lexical_cast<std::string>(messageQueueCounter++)),
		_status("creating new MessageQueue - not yet initialized"),
		_attributes(),
		_id(0),
		_isOpen(false)
	{
		// initialize attributes to zero
		memset(&_attributes, 0, sizeof(MessageQueueAttributes));
		memset(&_buffer, '\0', bufferSize);
		this->create();
	}

	MessageQueue(std::string const & name) :
		_messageSize(bufferSize),
		_numMessages(numMessages),
		_buffer(),
		_name(name),
		_status("creating new MessageQueue - not yet initialized"),
		_attributes(),
		_id(0),
		_isOpen(false)
	{
		// initialize attributes to zero
		memset(&_attributes, 0, sizeof(MessageQueueAttributes));
		memset(&_buffer, '\0', bufferSize);
		this->create();
	}

	MessageQueue(MessageQueue const& other) :
		_messageSize(bufferSize),
		_numMessages(numMessages),
		_buffer(),
		_name(other.name()),
		_status("connecting to existing MessageQueue - not yet initialized"),
		_attributes(other.attributes()),
		_id(0),
		_isOpen(other.isOpen())
	{
		memset(&_attributes, 0, sizeof(MessageQueueAttributes));
		memset(&_buffer, '\0', bufferSize);
		if(!other.isOpen())
		{
			return;
		}
		this->open();
	}
	
	~MessageQueue()
	{
		this->close();
	}

	void send(std::string const& message)
	{
		if(!this->_isOpen)
		{
			return;
		}
		int sendStatus = mq_send(this->_id, message.c_str(), message.size(), 0);
		if(sendStatus < 0)
		{
			this->_status = "unable to send message";
		}
	}

	std::string const receive()
	{
		if(!this->_isOpen)
		{
			return "";
		}
		ssize_t outSize;
		size_t inSize = this->_messageSize;
		outSize = mq_receive(this->_id, this->_buffer, inSize, 0);
		if(outSize == -1)
		{
			this->_status = "unable to receive message";
			return "";
		}
		std::string s(this->_buffer);
		memset(this->_buffer, '\0', bufferSize);
		return s;
	}

	void close()
	{
		if(!this->_isOpen || this->_id == -1){
			return;
		}
		if(mq_close(this->_id) == -1)
		{
			this->_status = "failed to close MessageQueue";
		}
		this->_isOpen = false;
		this->_status = "closed";
	}

	void destroy()
	{
		mq_unlink(this->_name.c_str());
	}

	std::string const & status() const {return this->_status;}
	bool const isOpen() const {return this->_isOpen;}
	std::string const& name() const {return this->_name;}

protected:
	MessageQueueAttributes const attributes() const {return this->_attributes; }
	int const messageSize() const { return this->_messageSize; }
	
private:

	void create(){
		if(this->_name == "/"){
			this->_status = "invalid MessageQueue name : must be string greater than lenght 0";
			return;
		}
		
		this->_attributes.mq_msgsize = static_cast<size_t>(this->_messageSize);
		this->_attributes.mq_maxmsg = static_cast<size_t>(this->_numMessages);

		this->resetErrno();
		this->_id = mq_open(this->_name.c_str(), O_CREAT | O_RDWR | O_CLOEXEC, 0777, &this->_attributes);
		if(errorOccured())
		{
			this->_status = "failed to create MessageQueue '" + this->_name + "'";
			return;
		}
		this->_isOpen = true;
		this->_status = "MessageQueue '" + this->_name + "' created and open";
	}

	void open(){
		this->resetErrno();
		this->_id = mq_open(this->_name.c_str(), O_RDWR);
		if(this->errorOccured()){
			this->_status = "unable to connect to MessageQueue '" + this->_name + "'";
			return;
		}
		this->_isOpen = true;
	}
	
	void const resetErrno() const {
		errno = 0;
	}
	bool const errorOccured() const {
		return errno != 0;
	}
	int _messageSize;
	int _numMessages;
	char _buffer[bufferSize];
	std::string _name;
	std::string _status;
	MessageQueueAttributes _attributes;
	MessageQueueId _id;
	bool _isOpen;
};

} // namespace messaging
} // namespace amcs
#endif /* MESSAGEQUEUE_H_ */
