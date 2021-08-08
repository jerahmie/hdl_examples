//-----------------------------------------------------------------------
// counter testbench
//-----------------------------------------------------------------------
`include "counter.v"

module counter_tb;

   reg clk, reset;
   wire [3:0] count;

   counter U0 (
	       .clk(clk),
	       .reset(reset),
	       .count(count)
	       );

   initial
     begin
	$dumpfile("count.vcd");
	$dumpvars(0, count);
	
	clk = 0;
	reset = 0;
	# 17 reset = 1;
	# 11 reset = 0;
	# 29 reset = 1;
	# 5  reset = 0;
	# 200 $finish;
     end

   always
     # 5   clk = ! clk;

   initial
     $monitor("At time %t, count = %h (%0d)", $time, count, count);
   
endmodule // counter_tb

