#include <signal.h>
#include "auto_pay_context.h"

Auto_pay_context::Auto_pay_context(int &argc, char **argv):QApplication(argc, argv)
{
        signal(SIGPIPE, SIG_IGN);
}
