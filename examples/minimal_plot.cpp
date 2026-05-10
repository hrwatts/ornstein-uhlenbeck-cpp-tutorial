#include <vector>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

#ifndef PYTHON3_EXECUTABLE_PATH
#define PYTHON3_EXECUTABLE_PATH ""
#endif

std::string read_environment_variable(const char* name) {
#ifdef _WIN32
    char* value = nullptr;
    std::size_t size = 0;
    if (_dupenv_s(&value, &size, name) != 0 || value == nullptr) {
        return {};
    }

    std::string result(value);
    std::free(value);
    return result;
#else
    const char* value = std::getenv(name);
    if (value == nullptr) {
        return {};
    }

    return value;
#endif
}

void configure_embedded_python_environment() {
#ifdef _WIN32
    const std::string python_home = read_environment_variable("PYTHONHOME");
    const std::string python_path = read_environment_variable("PYTHONPATH");
    const std::string configured_executable = PYTHON3_EXECUTABLE_PATH;

    if (configured_executable.empty()) {
        return;
    }

    const std::filesystem::path python_root =
        std::filesystem::path(configured_executable).parent_path();
    const std::string python_root_string = python_root.string();

    if (python_home.empty()) {
        _putenv_s("PYTHONHOME", python_root_string.c_str());
    }

    if (python_path.empty()) {
        const std::string lib_path = (python_root / "Lib").string();
        const std::string dlls_path = (python_root / "DLLs").string();
        _putenv_s("PYTHONPATH", (lib_path + ";" + dlls_path).c_str());
    }
#endif
}

int main(int argc, char** argv) {
    configure_embedded_python_environment();

    bool no_show = false;
    std::string save_path;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--no-show") {
            no_show = true;
            continue;
        }
        if (arg == "--save") {
            if (i + 1 >= argc) {
                std::cerr << "Missing value for --save" << std::endl;
                return 1;
            }
            save_path = argv[++i];
            continue;
        }

        std::cerr << "Unknown argument: " << arg << std::endl;
        std::cerr << "Usage: minimal_plot [--save <path>] [--no-show]" << std::endl;
        return 1;
    }

    const std::vector<double> values = {1.0, 3.0, 2.0, 4.0};
    plt::plot(values);
    plt::title("Minimal matplotlib-cpp plot");

    if (!save_path.empty()) {
        plt::save(save_path);
    }

    if (!no_show) {
        plt::show();
    }

    return 0;
}
