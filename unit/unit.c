#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include "mraa.h"

int main(int argc, char ** argv)
{
	pid_t pid;
	pid_t sid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
		exit(EXIT_SUCCESS);

	umask(0);

	sid = setsid();
	if (sid < 0)
		exit(EXIT_FAILURE);

	if ((chdir("/")) < 0)
		exit(EXIT_FAILURE);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	//openlog("unit", LOG_PID|LOG_CONS, LOG_USER);
	FILE *temp;
	temp = fopen("/var/log/unit/log", "a");

	char *board_name=mraa_get_platform_name();
	int i2c_bus;
	int i;
	int i2c_adapter;

	fprintf(temp, "hello mraa\n Version: %s\n Running on %s\n", mraa_get_version(), board_name);

	mraa_gpio_context gpio;
	gpio = mraa_gpio_init(6);

	while(1) {
		fprintf(temp, "Gpio is %d\n", mraa_gpio_read(gpio));
		//syslog(LOG_INFO, "foo");
		sleep(10);
	}

	mraa_gpio_close(gpio);

	fflush(temp);
	fclose(temp);
	mraaa_deinit();
	exit(EXIT_SUCCESS);
}
