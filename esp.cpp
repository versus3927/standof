

void run_esp_cycle(int pid) {
    // 1. Вход в Player Manager
    uintptr_t player_manager = read_mem<uintptr_t>(pid, offsets::base::player_manager());
    if (!player_manager) return;

    // 2. Цепочка указателей до списка
    uintptr_t ptr1 = read_mem<uintptr_t>(pid, player_manager + offsets::manager::ptr1());
    uintptr_t ptr2 = read_mem<uintptr_t>(pid, ptr1 + offsets::manager::ptr2());
    uintptr_t ptr3 = read_mem<uintptr_t>(pid, ptr2 + offsets::manager::ptr3());

    // 3. Список и размер
    uintptr_t entity_list = read_mem<uintptr_t>(pid, ptr3 + offsets::manager::list());
    int players_count = read_mem<int>(pid, ptr3 + offsets::manager::list_size());

    // 4. Цикл по врагам
    for (int i = 0; i < players_count; i++) {
        uintptr_t buffer = read_mem<uintptr_t>(pid, entity_list + offsets::list::buffer());
        uintptr_t player_entry = read_mem<uintptr_t>(pid, buffer + (i * offsets::list::stride()) + offsets::list::entry());

        if (!player_entry) continue;

        // Проверка команды
        int team = read_mem<int>(pid, player_entry + offsets::player::team());
        uintptr_t local_ptr = read_mem<uintptr_t>(pid, ptr3 + offsets::manager::local());
        int local_team = read_mem<int>(pid, local_ptr + offsets::player::team());

        if (team == local_team) continue;

        // Координаты
        uintptr_t transform_data = read_mem<uintptr_t>(pid, player_entry + offsets::player::transform_data());
        float posX = read_mem<float>(pid, transform_data + offsets::transform::position());
        float posY = read_mem<float>(pid, transform_data + offsets::transform::position() + 4);
        float posZ = read_mem<float>(pid, transform_data + offsets::transform::position() + 8);

        std::cout << "Враг обнаружен! Позиция: " << posX << ", " << posY << ", " << posZ << " ✨" << std::endl;
    }
}
