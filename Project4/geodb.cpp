//
//  geodb.cpp
//  Project4
//
//  Created by venkat on 3/8/24.
//

#include <iostream> // needed for any I/O
#include <fstream>  // needed in addition to <iostream> for file I/O
#include <sstream>  // needed in addition to <iostream> for string stream I/O
#include "geodb.h"
#include "geotools.h"

// Load map data from file
bool GeoDatabase::load(const std::string& map_data_file){
    std::ifstream inf(map_data_file); // Open file stream
    
    // Test for failure to open
    if (!inf.is_open()) {
        //std::cerr << "Failed to open file: " << map_data_file << std::endl;
        return false;
    }
    
    std::string line;
    std::string line2;
    std::string line3;
    
    // Read lines from the file
    while (getline(inf, line)) {
        std::istringstream iss(line);
        
        // Read the next line containing street coordinates
        if (!getline(inf, line2)) {
            return false;
        }
        std::istringstream iss2(line2);
        std::string xcoordinate;
        std::string ycoordinate;
        std::string x2coordinate;
        std::string y2coordinate;
        iss2 >> xcoordinate >> ycoordinate >> x2coordinate >> y2coordinate;
        
        // Insert street connections
        insertBiConnectStreet(GeoPoint(xcoordinate, ycoordinate), GeoPoint(x2coordinate, y2coordinate), line);
        addConnects(GeoPoint(xcoordinate, ycoordinate), GeoPoint(x2coordinate, y2coordinate));
        
        // Read the next line containing the number of points of interest (POIs)
        if (!getline(inf, line3)) {
            return false;
        }
        std::istringstream iss3(line3);
        
        int amt;
        
        // Extract the number of POIs
        if (!(iss3 >> amt)) {
            return false;
        }
        
        GeoPoint g = midpoint(GeoPoint(xcoordinate, ycoordinate), GeoPoint(x2coordinate, y2coordinate));
        
        // Insert POIs and connect them to the midpoint of the street segment
        if (amt >= 1) {
            insertBiConnectStreet(GeoPoint(xcoordinate, ycoordinate), g, line);
            addConnects(GeoPoint(xcoordinate, ycoordinate), g);
            insertBiConnectStreet(GeoPoint(x2coordinate, y2coordinate), g, line);
            addConnects(g, GeoPoint(x2coordinate, y2coordinate));
        }
        
        char dummy;
        if (iss3 >> dummy) { // succeeds if there are non-whitespace characters
           // std::cerr << "Ignoring extra data in line: " << line << std::endl;
        }
        
        std::string line4;
        std::string name;
        std::string x3coordinate;
        std::string y3coordinate;
        
        // Read POI names and coordinates
        for (int i = 0; i < amt; i++) {
            if (!getline(inf, name, '|')) {
                return false;
            }
            if (getline(inf, line4)) {
                std::istringstream iss4(line4);
                iss4 >> x3coordinate >> y3coordinate;
                mapPOI.insert(name, GeoPoint(x3coordinate, y3coordinate));
                insertBiConnectStreet(GeoPoint(x3coordinate, y3coordinate), g, "a path");
                addConnects(GeoPoint(x3coordinate, y3coordinate), g);
            }
        }
    }
    
    return true; // Successfully loaded data from file
}

// Get the location of a point of interest (POI)
bool GeoDatabase::get_poi_location(const std::string& poi, GeoPoint& point) const{
    // Check if the POI exists in the map
    if (mapPOI.find(poi) != nullptr) {
        point = *mapPOI.find(poi); // Assign the POI location
        return true;
    }
    return false; // POI not found
}

// Get connected points to a given point
std::vector<GeoPoint> GeoDatabase::get_connected_points(const GeoPoint& pt) const{
    // Check if the point exists in the map
    if (mapConnect.find(pt.to_string()) != nullptr) {
        return *mapConnect.find(pt.to_string()); // Return the connected points
    }
    return std::vector<GeoPoint>(); // No connected points found
}

// Get the name of the street between two points
std::string GeoDatabase::get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const{
    // Check if the street name exists in the map
    if (mapStreetName.find(pt1.to_string() + pt2.to_string()) != nullptr) {
        return *mapStreetName.find(pt1.to_string() + pt2.to_string()); // Return the street name
    }
    return ""; // Street name not found
}
