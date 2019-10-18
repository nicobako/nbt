#ifndef _AMCS_VARIANT_VISITOR_H_
#define _AMCS_VARIANT_VISITOR_H_

#include <amcs/variant/MonoState.h>
#include <amcs/variant/getIf.h>
#include <amcs/variant/Variant.h>

namespace amcs {
namespace variant {

template<class ReturnType, class VisitorT>
class Visitor
{
public:
  ReturnType operator()(MonoState<0> const& monoState) const { return ReturnType(); }  
  ReturnType operator()(MonoState<1> const& monoState) const { return ReturnType(); }
  ReturnType operator()(MonoState<2> const& monoState) const { return ReturnType(); }
  ReturnType operator()(MonoState<3> const& monoState) const { return ReturnType(); }
  ReturnType operator()(MonoState<4> const& monoState) const { return ReturnType(); }
  ReturnType operator()(MonoState<5> const& monoState) const { return ReturnType(); }
  ReturnType operator()(MonoState<6> const& monoState) const { return ReturnType(); }
  ReturnType operator()(MonoState<7> const& monoState) const { return ReturnType(); }
  ReturnType operator()(MonoState<8> const& monoState) const { return ReturnType(); }
  ReturnType operator()(MonoState<9> const& monoState) const { return ReturnType(); }
  ReturnType operator()() const { return ReturnType(); }
  template<class C>
  ReturnType operator()(C const& c) const
  {
    return static_cast< VisitorT const& >(*this)(c);
  }
};

template<class VisitorT>
class Visitor<void, VisitorT>
{
public:
  void operator()(MonoState<0> const& monoState) const {} 
  void operator()(MonoState<1> const& monoState) const {}
  void operator()(MonoState<2> const& monoState) const {}
  void operator()(MonoState<3> const& monoState) const {}
  void operator()(MonoState<4> const& monoState) const {}
  void operator()(MonoState<5> const& monoState) const {}
  void operator()(MonoState<6> const& monoState) const {}
  void operator()(MonoState<7> const& monoState) const {}
  void operator()(MonoState<8> const& monoState) const {}
  void operator()(MonoState<9> const& monoState) const {}
  void operator()() const {}
  template<class C>
  void operator()(C const& c) const
  {
    return static_cast< VisitorT const& >(*this)(c);
  }
};

template<
  class ReturnType,
  class VisitorT,
  template <class, class, class, class, class, class, class, class, class, class> class Variant, 
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9>
ReturnType visit(
  VisitorT const& visitor,
  Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const& variant)
{
  if(T0 const* t0 = getIf<T0>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t0);
  }
  else if(T1 const* t1 = getIf<T1>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t1);
  }
  else if(T2 const* t2 = getIf<T2>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t2);
  }
  else if(T3 const* t3 = getIf<T3>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t3);
  }
  else if(T4 const* t4 = getIf<T4>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t4);
  }
  else if(T5 const* t5 = getIf<T5>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t5);
  }
  else if(T6 const* t6 = getIf<T6>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t6);
  }
  else if(T7 const* t7 = getIf<T7>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t7);
  }
  else if(T8 const* t8 = getIf<T8>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t8);
  }
  else if(T9 const* t9 = getIf<T9>(&variant))
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)(*t9);
  }
  else
  {
    return static_cast< Visitor<ReturnType, VisitorT>const& >(visitor)();
  }
}

} // namespace variant
} // namespace amcs

#endif

