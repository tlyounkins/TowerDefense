//
//  CastleModel.cpp
//  Zombie Tower Defense
//


#include "CastleModel.hpp"

// Constructor
CastleModel::CastleModel() {
    // ArrayList<>Castle = new ArrayList<>(); ?
     castle_health = 100;
}

// Destructor
CastleModel::~CastleModel() {
    
}

int CastleModel::get_castle_health() {
    return castle_health;
}

void CastleModel::set_castle_health(int castle_health) {
    //this.castle_health = castle_health;
}