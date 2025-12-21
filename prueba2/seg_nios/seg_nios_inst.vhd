	component seg_nios is
		port (
			clk_clk    : in  std_logic                    := 'X'; -- clk
			mux_export : out std_logic_vector(3 downto 0);        -- export
			seg_export : out std_logic_vector(7 downto 0)         -- export
		);
	end component seg_nios;

	u0 : component seg_nios
		port map (
			clk_clk    => CONNECTED_TO_clk_clk,    -- clk.clk
			mux_export => CONNECTED_TO_mux_export, -- mux.export
			seg_export => CONNECTED_TO_seg_export  -- seg.export
		);

