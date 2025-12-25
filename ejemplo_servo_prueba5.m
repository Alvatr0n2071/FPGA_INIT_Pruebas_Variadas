clear all;

s = serialport("COM9", 115200);

angle = input("Ingrese ángulo (0–180): ");
angle = max(0, min(180, angle));

write(s, uint8(angle), "uint8");

fprintf("Ángulo enviado: %d°\n", angle);

clear s

