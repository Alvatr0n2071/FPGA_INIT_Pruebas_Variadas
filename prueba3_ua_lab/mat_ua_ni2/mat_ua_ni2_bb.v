
module mat_ua_ni2 (
	clk_clk,
	leds_export,
	uart_rxd,
	uart_txd);	

	input		clk_clk;
	output	[3:0]	leds_export;
	input		uart_rxd;
	output		uart_txd;
endmodule
