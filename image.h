#ifdef IMAGE_H
#define IMAGE_H
#include <systemc.h>

SC_MODULE(image)
{
	sc_in<bool> sys_clk;
	sc_in<bool> reset_n;
	sc_in<int> col;
	sc_in<int> row;
	sc_out<sc_uint<8> > red;
	sc_out<sc_uint<8> > green;
	sc_out<sc_uint<8> > blue;

	void image_main(void);

	SC_CTOR(image)
	{
		SC_CTHREAD(image_main,sys_clk.pos());
		reset_signal_is(reset_n,false);
		sensitive<<disp_en<<col<<row;
	};
	~image(){};
};
#endif
