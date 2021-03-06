library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity digipixel is
port(
	Ri : in std_logic_vector(7 downto 0);
	Gi : in std_logic_vector(7 downto 0);
	Bi : in std_logic_vector(7 downto 0);
	Reset : in std_logic;
	Clock : in std_logic;
	Ci : in std_logic_vector(7 downto 0);
	Ro : out std_logic_vector(7 downto 0);
	Go : out std_logic_vector(7 downto 0);
	Bo : out std_logic_vector(7 downto 0));
end digipixel;

architecture arch of digipixel is

signal temp_X: std_logic_vector(7 downto 0);

begin
	kanavanvalitsin : process(Clock, Reset, Ci, Ri, Gi, Bi) is 
	variable temp_S : std_logic_vector(8 downto 0);
	begin
		if reset = '0' then
			temp_X <= (others => '0');
			Ro <= "00000000";
			Go <= "00000000";
			Bo <= "00000000";
		elsif clock'event and clock='1' then
			if Ci(0) = '1' then
					temp_X <= iC(6 downto 3)&"0000";
					if Ci(7) = '1' then
						if Ci(2 downto 1)="00" then 
							Ro <= Ri;
							Go <= Gi;
							Bo <= Bi;
						elsif Ci(2 downto 1)="01" then
							temp_S := std_logic_vector(unsigned('0'&Ri) + unsigned('0'&temp_X ));
							if temp_S(8)='1' then
								Ro <= "11111111";
							elsif temp_S(8)='0' then
								Ro <= temp_S(7 downto 0);
							end if;
							Go <= Gi;
							Bo <= Bi;
						elsif Ci(2 downto 1)="10" then
							temp_S := std_logic_vector(unsigned('0'&Gi) + unsigned('0'&temp_X ));
								
							if temp_S(8)='1' then
								Go <= "11111111";
							elsif temp_S(8)='0' then
								Go <= temp_S(7 downto 0);
							end if;
							Ro <= Ri;
							Bo <= Bi;
						elsif Ci(2 downto 1)="11" then
							temp_S := std_logic_vector(unsigned('0'&Bi) + unsigned('0'&temp_X ));	
							if temp_S(8)='1' then
								Bo <= "11111111";
							elsif temp_S(8)='0' then
								Bo <= temp_S(7 downto 0);
							end if;							
							Ro <= Ri;
							Go <= Gi;
						end if;
					elsif Ci(7) = '0' then
						if Ci(2 downto 1)="00" then 
							Ro <= Ri;
							Go <= Gi;
							Bo <= Bi;
						elsif Ci(2 downto 1)="01" then
							temp_S := std_logic_vector(unsigned('0'&Ri) - unsigned('0'&temp_X ));	
							if temp_S(8)='1' then
								Ro <= "11111111";
							elsif temp_S(8)='0' then
								Ro <= temp_S(7 downto 0);
							end if;
							Go <= Gi;
							Bo <= Bi;
						elsif Ci(2 downto 1)="10" then
							temp_S := std_logic_vector(unsigned('0'&Gi) - unsigned('0'&temp_X ));
								
							if temp_S(8)='1' then
								Go <= "11111111";
							elsif temp_S(8)='0' then
								Go <= temp_S(7 downto 0);
							end if;
							Ro <= Ri;
							Bo <= Bi;
						elsif Ci(2 downto 1)="11" then
							temp_S := std_logic_vector(unsigned('0'&Bi) - unsigned('0'&temp_X ));
								
							if temp_S(8)='1' then
								Bo <= "11111111";
							elsif temp_S(8)='0' then
								Bo <= temp_S(7 downto 0);
							end if;							
							Ro <= Ri;
							Go <= Gi;
						end if;
					end if;
			elsif Ci(0) = '0' then
				Ro <= Ri;
				Go <= Gi;
				Bo <= Bi;				
			end if;
		end if;
	end process;
end arch;
