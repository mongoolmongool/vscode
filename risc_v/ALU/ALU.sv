`timescale 1ns / 1ps

module ALU(
    input wire [31:0] ALU_A, ALU_B,
    input wire [3:0] ALU_control,
    output reg [31:0] result    
);

    wire [31:0] and_res;
    wire [31:0] or_res;
    
    AND_gate and_unit(
        .a(ALU_A),
        .b(ALU_B),
        .out(and_res)
    );
    
    OR_gate or_unit(
        .a(ALU_A),
        .b(ALU_B),
        .out(or_res)
    );
    
    // MUX LOGIC //
    always_comb begin
    
        case(ALU_control)
            4'b0000 : result = and_res;
            4'b0001 : result = or_res;
            
            default : result = 32'bx; // 기본값 x -> 정의되지 않음.
        endcase
        
    end
    
    
endmodule
