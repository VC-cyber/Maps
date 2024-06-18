#ifndef TOURCMD_H
#define TOURCMD_H

// STUDENTS: YOU MUST NOT MODIFY ANY CODE IN THIS FILE

#include <iostream>
#include <string>

#include "geopoint.h"

class TourCommand
{
public:
	enum TOUR_COMMAND
	{
		invalid,
		turn,
		proceed,
		commentary
	};

	TourCommand()
	{
		command_ = invalid;
	}

	void init_turn(const std::string& turn_direction, const std::string& street_name)
	{
		command_ = turn;
		street_name_ = street_name;
		direction_ = turn_direction;
		distance_ = 0;
	}

	void init_proceed(const std::string& direction, const std::string& streetName,
					  double distance, const GeoPoint& start, const GeoPoint& end)
	{
		command_ = proceed;
		direction_ = direction;
		street_name_ = streetName;
		distance_ = distance;
		start_ = start;
		end_ = end;
	}

	void init_commentary(const std::string& poi, const std::string& commentary)
	{
		command_ = TOUR_COMMAND::commentary;
		poi_ = poi;	
		commentary_ = commentary;
	}

	TOUR_COMMAND get_command_type() const
	{
		return command_;
	}

	std::string get_direction() const
	{
		return direction_;
	}

	std::string get_street() const
	{
		return street_name_;
	}

	double get_distance() const
	{
		return distance_;
	}

	void set_distance(double dist)
	{
		distance_ = dist;
	}

	std::string get_commentary() const
	{
		return commentary_;
	}

	std::string get_poi() const {
		return poi_;
	}

	void get_points(GeoPoint& start, GeoPoint& end) const
	{
		start = start_;
		end = end_;
	}

private:
	TOUR_COMMAND command_;	  // turn left, turn right, proceed
	std::string street_name_; // Westwood Blvd
	std::string direction_;	  // "left" for turn or "northeast" for proceed
	std::string commentary_;  // "this is the bruin bear, which was added in ..."
	std::string poi_;		  // "Bruin Bear"
	double distance_;		  // 3.2 //KM
	GeoPoint start_, end_;
};

#endif // TOURCMD_H
