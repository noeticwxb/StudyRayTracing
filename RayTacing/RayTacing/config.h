#ifndef _CONFIG_H
#define  _CONFIG_H 1

#include <assert.h>


#define NEW(type) new type
#define NEW_ARRAY(type,size) new type[size]
#define DELETE(ptr) delete ptr
#define DELETE_ARRAY(ptr) delete[] ptr

#define SAFE_DELETE(p)   do { if(p != NULL) { delete (p); (p) = NULL; } } while(0)
#define SAFE_DELETE_ARRAY(p)   do { if(p != NULL) { delete[] (p); (p) = NULL; } } while(0)


#endif

