#include <stdint.h>

typedef uint8_t  BYTE;

typedef struct
{
    BYTE first;
    BYTE second;
    BYTE third;
} __attribute__((__packed__))
FIRST3BYTES;
