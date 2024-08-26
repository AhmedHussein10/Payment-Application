#ifndef PLATFORM_TYPE_H_INCLUDED
#define PLATFORM_TYPE_H_INCLUDED

#define CPU_TYPE_8 8
#define CPU_TYPE_16 16
#define CPU_TYPE_32 32
#define CPU_TYPE_64 64

#define CPU_TYPE (CPU_TYPE_64)

#if(CPU_TYPE==CPU_TYPE_64)
typedef unsigned char boolean;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef float float32;
typedef double float64;

#elif(CPU_TYPE==CPU_TYPE_32)

typedef unsigned char boolean;
typedef unsigned char unit8;
typedef unsigned short unit16;
typedef unsigned long unit32;
typedef unsigned long long unit64;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef signed long long sint64;
typedef float float32;
typedef double float64;

#elif(CPU_TYPE==CPU_TYPE_16)

typedef unsigned char boolean;
typedef unsigned char unit8;
typedef unsigned short unit16;
typedef unsigned long unit32;
typedef unsigned long long unit64;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef signed long long sint64;
typedef float float32;
typedef double float64;

#elif(CPU_TYPE==CPU_TYPE_8)

typedef unsigned char boolean;
typedef unsigned char unit8;
typedef unsigned short unit16;
typedef unsigned long unit32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef float float32;

#endif


#endif // PLATFORM_TYPE_H_INCLUDED
