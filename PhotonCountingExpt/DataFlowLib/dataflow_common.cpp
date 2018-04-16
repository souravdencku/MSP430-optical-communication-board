/*
 * dataflow_common.cpp
 *
 *  Created on: 08-Apr-2015
 *      Author: jyothish
 */

#include "dataflow_common.h"

//void *__gxx_personality_v0;
#if 1
void * operator new(size_t n)
{
  void * const p = malloc(n);
  // handle p == 0
  return p;
}

void operator delete(void * p) // or delete(void *, std::size_t)
{
  free(p);
}

void * operator new[](size_t size)
{
    return malloc(size);
}

void operator delete[](void * ptr)
{
    free(ptr);
}


#endif
