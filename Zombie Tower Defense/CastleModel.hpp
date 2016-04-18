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
    int castle_width;
    int castle_length;
    
    // Public interface
    int get_castle_health();
    void set_castle_health(int health);
};
#endif /* CastleModel_hpp */
