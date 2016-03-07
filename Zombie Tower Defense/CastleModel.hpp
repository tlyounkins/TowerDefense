//
//  CastleModel.hpp
//  Zombie Tower Defense
//


#ifndef CastleModel_hpp
#define CastleModel_hpp

#include <stdio.h>

class CastleModel {
    
public:
    // Constructor, destructor
    CastleModel();
    ~CastleModel();
    
    // Variables
    int castle_health;
    // ArrayList<>Castle ?
    
    // Public interface
    // ArrayList<>getCastle(); ?
    // ArrayList<>setCastle(); ?
    int get_castle_health();
    void set_castle_health(int castle_health);
    void draw();
    
};
#endif /* CastleModel_hpp */
