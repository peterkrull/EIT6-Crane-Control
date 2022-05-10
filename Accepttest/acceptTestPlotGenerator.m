data = csvread()

x0=0;
y0=0;
plotwidth=650;
height=400;

figure(1);
plot(closedLoop1.tout, closedLoop1.X, t1/10^3-21.44, xTrolley1)
yline(0.49)
yline(0.51)
xlim([0.9,4])
legend('Simulated', 'Measured')
grid on
set(gcf,'position',[x0,y0,plotwidth,height])
exportgraphics(gcf,'xl0TrolleyQTS.pdf','ContentType','vector')