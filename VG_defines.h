#ifndef __VG_DEFINES_H__
#define __VG_DEFINES_H__

#include "pub_tool_basics.h" 		// this include the types like HChar, etc
#include "pub_tool_libcbase.h"		// libc
#include "pub_tool_mallocfree.h"	// malloc
#include "pub_tool_libcprint.h"		// VG_(*printf)

#undef 	cs_strncpy
#define cs_strncpy 		VG_(strncpy)

#undef cs_strcpy
#define cs_strcpy 		VG_(strcpy)

#undef cs_memset
#define cs_memset 		VG_(memset)

#undef cs_memcpy
#define cs_memcpy 		VG_(memcpy)

#undef cs_memmove
#define cs_memmove 		VG_(memmove)

#undef cs_strlen
#define cs_strlen 		VG_(strlen)

#undef cs_strcmp
#define cs_strcmp 		VG_(strcmp)

#undef cs_strncmp
#define cs_strncmp 		VG_(strncmp)

#undef cs_strrchr
#define cs_strrchr		VG_(strrchr)

#undef cs_strchr
#define cs_strchr		VG_(strchr)
 
#undef cs_strstr
#define cs_strstr 		VG_(strstr)

#undef cs_tolower
#define cs_tolower 		VG_(tolower)

#undef cs_sprintf
#define cs_sprintf		VG_(sprintf)

static inline int cs_atoi (const char * str) { HChar * end; return VG_(strtoll10)(str, &end); /* assume no overflow */} 

// this is ONLY for cs.c
static inline int vg_vsnprintf(char *str, size_t size, const char *format, va_list ap) { return VG_(vsnprintf)(str, size, format, ap); } // Note: never fails by returning negative integer
static inline void * vg_malloc(size_t n) { return VG_(malloc)("anyname", n); }
static inline void * vg_calloc(size_t n, size_t s) { return VG_(calloc)("anyname", n, s); }
static inline void * vg_realloc(void* p, size_t n) { return VG_(realloc)("anyname", p, n); }
static inline void vg_free(void *p) { VG_(free)(p); }
//#define vg_vsnprintf 
//#define strtol VG_(strtoll10) // Note: assume no overflow...

#endif // __VG_DEFINES_H__
