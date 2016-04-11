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
    int tower_cost;
    int castle_health_upgrade_cost;
    int castle_health_upgrade;
    int moat_upgrade_cost;
    // Public interface
    
};

#endif /* UpgradesModel_hpp */
