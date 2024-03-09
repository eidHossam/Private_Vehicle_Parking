#ifndef MY_PLATFORM_TYPES_H_
#define MY_PLATFORM_TYPES_H_
#include <stdint.h>

/*--------Types------------*/
#define NULL  (void*)(0u)

typedef enum{
    E_OK,
    E_NOK
}eStatus_t;

typedef unsigned char        boolean;
#define TRUE                (1U)
#define FALSE               (0U)

typedef signed char          sint8_t;
typedef signed short         sint16_t;
typedef signed long          sint32_t;
typedef signed long long     sint64_t;

typedef uint8_t    uint8_t;
typedef uint16_t   uint16_t;
typedef uint32_t   uint32_t;
typedef uint64_t   uint64_t;

typedef float                float32_t;
typedef double               float64_t;

typedef volatile sint8_t     vsint8_t;
typedef volatile sint16_t    vsint16_t;
typedef volatile sint32_t    vsint32_t;
typedef volatile sint64_t    vsint64_t;

typedef volatile uint8_t     vuint8_t;
typedef volatile uint16_t    vuint16_t;
typedef volatile uint32_t    vuint32_t;
typedef volatile uint64_t    vuint64_t;

typedef void(*Ptr_Func)(void);
#endif
