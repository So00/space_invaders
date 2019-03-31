#include "../header/AEntity.hpp"
#include "../header/SpaceShip.hpp"
#include "../header/Projectile.hpp"
#include "../header/ncurses.hpp"

int bulletTime = 200;
int shipTime = 350;
extern int score;

bool outOfBoundProj(gameInfo *game, Projectile *proj)
{
    if (proj == NULL)
        return false;
    if (proj->getY() < 5 || proj->getY() > game->height - 4)
        return true;
    return false;
}

bool IsColliding(SpaceShip *ship, Projectile *proj)
{
    int projx = proj->getX();
    int projy = proj->getY();
    int shipx = ship->getX();
    int shipy = ship->getY();

    if (projx >= shipx - 4 && projx <= shipx + 4 && projy >= shipy - 2 && projy <= shipy + 2)
        return true;
    return false;
}

void_node*  mgtCollide(SpaceShip *ship, Projectile *proj, void_node* shipNode, void_node *projNode, SpaceShip* motherShip) {
    ship->takeDamage(*proj);
    if (proj->getDirection())
        score += 1124;
    motherShip->popProj(projNode);
    if (ship->getHp() == 0)
    {
        if (ship->getType() == "player") {
            motherShip->popShip(shipNode);
            return NULL;
        }
        score += 3522;
        motherShip->popShip(shipNode);
    }
    return *(motherShip->getProjLst());
}

bool    removeProjectile(gameInfo *game, SpaceShip *motherShip)
{
    void_node **projec_lst = motherShip->getProjLst();
    void_node **ship_lst = motherShip->getShipLst();
    void_node *proj_tmp = *projec_lst;
    void_node *ship_tmp = *ship_lst;

    /* OUT OF BOUND PROJECTILE */
    while (proj_tmp)
    {
        if (outOfBoundProj(game, (Projectile *)proj_tmp->entity))
        {
            motherShip->popProj(proj_tmp);
            proj_tmp = *projec_lst;
            continue;
        }
        proj_tmp = proj_tmp->next;
    }
    /* PROJECTILE ON SHIP */
    projec_lst = motherShip->getProjLst();
    proj_tmp = *projec_lst;
    while (proj_tmp)
    {
        ship_tmp = *ship_lst;
        while (ship_tmp)
        {
            if (proj_tmp && IsColliding((SpaceShip *)ship_tmp->entity, (Projectile *)proj_tmp->entity))
            {
                proj_tmp = mgtCollide((SpaceShip *)ship_tmp->entity, (Projectile *)proj_tmp->entity, ship_tmp, proj_tmp, motherShip);
                if (proj_tmp == NULL) {
                    return false;
                }
                break;
            }
            ship_tmp = ship_tmp->next;
        }
        if (proj_tmp)
            proj_tmp = proj_tmp->next;
    }
    return true;
}

void moveProjectile(SpaceShip *motherShip)
{
    void_node **projec_act;
    void_node *act;
    Projectile *proj;

    projec_act = motherShip->getProjLst();
    act = *projec_act;
    while (act)
    {
        proj = (Projectile *)act->entity;
        if (proj->getDirection())
            proj->setY(proj->getY() - 1);
        else
            proj->setY(proj->getY() + 1);
        act = act->next;
    }
}

bool shipIsColliding(SpaceShip *ship, int x, int y)
{
    int enemyLX = ship->getX() - 4;
    int enemyUY = ship->getY() - 2;
    int enemyRX = ship->getX() + 4;
    int enemyLY = ship->getY() + 2;

    int allyLX = x - 4;
    int allyUY = y - 2;
    int allyRX = x + 4;
    int allyLY = y + 2;

    if ((enemyLX >= allyLX && enemyLX <= allyRX && enemyLY >= allyUY && enemyLY <= allyLY)
        || (enemyRX >= allyLX && enemyRX <= allyRX && enemyLY >= allyUY && enemyLY <= allyLY)
        || (enemyLX >= allyLX && enemyLX <= allyRX && enemyUY >= allyUY && enemyUY <= allyLY)
        || (enemyRX >= allyLX && enemyRX <= allyRX && enemyUY >= allyUY && enemyUY <= allyLY))
    {
        return true;
    }
    return false;
}

