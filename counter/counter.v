//---------------------------------------------------------------------
// counter.v
//---------------------------------------------------------------------

module counter(
	       clk,
	       reset,
	       count
	       );

   input wire  clk;
   input wire  reset;
   output reg	 [3:0] count;
   

   initial
     begin
	count = 4'b0;
     end
   
   always @ (posedge clk)
     begin
	if (!reset)
	  count <= count + 4'b1;
	else
	  count <= 4'b0;
     end
   
endmodule // counter
