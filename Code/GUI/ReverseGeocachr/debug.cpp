#include "debug.h"

//#define DEBUG_ON

void Debug(QString msg) {
#ifdef DEBUG_ON
    qDebug() << msg;
#endif
}
