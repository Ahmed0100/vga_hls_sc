#include "top_vga.h"
#include "tb_top.h"
#define WAVE_DUMP

int sc_main(int argc, char** argv)
{
	sc_clock sys_clk("clk", 25, SC_NS, 0.5,12.5, SC_NS,true);
	sc_signal<bool> reset_n;

	sc_signal<bool> h_sync;
	sc_signal<bool> v_sync;
	sc_signal<bool> n_blank;
	sc_signal<bool> n_sync;
	sc_signal<sc_uint<8> > red;
	sc_signal<sc_uint<8> > green;
	sc_signal<sc_uint<8> > blue;

	top_vga top_vga_inst("top_vga_inst");
	tb_top tb_test_inst("tb_test_inst");

	//connect to FIR
	top_vga_inst.sys_clk( sys_clk );
	top_vga_inst.reset_n( reset_n );
	top_vga_inst.h_sync(h_sync) ;//--horiztonal sync pulse
	top_vga_inst.v_sync(v_sync) ;//--vertical sync pulse
	top_vga_inst.n_blank(n_blank)  ;//--direct blacking output to DAC
	top_vga_inst.n_sync(n_sync)  ;//--sync-on-green output to DAC
	top_vga_inst.red(red); //red magnitude output to DAC
	top_vga_inst.green(green); //green magnitude output to DAC
	top_vga_inst.blue(blue); //blue magnitude output to DAC
	  // connect to test bench
	tb_test_inst.sys_clk( sys_clk );
	tb_test_inst.reset_n( reset_n );
	tb_test_inst.h_sync(h_sync) ;//--horiztonal sync pulse
	tb_test_inst.v_sync(v_sync) ;//--vertical sync pulse
	tb_test_inst.n_blank(n_blank)  ;//--direct blacking output to DAC
	tb_test_inst.n_sync(n_sync)  ;//--sync-on-green output to DAC
	tb_test_inst.red(red); //red magnitude output to DAC
	tb_test_inst.green(green); //green magnitude output to DAC
	tb_test_inst.blue(blue); //blue magnitude output to DAC

#ifdef WAVE_DUMP
	sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_file");
	sc_trace(trace_file,sys_clk,"sys_clk");
	sc_trace(trace_file,reset_n,"reset_n");
	sc_trace(trace_file,h_sync,"h_sync");
	sc_trace(trace_file,v_sync,"v_sync");
	sc_trace(trace_file,n_blank,"n_blank");
	sc_trace(trace_file,n_sync,"n_sync");
	sc_trace(trace_file,red,"red");
	sc_trace(trace_file,green,"green");
	sc_trace(trace_file,blue,"blue");
#endif
	sc_start(25,SC_NS);
	reset_n.write(0);
	sc_start(25,SC_NS);
	reset_n.write(1);

	sc_start();
#ifdef WAVE_DUMP
	sc_close_vcd_trace_file(trace_file);
#endif
	return 0;
}
