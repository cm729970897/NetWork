
// 记录各种业务状态的数据和处理各种业务逻辑
class ChatSession
{
    public:
        ChatSession(const std::shared_ptr<TcpConnection>& conn, int sessionid);
        
        virtual ~ChatSession();

        int32_t GetSessionId();
    
    private:
        int32_t m_id;
        OnLineUserInfo m_userinfo;
        int32_t m_seq;
        bool is_isLogin;

        std::weak_ptr<TcpConnection> tmpConn_i;
    
    }