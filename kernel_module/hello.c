// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RUBIN KHADKA");
MODULE_DESCRIPTION("A simple HELLO linux kernel module.");

static char *myname = "World";
module_param(myname, charp, 0444);
MODULE_PARM_DESC(myname, "A name to say hello to");

static int __init hello_init(void)
{
    pr_info("Hello, %s!\n", myname);
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Goodbye, %s!\n", myname);
}

module_init(hello_init);
module_exit(hello_exit);
