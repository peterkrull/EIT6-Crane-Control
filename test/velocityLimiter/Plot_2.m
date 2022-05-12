clf
close all

data1 = readtable('test_data_p1mps.csv');
data2 = readtable('test_data_p2mps.csv');
data3 = readtable('test_data_p3mps.csv');
data4 = readtable('test_data_p4mps.csv');
data5 = readtable('test_data_p5mps.csv');
data6 = readtable('test_data_p6mps.csv');
data7 = readtable('test_data_p7mps.csv');

data_verify_1 = readtable('test_data_p6mps_verify1.csv');
data_verify_2 = readtable('test_data_p6mps_verify2.csv');
data_verify_3 = readtable('test_data_p6mps_verify3.csv');
data_verify_4 = readtable('test_data_p6mps_verify4.csv');
%Time micros, pos-y, velocity-y, pwm-y, actual-current-y-driver, limit

timeFix = 1000000;

%% Calculate currents %%
current_actual_1 = 0.02441406250*data1.Var5-10;
current_demanded_1 = (data1.Var4-125.5)/10.2;

current_actual_2 = 0.02441406250*data2.Var5-10;
current_demanded_2 = (data2.Var4-125.5)/10.2;

current_actual_3 = 0.02441406250*data3.Var5-10;
current_demanded_3 = (data3.Var4-125.5)/10.2;

current_actual_4 = 0.02441406250*data4.Var5-10;
current_demanded_4 = (data4.Var4-125.5)/10.2;

current_actual_5 = 0.02441406250*data5.Var5-10;
current_demanded_5 = (data5.Var4-125.5)/10.2;

current_actual_6 = 0.02441406250*data6.Var5-10;
current_demanded_6 = (data6.Var4-125.5)/10.2;

current_actual_7 = 0.02441406250*data7.Var5-10;
current_demanded_7 = (data7.Var4-125.5)/10.2;

current_actual_verify_1 = 0.02441406250*data_verify_1.Var5-10;
current_demanded_verify_1 = (data_verify_1.Var4-125.5)/10.2;

current_actual_verify_2 = 0.02441406250*data_verify_2.Var5-10;
current_demanded_verify_2 = (data_verify_2.Var4-125.5)/10.2;

current_actual_verify_3 = 0.02441406250*data_verify_3.Var5-10;
current_demanded_verify_3 = (data_verify_3.Var4-125.5)/10.2;

current_actual_verify_4 = 0.02441406250*data_verify_4.Var5-10;
current_demanded_verify_4 = (data_verify_4.Var4-125.5)/10.2;


%% Plot actual current, demanded current as function of time %%
figure(1)
subplot(3,3,1)
plot(data1.Var1/timeFix, current_demanded_1, data1.Var1/timeFix, current_actual_1);
ylim([-11 11])
title('Velocity limit 0.1 m/s')
xlabel('Time [s]') 
ylabel('Current [A]') 
%legend('demanded','actual','Location','southeast')

subplot(3,3,2)
plot(data2.Var1/timeFix, current_demanded_2, data2.Var1/timeFix, current_actual_2);
ylim([-11 11])
title('Velocity limit 0.2 m/s')
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(3,3,3)
plot(data3.Var1/timeFix, current_demanded_3, data3.Var1/timeFix, current_actual_3);
ylim([-11 11])
title('Velocity limit 0.3 m/s')
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(3,3,4)
plot(data4.Var1/timeFix, current_demanded_4, data4.Var1/timeFix, current_actual_4);
ylim([-11 11])
title('Velocity limit 0.4 m/s')
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(3,3,5)
plot(data5.Var1/timeFix, current_demanded_5, data5.Var1/timeFix, current_actual_5);
ylim([-11 11])
title('Velocity limit 0.5 m/s')
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(3,3,6)
plot(data6.Var1/timeFix, current_demanded_6, data6.Var1/timeFix, current_actual_6);
ylim([-11 11])
title('Velocity limit 0.6 m/s')
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(3,3,8)
plot(data7.Var1/timeFix, current_demanded_7, data7.Var1/timeFix, current_actual_7);
ylim([-11 11])
title('Velocity limit 0.7 m/s')
xlabel('Time [s]') 
ylabel('Current [A]') 

x0=0;
   y0=0;
   plotwidth=600;
   height=500;
   set(gcf,'position',[x0,y0,plotwidth,height])

exportgraphics(gcf,'Plots_velocity_test.pdf','ContentType','vector')

