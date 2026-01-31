#ifndef WEATHER_APP_API_JSON_DECOMPOSER_H
#define WEATHER_APP_API_JSON_DECOMPOSER_H

#include <string>
#include <nlohmann/json.hpp>

//using namespace std;

struct temperature_holder_celcius
{
    double current_temp;
    double felt_temp;
    double max_today_temp;
    double min_today_temp;
    std::vector<float> max_week_temps;
    std::vector<float> min_week_temps;
    std::vector<std::string> dates_week_temps;
};
struct wind_holder
{
    double wind_speed_km_h;
    size_t wind_direction_degrees;

};
struct suntime
{
    std::string sunrise;
    std::string sunset;
};
struct mixed_other_data
{
    size_t humidity;
    double surface_pressure;
    double UV_index;
};
struct air_quality_data
{
    size_t EU_AQI;
    float pm10;
    float pm2_5;
    float CO;
    float NO2;
    float SO2;
    float O3;
};

const std::vector<std::string> main_URL_parts{"https://api.open-meteo.com/v1/forecast?latitude=", "&longitude=", "&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset,uv_index_max&current=temperature_2m,apparent_temperature,wind_direction_10m,wind_speed_10m,relative_humidity_2m,surface_pressure&timezone="};
const std::vector<std::string> AQ_URL_parts{"https://air-quality-api.open-meteo.com/v1/air-quality?latitude=", "&longitude=", "&current=european_aqi,pm10,pm2_5,carbon_monoxide,nitrogen_dioxide,sulphur_dioxide,ozone&timezone="};

class api_json_decomposer
{
public:
    void dual_init(const std::string& MAIN_URL, const std::string& AQ_URL);
    void refresh_from_city_name(const std::string& city_name);
    temperature_holder_celcius temp_holder_celcius{};
    wind_holder wind_holder{};
    suntime suntime{};
    mixed_other_data other_data{};
    air_quality_data AQ_data{};
    std::string status{"No data yet"};
private:
    size_t static useful_write_function(void *ptr, size_t size, size_t nmemb, void *userdata);
    std::string static useful_day_from_fulldate_function(const std::string& fulldate);

    static std::string url_spaces_remover(const std::string& unnormalized_string);
    std::string get_BASE_URL_from_city_name(const std::string& city_name);
    std::string get_URL_from_URL_PARTS(const std::string& base_url, const std::vector<std::string>& URL_PARTS);
    void main_attributes_filler(const nlohmann::json& json_data);
    void air_quality_attributes_filler(const nlohmann::json& json_data);
    nlohmann::json json_getter(const std::string& API_URL);
};


#endif //WEATHER_APP_API_JSON_DECOMPOSER_H