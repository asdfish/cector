#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdlib.h>

// generates functions & type definition for .h files

#ifdef INCLUDE_VECTOR_GENERATE_HEADER_MACRO
#define VECTOR_GENERATE_HEADER(type,\
    exit_type,\
    struct_name,\
    success, failure,\
    at_function_name,\
    init_function_name,\
    length_function_name,\
    pop_function_name,\
    push_function_name,\
    realloc_contents_function_name,\
    reserve_function_name,\
    uninit_function_name)\
  \
  struct struct_name {\
    type** contents;\
    size_t size;\
    size_t reserved;\
  };\
  \
  extern exit_type at_function_name(struct struct_name*, type** output);\
  extern exit_type init_function_name(struct struct_name*);\
  extern exit_type length_function_name(struct struct_name*, unsigned int* length);\
  extern exit_type pop_function_name(struct struct_name*);\
  extern exit_type push_function_name(struct struct_name*);\
  extern exit_type realloc_contents_function_name(struct struct_name*, unsigned int suggested_size);\
  extern exit_type reserve_function_name(struct struct_name*);\
  extern exit_type uninit_function_name(struct struct_name*);
#endif

// generates function source code for .c files

#ifdef INCLUDE_VECTOR_GENERATE_SOURCE_MACRO
#include <stdlib.h>
#define VECTOR_GENERATE_SOURCE(type,\
    exit_type,\
    struct_name,\
    success, failure,\
    at_function_name,\
    init_function_name,\
    length_function_name,\
    pop_function_name,\
    push_function_name,\
    realloc_contents_function_name,\
    reserve_function_name,\
    uninit_function_name)\
  \
  exit_type init_function_name(struct struct_name* vector) {\
    if(vector == NULL)\
      return failure;\
    \
    vector->contents = (type**) malloc(sizeof(type*));\
    if(vector->contents == NULL)\
      return failure;\
    \
    *vector->contents = NULL;\
    \
    vector->reserved = 0;\
    vector->size = 0;\
    \
    return success;\
  }\
  \
  exit_type length_function_name(struct struct_name* vector, unsigned int* length) { \
    if(vector == NULL || length == NULL)\
      return failure;\
    \
    unsigned int output_length = 0;\
    while(*(vector->contents + output_length) != NULL)\
      output_length ++;\
    \
    *length = output_length;\
    \
    return success;\
  }\
  \
  exit_type uninit_function_name(struct struct_name* vector) {\
    if(vector == NULL)\
      return failure;\
    \
    for(unsigned int i = 0; *(vector->contents + i) != NULL; i ++) {\
      free(*(vector->contents + i));\
      *(vector->contents + i) = NULL;\
    }\
    \
    free(vector->contents);\
    vector->contents = NULL;\
    return success;\
  }
#endif

#endif
