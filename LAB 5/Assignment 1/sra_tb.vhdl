library IEEE;
use IEEE.std_logic_1164.ALL;

entity memory_tbsra is
end memory_tbsra;

architecture behaviour of memory_tbsra is

  component memorysra
    port (
      clk         : in  std_logic;
      rst         : in  std_logic;
      memread     : in  std_logic;
      memwrite    : in  std_logic;
      address1    : in  std_logic_vector(31 downto 0);
      address2    : in  std_logic_vector(31 downto 0);
      writedata   : in  std_logic_vector(31 downto 0);
      instruction : out std_logic_vector(31 downto 0);
      readdata    : out std_logic_vector(31 downto 0)
    );
  end component;

  signal clk         : std_logic;
  signal rst         : std_logic;
  signal memread     : std_logic := '0';
  signal memwrite    : std_logic := '0';
  signal address1    : std_logic_vector(31 downto 0) := (others => '0');
  signal address2    : std_logic_vector(31 downto 0) := (others => '0');
  signal writedata   : std_logic_vector(31 downto 0) := (others => '0');
  signal instruction : std_logic_vector(31 downto 0);
  signal readdata    : std_logic_vector(31 downto 0);

begin

  uut: memorysra
    port map (
      clk         => clk,
      rst         => rst,
      memread     => memread,
      memwrite    => memwrite,
      address1    => address1,
      address2    => address2,
      writedata   => writedata,
      instruction => instruction,
      readdata    => readdata
    );

  	clk		<=	'1' after  0 ns,
				'0' after  1 ns when clk /= '0' else '1' after  1 ns;
	
	rst <= '1' after 0 ns,
		'0' after 50 ns;
    	memread <= '0' after 0 ns,
		'1' after 62 ns;
    	memwrite <= '0' after 0 ns,
			'1' after 60 ns,
			'0' after 62 ns;
    	address1 <= (others => '0')after 0 ns,
		"00000000000000000000000000000000"after 60 ns;
    	address2 <= (others => '0');
    	writedata <= (others => '0')after 0 ns,
		"00000001000000100000001100000100"after 62 ns;


end behaviour;