/**
 * @file serial_comm_test.cpp
 * @brief Serial Communication Protocol Test
 * 
 * This example demonstrates the serial communication protocol used between
 * the vehicle detection system and the LED controller.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "led_matrix.h"

using namespace std;

/**
 * @brief Structure to represent a serial command
 */
struct SerialCommand {
    char byte1;
    char byte2;
    char byte3;
    string description;
};

/**
 * @brief Generate serial command for single vehicle
 */
SerialCommand generate_single_vehicle_command(int position) {
    SerialCommand cmd;
    cmd.byte1 = 'x';
    cmd.byte2 = 'y';
    cmd.byte3 = '0' + position;
    
    stringstream desc;
    desc << "Single vehicle at position " << position;
    cmd.description = desc.str();
    
    return cmd;
}

/**
 * @brief Generate serial command for dual vehicles
 */
SerialCommand generate_dual_vehicle_command(int pos1, int pos2) {
    SerialCommand cmd;
    cmd.byte1 = 'x';
    cmd.byte2 = '0' + pos1;
    cmd.byte3 = '0' + pos2;
    
    stringstream desc;
    desc << "Two vehicles at positions " << pos1 << " and " << pos2;
    cmd.description = desc.str();
    
    return cmd;
}

/**
 * @brief Display command in various formats
 */
void display_command(const SerialCommand& cmd) {
    cout << "\n  Command: " << cmd.description << endl;
    cout << "    ASCII:  [" << cmd.byte1 << "][" << cmd.byte2 << "][" << cmd.byte3 << "]" << endl;
    cout << "    Hex:    [0x" << hex << setw(2) << setfill('0') << (int)(unsigned char)cmd.byte1 
         << "][0x" << setw(2) << setfill('0') << (int)(unsigned char)cmd.byte2
         << "][0x" << setw(2) << setfill('0') << (int)(unsigned char)cmd.byte3 << "]" << dec << endl;
    cout << "    Decimal: [" << (int)cmd.byte1 << "][" << (int)cmd.byte2 << "][" << (int)cmd.byte3 << "]" << endl;
}

/**
 * @brief Decode and interpret a serial command
 */
void decode_command(const SerialCommand& cmd) {
    cout << "\n  Decoding Command: [" << cmd.byte1 << "][" << cmd.byte2 << "][" << cmd.byte3 << "]" << endl;
    
    if (cmd.byte1 != 'x') {
        cout << "    ERROR: Invalid command format (byte1 must be 'x')" << endl;
        return;
    }
    
    if (cmd.byte2 == 'y') {
        // Single vehicle detection
        int position = cmd.byte3 - '0';
        if (position >= 0 && position <= 9) {
            cout << "    Type: Single Vehicle Detection" << endl;
            cout << "    Position: " << position << endl;
            
            if (position == 0) {
                cout << "    Action: All columns ON (no vehicle or position 0)" << endl;
            } else if (position == 9) {
                cout << "    Action: All columns OFF (>2 vehicles detected)" << endl;
            } else {
                cout << "    Action: Turn OFF columns around position " << position << endl;
            }
        } else {
            cout << "    ERROR: Invalid position value" << endl;
        }
    } else {
        // Dual vehicle detection
        int pos1 = cmd.byte2 - '0';
        int pos2 = cmd.byte3 - '0';
        
        if (pos1 >= 0 && pos1 <= 8 && pos2 >= 0 && pos2 <= 8) {
            cout << "    Type: Dual Vehicle Detection" << endl;
            cout << "    Position 1: " << pos1 << endl;
            cout << "    Position 2: " << pos2 << endl;
            cout << "    Action: Turn OFF columns around both positions" << endl;
        } else {
            cout << "    ERROR: Invalid position values" << endl;
        }
    }
}

/**
 * @brief Protocol specification display
 */
void display_protocol_spec() {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║          Serial Communication Protocol Specification       ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\nProtocol Overview:" << endl;
    cout << "  - Baud Rate: 9600" << endl;
    cout << "  - Data Format: 8N1 (8 data bits, no parity, 1 stop bit)" << endl;
    cout << "  - Command Length: 3 bytes" << endl;
    
    cout << "\nCommand Structure:" << endl;
    cout << "  Byte 1: Always 'x' (0x78) - Command identifier" << endl;
    cout << "  Byte 2: Position indicator or 'y' for single vehicle" << endl;
    cout << "  Byte 3: Position value (0-9)" << endl;
    
    cout << "\nSingle Vehicle Format:" << endl;
    cout << "  [x][y][P] where P = position (0-9)" << endl;
    cout << "    Position 0: No vehicle in detection zone" << endl;
    cout << "    Position 1-8: Vehicle detected at specific column zone" << endl;
    cout << "    Position 9: Multiple vehicles (>2), safety mode" << endl;
    
    cout << "\nDual Vehicle Format:" << endl;
    cout << "  [x][P1][P2] where P1, P2 = positions (0-8)" << endl;
    cout << "    Example: [x][1][6] = vehicles at positions 1 and 6" << endl;
    
    cout << "\nLED Matrix Response:" << endl;
    cout << "  - 8 columns (0-7), 4 rows" << endl;
    cout << "  - Columns near detected vehicles are turned OFF" << endl;
    cout << "  - Remaining columns stay ON for maximum visibility" << endl;
}

/**
 * @brief Main function
 */
int main() {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║       Serial Communication Protocol - Test Suite          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    display_protocol_spec();
    
    cout << "\n\n" << string(60, '=') << endl;
    cout << "Single Vehicle Command Examples" << endl;
    cout << string(60, '=') << endl;
    
    for (int i = 0; i <= 9; i++) {
        SerialCommand cmd = generate_single_vehicle_command(i);
        display_command(cmd);
        decode_command(cmd);
    }
    
    cout << "\n\n" << string(60, '=') << endl;
    cout << "Dual Vehicle Command Examples" << endl;
    cout << string(60, '=') << endl;
    
    int dual_tests[][2] = {
        {0, 1}, {0, 8}, {1, 6}, {2, 5}, {3, 7}, {4, 6}
    };
    
    for (auto& test : dual_tests) {
        SerialCommand cmd = generate_dual_vehicle_command(test[0], test[1]);
        display_command(cmd);
        decode_command(cmd);
    }
    
    // Interactive mode
    cout << "\n\n" << string(60, '=') << endl;
    cout << "Interactive Command Decoder" << endl;
    cout << string(60, '=') << endl;
    cout << "\nEnter three characters (e.g., 'xy5' or 'x13'), or 'quit' to exit:" << endl;
    
    string input;
    while (true) {
        cout << "\nCommand: ";
        cin >> input;
        
        if (input == "quit" || input == "exit" || input == "q") {
            break;
        }
        
        if (input.length() != 3) {
            cout << "Error: Command must be exactly 3 characters!" << endl;
            continue;
        }
        
        SerialCommand cmd;
        cmd.byte1 = input[0];
        cmd.byte2 = input[1];
        cmd.byte3 = input[2];
        cmd.description = "User input";
        
        decode_command(cmd);
    }
    
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║         Serial Communication Test - Complete              ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝\n" << endl;
    
    return 0;
}
