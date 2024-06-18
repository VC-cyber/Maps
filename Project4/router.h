//
//  router.hpp
//  Project4
//
//  Created by venkat on 3/11/24.
//

#ifndef router_hpp
#define router_hpp

#include "base_classes.h"


class Router: public RouterBase
{
    public:
    //constructor and deconstructor
         Router(const GeoDatabaseBase& geo_db);
         virtual ~Router(){}
    //router from geopoint pt1 and pt2
         virtual std::vector<GeoPoint> route(const GeoPoint& pt1,
         const GeoPoint& pt2) const;
    private:
    //Pair struct with geopoint, f heurisitc, g score and h score
        const GeoDatabaseBase* geoBase;
        struct Pair{
            Pair(GeoPoint x, double g1, double h1){
                p = x;
                f = g1+h1;
                g = g1;
                h = h1;
            }
            GeoPoint p;
            double f;
            double g;
            double h;
        };
        //Compare class that compares the two pairs
        class Compare {
            public:
               bool operator()(Pair pt1, Pair pt2){
                   if(pt1.f > pt2.f){
                       return true;
                   }
                   return false;
              }
        };
};
#endif /* router_hpp */
