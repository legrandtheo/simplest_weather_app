#define NOMINMAX
#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

#include "classes/api_json_decomposer.h"
#include "classes/ImGui_utilities.h"
#include "classes/weather_utilities.h"


using namespace std;

const string API_URL = "https://api.open-meteo.com/v1/forecast?latitude=48.85341&longitude=2.3488&daily=temperature_2m_max,temperature_2m_min,sunrise,sunset,uv_index_max&current=temperature_2m,apparent_temperature,wind_direction_10m,wind_speed_10m,relative_humidity_2m,surface_pressure&timezone=Europe%2FParis";
const string AQ_URL = "https://air-quality-api.open-meteo.com/v1/air-quality?latitude=48.8534&longitude=2.3488&current=european_aqi,pm10,pm2_5,carbon_monoxide,nitrogen_dioxide,sulphur_dioxide,ozone&timezone=Europe%2FBerlin";

void console_printer()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif


    api_json_decomposer data_retriever;
    data_retriever.dual_init(API_URL, AQ_URL);

    cout << "CURRENT TEMPERATURE : " << data_retriever.temp_holder_celcius.current_temp << "    |    "<< "FELT TEMPERATURE : " << data_retriever.temp_holder_celcius.felt_temp << endl;
    cout << "MAX TEMPERATURE TODAY : " << data_retriever.temp_holder_celcius.max_today_temp << "    |    "<< "MIN TEMPERATURE TODAY : " << data_retriever.temp_holder_celcius.min_today_temp << endl;
    cout << "WIND SPEED : " << data_retriever.wind_holder.wind_speed_km_h << "km/h" << "    |    "<< "WIND DIRECTION : " << data_retriever.wind_holder.wind_direction_degrees << weather_utilities::wind_azimuth_to_directions(data_retriever.wind_holder.wind_direction_degrees) << endl;
    cout << "CURRENT HUMIDITY : " << data_retriever.other_data.humidity << "    |    "<< "CURRENT PRESSURE : " << data_retriever.other_data.surface_pressure << endl;
    cout << "SUNRISE TIME : " << weather_utilities::get_time_from_fulldate_iso(data_retriever.suntime.sunrise) << "    |    "<< "SUNSET TIME : " << weather_utilities::get_time_from_fulldate_iso(data_retriever.suntime.sunset) << endl;
    cout << "MAX UV INDEX TODAY : " << data_retriever.other_data.UV_index << endl;
}

