// 一个socket只会对应一个channel对象、一个connection对象以及一个session对象，构成了一路连接信息，one thread one loop,
// 每一路连接信息只会属于某个线程，一个loop或一个线程可以同时拥有多个连接信息，这保证了在同一个线程里面处理特定的socket收发事件。

class sockets
{
    public:
        SOCKET createOrDie();
        SOCKET createNoblockingOrDie();

        void setReuseAddr(SOCKET sockfd, bool on);
        void setReusePort(SOCKET sockfdm bool on);

        int connect(SOCKET sockfdm const struct sockaddr_in & addr);


}