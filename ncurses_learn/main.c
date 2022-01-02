// #include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#define LENSTR 128

int main()
{
    initscr();

    //printw("Hi everyone!");
    //refresh();
    //getch();
    //raw(); // for off = cbreak()
    //while(true) {}

    // char string[32];
    // noecho();
    // printw("Enter: ");
    // scanw("%s", &string);
    // echo();
    // printw("Your text is: %s\n", string);
    // getch();




    // keypad(stdscr, true);
    // noecho();

    // halfdelay(20);

    // printw("Enter F3 to close.\n");
    // bool ex_t = false;

    // while (!ex_t) {
    //     switch (getch()) {
    //         case ERR:
    //             addstr("Please, press any key to exit...\n");
    //             // move(3, 7);
    //             // addch('A' | A_BOLD);
    //             break;
    //         case KEY_F(3):
    //             ex_t = true;
    //             clear();
    //             nocbreak();
    //             break;
    //         default:
    //             clear();
    //             printw("Enter F3 to close.\n");
    //             halfdelay(20);
    //             continue;
    //     }

    //     refresh();
    // }

    // printw("Thank you. Bye bye..");
    // getch();





/*    int y, x;
    const char str[] = "Hello my friend!";
    getmaxyx(stdscr, y, x);
    mvwprintw(stdscr, y/2, (x - strlen(str)) / 2, str);
    mvwprintw(stdscr, y-1, 0, "i can see you!\n");
    getch();*/





    const char select[4][8] = {
        "First",
        "Second",
        "Middle",
        "Last"
    };

    const char select_enter[4][20] = {
        "You enter \"First\"",
        "You enter \"Second\"",
        "You enter \"Middle\"",
        "You enter \"Last\""
    };

    uint8_t choise = 0;
    int y, x;
    bool status = false;
    curs_set(0);
    keypad(stdscr, true);

    while (!status) {
        clear();

        for (uint8_t i = 0; i <= 3; i++) {
            if (choise == i) addch('>' | A_BOLD);
            else addch(' ');
            wprintw(stdscr, "%s\n", select[i]);
        }

        switch (getch()) {
            case KEY_UP:
                if (choise != 0) choise--;
                break;
            case KEY_DOWN:
                if (choise != 3) choise++;
                break;
            case '\n':
                clear();
                getmaxyx(stdscr, y, x);
                mvwprintw(stdscr, y / 2, (x - strlen(select_enter[choise])) / 2, select_enter[choise]);
                status = true;
                keypad(stdscr, false);
                getch();
                break;
        }
    }


    clear();
    curs_set(1);
    char str_arr[LENSTR];
    addstr("Enter string: ");
    wgetstr(stdscr, str_arr);
    curs_set(0);
    clear();
    wprintw(stdscr, "you enter: %s", str_arr);
    getch();

    clear();
    curs_set(1);
    addstr("Enter string: ");
    wgetstr(stdscr, str_arr);
    curs_set(0);
    clear();

    while (true) {
        for (uint32_t x = 0; x < getmaxx(stdscr); x++) { // int x = getmaxx(stdscr); x != 0; x--
            clear();
            mvaddstr(getmaxy(stdscr) / 2, x, str_arr);
            refresh();
            usleep(20000);
        }
    }

    getch();

    endwin();
    return 0;
}