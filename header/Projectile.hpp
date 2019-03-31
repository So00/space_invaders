#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

#include "AEntity.hpp"
#include "SpaceShip.hpp"
#include <iostream>

class SpaceShip;

class   Projectile: public virtual AEntity {

    public: 
        Projectile();
        Projectile(Projectile const & inst);
        Projectile(int dmg, int x, int y, char design, SpaceShip* ship);
        virtual ~Projectile();
	    Projectile&	operator=(Projectile const & inst);

        int             getDamage();
        int             getID();
        static int      projCount;
        bool            getDirection();

        void    virtual pushProj(void_node* node);
        void    virtual popProj(void_node* node);
        void    virtual pushShip(void_node* node);
        void    virtual popShip(void_node* node);

        int             getX();
        int             getY();
        void            setX(int x);
        void            setY(int y);
        void            setDirection(bool dir);
        char            design;

    protected:
        int     id;
        int     dmg;
        int     x;
        int     y;
        bool    direction;

};

#endif
