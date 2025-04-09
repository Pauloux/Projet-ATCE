data = readmatrix('frequence.dat');

nbr_clk_ICP = data(:,1);
erreur = data(:,2);
commande = data(:,3);

figure;

% Fréquence
subplot(3, 1, 1);
plot(nbr_clk_ICP, 'LineWidth', 1.5);
title('Fréquence');
xlabel('Temps (s)');
ylabel('Fréquence (Hz)');
grid on;         
axis tight;      % Ajuste l'échelle automatiquement

% Erreur
subplot(3, 1, 2);
plot(erreur, 'LineWidth', 1.5);
title('Erreur');
xlabel('Temps (s)');
ylabel('Erreur (Hz)');
grid on;         
axis tight;      % Ajuste l'échelle automatiquement

% Commande
subplot(3, 1, 3);
plot(commande, 'LineWidth', 1.5);
title('Commande');
xlabel('Temps (s)');
ylabel('Commande (PWM)');
grid on;         
axis tight;      % Ajuste l'échelle automatiquement