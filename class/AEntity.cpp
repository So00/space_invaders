#include "../header/AEntity.hpp"
#include <iostream>

AEntity::AEntity() {
    // this->proj_list = new void_node;
    // this->proj_list->entity = NULL;
    // this->proj_list->next = NULL;
    // this->ship_list = new void_node;
    // this->ship_list->entity = NULL;
    // this->ship_list->next = NULL;
    this->ship_list = NULL;
    this->proj_list = NULL;
    return;
}

AEntity::AEntity(AEntity const & src) {
    *this = src;
    return;
}

AEntity::~AEntity() {
    return;
}

AEntity &	AEntity::operator=(AEntity const & rhs) {
    this->proj_list = rhs.proj_list;
    this->ship_list = rhs.ship_list;

    return *this;
}