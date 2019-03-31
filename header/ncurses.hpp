#ifndef NCURSES_HPP
# define NCURSES_HPP

#include <ncurses.h>
#include <ctime>
#include <iostream>
#include "SpaceShip.hpp"

#define Case break;case

typedef struct s_gameInfo {
    WINDOW      *board;
    int         status;
    int         width;
    int         height;
    int         actBackground;
    std::string *background;
}gameInfo;

void		    ft_init_ncurse(gameInfo*    game);
std::string*    spriteToTab(std::string path);
int	            print_board(SpaceShip *elem, WINDOW *board);
std::string *   spriteToTab(std::string path);
std::string *    spriteToLongTab(std::string path);
std::string *    spriteToBackgroundTab(std::string path);

void		    wait_plz(int ms);
void            erase(WINDOW **board);
void            print_ship(SpaceShip *elem, WINDOW *board);
void            print_proj(Projectile *elem, WINDOW *board);
int		        get_ev(int c, SpaceShip *elem, WINDOW* board);

uint64_t        get_posix_clock_time();
bool            manageGame(gameInfo* game, SpaceShip* ship, uint64_t* time, uint64_t* time2);
void            moveProjectile(SpaceShip* ship);
bool            removeProjectile(gameInfo* game, SpaceShip* ship);
void_node*      mgtCollide(SpaceShip *ship, Projectile *proj, void_node* shipNode, void_node *projNode);
bool            IsColliding(SpaceShip *ship, Projectile *proj);
bool            outOfBoundProj(gameInfo* game, Projectile* proj);


#endif