int main()
{

    if (!glfwInit()) return 1;

    GLFWwindow *window = glfwCreateWindow(460,480, "Simplest weather app", nullptr, nullptr);
    if (window == nullptr) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    api_json_decomposer data_retriever;
    char cityName[64] = "Paris";

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Weather Dashboard", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

        ImGui::TextDisabled("MAIN DASHBOARD");
        ImGui::Spacing();

        ImGui::Text("Enter your city name :");
        ImGui::InputText("##City",cityName, IM_ARRAYSIZE(cityName));
        ImGui::Separator();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - 180)*0.5f);
        if (ImGui::Button("Refresh weather", ImVec2(180,60)))
        {
            data_retriever.refresh_from_city_name(cityName);
        }
        ImGui::Spacing();
        ImGui::Text("Status : %s", data_retriever.status.c_str());

        if (ImGui::BeginTable("MainITable", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable))
        {
            //FIRST COLUMN
            ImGui::TableNextColumn();
            ImGui::Spacing();
            ImGui::Separator();

            if (data_retriever.status != "No data yet")
            {
                ImGui::Text("Temperature : %.1f C", data_retriever.temp_holder_celcius.current_temp);
                ImGui::Text("Max temp today : %.1f C", data_retriever.temp_holder_celcius.max_today_temp);
                ImGui::Text("Wind speed : %.1f km/h", data_retriever.wind_holder.wind_speed_km_h);
                ImGui::Text("Current humidity : %zu %%", data_retriever.other_data.humidity);
                ImGui::Text("Sunrise time : %s", weather_utilities::get_time_from_fulldate_iso(data_retriever.suntime.sunrise).c_str());
                ImGui::Text("UV index : %.1f U", data_retriever.other_data.UV_index);
            }
            //SECOND COLUMN
            ImGui::TableNextColumn();
            ImGui::Spacing();
            ImGui::Separator();

            if (data_retriever.status != "No data yet")
            {
                ImGui::Text("Felt temperature : %.1f C", data_retriever.temp_holder_celcius.felt_temp);
                ImGui::Text("Min temp today : %.1f C", data_retriever.temp_holder_celcius.min_today_temp);
                ImGui::Text("Wind direction : %zu %s", data_retriever.wind_holder.wind_direction_degrees, weather_utilities::wind_azimuth_to_directions(data_retriever.wind_holder.wind_direction_degrees).c_str());
                ImGui::Text("Current pressure : %.1f hPa", data_retriever.other_data.surface_pressure);
                ImGui::Text("Sunset time : %s", weather_utilities::get_time_from_fulldate_iso(data_retriever.suntime.sunset).c_str());
            }
            ImGui::EndTable();
        }
        if (ImGui::BeginTable("AirQTable", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable))
        {
            //FIRST COLUMN
            ImGui::TableNextColumn();
            ImGui::Spacing();
            ImGui::Separator();

            if (data_retriever.status != "No data yet")
            {
                ImGui::TextColored(ImGui_Utils::GetAQIColor(data_retriever.AQ_data.EU_AQI),"EU air quality index : %zu U", data_retriever.AQ_data.EU_AQI);
                ImGui::TextColored(ImGui_Utils::GetPM10color(data_retriever.AQ_data.pm10),"Coarse particles : %.1f µg/m³", data_retriever.AQ_data.pm10);
                ImGui::TextColored(ImGui_Utils::GetO3Color(data_retriever.AQ_data.O3),"O3 particles : %.1f µg/m³", data_retriever.AQ_data.O3);
                ImGui::TextColored(ImGui_Utils::GetSO2Color(data_retriever.AQ_data.SO2),"SO2 particles : %.1f µg/m³", data_retriever.AQ_data.SO2);

            }
            //SECOND COLUMN
            ImGui::TableNextColumn();
            ImGui::Spacing();
            ImGui::Separator();

            if (data_retriever.status != "No data yet")
            {
                ImGui::Text("");
                ImGui::TextColored(ImGui_Utils::GetPM2_5Color(data_retriever.AQ_data.pm2_5),"Fine particles : %.1f µg/m³", data_retriever.AQ_data.pm2_5);
                ImGui::TextColored(ImGui_Utils::GetNO2Color(data_retriever.AQ_data.NO2),"NO2 particles : %.1f µg/m³", data_retriever.AQ_data.NO2);
                ImGui::TextColored(ImGui_Utils::GetCOColor(data_retriever.AQ_data.CO),"CO particles : %.1f µg/m³", data_retriever.AQ_data.CO);
            }
            ImGui::EndTable();
        }

        if (!data_retriever.temp_holder_celcius.dates_week_temps.empty())
        {
            ImGui::Separator();
            ImGui::Text("Daily temperature data for the next week");

            const float global_weekly_mintemp = *ranges::min_element(data_retriever.temp_holder_celcius.min_week_temps);
            const float global_weekly_maxtemp = *ranges::max_element(data_retriever.temp_holder_celcius.max_week_temps);
            const float global_diff = (global_weekly_maxtemp - global_weekly_mintemp)*0.3f;

            const float min_scale = global_weekly_mintemp - global_diff;
            const float max_scale =  global_weekly_maxtemp + global_diff;

            float posY_start = ImGui::GetCursorPosY();

            ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(1,0,0,1));
            ImGui::PlotLines("##MeteoGraphMax", data_retriever.temp_holder_celcius.max_week_temps.data(), data_retriever.temp_holder_celcius.max_week_temps.size(), 0, nullptr, min_scale, max_scale, ImVec2(445,100));
            ImGui::PopStyleColor();

            ImGui::SetCursorPosY(posY_start);

            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0,0,0,0));
            ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0,0.5f,1,1));
            ImGui::PlotLines("##MeteoGraphMin", data_retriever.temp_holder_celcius.min_week_temps.data(), data_retriever.temp_holder_celcius.min_week_temps.size(), 0, nullptr, min_scale, max_scale, ImVec2(445,100));
            ImGui::PopStyleColor(2);

            if (ImGui::IsItemHovered())
            {

                const float mouseX = ImGui::GetMousePos().x - ImGui::GetItemRectMin().x;
                const float graphwidth = ImGui::GetItemRectSize().x;

                if (const int index = static_cast<int>(data_retriever.temp_holder_celcius.max_week_temps.size() * mouseX / graphwidth); index >= 0 && index < data_retriever.temp_holder_celcius.max_week_temps.size())
                {
                    ImGui::BeginTooltip();
                    ImGui::Text("Date : %s", data_retriever.temp_holder_celcius.dates_week_temps[index].c_str());
                    ImGui::Separator();
                    ImGui::TextColored(ImVec4(1,0.3f,0.3f,1), "Temperature max : %.1f C", data_retriever.temp_holder_celcius.max_week_temps[index]);
                    ImGui::TextColored(ImVec4(0.3f,0.6f,0,1), "Temperature min : %.1f C", data_retriever.temp_holder_celcius.min_week_temps[index]);
                    ImGui::EndTooltip();
                }
            }
        }

    ImGui::End();

    ImGui::Render();
    int display_w,display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f,0.55f,0.60f,1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}


