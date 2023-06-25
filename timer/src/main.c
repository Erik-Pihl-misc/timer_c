/********************************************************************************
 * @brief Example of timer implementation by using the timer library.
 ********************************************************************************/
#include <timer.h>
#include <stdio.h>

/********************************************************************************
 * @brief Runs two timer to print two separata messages every 500 ms and 1000 ms 
 *        respectively.
 * 
 * @return
 *        Success code 0 upon termination of the program.
 ********************************************************************************/
int main(void) {
    struct timer timer0, timer1;
    timer_init(&timer0, 500);
    timer_init(&timer1, 1000);
    timer_start(&timer0);
    timer_start(&timer1);

    while (1) {
        if (timer_elapsed(&timer0)) {
            printf("Timer 0 elapsed!\n\n");
        } 
        if (timer_elapsed(&timer1)) {
            printf("Timer 1 elapsed!\n\n");
        }
    }
    return 0;
}