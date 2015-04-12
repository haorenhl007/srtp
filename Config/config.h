#ifndef CONFIG_H
#define CONFIG_H

#include "config_global.h"

#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>

const char openCommand = 'a';
const char closeCommand = 'b';
const char openSystemCommand = 'c';
const char openSystemCommand2 = 'i';
const char connectSystemCommand = 'd';
const char disconnectSystemCommand = 'e';
const char startSystemCommand = 'f';
const char stopSystemCommand = 'g';
const char closeSystemCommand = 'h';
const char closeSystemCommand2 = 'j';

const char * OPENSYSTEM = "open_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L1FIPLQR.mdl')";
const char * OPENSYSTEM2 = "open_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L2FIPLQR.mdl')";
const char * CONNECTSYSTEM = "set_param('L2FIPLQR', 'SimulationCommand', 'connect')";
const char * DISCONNECTSYSTEM = "set_param('L2FIPLQR', 'SimulationCommand', 'disconnect')";
const char * STARTSYSTEM = "set_param('L2FIPLQR', 'SimulationCommand', 'start')";
const char * STOPSYSTEM = "set_param('L2FIPLQR', 'SimulationCommand', 'stop')";
const char * CLOSESYSTEM = "close_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L1FIPLQR.mdl')";
const char * CLOSESYSTEM2 = "close_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L2FIPLQR.mdl')";
const char * CDWORKDIRECTORY = "cd D:\\srtp-master";


QList<QHostAddress> CONFIGSHARED_EXPORT IPs();


const quint16 transfer_cmd_port = 9000;
const quint16 transfer_frame_port = 9999;

class CONFIGSHARED_EXPORT Config
{

public:
    Config();
};

#endif // CONFIG_H
