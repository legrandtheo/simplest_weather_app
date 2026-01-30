#include "ImGui_utilities.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"


//ALL OF THEM CAN BE COMPACTED INTO ONE AND ONLY FUNCTION WITH 5 ARGUMENTS, BUT I'LL LEAVE IT LIKE THIS FOR NOW

ImVec4 ImGui_Utils::GetAQIColor(const size_t &AQI)
{
    if (AQI <= 20) return ImVec4(0.0f, 0.8f, 0.5f, 1.0f);

    if (AQI <= 40) return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

    if (AQI <= 60) return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);

    if (AQI <= 80) return ImVec4(1.0f, 0.5f, 0.0f, 1.0f);

    if (AQI <= 100) return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

    return ImVec4(0.6f, 0.0f, 1.0f, 1.0f);
}
ImVec4 ImGui_Utils::GetPM10color(const float& pm10_amount)
{
    //VERT CLAIR
    if (pm10_amount <= 10) return ImVec4(0.0f, 0.8f, 0.5f, 1.0f);
    //VERT BLEU / CYAN
    if (pm10_amount <= 20) return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    //JAUNE
    if (pm10_amount <= 40) return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    //ORANGE
    if (pm10_amount <= 70) return ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
    //ROUGE
    if (pm10_amount <= 100) return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    //VIOLET
    return ImVec4(0.6f, 0.0f, 1.0f, 1.0f);
}
ImVec4 ImGui_Utils::GetPM2_5Color(const float& pm2_5_amount)
{
    //VERT CLAIR
    if (pm2_5_amount <= 5) return ImVec4(0.0f, 0.8f, 0.5f, 1.0f);
    //VERT BLEU / CYAN
    if (pm2_5_amount <= 10) return ImVec4(0.0f, 0.8f, 0.5f, 1.0f);
    //JAUNE
    if (pm2_5_amount <= 20) return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    //ORANGE
    if (pm2_5_amount <= 35) return ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
    //ROUGE
    if (pm2_5_amount <= 50) return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    //VIOLET
    return ImVec4(0.6f, 0.0f, 1.0f, 1.0f);
}
ImVec4 ImGui_Utils::GetO3Color(const float& O3_amount)
{
    //VERT CLAIR
    if (O3_amount <= 50) return ImVec4(0.0f, 0.8f, 0.5f, 1.0f);
    //VERT BLEU / CYAN
    if (O3_amount <= 100) return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    //JAUNE
    if (O3_amount <= 120) return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    //ORANGE
    if (O3_amount <= 200) return ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
    //ROUGE
    if (O3_amount <= 300) return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    //VIOLET
    return ImVec4(0.6f, 0.0f, 1.0f, 1.0f);
}
ImVec4 ImGui_Utils::GetNO2Color(const float& NO2_amount)
{
    //VERT CLAIR
    if (NO2_amount <= 20) return ImVec4(0.0f, 0.8f, 0.5f, 1.0f);
    //VERT BLEU / CYAN
    if (NO2_amount <= 40) return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    //JAUNE
    if (NO2_amount <= 90) return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    //ORANGE
    if (NO2_amount <= 160) return ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
    //ROUGE
    if (NO2_amount <= 240) return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    //VIOLET
    return ImVec4(0.6f, 0.0f, 1.0f, 1.0f);
}
ImVec4 ImGui_Utils::GetSO2Color(const float& SO2_amount)
{
    //VERT CLAIR
    if (SO2_amount <= 60) return ImVec4(0.0f, 0.8f, 0.5f, 1.0f);
    //VERT BLEU / CYAN
    if (SO2_amount <= 100) return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    //JAUNE
    if (SO2_amount <= 200) return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    //ORANGE
    if (SO2_amount <= 350) return ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
    //ROUGE
    if (SO2_amount <= 500) return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    //VIOLET
    return ImVec4(0.6f, 0.0f, 1.0f, 1.0f);
}
ImVec4 ImGui_Utils::GetCOColor(const float& CO_amount)
{
    //VERT CLAIR
    if (CO_amount <= 3000) return ImVec4(0.0f, 0.8f, 0.5f, 1.0f);
    //VERT BLEU / CYAN
    if (CO_amount <= 5000) return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    //JAUNE
    if (CO_amount <= 7500) return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    //ORANGE
    if (CO_amount <= 8750) return ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
    //ROUGE
    if (CO_amount <= 10000) return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    //VIOLET
    return ImVec4(0.6f, 0.0f, 1.0f, 1.0f);
}






