%Load measurements without container
Down_3 = readtable('x.csv');
Down_5 = readtable('x.csv');
Down_7 = readtable('x.csv');

Up_3 = readtable('x.csv');
Up_5 = readtable('x.csv');
Up_7 = readtable('x.csv');

%Load measurements with container
Down_3_container = readtable('x.csv');
Down_5_container = readtable('x.csv');
Down_7_container = readtable('x.csv');

Up_3_container = readtable('x.csv');
Up_5_container = readtable('x.csv');
Up_7_container = readtable('x.csv');

%%
%Calculate velocity
mn1 = 1;

%Down
v_down_3 = diff(movmean(,mn1))./diff();
v_down_5 = diff(movmean(,mn1))./diff();
v_down_7 = diff(movmean(,mn1))./diff();

%Up
v_up_3 = diff(movmean(,mn1))./diff();
v_up_5 = diff(movmean(,mn1))./diff();
v_up_7 = diff(movmean(,mn1))./diff();

%Container down
v_down_3_container = diff(movmean(,mn1))./diff();
v_down_5_container = diff(movmean(,mn1))./diff();
v_down_7_container = diff(movmean(,mn1))./diff();

%Container up
v_up_3_container = diff(movmean(,mn1))./diff();
v_up_5_container = diff(movmean(,mn1))./diff();
v_up_7_container = diff(movmean(,mn1))./diff();

%Makes time vector for velodity
tv_down_3 = neg1.Var1(1:length(neg1.Var1)-1,1);
tv_down_5 = neg1.Var1(1:length(neg1.Var1)-1,1);
tv_down_7 = neg1.Var1(1:length(neg1.Var1)-1,1);

tv_up_3 = neg1.Var1(1:length(neg1.Var1)-1,1);
tv_up_3 = neg1.Var1(1:length(neg1.Var1)-1,1);
tv_up_3 = neg1.Var1(1:length(neg1.Var1)-1,1);

tv_down_3_container = neg1.Var1(1:length(neg1.Var1)-1,1);
tv_down_5_container = neg1.Var1(1:length(neg1.Var1)-1,1);
tv_down_7_container = neg1.Var1(1:length(neg1.Var1)-1,1);

tv_up_3_container = neg1.Var1(1:length(neg1.Var1)-1,1);
tv_up_5_container = neg1.Var1(1:length(neg1.Var1)-1,1);
tv_up_7_container = neg1.Var1(1:length(neg1.Var1)-1,1);

%%
%Plot raw data position
figure(1)
tiledlayout(3,4);
nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Down 3')
nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Down 5')
nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Down 7')

nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Up 4')
nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Up 5')
nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Up 7')

nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Down container 3')
nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Down container 5')
nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Down container 7')

nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Up container 3')
nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Up container 3')
nexttile
plot()
xlabel('Time') 
ylabel('Position')
title('Up container 3')