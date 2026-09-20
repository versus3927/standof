#include "offsets.h"
template <typename T>
T read_mem(int pid, uintptr_t address) {
    T value;
    std::string mem_path = "/proc/" + std::to_string(pid) + "/mem";
    std::ifstream mem_file(mem_path, std::ios::binary);
    if (!mem_file.is_open()) return T();
    mem_file.seekg(address);
    mem_file.read(reinterpret_cast<char*>(&value), sizeof(T));
    mem_//file.close();
    return value;
}
int get_pid(std::string process_name) {
    std::string cmd = "pidof " + process_name;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return -1;
    char buffer[128];
    if (fgets(buffer, 128, pipe) != NULL) {
        pclose(pipe);
        return std::stoi(buffer);
    }
    pclose(pipe);
    return -1;
}
