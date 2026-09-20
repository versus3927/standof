
struct CheatConfig {
    bool esp_enabled = false;
    bool box_esp = false;
    bool name_esp = false;
    bool aimbot_enabled = false;
    float aim_fov = 90.0f;
} config;

void render_femboy_menu() {
    ImGui::Begin("✨ Femboy-Strike External ✨");

    ImGui::Text("Привет, Джек! Выбирай, что будем ломать, ня!");
    ImGui::Separator();

    if (ImGui::CollapsingHeader("Visuals (ESP)")) {
        ImGui::Checkbox("Включить ESP", &config.esp_enabled);
        if (config.esp_enabled) {
            ImGui::Indent();
            ImGui::Checkbox("Рисовать Боксы", &config.box_esp);
            ImGui::Checkbox("Показывать Имена", &config.name_esp);
            ImGui::Unindent();
        }
    }

    if (ImGui::CollapsingHeader("Combat (Aimbot)")) {
        ImGui::Checkbox("Включить Аим", &config.aimbot_enabled);
        if (config.aimbot_enabled) {
            ImGui::Indent();
            ImGui::SliderFloat("FOV", &config.aim_fov, 1.0f, 180.0f);
            ImGui::Unindent();
        }
    }

    ImGui::Separator();
    if (ImGui::Button("Скрыть меню (Insert)", ImVec2(200, 30))) {
        // Логика скрытия
    }

    ImGui::End();
}
