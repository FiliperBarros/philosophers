#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H

typedef enum {
    RESET        = 0,
    BLACK        = 30,
    RED          = 31,
    GREEN        = 32,
    YELLOW       = 33,
    BLUE         = 34,
    MAGENTA      = 35,
    CYAN         = 36,
    WHITE        = 37,
    BRIGHT_BLACK   = 90,
    BRIGHT_RED     = 91,
    BRIGHT_GREEN   = 92,
    BRIGHT_YELLOW  = 93,
    BRIGHT_BLUE    = 94,
    BRIGHT_MAGENTA = 95,
    BRIGHT_CYAN    = 96,
    BRIGHT_WHITE   = 97
} AnsiColor;

#define SET_COLOR(code)        printf("\033[%dm", code)
#define SET_BOLD_COLOR(code)   printf("\033[1;%dm", code)
#define RESET_COLOR()          printf("\033[0m")

#endif
