#include <assert.h>
#include "event_loop.h"
#include "common.h"
#include "log.h"
#include "event_dispatcher.h"
#include "channel.h"
#include "utils.h"


struct event_loop *event_loop_init()
{
    return event_loop_init_with_name(NULL);
}

struct event_loop_init_with_name(char *thread_name)
{
    struct event_loop *eventLoop = malloc(sizeof(struct event_loop));
    pthread_mutex_init(&eventLoop->mutex, NULL);
    pthread_cond_init(&eventLoop->cond, NULL);

    if(thread_name != NULL)
        eventLoop->thread_name = thread_name;
    else
        eventLoop->thread_name = "main thread";

    eventLoop->quit = 0;
    eventLoop->channelMap = malloc(sizeof(struct channel_map));
    map_init(eventLoop->channelMap);

    eventLoop->eventDispatcher = &epoll_dispatcher; //
    /*
    #ifdef EPOLL_ENABLE
       yolanda_msgx("set epoll as dispatcher, %s", eventLoop->thread_name);
       eventLoop->eventDispatcher = &epoll_dispatcher;
    #else
       yolanda_msgx("set poll as dispatcher, %s", eventLoop->thread_name);
       eventLoop->eventDispatcher = &poll_dispatcher;
    #endif
       */
    eventLoop->event_dispatcher_data = eventLoop->eventDispatcher->init(eventLoop);

    // add the sockfd to event
    eventLoop->owner_thread_id = pthread_self();
    if(sockpair(AF_UNIX, SOCK_SREAM, 0, eventLoop->socketPair) < 0)
        LOG_ERR("socketpair set failed");
    eventLoop->is_handle_pending = 0;
    eventLoop->pending_head = NULL;
    eventloop->pending_tail = NULL;

    struct channel *channel = channel_new(eventLoop->socketpair[1], EVENT_READ, handleWakeup,NULL,
            eventLoop);
    event_loop_add_channel_event(eventLoop, eventLoop->socketpair[0], channel);

    return eventLoop;
}

int event_loop_run(struct event_loop *eventLoop)
{
    assert(eventLoop != NULL);

    struct event_dispatcher *dispatcher = eventLoop->eventDispatcher;
    if(eventLoop->owner_thread_id != pthread_self())
        exit(1);
    yolanda_msgx("event loop run, %s", eventLoop->thread_name);

    struct timeval timeval;
    timeval.tv_sec = 1;

    while (!eventLoop->quit)
    {
        dispatcher->dispatch(eventLoop, &timeval);

        event_loop_handle_pending_channel(eventLoop);
    }

    yolanda_msgx("event loop end, %s", eventLoop->thread_name);
    return 0;
}



