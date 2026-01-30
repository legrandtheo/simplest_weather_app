#include "weather_utilities.h"

using namespace std;

std::string weather_utilities::wind_azimuth_to_directions(const size_t &wind_azimuth)
{
    std::string output_direction{", "};
    if (wind_azimuth <= 50 || wind_azimuth >= 310)
    {
        output_direction.append("N");
    }
    if (wind_azimuth >= 130 && wind_azimuth <= 230)
    {
        output_direction.append("S");
    }
    if (wind_azimuth >= 40 && wind_azimuth <= 140)
    {
        output_direction.append("E");
    }
    if (wind_azimuth >= 220 && wind_azimuth <= 320)
    {
        output_direction.append("W");
    }
    return output_direction;
}

std::string weather_utilities::get_time_from_fulldate_iso(const std::string &fulldate)
{
    string hour_and_minutes = fulldate.substr(fulldate.size()-5,5);
    return hour_and_minutes;
}
