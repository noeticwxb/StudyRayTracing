#ifndef _CONFIG_H
#define  _CONFIG_H 1

#include <assert.h>
#include <cmath>


#define NEW_PTR(type) new type
#define NEW_ARRAY(type,count) new type[count]
#define DELETE_PTR(ptr) delete ptr
#define DELETE_ARRAY(ptr) delete[] ptr

#define SAFE_DELETE_PTR(p)   do { if(p != NULL) { delete (p); (p) = NULL; } } while(0)
#define SAFE_DELETE_ARRAY(p)   do { if(p != NULL) { delete[] (p); (p) = NULL; } } while(0)


#endif

