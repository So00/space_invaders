#include "../header/AEntity.hpp"
#include "../header/SpaceShip.hpp"
#include "../header/Projectile.hpp"
#include "../header/ncurses.hpp"

int     score;
int     actBackgroundLine;

void    print_info(SpaceShip *MotherShip, WINDOW *board)
{
    mvwprintw(board, 2, 15, "Name = %s", MotherShip->getName().c_str());
    mvwprintw(board, 2, 40, "Health = %d", MotherShip->getHp());
    mvwprintw(board, 2, 80, "Score = %d", score);
    for (int i = 1; i < 358; i++)
        mvwprintw(board, 4, i, "%c", '_');
}

void    printBackground(gameInfo *game)
{
    int     actP;

    actP = game->actBackground;
    for (int i = 5; i < 81; i++, actP--)
    {
        mvwprintw(game->board, i, 1, "%s", game->background[actP].c_str());
        if (actP == 0)
            actP = 100;
    }
}

int     playGame(gameInfo*  game, SpaceShip* motherShip, uint64_t* prev_time, uint64_t* prev_time2, uint64_t *prev_time3) {

    int	            c;
    void_node       **list;
    void_node       *node;
    SpaceShip       *act_space;
    Projectile      *act_proj;

    for (int i = 1; i < 82; i++)
        mvwprintw(game->board, i, 1, "%*s", 358 ," ");
    printBackground(game);
    if (get_posix_clock_time() > *prev_time3 + 100) {
        game->actBackground += 1;
        if (game->actBackground > 100)
            game->actBackground = 0;
        *prev_time3 = get_posix_clock_time();
    }
    print_info(motherShip, game->board);
    list = motherShip->getShipLst();
    node = *list;
    while (node)
    {
        act_space = (SpaceShip*)node->entity;
        print_ship(act_space, game->board);
        node = node->next;
    }
    list = motherShip->getProjLst();
    node = *list;
    while (node)
    {
        act_proj = (Projectile*)node->entity;
        print_proj(act_proj, game->board);
        node = node->next;
    }
	wrefresh(game->board);
	c = wgetch(game->board);
    
    if (!manageGame(game, motherShip, prev_time, prev_time2)) {
        return false;
    }
	return (get_ev(c, motherShip, game->board));
}

int     endScreen(gameInfo *game)
{
    int     c;

    c = wgetch(game->board);
    return (get_ev(c, NULL, game->board));
}

void    print_end(gameInfo *game)
{
    std::string     *end = spriteToLongTab("assets/endgame.txt");

    mvwprintw(game->board, 2, 40, "Health = 0");
    for (int i = 0; i < 9; i++)
        mvwprintw(game->board, 35 + i,  140, "%s", end[i].c_str());
    wrefresh(game->board);
    delete [] end;
}

int     main() {
    setlocale(LC_ALL, "");
    gameInfo *game = new gameInfo;
    game->background = spriteToBackgroundTab("assets/background.txt");
    score = 0;
    ft_init_ncurse(game);
    srand((int)time(0));
    SpaceShip*  motherShip = new SpaceShip("Enterprise", "player", game->width / 2, game->height - 4, 100, spriteToTab("assets/mothership.txt"));
    void_node   *add = new void_node;
    add->entity = motherShip;
    add->next = NULL;
    motherShip->pushShip(add);


    uint64_t       tmp = 0;
    uint64_t       tmp2 = 0;
    uint64_t       tmp3 = 0;
    
    while (game->status) {
        game->status = playGame(game, motherShip, &tmp, &tmp2, &tmp3);
    }

    game->status = 1;
    print_end(game);
    while (game->status)
    {
        game->status = endScreen(game);
    }

    erase(&(game->board));

    return 0;
}