#ifndef WEATHER_APP_WEATHER_UTILITIES_H
#define WEATHER_APP_WEATHER_UTILITIES_H
#include <string>

namespace weather_utilities {
    std::string wind_azimuth_to_directions(const size_t& wind_azimuth);
    std::string get_time_from_fulldate_iso(const std::string& fulldate);
}

#endif //WEATHER_APP_WEATHER_UTILITIES_H
