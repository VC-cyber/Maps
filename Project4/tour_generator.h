//
//  tour_generator.hpp
//  Project4
//
//  Created by venkat on 3/12/24.
//
#include <vector>
#include "base_classes.h"

#ifndef tour_generator_hpp
#define tour_generator_hpp

class TourGenerator: public TourGeneratorBase
{
    public:
    //constructor and destructor, with generate_tour
        TourGenerator(const GeoDatabaseBase& geodb, const RouterBase& router){
            geoBase = &geodb;
            route = &router;
        }
        virtual ~TourGenerator(){}
         virtual std::vector<TourCommand> generate_tour(const Stops& stops) const;
    
    private:
    //pointers of the base classes of route and geodatabase
        const GeoDatabaseBase* geoBase;
        const RouterBase* route;
    //getting angle for geotour
        std::string getAngle(double angle) const{
            if(angle >=360 && angle < 1){
                return "L";
            }
            if(angle >= 337.5){
                return "east";
            }
            if(angle >= 292.5){
                return "southeast";
            }
            if(angle >= 247.5){
                return "south";
            }
            if(angle >= 202.5){
                return "southwest";
            }
            if(angle >= 157.5){
                return "west";
            }
            if(angle >= 112.5){
                return "northwest";
            }
            if(angle >= 67.5){
                return "north";
            }
            if(angle >= 22.5){
                return "northeast";
            }
            else{
                return "east";
            }
        }
    
};

#endif /* tour_generator_hpp */
