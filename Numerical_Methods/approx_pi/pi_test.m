r = 30; % Sett radiusen
size = r*2; % Sett str til matrisen

sum_area = 0; % Summen av arealet
numb_x = zeros(size, size); % Lag en tom matrise
numb_y = numb_x; % La Y matrisen == X
enhets_sirkel(0, 0, r); % Tegn enhetssirkelen
hold on 
for i = 1:numel(numb_x) % Bruk numel til indexer
    numb_x(i) = (-r-r).*rand(1) + r; % Kalkuler tilfeldig x
    numb_y(i) = (-r-r).*rand(1) + r; % Kalkuler tilfeldig y
    if (sqrt(numb_x(i)^2+numb_y(i)^2) <= r) % Sjekk om punktet er innenfor radiusen eller ikke
        plot(numb_x(i), numb_y(i), "b*") % plot punktet blaatt hvis det er innenfor
        sum_area = sum_area + 1; % Legg til 1 i sum_area
    else
        plot(numb_x(i), numb_y(i), "r*") % plot punktet roedt hvis det er utenfor
    end
end

saveas(gcf, [numb_x, numb_y], "test.png")
pi_approx = 1/r^2*(sum_area);
fprintf("A:%d r:%f pi:%f\n", sum_area, r, pi_approx);
hold off