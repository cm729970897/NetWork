# NetWork

1. 基于epoll的程序
```
do
{
    poller.dispatch();
    for fd_event in active_event_set
    {
        if(is_readable_event(fd_event) == true)
            handle_read(fd_event);
        if(is_writeable(fd_event) == true)
            handle_wwrite(fd_event);
    }
}while(true);
```
2. 事件驱动模型
       
第一，它存在一个无限循环的事件分发线程，或者叫做 reactor 线程、Event loop 线程。
这个事件分发线程的背后，就是 poll、epoll 等 I/O 分发技术的使用；  
第二，所有的 I/O 操作都可以抽象成事件，每个事件必须有回调函数来处理。acceptor上有连接建立成功、已连接套接字上发送缓冲区空出可以写、通信管道 pipe 上有数据可以读，这些都是一个个事件，通过事件分发，这些事件都可以一一被检测，并调用对应的回调函数加以处理。

3. I/O 模型和线程模型设计  
   
任何一个网络程序，所做的事情可以总结成下面几种：    
read：从套接字收取数据；  
decode：对收到的数据进行解析；  
compute：根据解析之后的内容，进行计算和处理；  
encode：将处理之后的结果，按照约定的格式进行编码；  
send：最后，通过套接字把结果发送出去。

4. single reactor thread + worker threads  

和 I/O 事件处理相比，应用程序的业务逻辑处理是比较耗时的，将这些 decode、compute、enode 型工作放置到另外的线程池中，和反应堆线程解耦，是比较明智的选择。
