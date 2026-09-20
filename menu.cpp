#include "imgui.h"
#include "offsets.h"

struct CheatConfig {
    bool esp_enabled = false;
} config;

void render_femboy_menu() {
    ImGui::Begin("✨ Femboy-Strike ✨");
    ImGui::Checkbox("ESP", &config.esp_enabled);
    ImGui::End();
}

5. Обновляем  main.cpp :

#include "offsets.h"
#include <thread>
#include <chrono>

void esp_thread(int pid) {
    while (true) {
        run_esp_cycle(pid);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    int pid = get_pid("Standoff2");
    if (pid != -1) {
        std::thread t(esp_thread, pid);
        t.detach();
    }
    while (true) {
        render_femboy_menu();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    return 0;
}
