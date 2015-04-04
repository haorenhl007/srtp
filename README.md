#SRTP项目: 远程控制二级柔性倒立摆

*关键词*: Qt OpenCV Tcp Thread

#### 不小心做成了远程视频监控~ 记录一下经验教训

* 我们这种小打小闹的做的视频传输实质上是静态图片传输.我的程序采用的方案是将OpenCV采集的图像,
也就是Mat转换成Qt的QImage,用QImage压缩后再传输.为什么不直接传输Mat呢?因为Mat是未压缩的,
将Mat保存为文件时才可以进行压缩,但是我又不需要保存文件,方案就是使用QImage的save方法保存到QBuffer,然后发送QBufer的data.

* 就算调用QImage的save方法时压缩了,图片的size依然很大.最开始的程序计划使用UDP传输,想法是视频嘛丢几帧也没关系 ,
后来发现一个UDP用户数据报不可能存得了,
对于UDP而言,你write多大的包,它就发多大的包,但是这个包太大的话就会被IP层?数据链路层?切成小包,UDP不会去组合它们,丢了也不管.
而且丢了数据我就不能利用剩下的数据构造QImage了.

* 所以我改为使用TCP传输怎么传呢?TCP是流,但是我的QImage得有首部和身体,所以先发送QImage的size,再发送QImage的body(即buffer的size和data).

* 于是我自以为是的使用`DataStream << buffer.size() << buffer.data()`发送,在接收端先接受size再等到来了足够数量的data后构造我的QImage.
结果只读出了第一帧.经检查接收端第二次收到的size是负值,发送端write的数大于sizeof(buffer.size)+buffer.size.

* 然后从[stackoverflow.com](http://stackoverflow.com/questions/24379915/receiving-raw-image-data-through-tcp-for-display-using-qt)
上找到了答案,原来QDataStream处理定长数据的输入输出,我的buffer.data()不像int,double是固定size的类型,所以不能使用QDataStrem,
无论输入输出,对于这种不是固定长度的类型你都不能用QDataStream!

* 发送/接收这两个函数是本程序的精髓,哈~

* 当Qt的一个信号触发一个槽时,如果这个槽里有一个死循环,并且这个槽是在主线程执行的,一般我们的主线程是负责界面和交互的,那么你的
界面就会僵死在那里,任你怎么按Art-F4都关闭掉它.

* 还有多重继承的问题,我曾经设计了一个类同是继承了QTcpSocket和QThread,这个类里还有一个槽,这样会编译错误,提示二义什么的,就是
这两个类里有相同的函数或者变量,你编译的时候它也不知道使用哪一个了.解决这个问题就是使用组合了

* 在Qt中添加OpenCV3的库,需要注意include path和lib path都是bin目录下的,如果路径有空格需要使用双引号包裹起来,最好Linux风格的斜杠.

* 调试网络程序可以借助nc/ncat/netcat来判断究竟是发送端的故障还是接收端的故障.

* 其实我猜测wireshark熟的话更好调试,毕竟可以看到你的TCP握手的过程.

* 控制的那部分, 实际是调用MatLab的API, 那些命令可以查MatLab自带的文档, 也可以参考下[我的](http://28hua.org/post/2014-10/remote_control_matlab)


![j](https://github.com/28hua/srtp/blob/master/j.png)
