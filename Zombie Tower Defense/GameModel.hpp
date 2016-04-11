//
//  GameModel.hpp
//  Zombie Tower Defense
//


#ifndef GameModel_hpp
#define GameModel_hpp

#include <stdio.h>
#include "LevelModel.hpp"
#include "LevelModel.cpp"

class GameModel {

public:
    // Constructor, destructor
    GameModel();
    ~GameModel();
    
    // Variables
    int total_points;
    int wave_num;
    int current_level;
    int num_resources;
    //LevelModel levels[8];
    LevelModel levels;
   
    
    // Public interface (GameModel's functions)
    int get_total_points();
    void set_total_points(int points);
    int get_wave_num();
    void create_levels();
    void set_wave_num(int wave);
    int get_level();
    void set_level(int level);
    int get_num_resources();
    void set_num_resources(int resources);
    
};
#endif /* GameModel_hpp */