figure(2)
subplot(2,2,1)
plot(data_verify_1.Var1/timeFix, current_demanded_verify_1, data_verify_1.Var1/timeFix, current_actual_verify_1)
title('Without container')
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(2,2,2)
plot(data_verify_2.Var1/timeFix, current_demanded_verify_2, data_verify_2.Var1/timeFix, current_actual_verify_2)
title('With container')
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(2,2,3)
plot(data_verify_3.Var1/timeFix, current_demanded_verify_3, data_verify_3.Var1/timeFix, current_actual_verify_3)
title('With container')
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(2,2,4)
plot(data_verify_4.Var1/timeFix, current_demanded_verify_4, data_verify_4.Var1/timeFix, current_actual_verify_4)
title('With container')
xlabel('Time [s]') 
ylabel('Current [A]') 

x0=0;
   y0=0;
   plotwidth=600;
   height=500;
   set(gcf,'position',[x0,y0,plotwidth,height])

exportgraphics(gcf,'Plots_velocity_test_verify.pdf','ContentType','vector')

figure(3)
subplot(2,1,1)
plot(data6.Var1/timeFix, current_demanded_6, data6.Var1/timeFix, current_actual_6);
ylim([-11 11])
title('Velocity limit 0.6 m/s')
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(2,1,2)
plot(data7.Var1/timeFix, current_demanded_7, data7.Var1/timeFix, current_actual_7);
ylim([-11 11])
title('Velocity limit 0.7 m/s')
xlabel('Time [s]') 
ylabel('Current [A]') 

x0=0;
   y0=0;
   plotwidth=600;
   height=500;
   set(gcf,'position',[x0,y0,plotwidth,height])

exportgraphics(gcf,'Plots_velocity_test_main.pdf','ContentType','vector')

figure(4)
plot(data6.Var1/timeFix-28-0.5, current_demanded_6, data6.Var1/timeFix-28-0.5, current_actual_6);
ylim([-11 11])
xlim([0 3])
xlabel('Time [s]') 
ylabel('Current [A]') 
grid on
legend('Commanded','Actual','Location','southwest')

x0=0;
   y0=0;
   plotwidth=300;
   height=200;
   set(gcf,'position',[x0,y0,plotwidth,height])

exportgraphics(gcf,'Plots_velocity_test_main_1.pdf','ContentType','vector')

figure(5)
plot(data7.Var1/timeFix-32.7-0.5, current_demanded_7, data7.Var1/timeFix-32.7-0.5, current_actual_7);
ylim([-11 11])
xlim([0 3])
xlabel('Time [s]') 
ylabel('Current [A]') 
grid on
legend('Commanded','Actual','Location','southwest')
x = [0.8,0.8];
y = [0.42,0.52];
annotation('textarrow',x,y,'String','Unwanted ');
x1 = [0.8,0.8];
y1 = [0.32,0.22];
annotation('textarrow',x1,y1);

x0=0;
   y0=0;
   plotwidth=300;
   height=200;
   set(gcf,'position',[x0,y0,plotwidth,height])

exportgraphics(gcf,'Plots_velocity_test_main_2.pdf','ContentType','vector')

figure(6)
subplot(2,1,1)
plot(data6.Var1/timeFix,data6.Var3);
%ylim([-11 11])
xlabel('Time [s]') 
ylabel('Current [A]') 

subplot(2,1,2)
plot(data7.Var1/timeFix,data7.Var3);
%ylim([-11 11])
xlabel('Time [s]') 
ylabel('Current [A]') 

figure(7)
plot(data6.Var1/timeFix-28-0.5, data6.Var3);
ylim([-0.1 0.8])
xlim([0 3])
xlabel('Time [s]') 
ylabel('Velocity [m/s]') 
grid on
%legend('Commanded','Actual','Location','southwest')

x0=0;
   y0=0;
   plotwidth=300;
   height=200;
   set(gcf,'position',[x0,y0,plotwidth,height])

exportgraphics(gcf,'Plots_velocity_test_main_1_vel.pdf','ContentType','vector')

figure(8)
plot(data7.Var1/timeFix-32.7-0.5, data7.Var3);
ylim([-0.1 0.8])
xlim([0 3])
xlabel('Time [s]') 
ylabel('Velocity [m/s]') 
grid on
%legend('Commanded','Actual','Location','southwest')

x0=0;
   y0=0;
   plotwidth=300;
   height=200;
   set(gcf,'position',[x0,y0,plotwidth,height])

exportgraphics(gcf,'Plots_velocity_test_main_2_vel.pdf','ContentType','vector')
