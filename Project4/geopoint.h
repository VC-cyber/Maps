#ifndef GEOPOINT_H
#define GEOPOINT_H

// STUDENTS: YOU MUST NOT MODIFY ANY CODE IN THIS FILE

#include <string>

struct GeoPoint
{
  GeoPoint(const std::string& lat, const std::string& lon)
   : sLatitude(lat), sLongitude(lon)
  {
    latitude = std::stod(lat);
    longitude = std::stod(lon);
  }

  GeoPoint() : GeoPoint("0.0000000", "0.0000000") {}

  std::string to_string() const {
    return sLatitude + "," + sLongitude;
  }

  double latitude;
  double longitude;
  std::string sLatitude;
  std::string sLongitude;
};


#endif  // GEOPOINT_H
