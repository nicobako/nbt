#ifndef _AMCS_VARIANT_GETIF_H_
#define _AMCS_VARIANT_GETIF_H_

namespace amcs {
namespace variant {

template<
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T0 const* getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const* variant)
{
  if(variant->index() == 0)
  {
    return variant->t0();
  }
  else
  {
    return 0;
  } 
}

template<
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T0 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 0)
  {
    return variant->t0();
  }
  else
  {
    return 0;
  } 
}


template<
  class T1,
  class T0,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T1 const* getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const* variant)
{
  if(variant->index() == 1)
  {
    return variant->t1();
  }
  else
  {
    return 0;
  } 
}

template<
  class T1,
  class T0,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T1 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 1)
  {
    return variant->t1();
  }
  else
  {
    return 0;
  } 
}


template<
  class T2,
  class T0,
  class T1,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T2 const* getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const* variant)
{
  if(variant->index() == 2)
  {
    return variant->t2();
  }
  else
  {
    return 0;
  } 
}

template<
  class T2,
  class T0,
  class T1,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T2 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 2)
  {
    return variant->t2();
  }
  else
  {
    return 0;
  } 
}

template<
  class T3,
  class T0,
  class T1,
  class T2,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T3 const * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const * variant)
{
  if(variant->index() == 3)
  {
    return variant->t3();
  }
  else
  {
    return 0;
  } 
}

template<
  class T3,
  class T0,
  class T1,
  class T2,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T3 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 3)
  {
    return variant->t3();
  }
  else
  {
    return 0;
  } 
}

template<
  class T4,
  class T0,
  class T1,
  class T2,
  class T3,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T4 const* getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const* variant)
{
  if(variant->index() == 4)
  {
    return variant->t4();
  }
  else
  {
    return 0;
  } 
}

template<
  class T4,
  class T0,
  class T1,
  class T2,
  class T3,
  class T5,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T4 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 4)
  {
    return variant->t4();
  }
  else
  {
    return 0;
  } 
}

template<
  class T5,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T5 const* getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const* variant)
{
  if(variant->index() == 5)
  {
    return variant->t5();
  }
  else
  {
    return 0;
  } 
}

template<
  class T5,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T6,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T5 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 5)
  {
    return variant->t5();
  }
  else
  {
    return 0;
  } 
}


template<
  class T6,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T6 const* getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const* variant)
{
  if(variant->index() == 6)
  {
    return variant->t6();
  }
  else
  {
    return 0;
  } 
}

template<
  class T6,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T7,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T6 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 6)
  {
    return variant->t6();
  }
  else
  {
    return 0;
  } 
}

template<
  class T7,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T7 const* getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const* variant)
{
  if(variant->index() == 7)
  {
    return variant->t7();
  }
  else
  {
    return 0;
  } 
}

template<
  class T7,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T8,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T7 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 7)
  {
    return variant->t7();
  }
  else
  {
    return 0;
  } 
}


template<
  class T8,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T8 const* getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const* variant)
{
  if(variant->index() == 8)
  {
    return variant->t8();
  }
  else
  {
    return 0;
  } 
}

template<
  class T8,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T9,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T8 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 8)
  {
    return variant->t8();
  }
  else
  {
    return 0;
  } 
}


template<
  class T9,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T9 const* getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const* variant)
{
  if(variant->index() == 9)
  {
    return variant->t9();
  }
  else
  {
    return 0;
  } 
}

template<
  class T9,
  class T0,
  class T1,
  class T2,
  class T3,
  class T4,
  class T5,
  class T6,
  class T7,
  class T8,
  template <class, class, class, class, class, class, class, class, class, class> class Variant >
T9 * getIf( Variant<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> * variant)
{
  if(variant->index() == 9)
  {
    return variant->t9();
  }
  else
  {
    return 0;
  } 
}

} // namespace variant
} // namespace amcs

#endif

