#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
/* size of stack area used by each thread */
#define STACKSIZE 1024

#define PRIORITY_THREAD_1	(1)
#define PRIORITY_THREAD_2	(1)
#define PRIORITY_THREAD_3 	(1)

#define LED_NODE DT_ALIAS(led0)
#define LED_NODE DT_ALIAS(led1)
#define LED_NODE DT_ALIAS(led2)

	static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
	static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
	static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios);

K_THREAD_STACK_DEFINE(thread_1_stack_area, STACKSIZE);
static struct k_thread thread_1_data;

K_THREAD_STACK_DEFINE(thread_2_stack_area, STACKSIZE);
static struct k_thread thread_2_data;

K_THREAD_STACK_DEFINE(thread_3_stack_area, STACKSIZE);
static struct k_thread thread_3_data;

void thread_1(void *dummy1, void *dummy2, void *dummy3)
{
	ARG_UNUSED(dummy1);
	ARG_UNUSED(dummy2);
	ARG_UNUSED(dummy3);
	gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	printk("thread_1: thread started \n");
	

	while (1)
	{
		printk("thread_1: thread loop \n");
		 gpio_pin_toggle_dt(&led0);
		k_msleep(8000);
	}

}

void thread_2(void *dummy1, void *dummy2, void *dummy3)
{
	ARG_UNUSED(dummy1);
	ARG_UNUSED(dummy2);
	ARG_UNUSED(dummy3);
gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
	printk("thread_2: thread started \n");

	while (1)
	{

		printk("thread_2: thread loop \n");
		 gpio_pin_toggle_dt(&led1);
		k_msleep(4000);
	}

}

void thread_3(void *dummy1, void *dummy2, void *dummy3)
{
	ARG_UNUSED(dummy1);
	ARG_UNUSED(dummy2);
	ARG_UNUSED(dummy3);
	gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
	printk("thread_3: thread started \n");

	while (1)
	{
		printk("thread_3: thread loop \n");
		 gpio_pin_toggle_dt(&led2);
		k_msleep(2000);
		
	}

}
	

void main(void)
{
	
		
		
		
	k_thread_create(&thread_1_data, thread_1_stack_area,
			K_THREAD_STACK_SIZEOF(thread_1_stack_area),
			thread_1, NULL, NULL, NULL,
			PRIORITY_THREAD_1, 0, K_FOREVER);
	k_thread_name_set(&thread_1_data, "thread_1");

	k_thread_create(&thread_2_data, thread_2_stack_area,
			K_THREAD_STACK_SIZEOF(thread_2_stack_area),
			thread_2, NULL, NULL, NULL,
			PRIORITY_THREAD_2, 0, K_FOREVER);
	k_thread_name_set(&thread_2_data, "thread_2");

	k_thread_create(&thread_3_data, thread_3_stack_area,
			K_THREAD_STACK_SIZEOF(thread_3_stack_area),
			thread_3, NULL, NULL, NULL,
			PRIORITY_THREAD_3, 0, K_FOREVER);
	k_thread_name_set(&thread_3_data, "thread_3");

	k_thread_start(&thread_1_data);
	k_thread_start(&thread_2_data);
	k_thread_start(&thread_3_data);
}