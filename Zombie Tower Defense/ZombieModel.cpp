//
//  ZombieModel.cpp
//  Zombie Tower Defense
//


#include "ZombieModel.hpp"

// Constructor
ZombieModel::ZombieModel() {
    this->count = 0;
    this->right= true;
    this->left=true;
    this->up=true;
    this->path_location = 0;
    this->down=true;
    this->visible = true;
    this->health = 1;
}

// Destructor
ZombieModel::~ZombieModel() {
    
}

// Create path to follow
// Commented out until it works
/**void ZombieModel::create_path(int i, int j, int game_map[]){

    printf("%i, %i\n", this->x, this->y);
    // TEMP
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            if(game_map[(j*40)+i] == 9){
                printf(" |");
            } else{
                printf(" _");
            }
        }
        printf("\n");
    }
    printf("\n");
    
    // Create a start state
    MapSearchNode nodeStart;
    nodeStart.x = this->x;
    nodeStart.y = this->y;
    nodeStart.set_map(game_map);
    
    // Define the goal state
    MapSearchNode nodeEnd;
    nodeEnd.x = 20;
    nodeEnd.y = 15;
    nodeEnd.set_map(game_map);
    
    nodeStart.print_map();
    nodeEnd.print_map();
    
    // Set Start and goal states
    astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );
    
    unsigned int SearchCount = 0;
    
    const unsigned int NumSearches = 1;
    
    while(SearchCount<NumSearches){
    
        unsigned int SearchState;
        unsigned int SearchSteps = 0;
    
        do{
            SearchState = astarsearch.SearchStep();
            SearchSteps++;
            
            int len = 0;
            
            printf("giggles, %i, %i\n", this->x, this->y);

            MapSearchNode *p = astarsearch.GetOpenListStart();
            while( p ){
                len++;
                p = astarsearch.GetOpenListNext();
                
            }
            printf("Open list length: %i\n", len);
            len = 0;
            
            p = astarsearch.GetClosedListStart();
            while( p ){
                len++;
                p = astarsearch.GetClosedListNext();
                
            }
            printf("Closed list length: %i\n", len);
        } while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );
    
    
        if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
        {
            path[0] = astarsearch.GetSolutionStart();
            
            this->path_length = 1;
            bool cont = true;
            while(cont)
            {
                path[this->path_length] = astarsearch.GetSolutionNext();
                
                if(path[this->path_length] == NULL){
                    cont = false;
                } else{
                    this->path_length++;
                }
                
            };
        
            // For Debugging
            printf("Done, %i\n", this->path_length);
            astarsearch.FreeSolutionNodes();
            SearchCount ++;
        }
        else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED )
        {
            printf("Search terminated. Did not find goal state\n");
            printf("\t coord: %i, %i\n", this->x, this->y);
            
        }
        
    }
    
    printf("%i, %i\n", i, j);
}**/

// Update zombie location method
void ZombieModel::step(){
    // Head towards (0, -5)
    this->count += 1;
    if(count == this->speed){
        // For testing
        //printf("location: %i, length: %i\n", this->path_location, this->path_length);
        
        // For Astar algorithm
        /**if(this->path_location < this->path_length){
            this->path[path_location]->x = this->x;
            this->path[path_location]->y = this->y;
            this->path_location++;
        }**/
    
        // Print current coordinates (for testing)
        //printf("%i %i \n", this->x, this->y);
        int ran = rand() % 10;
        if(ran < 5){
            if(x > 20){
                x -= 1;
            } else if(x < 20){
                x += 1;
            } else {
                // Can only move y
                if(y > 15){
                    y -= 1;
                } else if(y < 15){
                    y += 1;
                }
            }
        } else{
            if(y > 15){
                y -= 1;
            } else if(y < 15){
                y += 1;
            } else {
                // Can only move x
                if(x > 20){
                    x -= 1;
                } else if(x < 20){
                    x += 1;
                }
            }
        }
        
        this->count = 0;
    }
}