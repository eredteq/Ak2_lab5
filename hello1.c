// SPDX-License-Identifier: Dual BSD/GPL
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_AUTHOR("Kolomiiets V. M. <kolomiiets.vladyslav_io42@edu.kpi.ua>");
MODULE_DESCRIPTION("Hello1 module with list and print time measurement");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_data {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

static LIST_HEAD(hello_list);

int print_hello(void)
{
	struct hello_data *data;

	data = kmalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->start_time = ktime_get();
	pr_info("Hello, world!\n");
	data->end_time = ktime_get();

	list_add_tail(&data->list, &hello_list);

	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("hello1 module loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_data *md, *tmp;

	list_for_each_entry_safe(md, tmp, &hello_list, list) {
		pr_info("Print time: %lld ns\n",
			ktime_to_ns(ktime_sub(md->end_time, md->start_time)));
		list_del(&md->list);
		kfree(md);
	}
	pr_info("hello1 module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
