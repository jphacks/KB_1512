#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include "mraa.h"

#define OUTPUT_ON 1

int main(int argc, char **argv)
{
	int dur;
	int i2c_bus;
	int i2c_adapter;

	int state = 0;

	if (argc != 2) {
		fprintf(stdout, "usage: pump duration\n");
		return EXIT_FAILURE;
	}

	dur = atoi(argv[1]);

	if (dur > 30) {
		fprintf(stdout, "Duration too long\n");
		return EXIT_FAILURE;
	} else if (dur <= 0) {
		fprintf(stdout, "Duration must be positive\n");
		return EXIT_FAILURE;
	}


	mraa_init();
	fprintf(stdout, "Output HIGH for %d seconds\n", dur);
	fflush(stdout);

	mraa_gpio_context gpio;
	gpio = mraa_gpio_init(6);
	mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
	mraa_gpio_write(gpio, 0);

	mraa_gpio_write(gpio, 1);
	sleep(atoi(argv[1]));
	mraa_gpio_write(gpio, 0);
	
	/*while(1) {
		if (state != OUTPUT_ON) {
			fprintf(stdout, "output 0->1\n");
			mraa_gpio_write(gpio, 1);
			state = 1;
		} else {
			fprintf(stdout, "output 1->0\n");
			mraa_gpio_write(gpio, 0);
			state = 0;
		}
		mraa_gpio_write(gpio, 1);
		sleep(5);
	}
	*/
	

	mraa_gpio_close(gpio);

	mraa_deinit();
	return MRAA_SUCCESS;
}
