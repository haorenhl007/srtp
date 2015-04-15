/*服务端和客户端传输的是字符,赋予字符实际含义.赋予MatLab运行的控制指令实际含义*/
#ifndef CONFIG_H
#define CONFIG_H

#include "config_global.h"

#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>

const char openCommand = 'a';//打开MatLab
const char closeCommand = 'b';//关闭MatLab
const char openSystemCommand = 'c';//打开倒立摆模块
const char openSystemCommand2 = 'i';//打开代理摆模块
const char connectSystemCommand = 'd';//连接倒立摆系统
const char disconnectSystemCommand = 'e';//与倒立摆系统断开连接
const char startSystemCommand = 'f';//起摆
const char stopSystemCommand = 'g';//停摆
const char closeSystemCommand = 'h';//关闭倒立摆系统
const char closeSystemCommand2 = 'j';//关闭倒立摆系统

const char * OPENSYSTEM = //打开倒立摆模块
    "open_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L1FIPLQR.mdl')";
const char * OPENSYSTEM2 = //打开倒立摆模块
    "open_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L2FIPLQR.mdl')";
const char * CONNECTSYSTEM = //连接倒立摆系统
    "set_param('L2FIPLQR', 'SimulationCommand', 'connect')";
const char * DISCONNECTSYSTEM = //与倒立摆系统断开连接
    "set_param('L2FIPLQR', 'SimulationCommand', 'disconnect')";
const char * STARTSYSTEM = //起摆
    "set_param('L2FIPLQR', 'SimulationCommand', 'start')";
const char * STOPSYSTEM = //停摆
    "set_param('L2FIPLQR', 'SimulationCommand', 'stop')";
const char * CLOSESYSTEM = //关闭倒立摆系统
    "close_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L1FIPLQR.mdl')";
const char * CLOSESYSTEM2 = //关闭倒立摆系统
    "close_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L2FIPLQR.mdl')";
const char * CDWORKDIRECTORY = //更改工作目录
    "cd D:\\srtp-master";


QList<QHostAddress> CONFIGSHARED_EXPORT IPs();//返回主机IP地址列表


const quint16 transfer_cmd_port = 9000;//服务端监听端口,处理控制命令
const quint16 transfer_frame_port = 9999;//服务端监听端口,处理视频传输

class CONFIGSHARED_EXPORT Config
{

public:
    Config();
};

#endif // CONFIG_H
