// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define LED_GPIO_PIN 534 // GPIO pin

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rubin Khadka");
MODULE_DESCRIPTION("A simple Linux LED driver");

static int __init led_init(void)
{
	int ret;

	ret = gpio_request(LED_GPIO_PIN, "LED_GPIO");
	if (ret)
	{
		pr_info(KERN_ERR "Failed to request GPIO %d\n", LED_GPIO_PIN);
		return ret;
	}

	gpio_direction_output(LED_GPIO_PIN, 0);

	pr_info(KERN_INFO "LED Driver Loaded, GPIO %d initialised\n", LED_GPIO_PIN);
	return 0;
}	

static void __exit led_exit(void)
{
	gpio_set_value(LED_GPIO_PIN, 0);
	gpio_free(LED_GPIO_PIN);
	pr_info(KERN_INFO "LED Driver Unloaded, GPIO %d freed\n", LED_GPIO_PIN);
}

module_init(led_init);
module_exit(led_exit);