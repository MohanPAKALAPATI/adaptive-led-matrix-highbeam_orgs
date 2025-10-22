/**
 * @file led_pattern_simulator.cpp
 * @brief LED Pattern Simulator Example
 * 
 * This example demonstrates the LED matrix patterns for different vehicle
 * detection scenarios, simulating the adaptive high beam behavior.
 */

#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include "led_matrix.h"

using namespace std;

/**
 * @brief Simulate LED patterns for various scenarios
 */
void simulate_scenario(const string& description, led_matrix_t *matrix) {
    cout << "\n" << string(60, '=') << endl;
    cout << description << endl;
    cout << string(60, '=') << endl;
    led_matrix_print(matrix);
    this_thread::sleep_for(chrono::milliseconds(800));
}

/**
 * @brief Main function demonstrating LED patterns
 */
int main() {
    led_matrix_t matrix;
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║    Adaptive LED Matrix High Beam - Pattern Simulator    ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    // Initialize matrix
    led_matrix_init(&matrix);
    simulate_scenario("Scenario 1: No vehicles detected - Full beam", &matrix);
    
    // Single vehicle scenarios
    led_matrix_update_single_vehicle(&matrix, 1);
    simulate_scenario("Scenario 2: Vehicle at position 1 (far left)", &matrix);
    
    led_matrix_update_single_vehicle(&matrix, 4);
    simulate_scenario("Scenario 3: Vehicle at position 4 (center)", &matrix);
    
    led_matrix_update_single_vehicle(&matrix, 7);
    simulate_scenario("Scenario 4: Vehicle at position 7 (right)", &matrix);
    
    // Dual vehicle scenarios
    led_matrix_update_dual_vehicle(&matrix, 1, 6);
    simulate_scenario("Scenario 5: Two vehicles at positions 1 and 6", &matrix);
    
    led_matrix_update_dual_vehicle(&matrix, 2, 5);
    simulate_scenario("Scenario 6: Two vehicles at positions 2 and 5", &matrix);
    
    // Multiple vehicles scenario
    led_matrix_update_single_vehicle(&matrix, 9);
    simulate_scenario("Scenario 7: More than 2 vehicles - Safety mode (all off)", &matrix);
    
    // Frame coordinate example
    cout << "\n" << string(60, '=') << endl;
    cout << "Frame Coordinate to Position Mapping Example" << endl;
    cout << string(60, '=') << endl;
    
    int frame_width = 640;
    cout << "\nFrame width: " << frame_width << " pixels" << endl;
    cout << "\nCoordinate -> Position mappings:" << endl;
    
    int test_coords[] = {50, 150, 250, 350, 450, 550};
    for (int coord : test_coords) {
        int pos = calculate_vehicle_position(coord, frame_width);
        cout << "  X=" << coord << " -> Position " << pos << endl;
    }
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              Simulation completed successfully             ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;
    
    return 0;
}
