/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_TEMPBUF_H
#define __SGI_STL_INTERNAL_TEMPBUF_H

# ifndef __STLPORT_CLIMITS
#  include <climits>
# endif
# ifndef __STLPORT_CSTDLIB
#  include <cstdlib>
# endif
# ifndef __SGI_STL_INTERNAL_UNINITIALIZED_H
#  include <stl/_uninitialized.h>
# endif

__STL_BEGIN_NAMESPACE

template <class _Tp>
pair<_Tp*, ptrdiff_t>  __STL_CALL
__get_temporary_buffer(ptrdiff_t __len, _Tp*);

#ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS

template <class _Tp>
inline pair<_Tp*, ptrdiff_t>  __STL_CALL get_temporary_buffer(ptrdiff_t __len) {
  return __get_temporary_buffer(__len, (_Tp*) 0);
}

#endif /* __STL_EXPLICIT_FUNCTION_TMPL_ARGS */


# if ! (defined(__STL_NO_EXTENSIONS) && defined (__STL_EXPLICIT_FUNCTION_TMPL_ARGS))
// This overload is not required by the standard; it is an extension.
// It is supported for backward compatibility with the HP STL, and
// because not all compilers support the language feature (explicit
// function template arguments) that is required for the standard
// version of get_temporary_buffer.
template <class _Tp>
inline pair<_Tp*, ptrdiff_t>  __STL_CALL
get_temporary_buffer(ptrdiff_t __len, _Tp*) {
  return __get_temporary_buffer(__len, (_Tp*) 0);
}
# endif

template <class _Tp>
inline void  __STL_CALL return_temporary_buffer(_Tp* __p) {
// SunPro brain damage
  free((char*)__p);
}

template <class _ForwardIterator, class _Tp>
class _Temporary_buffer {
private:
  ptrdiff_t  _M_original_len;
  ptrdiff_t  _M_len;
  _Tp*       _M_buffer;

  void _M_allocate_buffer() {
    _M_original_len = _M_len;
    _M_buffer = 0;

    if (_M_len > (ptrdiff_t)(INT_MAX / sizeof(_Tp)))
      _M_len = INT_MAX / sizeof(_Tp);

    while (_M_len > 0) {
      _M_buffer = (_Tp*) malloc(_M_len * sizeof(_Tp));
      if (_M_buffer)
        break;
      _M_len /= 2;
    }
  }

  void _M_initialize_buffer(const _Tp&, __true_type) {}
  void _M_initialize_buffer(const _Tp& val, __false_type) {
    uninitialized_fill_n(_M_buffer, _M_len, val);
  }

public:
  ptrdiff_t size() const { return _M_len; }
  ptrdiff_t requested_size() const { return _M_original_len; }
  _Tp* begin() { return _M_buffer; }
  _Tp* end() { return _M_buffer + _M_len; }

  _Temporary_buffer(_ForwardIterator __first, _ForwardIterator __last) {
    // Workaround for a __type_traits bug in the pre-7.3 compiler.
#   if defined(__sgi) && !defined(__GNUC__) && _COMPILER_VERSION < 730
    typedef typename __type_traits<_Tp>::is_POD_type _Trivial;
#   else
     typedef typename __type_traits<_Tp>::has_trivial_default_constructor
             _Trivial;
#   endif
    __STL_TRY {
      _M_len = 0;
      distance(__first, __last, _M_len);
      _M_allocate_buffer();
      if (_M_len > 0)
        _M_initialize_buffer(*__first, _Trivial());
    }
    __STL_UNWIND(free(_M_buffer); _M_buffer = 0; _M_len = 0);
  }
 
  ~_Temporary_buffer() {  
    _Destroy(_M_buffer, _M_buffer + _M_len);
    free(_M_buffer);
  }

private:
  // Disable copy constructor and assignment operator.
  _Temporary_buffer(const _Temporary_buffer<_ForwardIterator, _Tp>&) {}
  void operator=(const _Temporary_buffer<_ForwardIterator, _Tp>&) {}
};

# ifndef __STL_NO_EXTENSIONS

// Class temporary_buffer is not part of the standard.  It is an extension.

template <class _ForwardIterator, 
          class _Tp 
#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
                    = typename iterator_traits<_ForwardIterator>::value_type
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */
         >
struct temporary_buffer : public _Temporary_buffer<_ForwardIterator, _Tp>
{
  temporary_buffer(_ForwardIterator __first, _ForwardIterator __last)
    : _Temporary_buffer<_ForwardIterator, _Tp>(__first, __last) {}
  ~temporary_buffer() {}
};

# endif /* __STL_NO_EXTENSIONS */
    
__STL_END_NAMESPACE

# ifndef __STL_LINK_TIME_INSTANTIATION
#  include <stl/_tempbuf.c>
# endif

#endif /* __SGI_STL_INTERNAL_TEMPBUF_H */

// Local Variables:
// mode:C++
// End:
