#ifndef TCPSERVER_GLOBAL_H
#define TCPSERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TCPSERVER_LIBRARY)
#  define TCPSERVERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TCPSERVERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TCPSERVER_GLOBAL_H
