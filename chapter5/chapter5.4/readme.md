## 运行结果
我们采用telnet 192.168.1.1 5555创建了7个会话
![Alt text](img/image.png)
同时，我们设置backlog为5，但是队列超过5的时候依旧发现是SYN_SENT,有可能是因为backlog设置的较小,因此在队列已满的情况下依旧处于SYN_SEND状态