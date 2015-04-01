#ifndef CONFIG_GLOBAL_H
#define CONFIG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONFIG_LIBRARY)
#  define CONFIGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONFIGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CONFIG_GLOBAL_H
