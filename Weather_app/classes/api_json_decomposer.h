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

const std::vector<std::string> URL_parts{"https://api.open-meteo.com/v1/forecast?latitude=", "&longitude=", "&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset,uv_index_max&current=temperature_2m,apparent_temperature,wind_direction_10m,wind_speed_10m,relative_humidity_2m,surface_pressure&timezone="};

class api_json_decomposer
{
public:
    void old_init(const std::string& API_URL);
    void refresh_from_city_name(const std::string& city_name);
    temperature_holder_celcius temp_holder_celcius{};
    wind_holder wind_holder{};
    suntime suntime{};
    mixed_other_data other_data{};
    std::string status{"No data yet"};
private:
    size_t static useful_write_function(void *ptr, size_t size, size_t nmemb, void *userdata);

    static std::string url_spaces_remover(const std::string& unnormalized_string);
    std::string get_BASE_URL_from_city_name(const std::string& city_name);
    std::string get_FINAL_URL_from_BASE_URL(const std::string& base_url);
    void attributes_filler(const nlohmann::json& json_data);
    nlohmann::json json_getter(const std::string& API_URL);
};


#endif //WEATHER_APP_API_JSON_DECOMPOSER_H