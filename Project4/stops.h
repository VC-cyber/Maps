#ifndef STOPS_H
#define STOPS_H

// STUDENTS: YOU MUST NOT MODIFY ANY CODE IN THIS FILE

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Stops
{
public:
    Stops() {}
    
    bool load(const std::string& tourfile) {
        std::ifstream infile(tourfile);
        if (!infile)
            return false;
        std::string poi_info;
        while (std::getline(infile, poi_info))
        {
            if (poi_info.empty())
                break;
			size_t delim_pos = poi_info.find('|');
			if (delim_pos == std::string::npos  ||  poi_info.find('|', delim_pos+1) != std::string::npos)
				return false;
			poi_data_.push_back({poi_info.substr(0, delim_pos), poi_info.substr(delim_pos+1)});
        }
        return true;
    }

    int size() const { return poi_data_.size(); }

    bool get_poi_data(int index, std::string& poi, std::string& talking_points) const
    {
        if (index < 0 || index >= poi_data_.size())
            return false;
        poi = poi_data_[index].poi;
        talking_points = poi_data_[index].talking_points;
        return true;
    }

private:
    struct POI_DATA
    {
        std::string poi;
        std::string talking_points;
    };

    std::vector<POI_DATA> poi_data_;
};

#endif // __STOPS_H__
