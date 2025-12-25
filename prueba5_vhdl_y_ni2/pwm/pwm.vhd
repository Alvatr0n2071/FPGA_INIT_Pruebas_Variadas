library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity pwm is
    port (
        clk      : in  std_logic;                 -- 50 MHz
        reset_n  : in  std_logic;
        angle    : in  std_logic_vector(7 downto 0); -- 0..180
        pwm_out  : out std_logic
    );
end entity;

architecture rtl of pwm is

    -- 20 ms @ 50 MHz = 1,000,000 ciclos
    constant PERIOD : integer := 1_000_000;

    signal counter     : integer range 0 to PERIOD := 0;
    signal pulse_width : integer range 20_000 to 130_000;

begin

    --------------------------------------------------------------------
    -- Conversión ángulo → ancho de pulso
    -- 0°   → 1.0 ms  → 50,000
    -- 180° → 2.0 ms  → 100,000
    --------------------------------------------------------------------
    pulse_width <= 30_000 +
        (to_integer(unsigned(angle)) * 90_000) / 180;

    --------------------------------------------------------------------
    -- Generador PWM
    --------------------------------------------------------------------
    process(clk)
    begin
        if rising_edge(clk) then
            if reset_n = '0' then
                counter <= 0;
                pwm_out <= '0';
            else
                if counter = PERIOD then
                    counter <= 0;
                else
                    counter <= counter + 1;
                end if;

                if counter < pulse_width then
                    pwm_out <= '1';
                else
                    pwm_out <= '0';
                end if;
            end if;
        end if;
    end process;

end architecture;
