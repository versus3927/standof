#include "imgui.h"
#include "offsets.h"
struct CheatConfig {
    bool esp_enabled = false;
} config;
void render_femboy_menu() {
    ImGui::Begin("Femboy-Strike");
    ImGui::Checkbox("ESP", &config.esp_enabled);
    ImGui::End();
}
