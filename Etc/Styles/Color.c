#ifndef TEXT_COLOR_H
#define TEXT_COLOR_H

// Text color codes
#define TEXT_COLOR_BLACK          "\033[0;30m"
#define TEXT_COLOR_RED            "\033[0;31m"
#define TEXT_COLOR_GREEN          "\033[0;32m"
#define TEXT_COLOR_YELLOW         "\033[0;33m"
#define TEXT_COLOR_BLUE           "\033[0;34m"
#define TEXT_COLOR_MAGENTA        "\033[0;35m"
#define TEXT_COLOR_CYAN           "\033[0;36m"
#define TEXT_COLOR_WHITE          "\033[0;37m"
#define TEXT_COLOR_BRIGHT_BLACK   "\033[1;30m"
#define TEXT_COLOR_BRIGHT_RED     "\033[1;31m"
#define TEXT_COLOR_BRIGHT_GREEN   "\033[1;32m"
#define TEXT_COLOR_BRIGHT_YELLOW  "\033[1;33m"
#define TEXT_COLOR_BRIGHT_BLUE    "\033[1;34m"
#define TEXT_COLOR_BRIGHT_MAGENTA "\033[1;35m"
#define TEXT_COLOR_BRIGHT_CYAN    "\033[1;36m"
#define TEXT_COLOR_BRIGHT_WHITE   "\033[1;37m"
#define TEXT_COLOR_RESET          "\033[0m"

// Background color codes
#define BACKGROUND_COLOR_BLACK          "\033[40m"
#define BACKGROUND_COLOR_RED            "\033[41m"
#define BACKGROUND_COLOR_GREEN          "\033[42m"
#define BACKGROUND_COLOR_YELLOW         "\033[43m"
#define BACKGROUND_COLOR_BLUE           "\033[44m"
#define BACKGROUND_COLOR_MAGENTA        "\033[45m"
#define BACKGROUND_COLOR_CYAN           "\033[46m"
#define BACKGROUND_COLOR_WHITE          "\033[47m"
#define BACKGROUND_COLOR_BRIGHT_BLACK   "\033[100m"
#define BACKGROUND_COLOR_BRIGHT_RED     "\033[101m"
#define BACKGROUND_COLOR_BRIGHT_GREEN   "\033[102m"
#define BACKGROUND_COLOR_BRIGHT_YELLOW  "\033[103m"
#define BACKGROUND_COLOR_BRIGHT_BLUE    "\033[104m"
#define BACKGROUND_COLOR_BRIGHT_MAGENTA "\033[105m"
#define BACKGROUND_COLOR_BRIGHT_CYAN    "\033[106m"
#define BACKGROUND_COLOR_BRIGHT_WHITE   "\033[107m"
#define BACKGROUND_COLOR_RESET          "\033[49m"

#define TEXT_COLOR_RESET        "\033[0m"

// Change text color and background
#define SET_TEXT_COLOR(color, background) printf("\033[%s;%sm", color, background)

#endif /* TEXT_COLOR_H */
