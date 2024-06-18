//
//  tour_generator.cpp
//  Project4
//
//  Created by venkat on 3/12/24.
//
#include "tour_generator.h"
#include "geotools.h"

// Generate a tour based on the provided stops
std::vector<TourCommand> TourGenerator::generate_tour(const Stops& stops) const{
    std::vector<TourCommand> result; // Initialize the result vector
    std::vector<GeoPoint> v; // Vector to store route points
    std::string poi; // Point of interest
    int index = 0; // Index for iteration
    std::string talking_pts; // Information about the point of interest
    while(index < stops.size()){ // Iterate through each stop
        stops.get_poi_data(index, poi, talking_pts); // Get data for the current stop
        TourCommand t;
        t.init_commentary(poi, talking_pts); // Initialize commentary for the stop
        result.push_back(t); // Add commentary to the tour
        
        std::string poi2;
        std::string talking_pts2;
        if(stops.get_poi_data(index+1, poi2, talking_pts2)){ // Check if there's a next stop
            GeoPoint a;
            GeoPoint b;

            // Get the locations for the current and next stop
            if(geoBase -> get_poi_location(poi, a) && geoBase -> get_poi_location(poi2, b)){
                v = route -> route(a,b); // Get the route between the stops
            }
            int i = 0;
            while(i+1 < v.size()){ // Iterate through route points
                a = v.at(i);
                b = v.at(i+1);
                TourCommand p;
                p.init_proceed(getAngle(angle_of_line(a, b)), geoBase -> get_street_name(a, b), distance_earth_miles(a, b), a, b); // Initialize proceeding command
                
                result.push_back(p); // Add proceeding command to the tour
                
                // Add turn command if needed
                if(i+2 < v.size() && geoBase -> get_street_name(a, b) != geoBase -> get_street_name(b, v.at(i+2)) && angle_of_turn(a, b, v.at(i+2))!=0){
                    TourCommand f;
                    if(angle_of_turn(a, b, v.at(i+2))>=180 && angle_of_turn(a, b, v.at(i+2))<=359){
                        f.init_turn("right", geoBase -> get_street_name(b, v.at(i+2))); // Initialize right turn command
                    }
                    else{
                        if(angle_of_turn(a, b, v.at(i+2))>=1 && angle_of_turn(a, b, v.at(i+2))<180)
                            f.init_turn("left", geoBase -> get_street_name(b, v.at(i+2))); // Initialize left turn command
                    }
                    result.push_back(f); // Add turn command to the tour
                }
                i++;
            }
        }
        index++;
    }
    
    return result; // Return the generated tour
}
