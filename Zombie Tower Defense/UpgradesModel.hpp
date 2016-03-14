//
//  UpgradesModel.hpp
//  Zombie Tower Defense
//


#ifndef UpgradesModel_hpp
#define UpgradesModel_hpp

#include <stdio.h>

class UpgradesModel {
    
public:
    // Constructor, destructor
    UpgradesModel();
    ~UpgradesModel();
    
    // Variables
    GLUquadricObj *tower;
    
    // Public interface
    void draw_tower();
};

#endif /* UpgradesModel_hpp */
