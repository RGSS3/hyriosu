#ifndef HYHELPER_H
#define HYHELPER_H
typedef size_t hy_offset_t;
typedef void * hy_pointer_t;
#define HY_OFFSET_OF(type, field)  ((hy_offset_t)&(((__typeof(type))0)->field))
#define HY_FIELD(obj, offset, type)  ((type)((hy_offset_t)obj + (long long)(offset)))
#define HY_RIGHTVALUE(type, a)  (*(__typeof(type) *)(&(a)))
#define HY_SWAP(a, b, len)  do { char *s = malloc(len); memcpy(s, a, len); memcpy(a, b, len); memcpy(b, s, len); free(s); } while(0)
#endif
