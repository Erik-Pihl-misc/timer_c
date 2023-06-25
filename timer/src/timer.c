#include <timer.h>

void timer_init(struct timer* self, const uint32_t elapse_time_ms) {
    self->elapse_time_ms = elapse_time_ms;
    self->start_time = 0;
    self->enabled = false;
}

void timer_start(struct timer* self) {
    self->start_time = timer_get_current_time();
    self->enabled = true;
}

void timer_toggle(struct timer* self) {
    if (self->enabled) {
        timer_stop(self);
    } else {
        timer_start(self);
    }
}

bool timer_elapsed(struct timer* self) {
    if (self->enabled && self->elapse_time_ms) {
        if (timer_get_elapsed_time_ms(self) < self->elapse_time_ms) {
            return false;
        } else {
            self->start_time = timer_get_current_time();
            return true;
        }
    } else {
        return false;
    }
}