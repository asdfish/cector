#ifndef INT_VECTOR_H

#define INCLUDE_VECTOR_GENERATE_HEADER_MACRO
#include <cector.h>

VECTOR_GENERATE_HEADER(int,
    int,
    int_vector,
    0, -1,
    int_vector_at,
    int_vector_init,
    int_vector_length,
    int_vector_pop,
    int_vector_push,
    int_vector_realloc_contents,
    int_vector_reserve,
    int_vector_uninit)

#endif
