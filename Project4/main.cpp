#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "geodb.h"

#include "router.h"
#include "geotools.h"
#include "stops.h"
#include "tourcmd.h"
#include "tour_generator.h"

using namespace std;

void print_tour(vector<TourCommand>& tcs)
{
    double total_dist = 0;
    std::string direction;
    double street_distance = 0;

    cout << "Starting tour...\n";

    for (size_t i = 0; i < tcs.size(); ++i)
    {
        if (tcs[i].get_command_type() == TourCommand::commentary)
        {
            cout << "Welcome to " << tcs[i].get_poi() << "!\n";
            cout << tcs[i].get_commentary() << "\n";
        }
        else if (tcs[i].get_command_type() == TourCommand::turn)
        {
            cout << "Take a " << tcs[i].get_direction() << " turn on " << tcs[i].get_street() << endl;
        }
        else if (tcs[i].get_command_type() == TourCommand::proceed)
        {
            total_dist += tcs[i].get_distance();
            if (direction.empty())
                direction = tcs[i].get_direction();
            street_distance += tcs[i].get_distance();
            if (i+1 < tcs.size() && tcs[i+1].get_command_type() == TourCommand::proceed
                && tcs[i+1].get_street() == tcs[i].get_street() && tcs[i].get_street() != "a path")
            {
                continue;
            }

            cout << "Proceed " << std::fixed << std::setprecision(3) << street_distance << " miles " << direction << " on " << tcs[i].get_street() << endl;
            street_distance = 0;
            direction.clear();
        }
    }

    cout << "Your tour has finished!\n";
    cout << "Total tour distance: " << std::fixed << std::setprecision(3) << total_dist << " miles\n";
}

int main(int argc, char *argv[])
{
//    if (argc != 3)
//    {
//        cout << "usage: BruinTour mapdata.txt stops.txt\n";
//        return 1;
//    }

    GeoDatabase geodb;
    if (!geodb.load("/Users/venkat/Desktop/UCLA_CS/CS 32/Project4/Project4/Project4/mapdata.txt"))
    {
        cout << "Unable to load map data: " << argv[1] << endl;
        return 1;
    }

    Router router(geodb);
    TourGenerator tg(geodb, router);

    Stops stops;
    if (!stops.load("/Users/venkat/Desktop/UCLA_CS/CS 32/Project4/Project4/Project4/stops.txt"))
    {
        cout << "Unable to load tour data: " << argv[2] << endl;
        return 1;
    }

    std::cout << "Routing...\n\n";

    vector<TourCommand> tcs = tg.generate_tour(stops);
    if (tcs.empty())
        cout << "Unable to generate tour!\n";
    else
        print_tour(tcs);
}


