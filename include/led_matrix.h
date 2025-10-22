/**
 * @file led_matrix.h
 * @brief LED Matrix Control Library for Adaptive High Beam System
 * 
 * This header provides the core functionality for controlling an 8x4 LED matrix
 * used in adaptive high beam headlight systems. The matrix allows selective
 * illumination to prevent glare for other drivers.
 */

#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/** @brief Number of LED columns in the matrix */
#define NUM_LED_COLUMNS 8

/** @brief Number of LED rows in the matrix */
#define NUM_LED_ROWS 4

/** @brief Total number of LEDs */
#define TOTAL_LEDS (NUM_LED_COLUMNS * NUM_LED_ROWS)

/** @brief Maximum number of vehicles that can be tracked */
#define MAX_VEHICLES 2

/**
 * @brief LED state enumeration
 */
typedef enum {
    LED_OFF = 0,    /**< LED is off (dark zone) */
    LED_ON = 1      /**< LED is on (illuminated) */
} led_state_t;

/**
 * @brief LED color structure (RGB)
 */
typedef struct {
    uint8_t r;  /**< Red component (0-255) */
    uint8_t g;  /**< Green component (0-255) */
    uint8_t b;  /**< Blue component (0-255) */
} led_color_t;

/**
 * @brief Vehicle position structure
 */
typedef struct {
    int position;       /**< Column position (0-8) */
    bool detected;      /**< Whether vehicle is detected */
} vehicle_position_t;

/**
 * @brief LED matrix structure
 */
typedef struct {
    led_state_t columns[NUM_LED_COLUMNS];  /**< State of each column */
    uint8_t brightness;                     /**< Overall brightness (0-255) */
} led_matrix_t;

/**
 * @brief Initialize LED matrix
 * @param matrix Pointer to LED matrix structure
 */
void led_matrix_init(led_matrix_t *matrix);

/**
 * @brief Set all LEDs to a specific state
 * @param matrix Pointer to LED matrix structure
 * @param state State to set (LED_ON or LED_OFF)
 */
void led_matrix_set_all(led_matrix_t *matrix, led_state_t state);

/**
 * @brief Set specific column state
 * @param matrix Pointer to LED matrix structure
 * @param column Column index (0-7)
 * @param state State to set (LED_ON or LED_OFF)
 */
void led_matrix_set_column(led_matrix_t *matrix, uint8_t column, led_state_t state);

/**
 * @brief Update matrix based on single vehicle position
 * @param matrix Pointer to LED matrix structure
 * @param position Vehicle position (0-8)
 */
void led_matrix_update_single_vehicle(led_matrix_t *matrix, int position);

/**
 * @brief Update matrix based on two vehicle positions
 * @param matrix Pointer to LED matrix structure
 * @param pos1 First vehicle position (0-8)
 * @param pos2 Second vehicle position (0-8)
 */
void led_matrix_update_dual_vehicle(led_matrix_t *matrix, int pos1, int pos2);

/**
 * @brief Calculate vehicle position from frame coordinates
 * @param x_coord X coordinate in frame
 * @param frame_width Total frame width
 * @return Column position (0-8)
 */
int calculate_vehicle_position(int x_coord, int frame_width);

/**
 * @brief Set brightness level
 * @param matrix Pointer to LED matrix structure
 * @param brightness Brightness level (0-255)
 */
void led_matrix_set_brightness(led_matrix_t *matrix, uint8_t brightness);

/**
 * @brief Get current column state
 * @param matrix Pointer to LED matrix structure
 * @param column Column index (0-7)
 * @return Current state of the column
 */
led_state_t led_matrix_get_column(const led_matrix_t *matrix, uint8_t column);

/**
 * @brief Print matrix state (for debugging)
 * @param matrix Pointer to LED matrix structure
 */
void led_matrix_print(const led_matrix_t *matrix);

#ifdef __cplusplus
}
#endif

#endif /* LED_MATRIX_H */