bool shipOnShipDmg(void_node *enemyShip, SpaceShip *motherShip)
{
    int id = motherShip->getID();
    motherShip->popShip(enemyShip);

    motherShip->takeDamageFromShip(100);
    void_node **lst = motherShip->getShipLst();

    if (motherShip->getHp() == 0)
    {
        void_node *current = *lst;
        while (current)
        {
            SpaceShip *tmp = (SpaceShip *)current->entity;
            if (tmp->getID() == id)
            {
                motherShip->popShip(current);
                return false;
            }
            current = current->next;
        }
    }
    return true;
}

bool shipCollision(SpaceShip *motherShip)
{
    void_node **ship_lst = motherShip->getShipLst();
    void_node *tmp;
    void_node *act;
    SpaceShip *TheShip;
    bool myBool;

    int motherShipx = motherShip->getX();
    int motherShipy = motherShip->getY();
    tmp = *ship_lst;
    act = tmp;
    while (act)
    {
        TheShip = (SpaceShip *)act->entity;
        if (TheShip->getType() != "player" && shipIsColliding((SpaceShip *)act->entity, motherShipx, motherShipy))
        {
            myBool = shipOnShipDmg(act, motherShip);
            if (!myBool)
                return false;
        }
        act = act->next;
    }
    return true;
}

bool outOfBoundShip(gameInfo *game, SpaceShip *ship)
{
    if (ship == NULL)
        return false;
    if (ship->getY() < 2 || ship->getY() > game->height - 4)
        return true;
    return false;
}

void moveShip(gameInfo *game, SpaceShip *motherShip)
{
    void_node **list;
    void_node *act;
    SpaceShip *tmp;

    list = motherShip->getShipLst();
    act = *list;
    while (act)
    {
        tmp = (SpaceShip *)act->entity;
        if (tmp->getType() == "player")
        {
            act = act->next;
            continue;
        }
        else
        {
            tmp->setY(tmp->getY() + 1);
        }
        if (tmp->getType() != "player" && outOfBoundShip(game, tmp))
        {
            motherShip->popShip(act);
            // act = *list;
            // continue;
        }
        act = act->next;
    }
}

/* ADD RANDOMLY ENNEMY */
void add_enemy(SpaceShip *mothership, gameInfo *game)
{
    int         enemy_nb = rand() % 2;
    void_node   *list;
    SpaceShip   *actShip;

    for (int i = 0; i < enemy_nb; i++)
    {
        void_node   *enemy = new void_node;
        enemy->entity = new SpaceShip("Roger", "enemy", (rand() % game->width) + 5, 8,  10, spriteToTab("assets/enemy.txt"));
        enemy->next = NULL;
        list = *(mothership->getShipLst());
        while (list)
        {
            actShip = (SpaceShip*)list->entity;
            if ((shipIsColliding((SpaceShip*)enemy->entity, actShip->getX(), actShip->getY()) && actShip->getType() != "player")
            || ((SpaceShip*)enemy->entity)->getX() > game->width - 6)
            {
                ((SpaceShip*)enemy->entity)->setX(((SpaceShip*)enemy->entity)->getX() + 2);
                if (((SpaceShip*)enemy->entity)->getX() > game->width - 6)
                    ((SpaceShip*)enemy->entity)->setX(7);
                list = *(mothership->getShipLst());
            }
            else
            {
                list = list->next;
            }
        }
        mothership->pushShip(enemy);
    }
}

/* FIRE RANDOMLY ENEMY */

void        fire_enemy(SpaceShip *mothership)
{
    void_node   *list = *(mothership->getShipLst());
    SpaceShip   *actShip;

    while (list)
    {
        actShip = (SpaceShip*)list->entity;
        if (!(rand() % 5) && actShip->getType() != "player")
        {
            actShip->fire(mothership);
        }
        list = list->next;
    }
}

uint64_t get_posix_clock_time()
{
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
        return (uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    else
        return 0;
}

/* CONSTANT CHECK DE LA VIE DE MON SHIP */

bool manageGame(gameInfo *game, SpaceShip *motherShip, uint64_t *prev_time, uint64_t* prev_time2)
{
    if (!removeProjectile(game, motherShip))
        return false;
    if (!shipCollision(motherShip))
        return false;
    if (get_posix_clock_time() > *prev_time2 + bulletTime)
    {
        moveProjectile(motherShip);
        *prev_time2 = get_posix_clock_time();
    }
    if (get_posix_clock_time() > *prev_time + shipTime)
    {
        moveShip(game, motherShip);
        add_enemy(motherShip, game);
        fire_enemy(motherShip);
        *prev_time = get_posix_clock_time();
    }


    return true;
}

