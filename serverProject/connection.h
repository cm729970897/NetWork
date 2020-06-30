// 一般记录该路连接的状态、常见的状态有连接状态、数据缓冲区信息、数据流量记录状态、本端地址和端口号信息
class TcpConnection
{
    public:
        TcpConnection(EventLoop * loop, const string& name, int sockfd, const InetAddress& localAddr, const InetAddr& peerAddr);
        ~TcpConnection();

        void send(const void *message, int len);
        void send(const string& message);
        void send(Buffer *message);
        void shutdown();

        void setConnectionCallback(const ConnectionCallBack& cb)
        {
            messageCallback = cb;
        }

    private:
      enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };

    private:

        StateE state_;
        //
        std::shared_ptr<channel> channel_;

        const InetAddr localAddr_;
        cont InetAddress peerAddr_;
        
        ConnectionCallback connectionCallBack_;

        // 接收缓冲区
        Buffer inputBuffer_;
        // 发送缓冲区
        Buffer outputBuffer_;

        // 流量统计类
        CFlowStatistics flowStatistics;
};


