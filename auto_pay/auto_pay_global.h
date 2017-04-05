#ifndef AUTO_PAY_GLOBAL_H
#define AUTO_PAY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AUTO_PAY_LIBRARY)
#  define AUTO_PAYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define AUTO_PAYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // AUTO_PAY_GLOBAL_H
