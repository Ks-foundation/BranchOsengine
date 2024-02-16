#include <ncurses.h>
#include <string.h>

int main() {
    char password[20];
    int i = 0;

    initscr(); // ncurses 초기화
    noecho(); // 입력된 문자를 화면에 출력하지 않음

    printw("Enter password: ");
    refresh();

    WINDOW *win = newwin(3, 30, 1, 1); // 윈도우 생성
    box(win, 0, 0); // 윈도우 테두리 추가
    keypad(win, true); // 키보드 입력 활성화
    wrefresh(win);

    while (1) {
        int ch = wgetch(win); // 윈도우에서 한 글자를 받음

        if (ch == '\n' || ch == '\r') { // 엔터 키를 누르면 입력 종료
            break;
        } else if (ch == KEY_BACKSPACE || ch == 127) { // 백스페이스 키 처리
            if (i > 0) {
                i--;
                mvwprintw(win, 1, 2 + i, " "); // 입력한 글자 지우기
                wrefresh(win);
            }
        } else {
            password[i] = ch;
            mvwprintw(win, 1, 2 + i, "*"); // 입력한 글자를 '*'로 표시
            wrefresh(win);
            i++;
        }
    }

    password[i] = '\0'; // 문자열의 끝을 나타내는 NULL 문자 추가

    clear(); // 화면 지우기
    printw("Password entered: %s\n", password);
    refresh();
    getch(); // 잠시 대기
    endwin(); // ncurses 종료

    return 0;
}
