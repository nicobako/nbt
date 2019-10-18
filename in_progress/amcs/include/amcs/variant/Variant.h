#ifndef _AMCS_VARIANT_VARIANT_H_
#define _AMCS_VARIANT_VARIANT_H_

#include <amcs/variant/MonoState.h>
#include <amcs/variant/getIf.h>

namespace amcs {
namespace variant {

/** \brief An object that can store one object at a time f varying types.
 *
 * \todo Move Size<> and Max<> classes into a separate amcs::mpl library.
 */

template<
  class T0,
  class T1 = MonoState<1>,
  class T2 = MonoState<2>,
  class T3 = MonoState<3>,
  class T4 = MonoState<4>,
  class T5 = MonoState<5>,
  class T6 = MonoState<6>,
  class T7 = MonoState<7>,
  class T8 = MonoState<8>,
  class T9 = MonoState<9> >
class Variant
{
public:

typedef Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> VariantType;

Variant() { set<T0>(0, T0()); }

Variant(Variant const& rhs) {
  if(rhs.index() == 0)
  {
    set<T0>(0, *rhs.t0());
  }
  else if(rhs.index() == 1)
  {
    set<T1>(1, *rhs.t1());
  }
  else if(rhs.index() == 2)
  {
    set<T2>(2, *rhs.t2());
  }
  else if(rhs.index() == 3)
  {
    set<T3>(3, *rhs.t3());
  }
  else if(rhs.index() == 4)
  {
    set<T4>(4, *rhs.t4());
  }
  else if(rhs.index() == 5)
  {
    set<T5>(5, *rhs.t5());
  }
  else if(rhs.index() == 6)
  {
    set<T6>(6, *rhs.t6());
  }
  else if(rhs.index() == 7)
  {
    set<T7>(7, *rhs.t7());
  }
  else if(rhs.index() == 8)
  {
    set<T8>(8, *rhs.t8());
  }
  else if(rhs.index() == 9)
  {
    set<T9>(9, *rhs.t9());
  }
  else
  {
    set<T0>(0, T0());
  }

}

Variant(T0 value){ set<T0>(0, value);}
Variant(T1 value){ set<T1>(1, value);}
Variant(T2 value){ set<T2>(2, value);}
Variant(T3 value){ set<T3>(3, value);}
Variant(T4 value){ set<T4>(4, value);}
Variant(T5 value){ set<T5>(5, value);}
Variant(T6 value){ set<T6>(6, value);}
Variant(T7 value){ set<T7>(7, value);}
Variant(T8 value){ set<T8>(8, value);}
Variant(T9 value){ set<T9>(9, value);}

~Variant() { destroyCurrentType(); }

VariantType & operator=(T0 const& value) { destroyCurrentType(); return set<T0>(0, value); }
VariantType & operator=(T1 const& value) { destroyCurrentType(); return set<T1>(1, value); }
VariantType & operator=(T2 const& value) { destroyCurrentType(); return set<T2>(2, value); }
VariantType & operator=(T3 const& value) { destroyCurrentType(); return set<T3>(3, value); }
VariantType & operator=(T4 const& value) { destroyCurrentType(); return set<T4>(4, value); }
VariantType & operator=(T5 const& value) { destroyCurrentType(); return set<T5>(5, value); }
VariantType & operator=(T6 const& value) { destroyCurrentType(); return set<T6>(6, value); }
VariantType & operator=(T7 const& value) { destroyCurrentType(); return set<T7>(7, value); }
VariantType & operator=(T8 const& value) { destroyCurrentType(); return set<T8>(8, value); }
VariantType & operator=(T9 const& value) { destroyCurrentType(); return set<T9>(9, value); }

int const& index() const { return _index; }

protected:

template<class C>
VariantType & set(int const index, C const& value)
{
  C * position = reinterpret_cast<C*>(_types);
  new(position) C(value);
  _index = index;
  return *this;
}

template<class C>
void destroy()
{
  C * position = reinterpret_cast<C*>(_types);
  position->~C();
}

void destroyCurrentType()
{
  if(_index == 0)
  {
    destroy<T0>();
  }
  else if(_index == 1)
  {
    destroy<T1>();
  }
  else if(_index == 2)
  {
    destroy<T2>();
  }
  else if(_index == 3)
  {
    destroy<T3>();
  }
  else if(_index == 4)
  {
    destroy<T4>();
  }
  else if(_index == 5)
  {
    destroy<T5>();
  }
  else if(_index == 6)
  {
    destroy<T6>();
  }
  else if(_index == 7)
  {
    destroy<T7>();
  }
  else if(_index == 8)
  {
    destroy<T8>();
  }
  else if(_index == 9)
  {
    destroy<T9>();
  }
  else
  {
  }
}

T0 const* t0() const { return this->get<T0>(); }
T1 const* t1() const { return this->get<T1>(); }
T2 const* t2() const { return this->get<T2>(); }
T3 const* t3() const { return this->get<T3>(); }
T4 const* t4() const { return this->get<T4>(); }
T5 const* t5() const { return this->get<T5>(); }
T6 const* t6() const { return this->get<T6>(); }
T7 const* t7() const { return this->get<T7>(); }
T8 const* t8() const { return this->get<T8>(); }
T9 const* t9() const { return this->get<T9>(); }


T0 * t0()  { return this->get<T0>(); }
T1 * t1()  { return this->get<T1>(); }
T2 * t2()  { return this->get<T2>(); }
T3 * t3()  { return this->get<T3>(); }
T4 * t4()  { return this->get<T4>(); }
T5 * t5()  { return this->get<T5>(); }
T6 * t6()  { return this->get<T6>(); }
T7 * t7()  { return this->get<T7>(); }
T8 * t8()  { return this->get<T8>(); }
T9 * t9()  { return this->get<T9>(); }

friend T0 const* getIf<>(VariantType const* variant);
friend T1 const* getIf<>(VariantType const* variant);
friend T2 const* getIf<>(VariantType const* variant);
friend T3 const* getIf<>(VariantType const* variant);
friend T4 const* getIf<>(VariantType const* variant);
friend T5 const* getIf<>(VariantType const* variant);
friend T6 const* getIf<>(VariantType const* variant);
friend T7 const* getIf<>(VariantType const* variant);
friend T8 const* getIf<>(VariantType const* variant);
friend T9 const* getIf<>(VariantType const* variant);


friend T0 * getIf<>(VariantType * variant);
friend T1 * getIf<>(VariantType * variant);
friend T2 * getIf<>(VariantType * variant);
friend T3 * getIf<>(VariantType * variant);
friend T4 * getIf<>(VariantType * variant);
friend T5 * getIf<>(VariantType * variant);
friend T6 * getIf<>(VariantType * variant);
friend T7 * getIf<>(VariantType * variant);
friend T8 * getIf<>(VariantType * variant);
friend T9 * getIf<>(VariantType * variant);


private:
template<class T>
T const* get() const
{
  T const* position = reinterpret_cast<T const*>(_types);
  return position;
}

template<class T>
T * get() 
{
  T * position = reinterpret_cast<T*>(_types);
  return position;
}

int _index;

template<class C>
struct SizeOf{
  static const int value = sizeof(C);
};

template<int a, int b>
struct Max2 {
  static const int value = a >= b ? a : b;
};

template<int a, int b, int c>
struct Max3 {
  static const int value = 
    Max2<
      Max2<a, b>::value,
      Max2<a, c>::value
    >::value;
};

template<int a, int b, int c, int d>
struct Max4 {
  static const int value = 
    Max2<
      Max3<a, b, c>::value,
      d
    >::value;
};

template<int a, int b, int c, int d, int e>
struct Max5 {
  static const int value = 
    Max2<
      Max4<a, b, c, d>::value,
      e
    >::value;
};

template<int a, int b, int c, int d, int e, int f, int g, int h, int i, int j>
struct Max10 {
  static const int value = 
    Max2<
      Max5<a, b, c, d, e>::value,
      Max5<f, g, h, i, j>::value
    >::value;
};

char _types[ 
  Max10< 
    SizeOf<T0>::value,
    SizeOf<T1>::value,
    SizeOf<T2>::value,
    SizeOf<T3>::value,
    SizeOf<T4>::value,
    SizeOf<T5>::value,
    SizeOf<T6>::value,
    SizeOf<T7>::value,
    SizeOf<T8>::value,
    SizeOf<T9>::value
  >::value
];

};


} // namespace variant
} // namespace amcs

#endif

