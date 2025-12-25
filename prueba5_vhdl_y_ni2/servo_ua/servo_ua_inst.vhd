	component servo_ua is
		port (
			clk_clk                          : in  std_logic                    := 'X'; -- clk
			pio_0_external_connection_export : out std_logic_vector(7 downto 0);        -- export
			i2c_0_i2c_serial_sda_in          : in  std_logic                    := 'X'; -- sda_in
			i2c_0_i2c_serial_scl_in          : in  std_logic                    := 'X'; -- scl_in
			i2c_0_i2c_serial_sda_oe          : out std_logic;                           -- sda_oe
			i2c_0_i2c_serial_scl_oe          : out std_logic;                           -- scl_oe
			uart_0_external_connection_rxd   : in  std_logic                    := 'X'; -- rxd
			uart_0_external_connection_txd   : out std_logic;                           -- txd
			reset_reset_n                    : in  std_logic                    := 'X'  -- reset_n
		);
	end component servo_ua;

	u0 : component servo_ua
		port map (
			clk_clk                          => CONNECTED_TO_clk_clk,                          --                        clk.clk
			pio_0_external_connection_export => CONNECTED_TO_pio_0_external_connection_export, --  pio_0_external_connection.export
			i2c_0_i2c_serial_sda_in          => CONNECTED_TO_i2c_0_i2c_serial_sda_in,          --           i2c_0_i2c_serial.sda_in
			i2c_0_i2c_serial_scl_in          => CONNECTED_TO_i2c_0_i2c_serial_scl_in,          --                           .scl_in
			i2c_0_i2c_serial_sda_oe          => CONNECTED_TO_i2c_0_i2c_serial_sda_oe,          --                           .sda_oe
			i2c_0_i2c_serial_scl_oe          => CONNECTED_TO_i2c_0_i2c_serial_scl_oe,          --                           .scl_oe
			uart_0_external_connection_rxd   => CONNECTED_TO_uart_0_external_connection_rxd,   -- uart_0_external_connection.rxd
			uart_0_external_connection_txd   => CONNECTED_TO_uart_0_external_connection_txd,   --                           .txd
			reset_reset_n                    => CONNECTED_TO_reset_reset_n                     --                      reset.reset_n
		);

