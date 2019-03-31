#include "../header/SpaceShip.hpp"
#include "../header/AEntity.hpp"

int SpaceShip::shipCount = 0;

SpaceShip::SpaceShip() {
    return;
}

SpaceShip::SpaceShip(std::string name, std::string type, int x, int y, int hp, std::string* design) {
    this->id = SpaceShip::shipCount++;
    this->name = name;
    this->type = type;
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->design = design;
    return;
}

SpaceShip::SpaceShip(SpaceShip const & inst) {
    *this = inst;
    return ;
}

SpaceShip& SpaceShip::operator=(SpaceShip const & inst) {
    this->name = inst.name;
    this->type = inst.type;
    this->x = inst.x;
    this->y = inst.y;
    this->hp = inst.hp;
    this->design = inst.design;
    return *this;
}

SpaceShip::~SpaceShip() {
    return;
}

void    SpaceShip::takeDamage(Projectile & proj) {
    this->hp -= proj.getDamage();
    if (this->hp < 0)
        this->hp = 0;
    return;
}

std::string     SpaceShip::getType() {
    return this->type;
}

int         SpaceShip::getX() {
    return this->x;
}

int         SpaceShip::getY() {
    return this->y;
}

void         SpaceShip::setX(int x) {
    this->x = x;
    return;
}

void         SpaceShip::setY(int y) {
    this->y = y;
    return;
}

void_node   **SpaceShip::getProjLst() {
    return &(this->proj_list);
}

void_node   **SpaceShip::getShipLst() {
    return &(this->ship_list);
}

int         SpaceShip::getHp() {
    return this->hp;
}

void        SpaceShip::takeDamageFromShip(int dmg) {
    this->hp -= dmg;
    if (this->hp < 0)
        this->hp = 0;
    return;
}
//incr y dans fire pour que le proj start pas dans le sprite

void SpaceShip::fire(SpaceShip* motherShip) {
    void_node *newNode = new void_node;
    //new Projectile(50, this->x, this->y+5, 'A', this);
    if (this->type == "player")
        newNode->entity = new Projectile(50, this->x, this->y - 3, '^', this);
    else
        newNode->entity = new Projectile(10, this->x, this->y + 3, 'v', this);
    newNode->next = NULL;
    motherShip->pushProj(newNode);
}

std::string     SpaceShip::getName()
{
    return (this->name);
}

void    SpaceShip::pushProj(void_node* node) {
    void_node**     list = this->getProjLst();
    void_node*      tmp = *list;
    if (tmp == NULL)
    {
        (*list) = node;
    }
    else {
        for (; tmp->next;)
            tmp = tmp->next;
        tmp->next = node;
    }
}

void    SpaceShip::pushShip(void_node* node) {
    void_node**     list = this->getShipLst();
    void_node*      tmp = *list;
    if (tmp == NULL) {
        *list = node;
    }
    else {
        for (; tmp->next;)
            tmp = tmp->next;
        tmp->next = node;
    }
}

void    SpaceShip::popProj(void_node* node) {
    void_node**     list = this->getProjLst();
    void_node*      tmp = *list;
    void_node*      tmp2;
    Projectile*     projPtr;
    Projectile*     projPtr2;

    if (tmp == NULL)
        return ;
    projPtr = (Projectile*)tmp->entity;
    projPtr2 = (Projectile*)node->entity;
    if (projPtr->getID() == projPtr2->getID()) {
        if (tmp->next == NULL) {
            delete (Projectile *)node->entity;
            delete node;
            *list = NULL;
        } else {
            *list = tmp->next;
            delete (Projectile *)node->entity;
            delete node;
        }
        return ;
    }
    for (;tmp;) {
        projPtr = (Projectile*)tmp->entity;
        if (projPtr->getID() == projPtr2->getID()) {
            if (tmp->next == NULL) {
                delete projPtr;
                delete tmp;
                tmp2->next = NULL;
                return ;
            }
            tmp2->next = tmp->next;
            delete tmp;
            return;
        }
        tmp2 = tmp;
        tmp = tmp->next;
    }
}

void    SpaceShip::popShip(void_node* node) {
    void_node**     ship_lst = this->getShipLst();
    void_node*     tmp = *ship_lst;
    void_node*     tmp2;
    SpaceShip*     shipPtr;
    SpaceShip*     shipPtr2;

    if (*ship_lst == NULL)
        return ;
    shipPtr = (SpaceShip*)tmp->entity;
    shipPtr2 = (SpaceShip*)node->entity;
    if (shipPtr->getID() == shipPtr2->getID()) {
        *ship_lst = tmp->next;
        delete shipPtr;
        delete tmp;
        return;
    }
    for (;tmp;) {
        shipPtr = (SpaceShip*)tmp->entity;
        if (shipPtr->getID() == shipPtr2->getID()) {
            if (tmp->next == NULL) {
                delete shipPtr;
                delete tmp;
                tmp2->next = NULL;
                return ;
            }
            tmp2->next = tmp->next;
            delete tmp;
            return ;
        }
            tmp2 = tmp;
            tmp = tmp->next;
    }
}

int     SpaceShip::getID() {
    return this->id;
}