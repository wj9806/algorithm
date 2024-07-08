//
// Created by xsy on 2024/7/8.
//

#include "common.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void debug_print(int level, const char * file, const char * func, int line, const char * fmt, ...)
{
#ifdef EN_DEBUG
    const char * end = file + strlen(file);
    while (end >= file)
    {
        if ((*end == '\\') || (*end == '/'))
        {
            break;
        }

        end--;
    }
    end++;

    char * s_level;
    switch (level) {
        case DEBUG_LEVEL_ERROR:
            s_level = DEBUG_STYLE_RED "error";
            break;
        case DEBUG_LEVEL_WARN:
            s_level = DEBUG_STYLE_YELLOW "warn";
            break;
        default:
            s_level = DEBUG_STYLE_WHITE "info";
    }

    printf("[%s] %s - %s:%d: " , s_level, end, func, line);

    char str_buf[128];
    va_list args;
    va_start(args, fmt);
    vsprintf(str_buf, fmt, args);
    printf("%s\n" DEBUG_STYLE_WHITE, str_buf);

    //recycling va_list
    va_end(args);
#endif
}
