#include "tb_top.h"
void tb_top::recv()
{
	unsigned int n=0;
	unsigned int h_sync_out_read=0;
	unsigned int v_sync_out_read = 0;
	unsigned int n_blank_out_read=0;
	unsigned int n_sync_out_read=0;
	unsigned int red_out_read=0;
	unsigned int green_out_read=0;
	unsigned int blue_out_read=0;

	h_sync_out_file = fopen(OUTH_SYNC,"wt");
	v_sync_out_file = fopen(OUTV_SYNC,"wt");
	n_blank_out_file = fopen(OUTN_BLANK,"wt");
	n_sync_out_file = fopen(OUTN_SYNC,"wt");

	red_out_file = fopen(OUTRED,"wt");
	green_out_file = fopen(OUTGREEN,"wt");
	blue_out_file = fopen(OUTBLUE,"wt");
	wait();
	while(1)
	{
		while(1)
		{
			h_sync_out_read = h_sync.read();
			v_sync_out_read = v_sync.read();
			n_blank_out_read = n_blank.read();
			n_sync_out_read=  n_sync.read();
			red_out_read= red.read();
			green_out_read = green.read();
			blue_out_read = blue.read();
			fprintf(h_sync_out_file,"%d\n",h_sync_out_read);
			fprintf(v_sync_out_file,"%d\n",v_sync_out_read);
			fprintf(n_blank_out_file,"%d\n",n_blank_out_read);
			fprintf(n_sync_out_file,"%d\n",n_sync_out_read);
			fprintf(red_out_file,"%d\n",red_out_read);
			fprintf(blue_out_file,"%d\n",blue_out_read);
			fprintf(green_out_file,"%d\n",green_out_read);
			n++;
			if(n==1000) break;
			wait();
		}
		cout<<endl<<"starting comparing results "<<endl;
		compare_results();
		sc_stop();
		wait();
	}
}

void tb_top::compare_results()
{
	  int red_out, red_golden, line_red=1, errors_red=0;
	  int blue_out, blue_golden, line_blue=1, errors_blue=0;
	  int green_out, green_golden, line_green=1, errors_green=0;

	// close file where outputs are stored
	   fclose(h_sync_out_file);
	   fclose(v_sync_out_file);
	   fclose(n_blank_out_file);
	   fclose(n_sync_out_file);
	   fclose(red_out_file);
	   fclose(blue_out_file);
	   fclose(green_out_file);
	   //
	   red_out_file = fopen(OUTRED,"rt");
	   if(!red_out_file)
	   {
		   cout<< "could not open file "<<OUTRED<<endl;
		   sc_stop();
		   exit(-1);
	   }
	   red_golden_file = fopen(RED_GOLDEN,"rt");
	   if(!red_golden_file)
	   {
		   cout<< "could not open file "<<RED_GOLDEN<<endl;
		   sc_stop();
		   exit(-1);
	   }
	   diff_red_file = fopen(DIFFREDFILENAME,"w");
	   if(!diff_red_file)
	   {
		   cout<< "could not open file "<<DIFFREDFILENAME<<endl;
		   sc_stop();
		   exit(-1);
	   }
	   while(fscanf(red_golden_file,"%d",&red_golden)!=EOF)
	   {
		   fscanf(red_out_file,"%d",&red_out);
		   cout << endl <<"cycle["<< line_red << "]: " << red_golden << " -- "<< red_red;

		   if(red_out != red_golden)
		   {
			   cout << "\noutput missmatch [line:" << line_red << "] golden:" << red_golden << " -- output:" << red_out;
			   fprintf(diff_red_file,"\nOutput missmatch[line:%d] golden: %d -- output: %d",line_red, red_golden, red_out);
			   errors_red++;
		   }
		   line_red ++;
	   }
	   if(errors_red ==0)
		   cout<<endl<<"finished simulation successfully"<<endl;
	   else
		   cout<<endl<<"simulation failed"<<endl;
	   fclose(red_out_file);
	   fclose(diff_red_file);
	   fclose(red_golden_file);
	   //////////////////
	   blue_out_file = fopen(OUTBLUE,"rt");
	   if(!blue_out_file)
	   {
		   cout<< "could not open file "<<OUTBLUE<<endl;
		   sc_stop();
		   exit(-1);
	   }
	   blue_golden_file = fopen(BLUE_GOLDEN,"rt");
	   if(!blue_golden_file)
	   {
		   cout<< "could not open file "<<BLUE_GOLDEN<<endl;
		   sc_stop();
		   exit(-1);
	   }
	   diff_blue_file = fopen(DIFFBLUEFILENAME,"w");
	   if(!diff_blue_file)
	   {
		   cout<< "could not open file "<<DIFFBLUEFILENAME<<endl;
		   sc_stop();
		   exit(-1);
	   }
	   while(fscanf(blue_golden_file,"%d",&blue_golden)!=EOF)
	   {
		   fscanf(blue_out_file,"%d",&blue_out);
		   cout << endl <<"cycle["<< line_blue << "]: " << blue_golden << " -- "<< blue_blue;

		   if(blue_out != blue_golden)
		   {
			   cout << "\noutput missmatch [line:" << line_blue << "] golden:" << blue_golden << " -- output:" << blue_out;
			   fprintf(diff_blue_file,"\nOutput missmatch[line:%d] golden: %d -- output: %d",line_blue, blue_golden, blue_out);
			   errors_blue++;
		   }
		   line_blue ++;
	   }
	   if(errors_blue ==0)
		   cout<<endl<<"finished simulation successfully"<<endl;
	   else
		   cout<<endl<<"simulation failed"<<endl;
	   fclose(blue_out_file);
	   fclose(diff_blue_file);
	   fclose(blue_golden_file);
	   /////////////////////////
	   green_out_file = fopen(OUTGREEN,"rt");
	   if(!green_out_file)
	   {
		   cout<< "could not open file "<<OUTGREEN<<endl;
		   sc_stop();
		   exit(-1);
	   }
	   green_golden_file = fopen(GREEN_GOLDEN,"rt");
	   if(!green_golden_file)
	   {
		   cout<< "could not open file "<<GREEN_GOLDEN<<endl;
		   sc_stop();
		   exit(-1);
	   }
	   diff_green_file = fopen(DIFFGREENFILENAME,"w");
	   if(!diff_green_file)
	   {
		   cout<< "could not open file "<<DIFFGREENFILENAME<<endl;
		   sc_stop();
		   exit(-1);
	   }
	   while(fscanf(green_golden_file,"%d",&green_golden)!=EOF)
	   {
		   fscanf(green_out_file,"%d",&green_out);
		   cout << endl <<"cycle["<< line_green << "]: " << green_golden << " -- "<< green_green;

		   if(green_out != green_golden)
		   {
			   cout << "\noutput missmatch [line:" << line_green << "] golden:" << green_golden << " -- output:" << green_out;
			   fprintf(diff_green_file,"\nOutput missmatch[line:%d] golden: %d -- output: %d",line_green, green_golden, green_out);
			   errors_green++;
		   }
		   line_green ++;
	   }
	   if(errors_green ==0)
		   cout<<endl<<"finished simulation successfully"<<endl;
	   else
		   cout<<endl<<"simulation failed"<<endl;
	   fclose(green_out_file);
	   fclose(diff_green_file);
	   fclose(green_golden_file);
}



