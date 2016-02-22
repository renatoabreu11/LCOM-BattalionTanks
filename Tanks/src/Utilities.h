#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <stdio.h>

extern FILE* logfd;
#define LOG_PATH "home/lcom/Tanks/log.txt"
#define LOG(tag, msg) fprintf(logfd, "%s: %s\n", tag, msg)
#define LOG_VAR(tag, var) fprintf(logfd, "%s: %d\n", tag, var)
#define LOG_MSG(msg) fprintf(logfd, "%s", msg)

#endif /* __UTILITIES_H */
