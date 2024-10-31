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
  extern exit_type at_function_name(struct struct_name* vector, unsigned int index, type** output);\
  extern exit_type init_function_name(struct struct_name* vector);\
  extern exit_type length_function_name(struct struct_name* vector, unsigned int* length);\
  extern exit_type pop_function_name(struct struct_name* vector);\
  extern exit_type push_function_name(struct struct_name* vector, type item);\
  extern exit_type realloc_contents_function_name(struct struct_name* vector, unsigned int suggested_size);\
  extern exit_type reserve_function_name(struct struct_name* vector, unsigned int reservation);\
  extern exit_type uninit_function_name(struct struct_name* vector);
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
  exit_type at_function_name(struct struct_name* vector, unsigned int index, type** output) {\
    if(vector == NULL || output == NULL)\
      return failure;\
    \
    *output = *(vector->contents + index);\
    \
    return success;\
  }\
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
  exit_type push_function_name(struct struct_name* vector, type item) {\
    if(vector == NULL)\
      return failure;\
    \
    type* new_item = (type*) malloc(sizeof(type));\
    if(new_item == NULL)\
      return failure;\
    *new_item = item;\
    \
    unsigned int length = 0;\
    if(length_function_name(vector, &length) != success)\
      goto free_new_item;\
    \
    if(realloc_contents_function_name(vector, length + 1) != success)\
      goto free_new_item;\
    \
    *(vector->contents + length) = new_item;\
    *(vector->contents + length + 1) = NULL;\
    \
    return success;\
    \
free_new_item:\
    free(new_item);\
    new_item = NULL;\
    return failure;\
  }\
  \
  exit_type pop_function_name(struct struct_name* vector) {\
    if(vector == NULL)\
      return failure;\
    \
    unsigned int length = 0;\
    if(length_function_name(vector, &length) != success)\
      return failure;\
    \
    length --;\
    \
    if(length == 0)\
      return success;\
    \
    realloc_contents_function_name(vector, length);\
    \
    return success;\
  }\
  \
  exit_type realloc_contents_function_name(struct struct_name* vector, unsigned int suggested_size) {\
    if(vector == NULL ||\
        (suggested_size <= vector->reserved && vector->size == vector->reserved))\
      return failure;\
    \
    unsigned int new_size = suggested_size <= vector->reserved ? vector->reserved : suggested_size;\
    \
    unsigned int length = 0;\
    if(length_function_name(vector, &length) != success)\
      return failure;\
    \
    if(new_size < length)\
      for(unsigned int i = new_size; i < length; i ++) {\
        free(*(vector->contents + length));\
        *(vector->contents + length) = NULL;\
      }\
    \
    type** temp_pointer = realloc(vector->contents, (new_size + 1) * sizeof(type*));\
    if(temp_pointer == NULL)\
      return failure;\
    \
    vector->contents = temp_pointer;\
    vector->size = new_size;\
    \
    return success;\
  }\
  \
  exit_type reserve_function_name(struct struct_name* vector, unsigned int reservation) {\
    if(vector == NULL)\
      return failure;\
    \
    vector->reserved = reservation;\
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
