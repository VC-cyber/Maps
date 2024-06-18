//
//  router.cpp
//  Project4
//
//  Created by venkat on 3/11/24.
//
//
//  router.cpp
//  Project4
//
//  Created by venkat on 3/11/24.
//
#include "router.h"
#include <list>
#include <queue>
#include "geotools.h"
#include <unordered_set>
#include <unordered_map>

Router::Router(const GeoDatabaseBase& geo_db){
    //geobase object that has map data
    geoBase = &geo_db;
}

std::vector<GeoPoint> Router::route(const GeoPoint& pt1,
                                    const GeoPoint& pt2) const{
    
    std::vector<GeoPoint> v;  // Vector to store the final route
    std::list<GeoPoint> l;    // List to store the reconstructed path
    std::unordered_set<std::string> cannotGoPoints;  // Set to track explored points
    std::unordered_map<std::string,Pair> finalPath;  // Map to store parent nodes
    std::priority_queue<Pair, std::vector<Pair>, Compare> coord_queue;  // Priority queue for exploring points
    
    // Initialize priority queue with starting point and initial estimated cost
    coord_queue.push(Pair(pt1, 0, distance_earth_km(pt1, pt2)));
    cannotGoPoints.insert(pt1.to_string());  // Mark starting point as explored
    v.push_back(pt1);  // Add starting point to the route
    finalPath.insert(std::make_pair(pt1.to_string(), Pair(pt1, 0, distance_earth_km(pt1, pt2))));
    
    // Main loop for exploring points until destination is reached or no path is found
    while(!coord_queue.empty()){
        Pair top = coord_queue.top();  // Get the top element from priority queue
        coord_queue.pop();
        
        // Check if the destination has been reached
        if(top.p.to_string() == pt2.to_string()){
            // Reconstruct the path from destination to starting point
            GeoPoint g = pt2;
            while (g.to_string() != pt1.to_string()) {
                l.push_front(g);
                g = finalPath.at(g.to_string()).p;
            }
            // Add reconstructed path to the final route vector
            for(auto p = l.begin(); p != l.end(); p++){
                v.push_back(*p);
            }
            
            return v;  // Return the final route
        }
        
        else{
            // Explore neighbors of the current point
            std::vector<GeoPoint> route = geoBase -> get_connected_points(top.p);
            
            cannotGoPoints.insert(top.p.to_string());  // Mark current point as explored
            
            // Update or add neighbors to the priority queue
            for(auto i: route){
                double g  = (top.g + distance_earth_km(top.p, i));  // Calculate new cost
                if(cannotGoPoints.find(i.to_string()) == cannotGoPoints.end() || g < (finalPath.at(i.to_string())).g){
                    if(cannotGoPoints.find(i.to_string()) == cannotGoPoints.end()){
                        // Add new point to the priority queue
                        coord_queue.push(Pair(i, g, distance_earth_km(i, pt2)));
                        cannotGoPoints.insert(i.to_string());  // Mark new point as explored
                        finalPath.insert(std::make_pair(i.to_string(), top));  // Update parent node
                    }
                    else{
                        // Update existing point's cost and parent node
                        finalPath.at(i.to_string()).g = g;
                        finalPath.at(i.to_string()).h = distance_earth_km(pt2, i);
                        finalPath.at(i.to_string()).p = top.p;
                        coord_queue.push(finalPath.at(i.to_string()));
                    }
                }
            }
            
        }
    }
    return std::vector<GeoPoint>();  // Return empty vector if no route is found
}
