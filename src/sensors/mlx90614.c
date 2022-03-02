#include <mraa.h>
#include "include/sensors.h"

int mlx90614(float *ptr)
{
	uint8_t buffer[3];
	/* set I2C bus address */
	if (mraa_i2c_address(i2c, MLX90614_ADDR) != MRAA_SUCCESS) {
		return -1;
	}

	/* read data from TOBJ1 address, which returns the temp we want */
	if (mraa_i2c_read_bytes_data(i2c, MLX90614_TOB1, buffer, 3) != MRAA_SUCCESS) {
		return -1;
	}

	/* transform data according to datasheet */
	uint16_t data = (buffer[0] | (uint16_t)(buffer[1] << 8));
	*ptr = data;

	if (*ptr == 0) {
		return -1;
	}

	/* make celsius */
	*ptr *= 0.2;
	*ptr -= 273.15;

	return;
}
