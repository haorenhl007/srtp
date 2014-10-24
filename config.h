#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

const char openCommand = 'a';
const char closeCommand = 'b';
const char openSystemCommand = 'c';
const char connectSystemCommand = 'd';
const char disconnectSystemCommand = 'e';
const char startSystemCommand = 'f';
const char stopSystemCommand = 'g';
const char closeSystemCommand = 'h';

const char * OPENSYSTEM = "open_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L1FIPLQR.mdl')";
const char * CONNECTSYSTEM = "set_param('L1FIPLQR', 'SimulationCommand', 'connect')";
const char * DISCONNECTSYSTEM = "set_param('L1FIPLQR', 'SimulationCommand', 'disconnect')";
const char * STARTSYSTEM = "set_param('L1FIPLQR', 'SimulationCommand', 'start')";
const char * STOPSYSTEM = "set_param('L1FIPLQR', 'SimulationCommand', 'stop')";
const char * CLOSESYSTEM = "close_system('D:\\MATLAB\\R2010b\\toolbox\\GoogolTech\\InvertedPendulum\\Flexible-Joint Inverted Pendulum\\L1FIPLQR.mdl')";
const char * CDWORKDIRECTORY = "cd D:\\srtp-master\\build";

#endif
