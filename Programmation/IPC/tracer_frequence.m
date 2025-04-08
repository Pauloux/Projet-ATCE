data = readmatrix('frequence.dat');

nbr_cycle_ICP = data(:,1);
nbr_clk_ICP = data(:,2);

figure;
plot(nbr_clk_ICP);