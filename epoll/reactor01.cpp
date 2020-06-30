//
// Created by Administrator on 2020/3/12.
//
#include <lib/acceptor.h>
#include "lib/common.h"
#include "lib/event_loop.h"
#include "lib/tcp_server.h"

// 连接建立之后的callback
int onConnectionCompleted(struct tcp_connection *tcpConnection)
{
    printf("connection completed\n");
    return 0;
}

// 数据读到buffer之后的callback
int onMessage(struct buffer *input, struct tcp_connection *tcpConnection)
{

}
// 数据通过buffer写完之后的callback
int onWriteCompleted(struct tcp_connection *tcpConnection)
{

}

// 连接关闭之后的callback
int onConnectionClosed(struct tcp_connection *tcpConnection)
{

}


int main(int argc, char **argv)
{
    // 主线程 event_loop
    struct event_loop *eventLoop = event_loop_init();

    // 初始化acceptor
    struct acceptor *acceptor = acceptor_init(SERV_PORT);

    // 初始tcp_server, 可指定线程数目，如果线程为0，则只有一个线程，既负责acceptor,又负责IO
    struct TCPserver *tcpServer = tcp_server_init(eventLoop,acceptor,onConnectionCompleted,
            onMessage, onWriteCompleted, onConnectionClosed,0);

    tcp_server_start(tcpServer);

    event_loop_run(eventLoop);
}





