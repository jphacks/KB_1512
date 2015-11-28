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
	char *board_name = mraa_get_platform_name();
	int i2c_bus;
	int i2c_adapter;

	int state = 0;

	fprintf(stdout, "hello mraa\n Version: %s\n Running on %s\n", mraa_get_version(), board_name);

	mraa_gpio_context gpio;
	gpio = mraa_gpio_init(6);
	mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
	fprintf(stdout, "gpio init");

	while(1) {
		/*
		if (state == OUTPUT_ON) {
			fprintf(stdout, "state: 0->1");
			mraa_gpio_write(gpio, 1);
			state = 0;
		} else {
			fprintf(stdout, "state: 1->0");
			mraa_gpio_write(gpio, 0);
			state = 1;
		}
		*/
		fprintf(stdout, "state: 1->0");
		//mraa_gpio_write(gpio, 1);
		sleep(5);
	}

	//mraa_gpio_close(gpio);

	mraa_deinit();
	return MRAA_SUCCESS;
}
