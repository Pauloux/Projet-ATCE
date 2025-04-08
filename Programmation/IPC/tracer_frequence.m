data = readmatrix('frequence.dat');

nbr_cycle_ICP = data(:,1);
nbr_clk_ICP   = data(:,2);

figure;
plot(nbr_clk_ICP, 'LineWidth', 1.5);  
title('Fréquence');
xlabel('Temps (s)');
ylabel('Valeur ICP');  
grid on;          
axis tight;       % Ajuste l'affichage autour des données
