%Read CSV files
data_26 = readtable('26_data.csv');
data_51 = readtable('51_data.csv');
data_77 = readtable('77_data.csv');
data_153 = readtable('153_data.csv');
data_178 = readtable('178_data.csv');
data_230 = readtable('230_data.csv');
%% 
%Calculate velocity
v_data_26 = diff(data_26.y)./diff(data_26.t);
v_data_51 = diff(data_51.y)./diff(data_51.t);
v_data_77 = diff(data_77.y)./diff(data_77.t);
v_data_153 = diff(data_153.y)./diff(data_153.t);
v_data_178 = diff(data_178.y)./diff(data_178.t);
v_data_230 = diff(data_230.y)./diff(data_230.t);

%Makes time vector for velodity
tv_data_26 = data_26.t(1:length(data_26.t)-1,1);
tv_data_51 = data_51.t(1:length(data_51.t)-1,1);
tv_data_77 = data_77.t(1:length(data_77.t)-1,1);
tv_data_153 = data_153.t(1:length(data_153.t)-1,1);
tv_data_178 = data_178.t(1:length(data_178.t)-1,1);
tv_data_230 = data_230.t(1:length(data_230.t)-1,1);

%%
%Calculate acceleration
a_data_26 = diff(v_data_26)./diff(tv_data_26);
a_data_51 = diff(v_data_51)./diff(tv_data_51);
a_data_77 = diff(v_data_77)./diff(tv_data_77);
a_data_153 = diff(v_data_153)./diff(tv_data_153);
a_data_178 = diff(v_data_178)./diff(tv_data_178);
a_data_230 = diff(v_data_230)./diff(tv_data_230);

%Makes time vector for acceleration
ta_data_26 = tv_data_26(1:length(tv_data_26)-1,1);
ta_data_51 = tv_data_51(1:length(tv_data_51)-1,1);
ta_data_77 = tv_data_77(1:length(tv_data_77)-1,1);
ta_data_153 = tv_data_153(1:length(tv_data_153)-1,1);
ta_data_178 = tv_data_178(1:length(tv_data_178)-1,1);
ta_data_230 = tv_data_230(1:length(tv_data_230)-1,1);

%%
%Make initial position, velocity and acceleration plots
%Position plots
figure(1)
t = tiledlayout(2,3);
nexttile
plot(data_26.t, data_26.y)
xlabel('Time') 
ylabel('Y-pos')
title('26')
nexttile
plot(data_51.t, data_51.y)
xlabel('Time') 
ylabel('Y-pos')
title('51')
nexttile
plot(data_77.t, data_77.y)
xlabel('Time') 
ylabel('Y-pos')
title('77')
nexttile
plot(data_153.t, data_153.y)
xlabel('Time') 
ylabel('Y-pos')
title('153')
nexttile
plot(data_178.t, data_178.y)
xlabel('Time') 
ylabel('Y-pos')
title('178')
nexttile
plot(data_230.t, data_230.y)
xlabel('Time') 
ylabel('Y-pos')
title('230')

%Velocity plots
figure(2)
t = tiledlayout(2,3);
nexttile
plot(tv_data_26, v_data_26)
xlabel('Time') 
ylabel('Velocity')
title('26')
nexttile
plot(tv_data_51, v_data_51)
xlabel('Time') 
ylabel('Velocity')
title('51')
nexttile
plot(tv_data_77, v_data_77)
xlabel('Time') 
ylabel('Velocity')
title('77')
nexttile
plot(tv_data_153, v_data_153)
xlabel('Time') 
ylabel('Velocity')
title('153')
nexttile
plot(tv_data_178, v_data_178)
xlabel('Time') 
ylabel('Velocity')
title('178')
nexttile
plot(tv_data_230, v_data_230)
xlabel('Time') 
ylabel('Velocity')
title('230')

%Acceleration plots
figure(3)
t = tiledlayout(2,3);
nexttile
plot(ta_data_26, a_data_26)
xlabel('Time') 
ylabel('Acceleration')
title('26')
nexttile
plot(ta_data_51, a_data_51)
xlabel('Time') 
ylabel('Acceleration')
title('51')
nexttile
plot(ta_data_77, a_data_77)
xlabel('Time') 
ylabel('Acceleration')
title('77')
nexttile
plot(ta_data_153, a_data_153)
xlabel('Time') 
ylabel('Acceleration')
title('153')
nexttile
plot(ta_data_178, a_data_178)
xlabel('Time') 
ylabel('Acceleration')
title('178')
nexttile
plot(ta_data_230, a_data_230)
xlabel('Time') 
ylabel('Acceleration')
title('230')

%%
%Matematisk model for system
s=tf('s');

%konstanter
ke = 2.96e-2;
tg = 1/24;
i3 = 0.7e-3;
r3 = 49e-3;
m = 0.951;
m3 = m+(i3/r3);
b = 1;

h = (ke*tg)/(r3*m3*(s+(b/m3)))

figure(4)
margin(h)

figure(5)
step(h)

%%
ke = 2.96e-2;
r = 48e-3;
m = 0.951;
i3 = 140e-3+(r^2)*m;
b = 20;
c = (ke*24)/(i3*s+b);

%plot(6)
%step(c)

%plot model with data
syms s t
% b = 11
% i3 = 140e-3;
% m3 = m+(i3/r3);
ke = 2.96e-2;
r = 48e-3;
m = 0.951;
i3 = 0.14;
b = 7;
h = (ke*24)/(s*(i3/(r*2)+(m*r)/2)+(b)/(r*2));
%h=(ke*24)/()

r = ilaplace(h*(1/s))
% 
ht = matlabFunction(r)
% 
x = linspace(0,10,200);
y_26 = ht(x)*9.9;
y_51 = ht(x)*7.45;
y_77 = ht(x)*4.9;
y_153 = ht(x)*-2.55;
y_178 = ht(x)*-5;
y_230 = ht(x)*-10;

figure(6)
t = tiledlayout(2,3);
nexttile
plot(x+2.4,y_26,tv_data_26,v_data_26)
xlabel('Time') 
ylabel('Velocity')
title('26')
nexttile
plot(x+2,y_51,tv_data_51,v_data_51)
xlabel('Time') 
ylabel('Velocity')
title('51')
nexttile
plot(x+2,y_77,tv_data_77,v_data_77)
xlabel('Time') 
ylabel('Velocity')
title('77')
nexttile
plot(x+2.8,y_153,tv_data_153,v_data_153)
xlabel('Time') 
ylabel('Velocity')
title('153')
nexttile
plot(x+6,y_178,tv_data_178,v_data_178)
xlabel('Time') 
ylabel('Velocity')
title('178')
nexttile
plot(x+2.5,y_230,tv_data_230,v_data_230)
xlabel('Time') 
ylabel('Velocity')
title('230')

% x0=0;
%    y0=0;
%    plotwidth=600;
%    height=300;
%    set(gcf,'position',[x0,y0,plotwidth,height])
%    
% exportgraphics(gcf,'normal1.pdf','ContentType','vector')
