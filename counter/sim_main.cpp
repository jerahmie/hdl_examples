// verilator test bench

#include <stdlib.h>
#include "Vcounter.h"
#include "verilated.h"


// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
// Called $time in Verilog
double sc_time_stamp() {
  return main_time;  // Note does conversion to real, to match SystemC
}

int main(int argc, char **argv, char **env){

  // prevent unused variable warnings
  if (false && argc && argv && env) {}

  // Set debug level, 0 is off, 9 is highest
  Verilated::debug(0);

  // Randomization reset policy
  // May be overridden by commandArgs
  Verilated::randReset(2);

  // Verilator must compute traced signals
  Verilated::traceEverOn(true);

  // Pass arguments so Verilated code can see them
  // Initialize Verilators variables
  Verilated::commandArgs(argc, argv);  
  
  // Create logs/ directory in case we have traces to put under it.
  Verilated::mkdir("logs");

  // Create an instance of our module under test
  Vcounter *tb = new Vcounter();

  // Initial inputs
  tb->clk = 0;
  tb->reset = 0;
  tb->count = 0x0;

  // Tick the clock until we are done
  while(!Verilated::gotFinish()) {
    main_time++;  // Time passes
    
    // Toggle a fast clock (time/2 period)
    tb->clk = !tb->clk;

    // Toggle control signals on an edge that doesn't correspond
    // to where the controls are sampled; in this example we do
    // this only on negedge of clk, because we know reset is not
    // sampled there.
    if (!tb->clk) {
      if (main_time > 1 && main_time < 10) {
	tb->reset = 1;  // Assert reset
      } else {
	tb->reset = 0;  // Deassert reset
      }
    } 

    // Evaluate model
    // (if you have multiple models being simulated in the same timestep
    // then instead of eval(), call eval_step() on each, then
    // eval_end_step() on each.)
    tb->eval();
    
    // Read outputs
    VL_PRINTF("[%" VL_PRI64 "d] clk=%x rstl=%x count=%x\n",
	      main_time, tb->clk, tb->reset, tb->count);
  }

  // Final model cleanup
  tb->final();

  // Coverage analysis (since test passed)
#if VM_COVERAGE
  Verilated::mkdir("logs");
  VerilatedCov::write("logs/coverage.dat");
#endif
  
  // Destroy model
  delete tb;
  tb = NULL;

  exit(EXIT_SUCCESS);
}
