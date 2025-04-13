data = readmatrix('frequence.dat');

duty_cycle    = data(:,1);
nbr_cycle_ICP = data(:,2);
nbr_clk_ICP   = data(:,3);

figure;

disp(["Nombre de mesures : ", num2str(size(nbr_clk_ICP, 1)/10)])

% Tracé de toutes les mesures de fréquence
for i = 1:(size(nbr_clk_ICP, 1)/10) - 1
    plot(1:10 ,nbr_clk_ICP(1 + i * 10:10 + i * 10), 'LineWidth', 1.5);
    hold on
end
title('Fréquence');
xlabel('Temps (s)');
ylabel('Fréquence % 65536 (Hz)');
grid on;             
axis tight;

% Calcul de la moyenne sur chaque point de la période
num_periodes = size(nbr_clk_ICP, 1)/10; % Nombre total de périodes
clk_redim = reshape(nbr_clk_ICP, 10, num_periodes); % Redimensionnement en matrice 10xN
moyenne_clk = mean(clk_redim, 2); % Calcul de la moyenne colonne par colonne

% Tracé de la moyenne
figure;
plot(1:10, moyenne_clk, 'b-', 'LineWidth', 2);
title('Valeur moyenne de ICP sur une période');
xlabel('Temps (s)');
ylabel('Fréquence % 65536 moyenne (Hz)');
grid on;
axis tight;