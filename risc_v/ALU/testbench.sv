`timescale 1ns / 1ps

module testbench;

  // --- 신호 선언 (reg와 wire 명확히 구분) ---

  // 테스트벤치가 직접 값을 할당하고 '저장'해야 하는 신호들 (DUT의 입력)
  // '스위치' 역할이므로 reg 타입으로 선언합니다.
  reg [31:0] A_tb, B_tb;
  reg [3:0]  ALU_control_tb;

  // DUT의 출력 결과를 수동적으로 '전달'받기만 하는 신호
  // '램프' 역할이므로 wire 타입으로 선언합니다.
  wire [31:0] result_tb;

  // --- DUT 인스턴스화 ---
  ALU dut (
    .ALU_A      (A_tb),
    .ALU_B      (B_tb),
    .ALU_control (ALU_control_tb),
    .result     (result_tb)
  );

  // --- 시뮬레이션 시나리오 ---
  initial begin
    // Vivado에서는 $dumpfile, $dumpvars가 필요 없습니다.

    // --- 테스트 케이스 1: AND 연산 ---
    $display("--- Test Case 1: AND Operation ---");
    A_tb          = 32'hFFFF0000;
    B_tb          = 32'h00FFFF00;
    ALU_control_tb = 4'b0000;
    #10;

    $display("At time %0t: A=%h, B=%h, Control=%b => Result=%h", $time, A_tb, B_tb, ALU_control_tb, result_tb);

    // --- 테스트 케이스 2: OR 연산 ---
    $display("\n--- Test Case 2: OR Operation ---");
    ALU_control_tb = 4'b0001;
    #10;

    $display("At time %0t: A=%h, B=%h, Control=%b => Result=%h", $time, A_tb, B_tb, ALU_control_tb, result_tb);

    // --- 테스트 케이스 3: 덧셈(ADD) 연산 (미구현 상태 테스트) ---
    $display("\n--- Test Case 3: ADD Operation (Default Case) ---");
    ALU_control_tb = 4'b0010;
    #10;
    
    $display("At time %0t: A=%h, B=%h, Control=%b => Result=%h", $time, A_tb, B_tb, ALU_control_tb, result_tb);

    #10;
        
  end

endmodule