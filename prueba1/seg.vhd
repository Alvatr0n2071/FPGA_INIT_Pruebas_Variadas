Library ieee;
use ieee.std_logic_1164.all;

---entidad---
entity seg is
port(
	digitos_in: in std_logic_vector(7 downto 0);
	mux: in std_logic_vector(3 downto 0);
	mux_out: out std_logic_vector(3 downto 0);
	digitos_out: out std_logic_vector(7 downto 0)
	);
end entity;

---arquitectura---
architecture fn of seg is
begin
mux_out <= mux;
digitos_out <= digitos_in;
end fn;