//int main() {
//    ///Test Case 1: Create a HashMap with default max load
//    HashMap<int> intHashMap;
//    assert(intHashMap.size() == 0);
//
//    // Test Case 2: Insert elements into the HashMap
//    intHashMap.insert("one", 1);
//    intHashMap.insert("two", 2);
//    intHashMap.insert("three", 3);
//    assert(intHashMap.size() == 3);
//
//    // Test Case 3: Find elements in the HashMap
//    assert(*intHashMap.find("one") == 1);
//    assert(*intHashMap.find("two") == 2);
//    assert(*intHashMap.find("three") == 3);
//
//    // Test Case 4: Update existing value using operator[]
//    intHashMap["two"] = 20;
//    assert(*intHashMap.find("two") == 20);
//
//    // Test Case 5: Insert new element using operator[]
//    intHashMap["four"] = 4;
//    assert(*intHashMap.find("four") == 4);
//    assert(intHashMap.size() == 4);
//
//    // Test Case 6: Verify that duplicate keys are not allowed
//    intHashMap.insert("four", 44);
//    assert(*intHashMap.find("four") == 44); // Value should be changed
//
//    // Test Case 7: Check if default max load is set
//    HashMap<double> doubleHashMap;
//    assert(doubleHashMap.size() == 0);
//
//    // Test Case 8: Check custom max load
//    HashMap<std::string> strHashMap(0.5);
//    assert(strHashMap.size() == 0);
//
//    //Test case 9
//      HashMap<int> intHashMap2(0.5);
//      assert(intHashMap2.size() == 0);
//        for (int i = 0; i < 7; ++i) {
//            std::string key = "key" + std::to_string(i);
//            intHashMap2.insert(key, i);
//            assert(intHashMap2.size() == (i + 1));
//        }
//
//        // Attempt to insert one more element, which should trigger a rehash
//        intHashMap2.insert("overflow", 999); // This insertion should exceed the maximum load
//
//        // Verify that the size has increased
//        assert(intHashMap2.size() == 8);
//
//        // Verify that the 'overflow' key is correctly inserted
//        assert(*intHashMap2.find("overflow") == 999);
//
//    GeoDatabase g;
//    g.load("/Users/venkat/Desktop/UCLA CS/CS 32/Project4/Project4/Project4/mapdata.txt");
//
//    GeoPoint f;
//    g.get_poi_location("Brentwood Country Mart", f);
//
//    assert(g.get_street_name(GeoPoint("34.0476495","-118.4910837"), GeoPoint("34.0469402", "-118.4902543")) == "26th Street");
//
//    GeoPoint p1("34.0732851", "-118.4931016");
//    GeoPoint p2("34.0736122", "-118.4927669");
//
//    assert(g.get_street_name(p1, p2) == "Glenmere Way"); // writes
//    assert(g.get_street_name(p2, p1) == "Glenmere Way");
//
//    GeoPoint p3("34.0601422", "-118.4468929");
//    GeoPoint p4("34.0600768", "-118.4467216");
//
//    assert(g.get_street_name(p3, p4) == "a path"); // writes
//    assert(g.get_street_name(p4, p3) == "a path");
//
//    GeoPoint p5("34.0602175", "-118.4464952");
//    GeoPoint p6("34.0600768", "-118.4467216");
//
//    assert(g.get_street_name(p5, p6) == "Kinross Avenue"); // writes
//    assert(g.get_street_name(p5, p6) == "Kinross Avenue");
//
//    assert(f.latitude == 34.0474215 && f.longitude == -118.4901897);
//
//    std::vector<GeoPoint> pts = g.get_connected_points(
//    GeoPoint("34.0734335","-118.4449143" ));
//
//    for(auto p = 0; p < pts.size(); p++){
//        double x = distance_earth_km(GeoPoint("34.0734335","-118.4449143" ), pts.at(p)) +  distance_earth_km(pts.at(p),  GeoPoint("34.0674197", "-118.4257667"));
//        std::cout <<  x << std::endl;
//    }
//    std::cout << "ENOFINSDOIFNSOINFDSONIFSODINFSOIN ////////////" << std::endl;
//    if (pts.empty())
//        std::cout << "There are no points connected to your specified point\n";
//    else {
//        for (const auto p: pts){
//            std::cout << p.sLatitude << ", " << p.sLongitude << std::endl;
//        }
//    }
//    Router r(g);
//
//    std::cout <<"NEXT TEST/////////////////////////////////////" << std::endl;
//    std::vector<GeoPoint> route = r.route(GeoPoint("34.0630614", "-118.4468781") , GeoPoint("34.0614911", "-118.4464410"));
//
//
//    if (route.empty())
//        std::cout << "There are no points connected to your specified point\n";
//    else {
//        for (const auto p: route){
//           std::cout << p.sLatitude << ", " << p.sLongitude << std::endl;
//        }
//    }
//
//    std::cout <<"NEXT TEST/////////////////////////////////////" << std::endl;
//
//    Router rtr(g);
//    // Ackerman to Wooden
//    vector<GeoPoint> rte = rtr.route(GeoPoint("34.0747683" , "-118.4517921"), GeoPoint("34.0674197", "-118.4257667"));
//    for(GeoPoint p : rte)
//        cout << p.to_string() << endl;
//
//    std::cout << "All test cases passed!" << std::endl;
//
//    return 0;
//}

