data1QTS = csvread('1QTS.csv');
data8QTS = csvread('8QTS.csv');
data10QTS = csvread('10QTS.csv');
data13QTS = csvread('13QTS.csv');

t1QTS = data1QTS(:,1);
t8QTS = data8QTS(:,1);
t10QTS = data10QTS(:,1);
t13QTS = data13QTS(:,1);

x1QTS1 = data1QTS(:,2);
x8QTS1 = data8QTS(:,2);
x10QTS1 = data10QTS(:,2);
x13QTS1 = data13QTS(:,2);

y1QTS1 = data1QTS(:,3);
y8QTS1 = data8QTS(:,3);
y10QTS1 = data10QTS(:,3);
y13QTS1 = data13QTS(:,3);

x1QTS2 = data1QTS(:,4);
x8QTS2 = data8QTS(:,4);
x10QTS2 = data10QTS(:,4);
x13QTS2 = data13QTS(:,4);

y1QTS2 = data1QTS(:,5);
y8QTS2 = data8QTS(:,5);
y10QTS2 = data10QTS(:,5);
y13QTS2 = data13QTS(:,5);

angle1QTS = atan((x1QTS2-x1QTS1)./(y1QTS2-(y1QTS1)))*180/pi;
angle8QTS = atan((x8QTS2-x8QTS1)./(y8QTS2-(y8QTS1)))*180/pi;
angle10QTS = atan((x10QTS2-x10QTS1)./(y10QTS2-(y10QTS1)))*180/pi;
angle13QTS = atan((x13QTS2-x13QTS1)./(y13QTS2-(y13QTS1)))*180/pi;

x0=0;
y0=0;
plotwidth=650;
height=400;

figure(1)
plot(t1QTS(5:end),angle1QTS(5:end));
grid on
set(gcf,'position',[x0,y0,plotwidth,height])
exportgraphics(gcf,'angle1QTS.pdf','ContentType','vector')

figure(2)
plot(t8QTS(5:end),angle8QTS(5:end));
grid on
set(gcf,'position',[x0,y0,plotwidth,height])
exportgraphics(gcf,'angle8QTS.pdf','ContentType','vector')

figure(3)
plot(t10QTS(5:end),angle10QTS(5:end));
grid on
set(gcf,'position',[x0,y0,plotwidth,height])
exportgraphics(gcf,'angle10QTS.pdf','ContentType','vector')

figure(4)
plot(t13QTS(5:end),angle13QTS(5:end));
grid on
set(gcf,'position',[x0,y0,plotwidth,height])
exportgraphics(gcf,'angle13QTS.pdf','ContentType','vector')
