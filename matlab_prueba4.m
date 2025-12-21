clear all; close all;

port = "COM9"; %ojoooo
baud = 115200;

s = serialport(port, baud, "Timeout", 1);
flush(s);

msg = input("Escribe tu mensaje: ", "s");
bytes = uint8(msg);

if numel(bytes) > 255
    bytes = bytes(1:255);
end

write(s, [uint8(numel(bytes)) bytes], "uint8");

ack = read(s, 1, "uint8");
