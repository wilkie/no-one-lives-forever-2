#ifdef __STL_BROKEN_USING_DIRECTIVE
using namespace __STLPORT_STD;
#else
using __STL_NEW_IO_NAMESPACE::basic_filebuf;
using __STL_NEW_IO_NAMESPACE::filebuf;
using __STL_NEW_IO_NAMESPACE::basic_ifstream;
using __STL_NEW_IO_NAMESPACE::basic_ofstream;
using __STL_NEW_IO_NAMESPACE::ifstream;
using __STL_NEW_IO_NAMESPACE::ofstream;
using __STL_NEW_IO_NAMESPACE::basic_fstream;
using __STL_NEW_IO_NAMESPACE::fstream;

# ifndef __STL_NO_WIDE_STREAMS
using __STL_NEW_IO_NAMESPACE::wofstream;
using __STL_NEW_IO_NAMESPACE::wfilebuf;
using __STL_NEW_IO_NAMESPACE::wifstream;
using __STL_NEW_IO_NAMESPACE::wfstream;
# endif
#endif