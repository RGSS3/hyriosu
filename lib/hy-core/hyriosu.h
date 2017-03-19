#ifndef HYRIOSU_H
#define HYRIOSU_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifdef __cplusplus
  #define HYAPI extern "C"
#else
  #define HYAPI extern
#endif


typedef struct hy_object_t hy_object_t;
typedef void (*hy_object_freefunc_t)(void *);
typedef void (*hy_object_markfunc_t)(void *);
typedef struct hyobject_t hyobject_t;
struct hyobject_t{      
     int flags;                  
     hy_object_markfunc_t mark;  
     hy_object_freefunc_t free;  
};
#define HY_OBJECT_TRAIT 

#define HY_OBJECT_MARK(obj)           (((obj)->hyobj_mark)((void *)obj))
#define HY_OBJECT_FREE(obj)           (((obj)->hyobj_free)((void *)obj))
#define HY_OBJECT_MARKFUNC(obj, func) ((obj)->hyobj_mark = (func))
#define HY_OBJECT_FREEFUNC(obj, func) ((obj)->hyobj_free = (func))


#include "hyhelper.h"
#include "hylist.h"
#include "hyregister.h"


#endif
