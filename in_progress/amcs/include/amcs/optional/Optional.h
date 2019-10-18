#ifndef _AMCS_OPTIONAL_OPTIONAL_H
#define _AMCS_OPTIONAL_OPTIONAL_H

#include <amcs/optional/NullOptional.h>

namespace amcs {
namespace optional {


template<class C>
class Optional
{
public:
  Optional() : _isValueSet(false)
  {
    clearBuffer();
  }

  Optional(NullOptional const& nullOptional) : _isValueSet(false)
  {
    clearBuffer();
  }

  Optional(C const& c) : _isValueSet(false)
  {
    setValue(c);
  }
  

  ~Optional()
  {
    clearBuffer();
  }

  operator bool() const {return _isValueSet;}
  bool operator !() const {return !_isValueSet;}

  Optional<C>& operator=(C const& c)
  {
    setValue(c);
    return *this;
  }

  Optional<C>& operator=(NullOptional nullOptional)
  {
    clearBuffer();
    return *this;
  }

  C const& value() const
  {
    return *reinterpret_cast<C const*>(_buffer);
  }

  C & value()
  {
    return *reinterpret_cast<C*>(_buffer);
  }

  void reset() 
  {
    clearBuffer();
  }

  C const* operator->() const
  {
    return reinterpret_cast<C const*>(_buffer);
  }
  
  C * operator->()
  {
    return reinterpret_cast<C*>(_buffer);
  }
  
  C & operator*() {return *reinterpret_cast<C*>(_buffer);}
  C const& operator*() const {return *reinterpret_cast<C*>(_buffer);}
  
private:

  void destroyValue()
  {
    reinterpret_cast<C*>(_buffer)->~C();
    _isValueSet = false;
  }
  
  void clearBuffer()
  {
    if(_isValueSet)
    {
      destroyValue();
    }
    int const size = sizeof(C);
    for(int i = 0; i < size; ++i)
    {
      _buffer[i] = char(0);
    }
    _isValueSet = false;
  }

  void setValue(C const& c)
  {
    if(_isValueSet)
    {
      clearBuffer();
    }
    // we do a 'placement new' ... look it up
    C* position = reinterpret_cast<C*>(_buffer);
    new(position) C(c);
    _isValueSet = true;
  }

  char _buffer[sizeof(C)];
  bool _isValueSet;
};

} // namespace optional
} // namespace amcs

#endif
