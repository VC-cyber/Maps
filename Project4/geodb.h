//
//  geodb.hpp
//  Project4
//
//  Created by venkat on 3/8/24.
//
#include "base_classes.h"
#include "hashmap.h"
#ifndef geodb_hpp
#define geodb_hpp

#include <stdio.h>

class GeoDatabase: public GeoDatabaseBase
{
    public:
            //constructor and destructor
            GeoDatabase(){}
            virtual ~GeoDatabase(){}
    //load function to load mapdata.txt
         virtual bool load(const std::string& map_data_file);
        //get poi, connected points, street name
         virtual bool get_poi_location(const std::string& poi,
         GeoPoint& point) const;
    
         virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const;
    
         virtual std::string get_street_name(const GeoPoint& pt1,
         const GeoPoint& pt2) const;
     
    private:
    //three hashmaps with the POI, connected points, street name
        HashMap<GeoPoint> mapPOI;
        HashMap<std::vector<GeoPoint>> mapConnect;
        HashMap<std::string> mapStreetName;
    //bidirectionally insert street
        void insertBiConnectStreet(GeoPoint g1, GeoPoint g2, std::string name){
            mapStreetName.insert(g1.to_string() + g2.to_string(), name);
            mapStreetName.insert(g2.to_string() + g1.to_string(),name);
        }
    //add connections
        void addConnects(GeoPoint g1, GeoPoint connection){
            if(mapConnect.find(g1.to_string()) == nullptr){
                mapConnect.insert(g1.to_string(), std::vector<GeoPoint>());
            }

            mapConnect.find(g1.to_string())->push_back(connection);
            
            if(mapConnect.find(connection.to_string()) == nullptr){
                mapConnect.insert(connection.to_string(), std::vector<GeoPoint>());
            }

            mapConnect.find(connection.to_string())->push_back(g1);
            
        }
};

#endif /* geodb_hpp */
