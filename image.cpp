#include "image.h"

void image::image_main(void)
{
	const int pixels_y=5;
	const int pixels_x = 5;
	wait();
	while(1)
	{
		if(disp_en)
		{
			if(row < pixels_y && col<pixels_x)
			{
				red.write(0xaa);
				green.write(0xbb);
				blue.write(0xcc);
			}
			else
			{
				red.write(0xdd);
				green.write(0xee);
				blue.write(0xff);
			}
		}
		else
		{
			red.write(0x11);
			green.write(0x22);
			blue.write(0x33);
		}
		wait();
	}
}
