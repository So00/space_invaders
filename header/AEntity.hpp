#ifndef AENTITY_HPP
# define AENTITY_HPP

#include <iostream>
// #include "Projectile.hpp"
// #include "SpaceShip.hpp"

typedef struct s_void_node {
    void*                   entity;
    struct s_void_node*      next;
} void_node;

class AEntity {

public: 

    AEntity(); 
    AEntity(AEntity const & src); 
    virtual ~AEntity(); 
	AEntity &		operator=(AEntity const & rhs);
    void    virtual pushProj(void_node* node) = 0;
    void    virtual popProj(void_node* node) = 0;
    
    void    virtual pushShip(void_node* node) = 0;
    void    virtual popShip(void_node* node) = 0;


protected:
    void_node*    proj_list;
    void_node*    ship_list;

};


#endif

