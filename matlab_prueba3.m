clear all, close all;

port = "COM9"; %ojito con el port que tu compu elija xd
baud = 115200;

s = serialport(port, baud, "Timeout", 1);
flush(s);

a = uint8(input("Ingresa a: "));
b = uint8(input("Ingresa b: "));

write(s, [a b], "uint8");

sum_rx = read(s, 1, "uint8");

fprintf("MATLAB: %d + %d = %d | FPGA respondió: %d\n", a, b, a+b, sum_rx);
fprintf("En LEDs verás (sum & 0xF) = %d\n", bitand(sum_rx, 15));
