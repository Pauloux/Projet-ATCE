data = readmatrix('frequence.dat');

duty_cycle    = data(:,1);
nbr_cycle_ICP = data(:,2);
nbr_clk_ICP   = data(:,3);

figure;

% Duty cycle
subplot(2, 1, 1);
plot(duty_cycle/1023*100, 'LineWidth', 1.5);
title('Duty cycle');
xlabel('Temps (s)');
ylabel('Duty cycle (%)');
grid on;         
axis tight;      % Ajuste l'échelle automatiquement autour des valeurs de duty_cycle

% Fréquence
subplot(2, 1, 2);
plot(nbr_clk_ICP, 'LineWidth', 1.5);
title('Fréquence');
xlabel('Temps (s)');
ylabel('Valeur ICP');   
grid on;             
axis tight;               % Ajuste l'échelle automatiquement autour des valeurs de nbr_clk_ICP
