#include "mraa.h"

int main(int argc, char ** argv)
{
	char *board_name=mraa_get_platform_name();
	int i2c_bus;
	int i;
	int i2c_adapter;

	fprintf(stdout, "hello mraa\n Version: %s\n Running on %s\n", mraa_get_version(), board_name);

	mraa_gpio_context gpio;
	gpio = mraa_gpio_init(6);

	for (;;) {
		fprintf(stdout, "Gpio is %d\n", mraa_gpio_read(gpio));
		sleep(1);
	}

	mraa_gpio_close(gpio);

	mraaa_deinit();
	return MRAA_SUCCESS;
}
