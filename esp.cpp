#include "offsets.h"
#include <iostream>

void run_esp_cycle(int pid) {
    // 1. Получаем Player Manager
    uintptr_t player_manager = read_uintptr(pid, offsets::base::player_manager());
    if (!player_manager) return;

    // 2. Цепочка указателей до списка сущностей
    uintptr_t ptr1 = read_uintptr(pid, player_manager + offsets::manager::ptr1());
    uintptr_t ptr2 = read_uintptr(pid, ptr1 + offsets::manager::ptr2());
    uintptr_t ptr3 = read_uintptr(pid, ptr2 + offsets::manager::ptr3());

    // 3. Получаем список и количество игроков
    uintptr_t entity_list = read_uintptr(pid, ptr3 + offsets::manager::list());
    int players_count = read_int(pid, ptr3 + offsets::manager::list_size());

    if (players_count <= 0) return;

    // 4. Цикл по всем игрокам
    for (int i = 0; i < players_count; i++) {
        uintptr_t buffer = read_uintptr(pid, entity_list + offsets::list::buffer());
        uintptr_t player_entry = read_uintptr(pid, buffer + (i * offsets::list::stride()) + offsets::list::entry());

        if (!player_entry) continue;

        // Проверка команды: не подсвечиваем своих, милашка!
        int team = read_int(pid, player_entry + offsets::player::team());
        uintptr_t local_ptr = read_uintptr(pid, ptr3 + offsets::manager::local());
        int local_team = read_int(pid, local_ptr + offsets::player::team());

        if (team == local_team) continue;

        // Достаем координаты X, Y, Z
        uintptr_t transform_data = read_uintptr(pid, player_entry + offsets::player::transform_data());
        float posX = read_float(pid, transform_data + offsets::transform::position());
        float posY = read_float(pid, transform_data + offsets::transform::position() + 4);
        float posZ = read_float(pid, transform_data + offsets::transform::position() + 8);

        // Вывод в консоль (в реальном APK это будет отрисовка бокса на экране)
        std::cout << "Enemy Found! Pos: " << posX << ", " << posY << ", " << posZ << " ✨" << std::endl;
    }
}
