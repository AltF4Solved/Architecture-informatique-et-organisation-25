library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity memory is
	port
	(
		clk			: in  std_logic;
		rst			: in  std_logic;
		memread			: in  std_logic;
		memwrite		: in  std_logic;
		address1		: in  std_logic_vector (31 downto 0);
		address2		: in  std_logic_vector (31 downto 0);
		writedata		: in  std_logic_vector (31 downto 0);
		instruction		: out std_logic_vector (31 downto 0);
		readdata		: out std_logic_vector (31 downto 0)
	);
end memory;

architecture behavior of memory is
	type ramcell is array (0 to 255) of std_logic_vector (7 downto 0);
	signal ram			: ramcell;
	signal masked1, masked2		: std_logic_vector (7 downto 0);
	signal selector1, selector2	: natural range 0 to 255;
begin
	masked1 <= address1 (7 downto 2) & "00";
	masked2 <= address2 (7 downto 2) & "00";
	selector1 <= to_integer (unsigned (masked1));
	selector2 <= to_integer (unsigned (masked2));

	process (clk, rst, memread, memwrite, address1, address2, writedata)
	begin
		if (rising_edge (clk)) then
			if (rst = '1') then
				ram (  0) <= "00000111"; -- j main
				ram (  1) <= "00000000";
				ram (  2) <= "00000000";
				ram (  3) <= "00001000";
				ram (  4) <= "11111100"; -- addi $sp,$sp,-4
				ram (  5) <= "11111111";
				ram (  6) <= "10111101";
				ram (  7) <= "00100011";
				ram (  8) <= "00000000"; -- sw   $ra,0($sp)
				ram (  9) <= "00000000";
				ram ( 10) <= "10111111";
				ram ( 11) <= "10101111";
				ram ( 12) <= "00000011"; -- sra  $t2,$t2,4
				ram ( 13) <= "01010001";
				ram ( 14) <= "00001010";
				ram ( 15) <= "00000000";
				ram ( 16) <= "00000000"; -- lw   $ra,0($sp)
				ram ( 17) <= "00000000";
				ram ( 18) <= "10111111";
				ram ( 19) <= "10001111";
				ram ( 20) <= "00000100"; -- addi $sp,$sp,4
				ram ( 21) <= "00000000";
				ram ( 22) <= "10111101";
				ram ( 23) <= "00100011";
				ram ( 24) <= "00001000"; -- jr   $ra
				ram ( 25) <= "00000000";
				ram ( 26) <= "11100000";
				ram ( 27) <= "00000011";
				ram ( 28) <= "11110100"; -- addi $s0,$0,-12
				ram ( 29) <= "11111111";
				ram ( 30) <= "00010000";
				ram ( 31) <= "00100000";
				ram ( 32) <= "11111100"; -- addi $s1,$0,-4
				ram ( 33) <= "11111111";
				ram ( 34) <= "00010001";
				ram ( 35) <= "00100000";
				ram ( 36) <= "00000000"; -- addi  $t0,$s0,0
				ram ( 37) <= "00000000";
				ram ( 38) <= "00001000";
				ram ( 39) <= "00100010";
				ram ( 40) <= "00000000"; -- addi  $t1,$s1,0
				ram ( 41) <= "00000000";
				ram ( 42) <= "00101001";
				ram ( 43) <= "00100010";
				ram ( 44) <= "00100000"; -- add $s2,$s1,$s0
				ram ( 45) <= "10010000";
				ram ( 46) <= "00110000";
				ram ( 47) <= "00000010";
				ram ( 48) <= "00000000"; -- addi  $t2,$s2,0
				ram ( 49) <= "00000000";
				ram ( 50) <= "01001010";
				ram ( 51) <= "00100010";
				ram ( 52) <= "00000001"; -- jal ShiftFunction
				ram ( 53) <= "00000000";
				ram ( 54) <= "00000000";
				ram ( 55) <= "00001100";
				ram ( 56) <= "00000000"; -- addi $s0,$t0,0
				ram ( 57) <= "00000000";
				ram ( 58) <= "00010000";
				ram ( 59) <= "00100001";
				ram ( 60) <= "00000000"; -- addi $s1,$t1,0
				ram ( 61) <= "00000000";
				ram ( 62) <= "00110001";
				ram ( 63) <= "00100001";
				ram ( 64) <= "00000000"; -- addi $s2,$t2,0
				ram ( 65) <= "00000000";
				ram ( 66) <= "01010010";
				ram ( 67) <= "00100001";
				for i in 68 to 255 loop
					ram (i) <= std_logic_vector (to_unsigned (0, 8));
				end loop;
			else
				if (memwrite = '1') then
					ram (selector2 + 0) <= writedata (7 downto 0);
					ram (selector2 + 1) <= writedata (15 downto 8);
					ram (selector2 + 2) <= writedata (23 downto 16);
					ram (selector2 + 3) <= writedata (31 downto 24);
				end if;
			end if;
		end if;
	end process;
	instruction <= ram (selector1 + 3) & ram (selector1 + 2) & ram (selector1 + 1) & ram (selector1 + 0);
	with memread select
		readdata <=	std_logic_vector (to_unsigned (0, 32)) when '0',
				ram (selector2 + 3) & ram (selector2 + 2) & ram (selector2 + 1) & ram (selector2 + 0) when others;
end behavior;
