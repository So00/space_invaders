#include "../header/Projectile.hpp"
#include "../header/AEntity.hpp"

int Projectile::projCount = 0;

Projectile::Projectile() {
    return ;
}

Projectile::Projectile(Projectile const & inst) {
    *this = inst;
    return;
}

Projectile::Projectile(int dmg, int x, int y, char design, SpaceShip *ship) {
    this->id = Projectile::projCount++;
    this->dmg = dmg;
    this->x = x;
    this->y = y;
    this->design = design;
    if (ship->getType() == "player")
        this->direction = true;
    else
        this->direction = false;

    return;
}

Projectile::~Projectile() {
    return;
}

Projectile& Projectile::operator=(Projectile const & inst) {
    this->dmg = inst.dmg;
    this->x = inst.x;
    this->y = inst.y;
    this->design = inst.design;
    this->direction = inst.direction;
    return *this;
}

int     Projectile::getID() {
    return this->id;
}

int     Projectile::getDamage() {
    return this->dmg;
}

int         Projectile::getX() {
    return this->x;
}

int         Projectile::getY() {
    return this->y;
}

void         Projectile::setX(int x) {
    this->x = x;
    return;
}

void         Projectile::setY(int y) {
    this->y = y;
    return;
}

bool          Projectile::getDirection()
{
    return this->direction;
}

void          Projectile::setDirection(bool dir)
{
    this->direction = dir;
}

void    Projectile::pushProj(void_node* node) {
    void_node**     tmp = &(this->proj_list);
    if (*tmp == NULL)
    {
        (*tmp)= node;
    }
    else {
        for (; (*tmp)->next;)
            *tmp = (*tmp)->next;
        (*tmp)->next = node;
    }
}

void    Projectile::pushShip(void_node* node) {
    void_node**     tmp = &(this->ship_list);
    if ((*tmp) == NULL)
    {
        (*tmp) = node;
    }
    else {
        for (; (*tmp)->next;)
            *tmp = (*tmp)->next;
        (*tmp)->next = node;
    }
}

void    Projectile::popProj(void_node* node) {
    void_node*     tmp = AEntity::proj_list;
    void_node*     tmp2;
    Projectile*     projPtr;
    Projectile*     projPtr2;

    if (this->proj_list == NULL)
        return ;
    projPtr = (Projectile*)tmp->entity;
    projPtr2 = (Projectile*)node->entity;
    if (projPtr->getID() == projPtr2->getID()) {
        this->proj_list = tmp->next;
        delete projPtr;
        return;
    }
    for (;tmp->next;) {
        projPtr = (Projectile*)tmp->next->entity;
        if (projPtr->getID() == projPtr2->getID()) {
            if (tmp->next->next == NULL) {
                delete projPtr;
                tmp->next = NULL;
                return ;
            }
            tmp2 = tmp->next->next;
            delete projPtr;
            tmp->next = tmp2;
            return;
        }
        tmp = tmp->next;
    }
}

void    Projectile::popShip(void_node* node) {
    void_node*     tmp = AEntity::proj_list;
    void_node*     tmp2;
    SpaceShip*     projPtr;
    SpaceShip*     projPtr2;

    if (this->proj_list == NULL)
        return ;
    projPtr = (SpaceShip*)tmp->entity;
    projPtr2 = (SpaceShip*)node->entity;
    if (projPtr->getID() == projPtr2->getID()) {
        this->proj_list = tmp->next;
        delete projPtr;
        return;
    }
    for (;tmp->next;) {
        projPtr = (SpaceShip*)tmp->next->entity;
        if (projPtr->getID() == projPtr2->getID()) {
            if (tmp->next->next == NULL) {
                delete projPtr;
                tmp->next = NULL;
                return ;
            }
            tmp2 = tmp->next->next;
            delete projPtr;
            tmp->next = tmp2;
            return;
        }
        tmp = tmp->next;
    }
}
