cmake_minimum_required(VERSION 3.10)

# Shared LED matrix implementation
set(LED_MATRIX_SRC led_matrix_impl.cpp)

# Example: LED Pattern Simulator
add_executable(led_pattern_simulator
    led_pattern_simulator.cpp
    ${LED_MATRIX_SRC}
)

target_include_directories(led_pattern_simulator
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

# Example: Vehicle Position Calculator
add_executable(vehicle_position_calc
    vehicle_position_calc.cpp
    ${LED_MATRIX_SRC}
)

target_include_directories(vehicle_position_calc
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

# Example: Serial Communication Test
add_executable(serial_comm_test
    serial_comm_test.cpp
    ${LED_MATRIX_SRC}
)

target_include_directories(serial_comm_test
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

# Installation
install(TARGETS 
    led_pattern_simulator
    vehicle_position_calc
    serial_comm_test
    RUNTIME DESTINATION bin
)
