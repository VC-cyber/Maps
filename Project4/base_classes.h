#ifndef BASECLASSES_H
#define BASECLASSES_H

// STUDENTS MUST NOT CHANGE THIS FILE

#include <string>
#include <vector>

#include "geopoint.h"
#include "stops.h"
#include "tourcmd.h"

class GeoDatabaseBase
{
public:
    GeoDatabaseBase() {}
    virtual ~GeoDatabaseBase() {}

    virtual bool load(const std::string& map_data_file) = 0;
    virtual bool get_poi_location(const std::string& poi, GeoPoint& point) const = 0;
    virtual std::vector<GeoPoint> get_connected_points(const GeoPoint& pt) const = 0;
    virtual std::string get_street_name(const GeoPoint& pt1, const GeoPoint& pt2) const = 0;
};

class RouterBase
{
public:
    RouterBase() {}
    virtual ~RouterBase() {}
    virtual std::vector<GeoPoint> route(const GeoPoint& pt1, const GeoPoint& pt2) const = 0;
};

class TourGeneratorBase
{
public:
    TourGeneratorBase() { }
    virtual ~TourGeneratorBase() {}
    virtual std::vector<TourCommand> generate_tour(const Stops &stops) const = 0;
};

#endif // BASECLASSES_H
