#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/time64.h>
#include <linux/ktime.h>
#include <linux/hrtimer.h>

#define MAX_TIMERS 16

extern void check_timer(void);

static struct hrtimer hr_timer;

static unsigned long delays[MAX_TIMERS];
static unsigned int dnum = sizeof(delays) / sizeof(delays[0]);
module_param_array(delays, ulong, &dnum, S_IRUGO | S_IWUSR);

enum hrtimer_restart timer_callback(struct hrtimer *timer_for_restart)
{
        static unsigned int i = 0;
        i++;
        ktime_t interval = ktime_set(0, delays[i] * 1000000L);
        hrtimer_forward_now(timer_for_restart, interval);
        check_timer();
        return HRTIMER_RESTART;
}

static int __init init_mod(void)
{
        ktime_t ktime = ktime_set(0, delays[0] * 1000000L);
        hrtimer_init(&hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
        hr_timer.function = &timer_callback;
        hrtimer_start(&hr_timer, ktime, HRTIMER_MODE_REL);
        check_timer();
        return 0;
}

static void __exit exit_mod(void)
{
        hrtimer_cancel(&hr_timer);
        return;
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Module4Task4");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");
