library ieee;
use ieee.std_logic_1164.all;

entity servo_ua_top is
    port (
        clk_50   : in  std_logic;
        reset_n  : in  std_logic;

        -- UART
        uart_rx  : in  std_logic;
        uart_tx  : out std_logic;

        -- I2C OLED (pines físicos)
        i2c_sda  : inout std_logic;
        i2c_scl  : inout std_logic;

        -- Servo
        servo_pwm : out std_logic
    );
end entity;

architecture rtl of servo_ua_top is

    ------------------------------------------------------------------
    -- Señales internas I2C (desde IP)
    ------------------------------------------------------------------
    signal sda_in  : std_logic;
    signal sda_oe  : std_logic;
    signal scl_in  : std_logic;
    signal scl_oe  : std_logic;

    ------------------------------------------------------------------
    -- Señal ángulo desde PIO
    ------------------------------------------------------------------
    signal servo_angle : std_logic_vector(7 downto 0);

    ------------------------------------------------------------------
    -- Componentes
    ------------------------------------------------------------------
    component pwm
        port (
            clk     : in  std_logic;
            reset_n : in  std_logic;
            angle   : in  std_logic_vector(7 downto 0);
            pwm_out : out std_logic
        );
    end component;

    component servo_ua
        port (
				clk_clk                          : in  std_logic                    := '0'; --                        clk.clk
				reset_reset_n                    : in  std_logic                    := '0'; --                      reset.reset_n
            uart_0_external_connection_rxd      : in  std_logic;
            uart_0_external_connection_txd      : out std_logic;

            pio_0_external_connection_export : out std_logic_vector(7 downto 0);

            i2c_0_i2c_serial_sda_in    : in  std_logic;
            i2c_0_i2c_serial_sda_oe    : out std_logic;
            i2c_0_i2c_serial_scl_in    : in  std_logic;
            i2c_0_i2c_serial_scl_oe    : out std_logic
        );
    end component;

begin

    ------------------------------------------------------------------
    -- Open-drain I2C (OBLIGATORIO)
    ------------------------------------------------------------------
    i2c_sda <= '0' when sda_oe = '1' else 'Z';
    sda_in  <= i2c_sda;

    i2c_scl <= '0' when scl_oe = '1' else 'Z';
    scl_in  <= i2c_scl;

    ------------------------------------------------------------------
    -- Nios II system
    ------------------------------------------------------------------
    U_NIOS : servo_ua
        port map (
            clk_clk       => clk_50,
            reset_reset_n => reset_n,

            uart_0_external_connection_rxd      => uart_rx,
            uart_0_external_connection_txd      => uart_tx,

            pio_0_external_connection_export => servo_angle,

            i2c_0_i2c_serial_sda_in    => sda_in,
            i2c_0_i2c_serial_sda_oe    => sda_oe,
            i2c_0_i2c_serial_scl_in    => scl_in,
            i2c_0_i2c_serial_scl_oe    => scl_oe
        );

    ------------------------------------------------------------------
    -- PWM Servo (hardware puro)
    ------------------------------------------------------------------
    U_PWM : pwm
        port map (
            clk     => clk_50,
            reset_n => reset_n,
            angle   => servo_angle,
            pwm_out => servo_pwm
        );

end architecture;
