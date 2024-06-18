#ifndef GEOTOOLS_H
#define GEOTOOLS_H

// STUDENTS: YOU MUST NOT MODIFY ANY CODE IN THIS FILE
#include <iostream>
#include <sstream>
#include <iomanip>

#include "geopoint.h"

// Haversine formula: http://stackoverflow.com/questions/10198985/calculating-the-distance-between-2-latitudes-and-longitudes-that-are-saved-in-a

#include <cmath>

const double pi = 4 * atan(1.0);
const double earthRadiusKm = 6371.0;

// This function converts decimal degrees to radians
inline double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
inline double rad2deg(double rad) {
  return (rad * 180 / pi);
}

/**
* Returns the distance between two points on the Earth.
* Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
* @param lat1d Latitude of the first point in degrees
* @param lon1d Longitude of the first point in degrees
* @param lat2d Latitude of the second point in degrees
* @param lon2d Longitude of the second point in degrees
* @return The distance between the two points in kilometers
*/

inline double distance_earth_km(const GeoPoint &g1, const GeoPoint &g2) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(g1.latitude);
  lon1r = deg2rad(g1.longitude);
  lat2r = deg2rad(g2.latitude);
  lon2r = deg2rad(g2.longitude);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

inline double distance_earth_miles(const GeoPoint &g1, const GeoPoint &g2) {
  const double milesPerKm = 0.621371;
  return distance_earth_km(g1, g2) * milesPerKm;
}


inline double angle_of_turn(const GeoPoint &p1, const GeoPoint &p2, const GeoPoint &p3)
{
  const double angle1 = atan2(p2.latitude - p1.latitude, p2.longitude - p1.longitude);
  const double angle2 = atan2(p3.latitude - p2.latitude, p3.longitude - p2.longitude);

  double result = (angle2 - angle1) * 180 / pi;
  if (result < 0)
    result += 360;

  return result;
}

inline double angle_of_line(const GeoPoint &p1, const GeoPoint &p2)
{
  const double angle = atan2(p2.latitude - p1.latitude, p2.longitude - p1.longitude);
  double result = angle * 180 / pi;
  if (result < 0)
    result += 360;

  return result;
}

inline GeoPoint midpoint(const GeoPoint &p1, const GeoPoint &p2) {
  GeoPoint mid;
  mid.latitude = (p1.latitude + p2.latitude) / 2;
  mid.longitude = (p1.longitude + p2.longitude) / 2;

  std::ostringstream oss_lat;
  oss_lat << std::fixed << std::setprecision(7) << mid.latitude;
  mid.sLatitude = oss_lat.str();

  std::ostringstream oss_long;
  oss_long << std::fixed << std::setprecision(7) << mid.longitude;
  mid.sLongitude = oss_long.str();

  return mid;
}

#endif // GEOTOOLS_H
