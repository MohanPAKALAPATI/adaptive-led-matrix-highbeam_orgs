/**
 * @file led_matrix_impl.cpp
 * @brief LED Matrix Control Implementation
 * 
 * Core implementation of LED matrix control functions used across examples.
 */

#include "led_matrix.h"
#include <iostream>

/**
 * @brief Initialize LED matrix
 */
void led_matrix_init(led_matrix_t *matrix) {
    if (!matrix) return;
    
    // Set all columns to ON (full beam)
    for (int i = 0; i < NUM_LED_COLUMNS; i++) {
        matrix->columns[i] = LED_ON;
    }
    matrix->brightness = 255;
}

/**
 * @brief Set all LEDs to a specific state
 */
void led_matrix_set_all(led_matrix_t *matrix, led_state_t state) {
    if (!matrix) return;
    
    for (int i = 0; i < NUM_LED_COLUMNS; i++) {
        matrix->columns[i] = state;
    }
}

/**
 * @brief Set specific column state
 */
void led_matrix_set_column(led_matrix_t *matrix, uint8_t column, led_state_t state) {
    if (!matrix || column >= NUM_LED_COLUMNS) return;
    matrix->columns[column] = state;
}

/**
 * @brief Update matrix based on single vehicle position
 */
void led_matrix_update_single_vehicle(led_matrix_t *matrix, int position) {
    if (!matrix) return;
    
    // First, turn all columns on
    led_matrix_set_all(matrix, LED_ON);
    
    // Then turn off columns based on vehicle position
    switch (position) {
        case 0:
            // No vehicles, all on
            break;
        case 1:
            led_matrix_set_column(matrix, 0, LED_OFF);
            led_matrix_set_column(matrix, 1, LED_OFF);
            break;
        case 2:
            led_matrix_set_column(matrix, 0, LED_OFF);
            led_matrix_set_column(matrix, 1, LED_OFF);
            led_matrix_set_column(matrix, 2, LED_OFF);
            break;
        case 3:
            led_matrix_set_column(matrix, 2, LED_OFF);
            led_matrix_set_column(matrix, 3, LED_OFF);
            led_matrix_set_column(matrix, 4, LED_OFF);
            break;
        case 4:
            led_matrix_set_column(matrix, 3, LED_OFF);
            led_matrix_set_column(matrix, 4, LED_OFF);
            break;
        case 5:
            led_matrix_set_column(matrix, 4, LED_OFF);
            led_matrix_set_column(matrix, 5, LED_OFF);
            break;
        case 6:
            led_matrix_set_column(matrix, 5, LED_OFF);
            led_matrix_set_column(matrix, 6, LED_OFF);
            led_matrix_set_column(matrix, 7, LED_OFF);
            break;
        case 7:
            led_matrix_set_column(matrix, 6, LED_OFF);
            led_matrix_set_column(matrix, 7, LED_OFF);
            break;
        case 8:
            led_matrix_set_column(matrix, 7, LED_OFF);
            break;
        case 9:
            // Multiple vehicles, turn all off
            led_matrix_set_all(matrix, LED_OFF);
            break;
        default:
            break;
    }
}

/**
 * @brief Update matrix based on two vehicle positions
 */
void led_matrix_update_dual_vehicle(led_matrix_t *matrix, int pos1, int pos2) {
    if (!matrix) return;
    
    // First, turn all columns on
    led_matrix_set_all(matrix, LED_ON);
    
    // Turn off columns for both vehicles
    int min_pos = (pos1 < pos2) ? pos1 : pos2;
    int max_pos = (pos1 > pos2) ? pos1 : pos2;
    
    // Turn off columns around both positions
    for (int i = 0; i < NUM_LED_COLUMNS; i++) {
        if ((i >= min_pos && i <= min_pos + 1) || 
            (i >= max_pos && i <= max_pos + 1)) {
            led_matrix_set_column(matrix, i, LED_OFF);
        }
    }
}

/**
 * @brief Calculate vehicle position from frame coordinates
 */
int calculate_vehicle_position(int x_coord, int frame_width) {
    if (frame_width <= 0) return 0;
    
    float col1 = frame_width * 0.1f - 20;
    float col2 = frame_width * 0.2f;
    float col3 = frame_width * 0.3f;
    float col4 = frame_width * 0.4f;
    float col5 = frame_width * 0.5f;
    float col6 = frame_width * 0.6f;
    float col7 = frame_width * 0.7f;
    float col8 = frame_width * 0.8f;
    float col9 = frame_width * 0.9f;
    
    if (x_coord < col1) return 0;
    else if (x_coord >= col1 && x_coord < col2) return 1;
    else if (x_coord >= col2 && x_coord < col3) return 2;
    else if (x_coord >= col3 && x_coord < col4) return 3;
    else if (x_coord >= col4 && x_coord < col5) return 4;
    else if (x_coord >= col5 && x_coord < col6) return 5;
    else if (x_coord >= col6 && x_coord < col7) return 6;
    else if (x_coord >= col7 && x_coord < col8) return 7;
    else if (x_coord >= col8 && x_coord < col9) return 8;
    else return 9;
}

/**
 * @brief Set brightness level
 */
void led_matrix_set_brightness(led_matrix_t *matrix, uint8_t brightness) {
    if (!matrix) return;
    matrix->brightness = brightness;
}

/**
 * @brief Get current column state
 */
led_state_t led_matrix_get_column(const led_matrix_t *matrix, uint8_t column) {
    if (!matrix || column >= NUM_LED_COLUMNS) return LED_OFF;
    return matrix->columns[column];
}

/**
 * @brief Print matrix state
 */
void led_matrix_print(const led_matrix_t *matrix) {
    if (!matrix) return;
    
    std::cout << "\n=== LED Matrix State (Brightness: " 
              << (int)matrix->brightness << ") ===" << std::endl;
    std::cout << "Columns: ";
    for (int i = 0; i < NUM_LED_COLUMNS; i++) {
        std::cout << "[" << i << ":" << (matrix->columns[i] == LED_ON ? "ON " : "OFF") << "] ";
    }
    std::cout << "\nVisual representation:" << std::endl;
    
    // Display rows
    for (int row = 0; row < NUM_LED_ROWS; row++) {
        std::cout << "  ";
        for (int col = 0; col < NUM_LED_COLUMNS; col++) {
            if (matrix->columns[col] == LED_ON) {
                std::cout << "██ ";
            } else {
                std::cout << "░░ ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
