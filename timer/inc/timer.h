/********************************************************************************
 * @brief Library for implementation of user-friendly timers via struct timer
 *        and associated functions.
 ********************************************************************************/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

/********************************************************************************
 * @brief The frequency of the clock used for measuring the elapsed time
 *        measured in Hz.
 ********************************************************************************/
#define TIMER_CLOCK_FREQUENCY_HZ 1000.0

/********************************************************************************
 * @brief Struct for implementation of timers.
 * 
 * @param elapse_time_ms
 *        The elapse time of the time in milliseconds, determines the delay
 *        between when the timer starts and when it elapses.
 * @param start_time
 *        Time stamp for measuring when the timer was started.
 * @param enabled
 *        Indicates if the timer is running.
 ********************************************************************************/
struct timer {
    uint32_t elapse_time_ms;
    int32_t start_time;
    bool enabled;
};

/********************************************************************************
 * @brief Initializes timer with specified elapse time. The timer is disabled
 *        at start, but can be started by calling the timer_start function.
 * 
 * @param self
 *        Reference to the timer.
 * @param elapse_time_ms
 *        The elapse time of the timer in milliseconds. Set this value to 0 to 
 *        use this timer for measuring time without the timer elapsing.
 ********************************************************************************/
void timer_init(struct timer* self, const uint32_t elapse_time_ms);

/********************************************************************************
 * @brief Starts the timer with start time set to the time of the function call.
 * 
 * @param self
 *        Reference to the timer.
 ********************************************************************************/
void timer_start(struct timer* self);

/********************************************************************************
 * @brief Stops the timer.
 * 
 * @param self
 *        Reference to the timer.
 ********************************************************************************/
static inline void timer_stop(struct timer* self);

/********************************************************************************
 * @brief Toggles start/stop of the timer.
 * 
 * @param self
 *        Reference to the timer.
 ********************************************************************************/
void timer_toggle(struct timer* self);

/********************************************************************************
 * @brief Indicates if the timer has elapsed, i.e. checks if the set elapse 
 *        time has passed. If true, the timer is restarted at the time of the
 *        function call.
 * 
 * @param self
 *        Reference to the timer.
 * @return
 *        True if the timer has elapsed, else false.
 ********************************************************************************/
bool timer_elapsed(struct timer* self);

/********************************************************************************
 * @brief Sets new elapse time for timer.
 * 
 * @param self
 *        Reference to the timer.
 * @param elapse_time_ms
 *        The elapse time of the timer in milliseconds. Set this value to 0 to 
 *        use this timer for measuring time without the timer elapsing.
 ********************************************************************************/
static inline void timer_set_elapse_time_ms(struct timer* self, 
                                            const uint32_t elapse_time_ms);

/********************************************************************************
 * @brief Provides the time elapsed since the timer started in milliseconds.
 * 
 * @param self
 *        Reference to the timer.
 * @return
 *        The time elapsed since the start of the timer in milliseconds.
 ********************************************************************************/
static inline double timer_get_elapsed_time_ms(const struct timer* self);

/********************************************************************************
 * @brief Provides the current time measured in the number of elapsed clock
 *        ticks since the start of the program, where 1000 clock pulses elapse
 *        every second. 
 * 
 * @note  This function is intended for taking time stamps to measure elapsed 
 *        time only.
 * 
 * @return
 *        The current time measured in clock ticks since the program started.
 ********************************************************************************/
static inline int32_t timer_get_current_time(void);

/********************************************************************************
 * @brief Provides the time elapsed between specified time stamp and current
 *        time measured in milliseconds.
 * 
 * @param time_stamp
 *        Time stamp for measuring the elapsed time.
 * @return
 *        The time elapsed since the specified time stamp in milliseconds.
 ********************************************************************************/
static inline double timer_get_delta_ms(const int32_t time_stamp);

/********************************************************************************
 * @brief Implementation details.
 ********************************************************************************/
static inline void timer_stop(struct timer* self) { self->enabled = false; }

static inline void timer_set_elapse_time_ms(struct timer* self, 
                                            const uint32_t elapse_time_ms) {
    self->elapse_time_ms = elapse_time_ms;
}

static inline double timer_get_elapsed_time_ms(const struct timer* self) {
    return self->enabled ? timer_get_delta_ms(self->start_time) : 0;
}

static inline int32_t timer_get_current_time(void) { return clock(); }

static inline double timer_get_delta_ms(const int32_t time_stamp) {
    return (double)(timer_get_current_time() - time_stamp) / TIMER_CLOCK_FREQUENCY_HZ;
}

#ifdef __cplusplus
}
#endif