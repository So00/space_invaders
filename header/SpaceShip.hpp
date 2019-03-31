#ifndef SPACESHIP_HPP
# define SPACESHIP_HPP

#include "AEntity.hpp"
#include "Projectile.hpp"
#include <iostream>

class Projectile;

class   SpaceShip: public virtual AEntity {

     public:
        SpaceShip();
        SpaceShip(std::string name, std::string type, int x, int y, int hp, std::string* design);
        SpaceShip(SpaceShip const & inst);
        SpaceShip& operator=(SpaceShip const & inst);
        virtual ~SpaceShip();

        void            takeDamage(Projectile & proj);
        void            takeDamageFromShip(int dmg);
        void            fire(SpaceShip* motherShip);
        std::string     getType();
        std::string     getName();
        int             getX();
        int             getY();
        void            setX(int x);
        void            setY(int y);
        int             getHp();
        int             getID();
        void_node       **getProjLst();
        void_node       **getShipLst();
        static int      shipCount;

        void    virtual     pushProj(void_node* node);
        void    virtual     popProj(void_node* node);
        void    virtual     pushShip(void_node* node);
        void    virtual     popShip(void_node* node);
        std::string*        design;
        
    protected:
        int             id;
        std::string     name;
        std::string     type;
        int             x;
        int             y;
        int             hp;
};
#endif