#ifndef HYLIST_H
#define HYLIST_H


typedef struct hylist_t hylist_t;
struct hylist_t { void *next; void *value; void *prev; int flags;};
#define HYLIST_TRAIT \
   hylist_t hylist;

#define HYLIST_SENTINAL                       1
#define HYLIST_HEAD                           2

#define HYLIST_GET(obj, offset)               HY_FIELD(obj, offset, hylist_t *)
#define HYLIST_NEXT_BYOFFSET(obj, offset)     (*(__typeof(obj)*)&(HYLIST_GET(obj, offset)->next))
#define HYLIST_PREV_BYOFFSET(obj, offset)     (*(__typeof(obj)*)&(HYLIST_GET(obj, offset)->prev))
#define HYLIST_VALUE_BYOFFSET(obj, offset)    (HY_RIGHTVALUE(void *, HYLIST_GET(obj, offset)->value))
#define HYLIST_FLAGS_BYOFFSET(obj, offset)    (HY_RIGHTVALUE(int, HYLIST_GET(obj, offset)->flags))
#define HYLIST_NEXT(obj)                      (HY_RIGHTVALUE(obj, ((obj)->hylist.next)))
#define HYLIST_PREV(obj)                      (HY_RIGHTVALUE(obj, ((obj)->hylist.prev)))
#define HYLIST_VALUE(obj)                     ((obj)->hylist.value)
#define HYLIST_FLAGS(obj)                     ((obj)->hylist.flags)
#define HYLIST_FREE(obj)                      free(obj)
#define HYLIST_NEW(type)             ((__typeof(type))(hylist_new(HYLIST_ALLOC(0, (__typeof(type))0), HY_OFFSET_OF(type, hylist))))
#define HYLIST_CONS(val, b)         ((__typeof(b))(hylist_cons((void *)(val), (b), sizeof(*(b)), HY_OFFSET_OF(b, hylist)))) 
#define HYLIST_ALLOC(val, b)         ((__typeof(b))(hylist_alloc((void *)(val), (b), sizeof(*(b)), HY_OFFSET_OF(b, hylist))))
#define HYLIST_DELETE(obj)           ((__typeof(obj))(hylist_delete((obj), sizeof(*(obj)),  HY_OFFSET_OF(obj, hylist))))
#define HYLIST_INSERT(val, obj)      ((__typeof(obj))(hylist_insert((void *)(val), (obj), sizeof(*(obj)), HY_OFFSET_OF(obj, hylist))))
#define HYLIST_FOREACH(list, node)   for(__typeof(list) node = list; node; node = HYLIST_NEXT(node)) if(!(HYLIST_FLAGS(node) & ~HYLIST_HEAD))
HYAPI hy_pointer_t hylist_alloc(void *val, void *ptr, size_t len, hy_offset_t offset);
HYAPI hy_pointer_t hylist_cons(void *val, void *ptr, size_t len, hy_offset_t offset);

HYAPI hy_pointer_t hylist_new(void *ret, hy_offset_t offset){
  HYLIST_GET(ret, offset)->flags |= HYLIST_SENTINAL;
  return ret;
}


HYAPI hy_pointer_t hylist_delete(void *ret, size_t len, hy_offset_t offset){
  if(!ret) return ret; // real null
  if(HYLIST_GET(ret, offset)->flags & HYLIST_HEAD){ // sentinal null
     ret = HYLIST_NEXT_BYOFFSET(ret, offset);
  }
  hylist_t *current = HYLIST_GET(ret, offset);
  void *prev = current->prev;
  void *node = current->next;
  HYLIST_NEXT_BYOFFSET(prev, offset) = node;
  HYLIST_PREV_BYOFFSET(node, offset) = prev; 
  return ret;
}

HYAPI hy_pointer_t hylist_insert(void *val, void *ptr, size_t len, hy_offset_t offset){
  if(!ptr) return ptr; // real null
  if(HYLIST_GET(ptr, offset)->flags & HYLIST_HEAD){ // sentinal null
     ptr = HYLIST_NEXT_BYOFFSET(ptr, offset);
  }
  void *prev_node   = HYLIST_PREV_BYOFFSET(ptr, offset);
  void *new_node    = hylist_alloc(val, ptr, len, offset);
  HYLIST_PREV_BYOFFSET(new_node, offset) = prev_node;
  HYLIST_NEXT_BYOFFSET(prev_node, offset) = new_node;
  HYLIST_FLAGS_BYOFFSET(new_node, offset)  &= ~HYLIST_HEAD;
  return new_node;
}

HYAPI hy_pointer_t hylist_cons(void *val, void *ptr, size_t len, hy_offset_t offset){
  if(!ptr) return 0;
  if(!HYLIST_GET(ptr, offset)->flags & HYLIST_HEAD){ // sentinal null
     return 0;
  }
  void *new_node = hylist_alloc(val, HYLIST_NEXT_BYOFFSET(ptr, offset), len, offset);
  HYLIST_PREV_BYOFFSET(new_node, offset) = ptr;
  HYLIST_NEXT_BYOFFSET(ptr, offset)      = new_node;
  HYLIST_FLAGS_BYOFFSET(new_node, offset)  &= ~HYLIST_HEAD;
  return ptr;
}

HYAPI hy_pointer_t hylist_alloc(void *val, void *ptr, size_t len, hy_offset_t offset){
  hy_pointer_t ret                   = malloc(len);
  HYLIST_NEXT_BYOFFSET(ret, offset)  = ptr;
  if(ptr){  
     HYLIST_PREV_BYOFFSET(ptr, offset)  = ret;  
     HYLIST_FLAGS_BYOFFSET(ptr, offset)  &= ~HYLIST_HEAD;  
  }
  HYLIST_PREV_BYOFFSET(ret, offset)  = 0;
  HYLIST_GET(ret, offset)->flags     = HYLIST_HEAD;
  HYLIST_VALUE_BYOFFSET(ret, offset) = val;
  return ret;
}


#endif
