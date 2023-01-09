#ifndef TB_TOP_H
#define TB_TOP_H
SC_MODULE(tb_top)
{
	sc_in<bool> sys_clk;
	sc_in<bool> reset_n;
	sc_in<bool> h_sync;
	sc_in<bool> v_sync;
	sc_in<bool> n_blank;
	sc_in<bool> n_sync;
	sc_in<sc_uint<8> > red;
	sc_in<sc_uint<8> > green;
	sc_in<sc_uint<8> > blue;
	//file pointers
	FILE* h_sync_out_file, *v_sync_out_file, *n_blank_out_file,
	*n_sync_out_file, *red_out_file, *green_out_file, *green_out_file;
	FILE* diff_red_file,*diff_green_file, *diff_blue_file;
	FILE* red_golden_file, *green_golden_file, *blue_golden_file;
	void recv();
	void compare_results();

	SC_CTOR(tb_top)
	{
		SC_CTHREAD(recv,sys_clk.pos());
		reset_signal_is(reset_n,false);
	};
	~tb_top(){};

};
#endif
