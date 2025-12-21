	component mat_ua_ni2 is
		port (
			clk_clk     : in  std_logic                    := 'X'; -- clk
			leds_export : out std_logic_vector(3 downto 0);        -- export
			uart_rxd    : in  std_logic                    := 'X'; -- rxd
			uart_txd    : out std_logic                            -- txd
		);
	end component mat_ua_ni2;

	u0 : component mat_ua_ni2
		port map (
			clk_clk     => CONNECTED_TO_clk_clk,     --  clk.clk
			leds_export => CONNECTED_TO_leds_export, -- leds.export
			uart_rxd    => CONNECTED_TO_uart_rxd,    -- uart.rxd
			uart_txd    => CONNECTED_TO_uart_txd     --     .txd
		);

