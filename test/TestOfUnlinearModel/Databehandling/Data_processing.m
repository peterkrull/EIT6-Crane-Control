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

%Plot raw data
figure(2)
tiledlayout(2,4);
nexttile