#include <int_vector.h>
#include <stdio.h>
int main(void) {
  struct int_vector vector;
  if(int_vector_init(&vector) != 0)
    return -1;

  int_vector_push(&vector, 69);

  unsigned int length = 0;
  if(int_vector_length(&vector, &length) != 0)
    goto cleanup;

  printf("length: %u\n", length);

  int* my_int = NULL;
  if(int_vector_at(&vector, 0, &my_int) != 0)
    goto cleanup;
  printf("[0]: %i\n", *my_int);

  /*int_vector_pop(&vector);*/

cleanup:
  int_vector_uninit(&vector);
  return 0;
}
