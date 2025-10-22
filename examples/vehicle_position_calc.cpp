/**
 * @file vehicle_position_calc.cpp
 * @brief Vehicle Position Calculator Example
 * 
 * This example demonstrates the calculation of vehicle positions from
 * camera frame coordinates for the adaptive high beam system.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include "led_matrix.h"

using namespace std;

/**
 * @brief Structure to hold test data
 */
struct TestCase {
    int frame_width;
    int x_coordinate;
    string description;
};

/**
 * @brief Calculate and display position for a test case
 */
void process_test_case(const TestCase& test) {
    int position = calculate_vehicle_position(test.x_coordinate, test.frame_width);
    
    cout << "  " << setw(40) << left << test.description 
         << " | Frame: " << setw(4) << test.frame_width
         << " | X: " << setw(4) << test.x_coordinate
         << " -> Position: " << position << endl;
}

/**
 * @brief Visualize the column divisions
 */
void visualize_column_divisions(int frame_width) {
    cout << "\n=== Column Divisions for Frame Width " << frame_width << " ===" << endl;
    cout << "\nPixel ranges for each position:" << endl;
    
    float col1 = frame_width * 0.1f - 20;
    float col2 = frame_width * 0.2f;
    float col3 = frame_width * 0.3f;
    float col4 = frame_width * 0.4f;
    float col5 = frame_width * 0.5f;
    float col6 = frame_width * 0.6f;
    float col7 = frame_width * 0.7f;
    float col8 = frame_width * 0.8f;
    float col9 = frame_width * 0.9f;
    
    cout << "  Position 0: 0 to " << (int)col1 << " pixels" << endl;
    cout << "  Position 1: " << (int)col1 << " to " << (int)col2 << " pixels" << endl;
    cout << "  Position 2: " << (int)col2 << " to " << (int)col3 << " pixels" << endl;
    cout << "  Position 3: " << (int)col3 << " to " << (int)col4 << " pixels" << endl;
    cout << "  Position 4: " << (int)col4 << " to " << (int)col5 << " pixels" << endl;
    cout << "  Position 5: " << (int)col5 << " to " << (int)col6 << " pixels" << endl;
    cout << "  Position 6: " << (int)col6 << " to " << (int)col7 << " pixels" << endl;
    cout << "  Position 7: " << (int)col7 << " to " << (int)col8 << " pixels" << endl;
    cout << "  Position 8: " << (int)col8 << " to " << (int)col9 << " pixels" << endl;
    cout << "  Position 9: " << (int)col9 << " to " << frame_width << " pixels" << endl;
}

/**
 * @brief Main function
 */
int main() {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║      Vehicle Position Calculator - Test Suite             ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    // Standard test cases for different frame sizes
    vector<TestCase> test_cases = {
        // 640x480 resolution tests
        {640, 20, "640p - Far left edge"},
        {640, 80, "640p - Left region"},
        {640, 150, "640p - Left-center"},
        {640, 250, "640p - Center-left"},
        {640, 320, "640p - Dead center"},
        {640, 400, "640p - Center-right"},
        {640, 480, "640p - Right-center"},
        {640, 550, "640p - Right region"},
        {640, 620, "640p - Far right edge"},
        
        // 1280x720 resolution tests
        {1280, 50, "720p - Far left edge"},
        {1280, 200, "720p - Left region"},
        {1280, 400, "720p - Left-center"},
        {1280, 640, "720p - Dead center"},
        {1280, 900, "720p - Right-center"},
        {1280, 1100, "720p - Right region"},
        {1280, 1250, "720p - Far right edge"},
        
        // 1920x1080 resolution tests
        {1920, 100, "1080p - Far left edge"},
        {1920, 400, "1080p - Left region"},
        {1920, 800, "1080p - Left-center"},
        {1920, 960, "1080p - Dead center"},
        {1920, 1200, "1080p - Center-right"},
        {1920, 1600, "1080p - Right region"},
        {1920, 1850, "1080p - Far right edge"},
    };
    
    cout << "\n=== Processing Test Cases ===" << endl;
    cout << "\nTest Description                          | Frame | X    -> Position" << endl;
    cout << string(75, '-') << endl;
    
    for (const auto& test : test_cases) {
        process_test_case(test);
    }
    
    // Visualize divisions for common resolutions
    visualize_column_divisions(640);
    visualize_column_divisions(1280);
    visualize_column_divisions(1920);
    
    // Interactive mode
    cout << "\n=== Interactive Mode ===" << endl;
    cout << "Enter frame width and X coordinate (or 0 0 to exit):" << endl;
    
    int frame_width, x_coord;
    while (true) {
        cout << "\nFrame width X-coord: ";
        if (!(cin >> frame_width >> x_coord)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter two numbers." << endl;
            continue;
        }
        
        if (frame_width == 0 && x_coord == 0) {
            break;
        }
        
        if (frame_width <= 0) {
            cout << "Frame width must be positive!" << endl;
            continue;
        }
        
        if (x_coord < 0 || x_coord > frame_width) {
            cout << "X coordinate out of range!" << endl;
            continue;
        }
        
        int position = calculate_vehicle_position(x_coord, frame_width);
        cout << "  Vehicle at X=" << x_coord << " in " << frame_width 
             << "px frame -> Position " << position << endl;
        
        // Show which columns would be affected
        cout << "  LED columns affected: ";
        switch (position) {
            case 0: cout << "All ON (no vehicle in detection zone)" << endl; break;
            case 1: cout << "Columns 0-1 OFF" << endl; break;
            case 2: cout << "Columns 0-2 OFF" << endl; break;
            case 3: cout << "Columns 2-4 OFF" << endl; break;
            case 4: cout << "Columns 3-4 OFF" << endl; break;
            case 5: cout << "Columns 4-5 OFF" << endl; break;
            case 6: cout << "Columns 5-7 OFF" << endl; break;
            case 7: cout << "Columns 6-7 OFF" << endl; break;
            case 8: cout << "Column 7 OFF" << endl; break;
            case 9: cout << "All OFF (safety mode)" << endl; break;
            default: cout << "Unknown position" << endl; break;
        }
    }
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║            Vehicle Position Calculator - Complete         ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;
    
    return 0;
}
