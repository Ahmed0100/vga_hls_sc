#include "vga.h"
void vga::vga_main(void)
{
	const int h_pulse =5;
	const int h_bp = 10;
	const int h_fp = 5;
	const int h_pixels = 20;
	bool h_pol = false;
	const int v_pulse = 3;
	const int v_bp = 5;
	const int v_pixels = 10;
	const int v_fp = 1;
	bool v_pol = true;
	const int h_period = h_pulse + h_fp+h_bp + h_pixels;
	const int v_period = v_pulse + v_fp+ v_bp + v_pixels;
	int h_count=0;
	int v_count =0;
	n_blank.write(1);
	n_sync.write(0);
	wait();
	while(1)
	{
		if(h_count<h_period-1)
			h_count = h_count+1;
		else
		{
			h_count = 0;
			if(v_count < v_period-1)
				v_count = v_count+1;
			else
				v_count=0;
		}
		if(h_count < h_pixels + h_fp || h_count > h_pixels + h_fp + h_pulse)
			h_sync.write(!h_pol);
		else
			h_sync.write(h_pol);
		if(v_count < v_pixels + v_fp || v_count > v_pixels + v_fp + v_pulse)
			v_sync.write(!v_pol);
		else
			v_sync.write(v_pol);

		if(h_count<h_pixels)
			col.write(h_count);
		if(v_count<v_pixels)
			row.write(v_count);
	    if (h_count < h_pixels && v_count < v_pixels) //display time
	    	disp_en.write (true) ;                // enable display
	    else  					//blanking time
	    	disp_en.write (false);  //disable display

		wait();
	}
}
