#ifndef HYREGISTER_H
#define HYREGISTER_H

#define HY_REGISTER(name, handler)      (hy_register((name), (handler)))
#define HY_SEND(name, subcmd, request)  (hy_send((name), (subcmd), (request)))
#define HY_MESSAGE_T hy_message_t



typedef struct hy_message_t hy_message_t;
struct hy_message_t{
  
};
typedef int (*hy_handler_t)(hy_message_t*);


HYAPI int hy_register(const char*, hy_handler_t);


#endif
