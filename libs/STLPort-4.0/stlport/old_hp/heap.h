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

#ifndef __SGI_STL_HEAP_H
#define __SGI_STL_HEAP_H

# ifndef __STL_OUTERMOST_HEADER_ID
#  define __STL_OUTERMOST_HEADER_ID 0x12
#  include <stl/_prolog.h>
# endif

#include <stl/_heap.h>

#ifdef __STL_USE_NAMESPACES

# ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace std;
# else
using STLPORT::push_heap;
using STLPORT::pop_heap;
using STLPORT::make_heap;
using STLPORT::sort_heap;
# endif

#endif /* __STL_USE_NAMESPACES */

# if (__STL_OUTERMOST_HEADER_ID == 0x12)
#  include <stl/_epilog.h>
#  undef __STL_OUTERMOST_HEADER_ID
# endif

#endif /* __SGI_STL_HEAP_H */

// Local Variables:
// mode:C++
// End:
