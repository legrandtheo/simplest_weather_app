#ifndef WEATHER_APP_IMGUI_UTILITIES_H
#define WEATHER_APP_IMGUI_UTILITIES_H
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"


namespace ImGui_Utils {
    ImVec4 GetAQIColor(const size_t& AQI);
    ImVec4 GetPM10color(const float& pm10_amount);
    ImVec4 GetPM2_5Color(const float& pm2_5_amount);
    ImVec4 GetO3Color(const float& O3_amount);
    ImVec4 GetNO2Color(const float& NO2_amount);
    ImVec4 GetSO2Color(const float& SO2_amount);
    ImVec4 GetCOColor(const float& CO_amount);

};
#endif //WEATHER_APP_IMGUI_UTILITIES_H