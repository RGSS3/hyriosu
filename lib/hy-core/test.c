#include "hyriosu.h"
struct A{
  int dummy;
  HYLIST_TRAIT;
  int dummy2;
};

int main(){
  struct A* p = HYLIST_CONS(3, HYLIST_CONS(2, HYLIST_CONS(1, HYLIST_NEW(p))));
  HYLIST_INSERT(4, p);
  HYLIST_INSERT(5, HYLIST_NEXT(HYLIST_NEXT(p)));
  free(HYLIST_DELETE(HYLIST_NEXT(HYLIST_NEXT(p))));
  HYLIST_FOREACH(p, node){
    printf("%lld\n", (long long)HYLIST_VALUE(node));
  }
}
