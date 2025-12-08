default : 
	iverilog -o my_or_gate.vvp OR_gate.sv testbench.sv
	vvp my_or_gate.vvp

wave :
	gtkwave dump.vcd