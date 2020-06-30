#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "channel.h"
// 抽象的event_dispatcher结构体，对应的实现select,poll,epoll等IO复用
struct event_dispatcher
{
    const char *name;

    // 初始化函数
    void *(*init)(struct event_loop *eventLoop);
    //
    int (*add)(struct event_loop *eventLoop, struct channel *channel);

    int (*del)(struct event_loop *eventLoop, struct channel *channel);

    int (*update)(struct event_loop *eventLoop, struct channel *channel);

    int (*dispatcher)(struct event_loop *eventLoop, struct timeval *);

    void (*clear)(struct event_loop *eventLoop);
};

#endif