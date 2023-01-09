#ifdef TOP_H
#define TOP_H
#include <system.h>
#include "vga.h"
#include "image.h"
SC_MODULE(top_vga)
{
	sc_in<bool> sys_clk;
	sc_in<bool> reset_n;
	sc_out<bool> h_sync;
	sc_out<bool> v_sync;
	sc_out<bool> n_blank;
	sc_out<bool> n_sync;
	sc_out<sc_uint<8> > red;
	sc_out<sc_uint<8> > green;
	sc_out<sc_uint<8> > blue;

	vga vga_inst;
	image image_inst;
	sc_signal<bool> disp_en;
	sc_signal<bool> row;
	sc_signal<bool> col;

	SC_CTOR(top_vga): vga_inst("vga_inst"),image_inst("image_inst"){
		vga_inst.sys_clk(sys_clk);
		vga_inst.reset_n(reset_n);
		vga_inst.h_sync(h_sync);
		vga_inst.v_sync(v_sync);
		vga_inst.disp_en(disp_en);
		vga_inst.col(col);
		vga_inst.row(row);
		vga_inst.n_blank(n_blank);
		vga_inst.n_sync(n_sync);

		image_inst.sys_clk(sys_clk);
		image_inst.reset_n(reset_n);
		image_inst.h_sync(h_sync);
		image_inst.v_sync(v_sync);
		image_inst.disp_en(disp_en);
		image_inst.col(col);
		image_inst.row(row);
		image_inst.n_blank(n_blank);
		image_inst.n_sync(n_sync);
	};
};
#endif
