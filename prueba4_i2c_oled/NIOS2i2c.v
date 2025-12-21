module NIOS2i2c (
    input  wire       clk_clk,
    input  wire       uart_rxd,
    output wire       uart_txd,
    output wire [3:0] leds_export,

    inout  wire       I2C_SCL,
    inout  wire       I2C_SDA
);

    wire i2c_scl_oe, i2c_sda_oe;
    wire i2c_scl_in, i2c_sda_in;

    assign i2c_scl_in = I2C_SCL;
    assign I2C_SCL    = i2c_scl_oe ? 1'b0 : 1'bz;

    assign i2c_sda_in = I2C_SDA;
    assign I2C_SDA    = i2c_sda_oe ? 1'b0 : 1'bz;

    i2c_oled_ni2 u0 (
        .clk_clk     (clk_clk),
        .i2c_sda_in  (i2c_sda_in),
        .i2c_scl_in  (i2c_scl_in),
        .i2c_sda_oe  (i2c_sda_oe),
        .i2c_scl_oe  (i2c_scl_oe),
        .leds_export (leds_export),
        .uart_rxd    (uart_rxd),
        .uart_txd    (uart_txd)
    );

endmodule
