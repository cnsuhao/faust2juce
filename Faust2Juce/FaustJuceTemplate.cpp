#include "FaustJuce.h"

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
//#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <math.h>

using namespace std ;


#ifdef __GNUC__

//-------------------------------------------------------------------
// Generic min and max using gcc extensions
//-------------------------------------------------------------------

#define max(x,y) ((x)>?(y))
#define min(x,y) ((x)<?(y))

//abs(x) should be already predefined

#else

//-------------------------------------------------------------------
// Generic min and max using c++ inline
//-------------------------------------------------------------------

inline int 		max (unsigned int a, unsigned int b) { return (a>b) ? a : b; }
inline int 		max (int a, int b) 			{ return (a>b) ? a : b; }

inline long 	max (long a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (int a, long b) 		{ return (a>b) ? a : b; }
inline long 	max (long a, int b) 		{ return (a>b) ? a : b; }

inline float 	max (float a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (int a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, int b) 		{ return (a>b) ? a : b; }
inline float 	max (long a, float b) 		{ return (a>b) ? a : b; }
inline float 	max (float a, long b) 		{ return (a>b) ? a : b; }

inline double 	max (double a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (int a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, int b) 		{ return (a>b) ? a : b; }
inline double 	max (long a, double b) 		{ return (a>b) ? a : b; }
inline double 	max (double a, long b) 		{ return (a>b) ? a : b; }
inline double 	max (float a, double b) 	{ return (a>b) ? a : b; }
inline double 	max (double a, float b) 	{ return (a>b) ? a : b; }


inline int 		min (int a, int b) 			{ return (a<b) ? a : b; }

inline long 	min (long a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (int a, long b) 		{ return (a<b) ? a : b; }
inline long 	min (long a, int b) 		{ return (a<b) ? a : b; }

inline float 	min (float a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (int a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, int b) 		{ return (a<b) ? a : b; }
inline float 	min (long a, float b) 		{ return (a<b) ? a : b; }
inline float 	min (float a, long b) 		{ return (a<b) ? a : b; }

inline double 	min (double a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (int a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, int b) 		{ return (a<b) ? a : b; }
inline double 	min (long a, double b) 		{ return (a<b) ? a : b; }
inline double 	min (double a, long b) 		{ return (a<b) ? a : b; }
inline double 	min (float a, double b) 	{ return (a<b) ? a : b; }
inline double 	min (double a, float b) 	{ return (a<b) ? a : b; }

#endif

inline int lsr (int x, int n) { return int(((unsigned int)x) >> n); }

inline int int2pow2 (int x) { int r=0; while ((1<<r)<x) r++; return r; }

/******************************************************************************
 *******************************************************************************
 *
 *							       VECTOR INTRINSICS
 *
 *******************************************************************************
 *******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }

<<includeIntrinsic>>

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

<<includeclass>>

dsp* faustCreateDSP()
{
	return new mydsp();
}
