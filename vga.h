#ifndef VGA_H
#define VGA_H
#include <systemc.h>
SC_MODULE(vga)
{
	sc_in<bool> sys_clk;
	sc_in<bool> reset_n;
	sc_out<bool> h_sync;
	sc_out<bool> v_sync;
	sc_out<bool> disp_en;
	sc_out<int> col;
	sc_out<int> row;
	sc_out<bool> n_blank;
	sc_out<bool> n_sync;
	void vga_main(void);
	SC_CTOR(vga)
	{
		SC_CTHREAD(vga_main,sys_clk.pos());
		reset_signal_is(reset_n,false);
		sensitive<<sys_clk;
	};
	~vga(){};
};
#endif
