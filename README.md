# Qt 远程控制 MatLab 的几个问题

1.调用 engihe.h 头文件中的函数需要在 Qt 项目的 .pro 文件中加上头文件所在目录和链接库所在目录
```
INCLUDEPATH += "C:\Program Files\MATLAB\R2014a\extern\include"
LIBS += -L"C:\Program Files\MATLAB\R2014a\extern\lib\win32\microsoft" -llibeng -llibmat -llibmx
```
上面的内容根据自己 MatLab 的安装路径和安装版本进行修改。只链接自己使用到的库就可以，其实我现在只用到了 -llibeng。

2.添加了上面两行应该可以编译过去了，但是运行时会提示缺少 dll 文件，需要找到缺少的 dll 文件添加到 Path 环境变量中，Windows 添加环境变量的方法 右击我的电脑-> 属性 -> 更改设置 -> 高级 -> 环境变量 -> 系统变量 -> Path -> 编辑
```
C:\Program Files\MATLAB\R2014a\bin\win32
```
3.在一台老 XP 上启动一个较老版本的 MatLab 没有启动起来.如果用  MatLab 自带的例子会出现这样的提示
```
Can't start MATLAB engine
```
这时候启动 MatLab 并输入
```
cd(fullfile(matlabroot,'bin',computer('arch')))
!matlab /regserver
```
4.我们需要将几个鼠标点击动作转换为命令,翻阅 MatLab 的帮助文档找到了所需命令.就在 Control Simulation Using the set_param Command
```
set_param('sys','SimulationCommand','cmd')
'sys' is the name of the system you want to simulate
 'cmd' is the command to control simulation. Possible valuess are:
'start'
'stop'
'pause'
'continue'
'connect' (to a target)
'update'
 'WriteDataLogs'
```
当然,还有打开关闭一个模型的命令,这个好找
```
help open_system
help close_system
```
