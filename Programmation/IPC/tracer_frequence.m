data = readmatrix('frequence.dat');

nbr_cycle_ICP = data(:,1);
nbr_clk_ICP   = data(:,2);

figure;
plot(nbr_clk_ICP, 'LineWidth', 1.5);
title("Évolution de la valeur de l'ICP (ou de la fréquence % 65536 en Hz) en fonction du temps");
xlabel('Temps (s)');
ylabel('Valeur ICP ou fréquence % 65536 (Hz)');
grid on;
axis tight;
