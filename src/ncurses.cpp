#include "../header/ncurses.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

extern int bulletTime;
extern int shipTime;

std::string *    spriteToTab(std::string path) {

    std::ifstream   fileStream(path);
    std::string     line;
    std::string     *result = new std::string[5];

    for (int i = 0; (std::getline(fileStream, line) && !fileStream.eof()) || i < 5; i++)
        result[i] = line;
    fileStream.close();
    return result;
}

std::string *    spriteToLongTab(std::string path) {

    std::ifstream   fileStream(path);
    std::string     line;
    std::string     *result = new std::string[9];

    for (int i = 0; (std::getline(fileStream, line) && !fileStream.eof()) || i < 9; i++)
        result[i] = line;
    fileStream.close();
    return result;
}

std::string *    spriteToBackgroundTab(std::string path) {

    std::ifstream   fileStream(path);
    std::string     line;
    std::string     *result = new std::string[120];

    for (int i = 0; (std::getline(fileStream, line) && !fileStream.eof()) || i < 120; i++)
        result[i] = line;
    fileStream.close();
    return result;
}

void		wait_plz(int ms)
{
	clock_t start;

	start = clock();
	while ((clock() - start) * 1000 < (unsigned long)ms * CLOCKS_PER_SEC)
		;
}

int     get_ev(int c, SpaceShip *elem, WINDOW *board) {
    if (c == 'q')
        return (0);
    if (elem != NULL)
    {
        wrefresh(board);
        switch (c)
        {   
            case (47) :
                if (bulletTime < 450)
                bulletTime += 25;
            Case (42) :
                if (bulletTime > 30) 
                    bulletTime -= 25;
            Case (43) :
                if (shipTime > 30)
                    shipTime -= 25;
            Case (45) :
                if (shipTime < 600)
                    shipTime += 25;
            Case (119) : //top ok
                if (elem->getY() - 1 - 2 >= 1)
                    elem->setY(elem->getY() - 1);
            Case (115) : //down ok
                if (elem->getY() + 1 + 2 <= 81)
                    elem->setY(elem->getY() + 1);
            Case (97) : //left ok
                if (elem->getX() - 1 - 4 >= 1)
                    elem->setX(elem->getX() - 1);
            Case (100) : //right ok
                if (elem->getX() + 1 + 4 <= 358)
                    elem->setX(elem->getX() + 1);
            Case (32) :
                elem->fire(elem);
        }
    }
    return (1);
}

void        print_ship(SpaceShip *elem, WINDOW *board) {
    start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
    if (elem->getType() == "player")
        wattron(board, COLOR_PAIR(1));
    else
        wattron(board, COLOR_PAIR(2));
    for (int i = 0; i < 5; i++)
        mvwprintw(board, elem->getY() + i - 2, elem->getX() - 4, "%s", elem->design[i].c_str());
    if (elem->getType() == "player")
        wattroff(board, COLOR_PAIR(1));
    else
        wattroff(board, COLOR_PAIR(2));
    
    // if (elem->getType() == "enemy")
    //     mvwprintw(board, 60, 60, "%d %d", elem->getY(), elem->getX());
}

void        print_proj(Projectile *elem, WINDOW *board)
{
    start_color();
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    wattron(board, COLOR_PAIR(3));
    mvwprintw(board, elem->getY(), elem->getX(), "%c", elem->design);
    wattroff(board, COLOR_PAIR(3));
    // mvwprintw(board, 61, 60, "%d %d", elem->getY(), elem->getX());
}

static void	option_ncurses(void)
{
	curs_set(0);
    noecho();
	cbreak();
    keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_RED, COLOR_WHITE);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_CYAN, COLOR_BLACK);
	init_color(20, 255, 255, 255);
	init_pair(9, 20, COLOR_BLACK);
}

void    erase(WINDOW **board)
{
    delwin(*board);
	endwin();
}

void        ft_init_ncurse(gameInfo* game) {
    initscr();
    game->width = 360;
    game->height = 83;
    game->status = 1;
    game->board = newwin(game->height, game->width, 0, 0);
    game->actBackground = 0;
    box(game->board, ACS_VLINE, ACS_HLINE);
    nodelay(game->board, 1);
    option_ncurses();
    wrefresh(game->board);
}