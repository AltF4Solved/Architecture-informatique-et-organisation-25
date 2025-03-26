library IEEE;
use IEEE.std_logic_1164.all;

entity control is
	port
	(
		instruction		: in  std_logic_vector (5 downto 0);
		funct			: in  std_logic_vector (5 downto 0);
		branch			: out std_logic_vector (1 downto 0);
		jal_select		: out std_logic;
		regdst			: out std_logic;
		memread			: out std_logic;
		memtoreg		: out std_logic;
		aluop			: out std_logic_vector (2 downto 0);
		memwrite		: out std_logic;
		alusrc			: out std_logic;
		regwrite		: out std_logic
	);
end control;

architecture behavior of control is
begin
	process (instruction, funct)
	begin
		case instruction is
			when "000000" =>		-- add, addu, and, nor, or, sll, srl, sub, subu, xor, jr, sra
				regdst <= '1';
				if (funct = "001000") then
					branch <= "10";
				else
					branch <= "00";
				end if;
				jal_select <= '0';
				memread <= '0';
				memtoreg <= '0';
				aluop <= "000";
				memwrite <= '0';
				alusrc <= '0';
				regwrite <= '1';
			when "000001" =>		-- bgez, bltz
				jal_select <= '0';
				regdst <= '0';
				branch <= "11";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "110";
				memwrite <= '0';
				alusrc <= '0';
				regwrite <= '0';
			when "000010" =>		-- j
				jal_select <= '0';
				regdst <= '0';
				branch <= "01";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "000";
				memwrite <= '0';
				alusrc <= '0';
				regwrite <= '0';
			when "000011" =>		-- jal
				jal_select <= '1';
				regdst <= '0';
				branch <= "01";		-- same as j, because works similar
				memread <= '0';
				memtoreg <= '0';	-- set to 0, so we can write 
				aluop <= "000";		-- set to 0, same as j
				memwrite <= '0';	-- set to 0, because we are not writing to memory
				alusrc <= '0';
				regwrite <= '1';	-- set to 1, because we are writing to a register
			when "000100" =>		-- beq
				jal_select <= '0';
				regdst <= '0';
				branch <= "11";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "111";
				memwrite <= '0';
				alusrc <= '0';
				regwrite <= '0';
			when "000101" =>		-- bne
				jal_select <= '0';
				regdst <= '0';
				branch <= "11";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "111";
				memwrite <= '0';
				alusrc <= '0';
				regwrite <= '0';
			when "000110" =>		-- blez
				jal_select <= '0';
				regdst <= '0';
				branch <= "11";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "111";
				memwrite <= '0';
				alusrc <= '0';
				regwrite <= '0';
			when "000111" =>		-- bgtz
				jal_select <= '0';
				regdst <= '0';
				branch <= "11";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "111";
				memwrite <= '0';
				alusrc <= '0';
				regwrite <= '0';
			when "001000" =>		-- addi
				jal_select <= '0';
				regdst <= '0';
				branch <= "00";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "001";
				memwrite <= '0';
				alusrc <= '1';
				regwrite <= '1';
			when "001001" =>		-- addiu
				jal_select <= '0';
				regdst <= '0';
				branch <= "00";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "001";
				memwrite <= '0';
				alusrc <= '1';
				regwrite <= '1';
			when "001100" =>		-- andi
				jal_select <= '0';
				regdst <= '0';
				branch <= "00";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "010";
				memwrite <= '0';
				alusrc <= '1';
				regwrite <= '1';
			when "001101" =>		-- ori
				jal_select <= '0';
				regdst <= '0';
				branch <= "00";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "011";
				memwrite <= '0';
				alusrc <= '1';
				regwrite <= '1';
			when "001110" =>		-- xori
				jal_select <= '0';
				regdst <= '0';
				branch <= "00";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "100";
				memwrite <= '0';
				alusrc <= '1';
				regwrite <= '1';
			when "001111" =>		-- lui
				jal_select <= '0';
				regdst <= '0';
				branch <= "00";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "101";
				memwrite <= '0';
				alusrc <= '1';
				regwrite <= '1';
			when "100011" =>		-- lw
				jal_select <= '0';
				regdst <= '0';
				branch <= "00";
				memread <= '1';
				memtoreg <= '1';
				aluop <= "001";
				memwrite <= '0';
				alusrc <= '1';
				regwrite <= '1';
			when "101011" =>		-- sw
				jal_select <= '0';
				regdst <= '0';
				branch <= "00";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "001";
				memwrite <= '1';
				alusrc <= '1';
				regwrite <= '0';
			when others =>
				jal_select <= '0';
				regdst <= '0';
				branch <= "00";
				memread <= '0';
				memtoreg <= '0';
				aluop <= "000";
				memwrite <= '0';
				alusrc <= '0';
				regwrite <= '0';
		end case;
	end process;
end behavior;





