# 信号与槽

## connect第五个参数

| Qt::ConnectionType           | 说明                                                         |
| ---------------------------- | ------------------------------------------------------------ |
| Qt::AutoConnection(默认)     | 接收者与发送者在同一线程为Qt::DirectConnection 否则为Qt::QueuedConnection |
| Qt::DirectConnection         | 信号发送槽函数立即执行，槽函数与信号在同一线程               |
| Qt::QueuedConnection         | 事件循环到接收者线程后执行槽函数，槽函数与信号不在同一线程   |
| Qt::BlockingQueuedConnection | 信号线程会阻塞知道槽函数执行完毕，信号与槽函数在同一线程不能使用该方法，否则会死锁 |



## Sender()

获取发出信号对象指针，与qobject_cast搭配可获取发送者指针

```C++
//Test1
QPushButton *pPbt = qobject_cast<QPushButton*>(sender());//QObject::sender()获取发送信号对象指针
```

## 备注

1.发射信号会执行相关联的槽函数，至于是否**立即**执行槽函数，发射信号的线程是否等待槽函数执行完毕之后再执行后面的代码，与connect()函数设置信号与槽关联时设置的连接类型以及信号与槽是否在同一个线程有关。









