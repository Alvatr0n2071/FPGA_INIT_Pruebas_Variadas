	component i2c_oled_ni2 is
		port (
			clk_clk     : in  std_logic                    := 'X'; -- clk
			leds_export : out std_logic_vector(3 downto 0);        -- export
			i2c_sda_in  : in  std_logic                    := 'X'; -- sda_in
			i2c_scl_in  : in  std_logic                    := 'X'; -- scl_in
			i2c_sda_oe  : out std_logic;                           -- sda_oe
			i2c_scl_oe  : out std_logic;                           -- scl_oe
			uart_rxd    : in  std_logic                    := 'X'; -- rxd
			uart_txd    : out std_logic                            -- txd
		);
	end component i2c_oled_ni2;

	u0 : component i2c_oled_ni2
		port map (
			clk_clk     => CONNECTED_TO_clk_clk,     --  clk.clk
			leds_export => CONNECTED_TO_leds_export, -- leds.export
			i2c_sda_in  => CONNECTED_TO_i2c_sda_in,  --  i2c.sda_in
			i2c_scl_in  => CONNECTED_TO_i2c_scl_in,  --     .scl_in
			i2c_sda_oe  => CONNECTED_TO_i2c_sda_oe,  --     .sda_oe
			i2c_scl_oe  => CONNECTED_TO_i2c_scl_oe,  --     .scl_oe
			uart_rxd    => CONNECTED_TO_uart_rxd,    -- uart.rxd
			uart_txd    => CONNECTED_TO_uart_txd     --     .txd
		);

