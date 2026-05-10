#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <random>
#include <string>
#include <vector>

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

struct SimulationConfig {
    int path_count = 100;
    int step_count = 1000;
    double t_start = 0.0;
    double t_end = 10.0;
    double y0 = 0.0;
    double theta = 0.5;
    double mu = 0.0;
    double sigma = 0.05;
};

double brownian_increment(double dt, std::mt19937& generator) {
    std::normal_distribution<double> distribution(0.0, std::sqrt(dt));
    return distribution(generator);
}

double drift(double value, const SimulationConfig& config) {
    return config.theta * (config.mu - value);
}

std::vector<double> build_time_grid(const SimulationConfig& config, double dt) {
    std::vector<double> time_grid(config.step_count);
    for (int i = 0; i < config.step_count; ++i) {
        time_grid[i] = config.t_start + i * dt;
    }
    return time_grid;
}

std::vector<double> simulate_path(
    const SimulationConfig& config,
    double dt,
    std::mt19937& generator
) {
    std::vector<double> values(config.step_count);
    values[0] = config.y0;

    for (int i = 1; i < config.step_count; ++i) {
        const double previous = values[i - 1];
        values[i] = previous
            + drift(previous, config) * dt
            + config.sigma * brownian_increment(dt, generator);
    }

    return values;
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
        std::cerr << "Usage: ou_tutorial [--save <path>] [--no-show]" << std::endl;
        return 1;
    }

    const SimulationConfig config{};
    const double dt = (config.t_end - config.t_start) / (config.step_count - 1);
    auto generator = std::mt19937(std::random_device{}());
    const auto time_grid = build_time_grid(config, dt);

    for (int path_index = 0; path_index < config.path_count; ++path_index) {
        const auto values = simulate_path(config, dt, generator);
        plt::plot(time_grid, values);
    }

    plt::title("Ornstein-Uhlenbeck Sample Paths");
    plt::xlabel("time");
    plt::ylabel("Y(t)");

    if (!save_path.empty()) {
        plt::save(save_path);
    }

    if (!no_show) {
        plt::show();
    }

    return 0;
}
