/*
 * /dev/rps skeleton code
 *
 * Wonsun Ahn <wahn@pitt.edu>
 *
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>
#include <asm/uaccess.h>

char mode=0;
unsigned char get_random_byte(int max, int min) 
{
	unsigned char	c;
	get_random_bytes(&c,	1);
	return	c%max +	min;
}

/*
 * rps_read is the function called when a process calls read() on
 * /dev/rps.  It writes count bytes to the buffer passed in the
 * read() call.
 */

static ssize_t rps_read(struct file * file, char * buf, size_t count, loff_t *ppos)
{
	int i;
	if(mode==0)
	{
		for(i=0; i < count; i++)
		{
			unsigned char c = get_random_byte(3,1);
			buf[i]= c;
		}
	}
	else
	{
		for(i=0; i < count; i++)
		{
			buf[i]=mode;
		}
	}
    printk(KERN_ERR "read(file, 0x%p, %d, %lld)\n", buf, count, *ppos);
    // Refer to the Hello World device driver for hints
	return count;
}

/*
 * rps_write is the function called when a process calls write() on
 * /dev/rps.  It reads count bytes from the buffer passed in the
 * write() call.
 */

static ssize_t rps_write(struct file * file, const char * buf, size_t count, loff_t *ppos)
{
	mode=*(buf+count-sizeof(char));
    printk(KERN_ERR "write(file, 0x%p, %d, %lld)\n", buf, count, *ppos);
    return count;
}

/*
 * Now we have two file operations: read, write
 */

static const struct file_operations rps_fops = {
	.owner		= THIS_MODULE,
	.read		= rps_read,
    .write      = rps_write,
};

static struct miscdevice rps_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/rps.
	 */
	"rps",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&rps_fops
};

static int __init
rps_init(void)
{
	int ret;

	/*
	 * Create the "rps" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/rps device using
	 * the default rules.
	 */
	ret = misc_register(&rps_dev);
	if (ret)
                printk(KERN_ERR "Unable to register \"Hello, world!\" misc device\n");
        else {
                printk(KERN_ERR "Registered device under <MAJOR , MINOR><%d %d>\n" , 10, rps_dev.minor);
                printk(KERN_ERR "Create device file using: mknod /dev/rps c %d %d\n", 10, rps_dev.minor);
        }

	return ret;
}

module_init(rps_init);

static void __exit
rps_exit(void)
{
	misc_deregister(&rps_dev);
}

module_exit(rps_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wonsun Ahn <wahn@pitt.edu>");
MODULE_DESCRIPTION("/dev/rps skeleton code");
MODULE_VERSION("dev");
