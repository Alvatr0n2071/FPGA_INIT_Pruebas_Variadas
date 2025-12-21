
module i2c_oled_ni2 (
	clk_clk,
	leds_export,
	i2c_sda_in,
	i2c_scl_in,
	i2c_sda_oe,
	i2c_scl_oe,
	uart_rxd,
	uart_txd);	

	input		clk_clk;
	output	[3:0]	leds_export;
	input		i2c_sda_in;
	input		i2c_scl_in;
	output		i2c_sda_oe;
	output		i2c_scl_oe;
	input		uart_rxd;
	output		uart_txd;
endmodule
