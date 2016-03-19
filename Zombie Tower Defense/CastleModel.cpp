//
//  CastleModel.cpp
//  Zombie Tower Defense
//


#include "CastleModel.hpp"

// Constructor
CastleModel::CastleModel() {
     castle_health = 100;
}

// Destructor
CastleModel::~CastleModel() {
    
}

int CastleModel::get_castle_health() {
    return castle_health;
}

void CastleModel::set_castle_health(int health) {
    this->castle_health = castle_health;
}

int CastleModel::get_castle_width() {
    return castle_width;
}

void CastleModel::set_castle_width(int castle_length) {
    this->castle_length = castle_length;
}

int CastleModel::get_castle_length() {
    return castle_length;
}

void CastleModel::set_castle_length(int castle_length) {
    this->castle_length = castle_length;
}