#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/random.h>
#include <checker.h>

extern int array_sum(short *arr, size_t n);
extern ssize_t generate_output(int sum, short *arr, size_t size, char *buf);

#define ARR_SIZE 10
#define ITER_COUNT 10
#define BUFFER_SIZE 100

static void fill_random(short *arr, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
    {
	arr[i] = (short) get_random_int();
    }
}

static ssize_t real_array_sum(short *arr, size_t n)
{
    size_t sum = 0;
    size_t i;
    for (i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int __init init_mod(void)
{
    short arr[ARR_SIZE];
    ssize_t sum;
    ssize_t real_sum;
    char output_buffer[BUFFER_SIZE];
    size_t i;
    
    CHECKER_MACRO;
    
    for (i = 0; i < ITER_COUNT; i++)
    {
	fill_random(arr, ARR_SIZE);
        sum = array_sum(arr, ARR_SIZE);
	real_sum = real_array_sum(arr, ARR_SIZE);
	memset(output_buffer, 0, BUFFER_SIZE);
	generate_output(sum, arr, ARR_SIZE, output_buffer);
	if (sum == real_sum)
	{
	    printk(KERN_INFO "%s\n", output_buffer);
	}
	else
	{
	    printk(KERN_ERR "%s\n", output_buffer);
	}
    }
    return 0;
}

void __exit exit_mod(void)
{
    CHECKER_MACRO;
    return;
}

module_init(init_mod);
module_exit(exit_mod);

MODULE_DESCRIPTION("Task3");
MODULE_AUTHOR("Vadim Dyachkov <mail@vaddya.com>");
MODULE_LICENSE("GPL");

