#include <iostream>
#include <thread>
#include "offsets.h"
#include "memory.cpp"
#include "esp.cpp"
#include "menu.cpp"

// Функция, которая будет работать в отдельном потоке и обновлять ESP
void esp_thread(int pid) {
    while (true) {
        run_esp_cycle(pid);
        // Небольшая пауза, чтобы не перегружать процессор, ня!
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    std::cout << "--- Femboy Strike External Loaded! ---" << std::endl;
    
    std::string game_name = "Standoff2";
    int pid = get_pid(game_name);

    if (pid == -1) {
        std::cout << "Игра не найдена! Запусти её, милашка!" << std::endl;
        while (pid == -1) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            pid = get_pid(game_name);
        }
        std::cout << "Ура! Игра запущена! PID: " << pid << " ✨" << std::endl;
    }

    // Запускаем ESP в отдельном потоке, чтобы меню не зависало
    std::thread t(esp_thread, pid);
    t.detach();

    // Основной цикл программы (здесь работает наше меню)
    while (true) {
        render_femboy_menu();
        // В реальном APK здесь будет цикл обработки кадров ImGui
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
