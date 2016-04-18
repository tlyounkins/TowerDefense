//
//  CastleModel.cpp
//  Zombie Tower Defense
//


#include "CastleModel.hpp"

// Constructor
CastleModel::CastleModel() {
     castle_health = 50;
}

// Destructor
CastleModel::~CastleModel() {
    
}

int CastleModel::get_castle_health() {
    return castle_health;
}

void CastleModel::set_castle_health(int health) {
    this->castle_health = health;
}