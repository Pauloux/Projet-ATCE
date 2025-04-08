data = readmatrix('frequence.dat');

duty_cycle = data(:,1);
nbr_cycle_ICP = data(:,2);
nbr_clk_ICP = data(:,3);

figure;

subplot(2, 1, 1);
plot(duty_cycle);
title('Duty cycle');

subplot(2, 1, 2);
plot(nbr_clk_ICP);
title('Fréquence')