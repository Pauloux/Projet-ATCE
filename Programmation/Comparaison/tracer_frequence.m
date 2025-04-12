 fichier = fopen('Avec_PI.dat');
 premiere_ligne = fgetl(fichier);
 consigne = str2num(premiere_ligne(12:end));
 fclose(fichier);


data_sans_PI = readmatrix('Sans_PI.dat');
data_avec_PI = readmatrix('Avec_PI.dat');

frequence_sans_PI = data_sans_PI(:,2);
frequence_avec_PI = data_avec_PI(:,1);
commande_PI = data_avec_PI(:,3);

moyenne_sans_PI = mean(frequence_sans_PI)
moyenne_avec_PI = mean(frequence_avec_PI)

frequence_sans_PI = frequence_sans_PI - moyenne_sans_PI;
frequence_avec_PI = frequence_avec_PI - moyenne_avec_PI;

figure;

% Fréquence
subplot(2, 1, 1)
plot(frequence_sans_PI, 'LineWidth', 1.5, 'DisplayName', 'Sans régulation');
hold on
plot(frequence_avec_PI, 'LineWidth', 1.5, 'DisplayName', 'Avec régulation');
hold on
yline(consigne - moyenne_avec_PI, 'Linewidth', 1.5, 'DisplayName', 'Consigne');
title('Fréquence');
xlabel('Temps (s)');
xticks([0 30 60 90 120 150 180 210 240 270 300])
ylabel('Delta f (Hz)');
grid on;
lgd = legend;
lgd.Location = "northeast";
axis tight;      % Ajuste l'échelle automatiquement

subplot(2, 1, 2)
plot(commande_PI, 'LineWidth', 1.5);
title('Commande');
xlabel('Temps (s)');
ylabel('Commande');
grid on;
axis tight;