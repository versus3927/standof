#include "offsets.h"

uintptr_t read_uintptr(int pid, uintptr_t addr) {
    uintptr_t val = 0;
    std::ifstream f("/proc/" + std::to_string(pid) + "/mem", std::ios::binary);
    if (f) { f.seekg(addr); f.read((char*)&val, sizeof(val)); }
    return val;
}

int read_int(int pid, uintptr_t addr) {
    int val = 0;
    std::ifstream f("/proc/" + std::to_string(pid) + "/mem", std::ios::binary);
    if (f) { f.seekg(addr); f.read((char*)&val, sizeof(val)); }
    return val;
}

float read_float(int pid, uintptr_t addr) {
    float val = 0;
    std::ifstream f("/proc/" + std::to_string(pid) + "/mem", std::ios::binary);
    if (f) { f.seekg(addr); f.read((char*)&val, sizeof(val)); }
    return val;
}

int get_pid(std::string name) {
    std::string cmd = "pidof " + name;
    FILE* p = popen(cmd.c_str(), "r");
    if (!p) return -1;
    char b[128];
    int pid = -1;
    if (fgets(b, 128, p)) pid = std::stoi(b);
    pclose(p);
    return pid;
}
