#include "api_json_decomposer.h"

#include <complex>
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


size_t api_json_decomposer::useful_write_function(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t real_size = size * nmemb;

    std::string* stored_data = static_cast<std::string*>(userdata);

    stored_data->append(static_cast<char*>(ptr),real_size);

    return real_size;
}

nlohmann::json api_json_decomposer::json_getter(const std::string &API_URL)
{
    std::string request_buffer;
    nlohmann::json data_json{};

    curl_global_init(CURL_GLOBAL_ALL);
    CURL* api_session = curl_easy_init();

    if (api_session)
    {
        //SETTING UP THE REQUEST AND ITS VARIABLES
        curl_easy_setopt(api_session, CURLOPT_URL, API_URL.c_str());
        curl_easy_setopt(api_session, CURLOPT_WRITEFUNCTION, useful_write_function);
        curl_easy_setopt(api_session, CURLOPT_WRITEDATA, &request_buffer);

        CURLcode result = curl_easy_perform(api_session);

        if (result!= CURLE_OK)
        {
            // ERROR CATCHING
            status = "Data request error";
            fprintf(stderr, "FATAL ERROR", curl_easy_strerror(result));
        }
        else
        {
            try
            {
                //TURNING RECEIVED DATA INTO A JSON FORMAT, FOR EASY ACCESS TO DATA
                data_json = nlohmann::json::parse(request_buffer);
                //std::cout << "JSON REÇU BRUT :" << std::endl;
                //std::cout << data_json.dump(4) << std::endl; // .dump(4) affiche le JSON joliement indenté
                status = "Data Received, next step is parsing it";
            }
            catch (nlohmann::json::parse_error& e)
            {
                //ERROR CATCHING
                status = "Error in parsing the data";
                std::cerr << "Error in JSON data copy" << e.what() << std::endl;
            }
        }
    }
    curl_easy_cleanup(api_session);
    return data_json;
}

void api_json_decomposer::attributes_filler(const nlohmann::json& json_data)
{
    //FIRST FILLING THE TEMPERATURE DATA
    temp_holder_celcius.current_temp = json_data["current"]["temperature_2m"];
    temp_holder_celcius.felt_temp = json_data["current"]["apparent_temperature"];
    temp_holder_celcius.max_today_temp = json_data["daily"]["temperature_2m_max"][0];
    temp_holder_celcius.min_today_temp = json_data["daily"]["temperature_2m_min"][0];

    //SECONDLY WIND DATA
    wind_holder.wind_speed_km_h = json_data["current"]["wind_speed_10m"];
    wind_holder.wind_direction_degrees = json_data["current"]["wind_direction_10m"];
    //THIRD SUNTIME DATA
    suntime.sunrise = json_data["daily"]["sunrise"][0];
    suntime.sunset = json_data["daily"]["sunset"][0];

    //FINALLY THE REST OF THE DATA
    other_data.humidity = json_data["current"]["relative_humidity_2m"];
    other_data.surface_pressure = json_data["current"]["surface_pressure"];
    other_data.UV_index = json_data["daily"]["uv_index_max"][0];

    status = "Data fully parsed";
}

void api_json_decomposer::old_init(const std::string &API_URL)
{
    status = "Initializing the new data";
    attributes_filler(json_getter(API_URL));
}

std::string api_json_decomposer::url_spaces_remover(const std::string &unnormalized_string)
{
    std::string string_final{};
    for (size_t k = 0; k < unnormalized_string.size(); k++)
    {
        if (unnormalized_string[k]== ' ') string_final.append("%20");
        else if (unnormalized_string[k] == '/') string_final.append("%2F");
        else string_final.push_back(unnormalized_string[k]);
    }
    return string_final;
}

std::string api_json_decomposer::get_BASE_URL_from_city_name(const std::string &city_name)
{
    std::string BASE_API_URL{"https://geocoding-api.open-meteo.com/v1/search?name="};
    const std::string normalized_city_name = url_spaces_remover(city_name);
    BASE_API_URL.append(normalized_city_name);

    return BASE_API_URL;
}

std::string api_json_decomposer::get_FINAL_URL_from_BASE_URL(const std::string &base_url)
{
    auto city_name_json = json_getter(base_url);

    std::string finalURL{URL_parts.at(0)};
    finalURL.append(to_string(city_name_json["results"][0]["latitude"]));

    finalURL.append(URL_parts.at(1));
    finalURL.append(to_string(city_name_json["results"][0]["longitude"]));

    finalURL.append(URL_parts.at(2));
    const std::string normalized_timezone = url_spaces_remover(city_name_json["results"][0]["timezone"]);
    finalURL.append(normalized_timezone);

    return finalURL;
}

void api_json_decomposer::refresh_from_city_name(const std::string &city_name)
{
    const std::string baseURL = get_BASE_URL_from_city_name(city_name);

    const std::string finalURL = get_FINAL_URL_from_BASE_URL(baseURL);
    old_init(finalURL);
}
