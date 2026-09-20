#ifndef OFFSETS_H
#define OFFSETS_H
#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>

namespace offsets {
    namespace base {
        inline uint64_t player_manager() { return 180740496; }
    }
    namespace manager {
        inline int ptr1() { return 0x90; }
        inline int ptr2() { return 0x10; }
        inline int ptr3() { return 0x0; }
        inline int local() { return 0x70; }
        inline int list() { return 0x28; }
        inline int list_size() { return 0x20; }
    }
    namespace list {
        inline int buffer() { return 0x18; }
        inline int entry() { return 0x30; }
        inline int stride() { return 0x18; }
    }
    namespace player {
        inline int team() { return 0x79; }
        inline int transform_data() { return 0xB0; }
    }
    namespace transform {
        inline int position() { return 0x44; }
    }
    namespace camera {
        inline int matrix() { return 0xF0; }
    }
}
template <typename T> T read_mem(int pid, uintptr_t address);
int get_pid(std::string process_name);
void run_esp_cycle(int pid);
void render_femboy_menu();
#endif
