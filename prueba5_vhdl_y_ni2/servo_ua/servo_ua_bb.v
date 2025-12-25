
module servo_ua (
	clk_clk,
	pio_0_external_connection_export,
	i2c_0_i2c_serial_sda_in,
	i2c_0_i2c_serial_scl_in,
	i2c_0_i2c_serial_sda_oe,
	i2c_0_i2c_serial_scl_oe,
	uart_0_external_connection_rxd,
	uart_0_external_connection_txd,
	reset_reset_n);	

	input		clk_clk;
	output	[7:0]	pio_0_external_connection_export;
	input		i2c_0_i2c_serial_sda_in;
	input		i2c_0_i2c_serial_scl_in;
	output		i2c_0_i2c_serial_sda_oe;
	output		i2c_0_i2c_serial_scl_oe;
	input		uart_0_external_connection_rxd;
	output		uart_0_external_connection_txd;
	input		reset_reset_n;
endmodule
