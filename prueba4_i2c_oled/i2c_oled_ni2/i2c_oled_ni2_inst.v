	i2c_oled_ni2 u0 (
		.clk_clk     (<connected-to-clk_clk>),     //  clk.clk
		.leds_export (<connected-to-leds_export>), // leds.export
		.i2c_sda_in  (<connected-to-i2c_sda_in>),  //  i2c.sda_in
		.i2c_scl_in  (<connected-to-i2c_scl_in>),  //     .scl_in
		.i2c_sda_oe  (<connected-to-i2c_sda_oe>),  //     .sda_oe
		.i2c_scl_oe  (<connected-to-i2c_scl_oe>),  //     .scl_oe
		.uart_rxd    (<connected-to-uart_rxd>),    // uart.rxd
		.uart_txd    (<connected-to-uart_txd>)     //     .txd
	);

