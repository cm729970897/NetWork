// channel层一般持有一个socket，是实际数据收发的地方，

class Channel
{
    public:
        Channel(EVentLoop* loop, int fd);
        ~Channel();

        int fd() const;
        int events() const;
        void set_revents(int revt);
        void add_revents(int revt);
        void remove_events();
        bool isNoEvent() const;

        bool enableReading();

        bool isWriting() const {return events_ & kWriteEvent;}

private:
    const int fd_;
    int events_;
    int revents_
}