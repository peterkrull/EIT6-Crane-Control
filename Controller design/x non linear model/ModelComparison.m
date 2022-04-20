clear
close all
clc
run("variables.m");

testData = readmatrix('testOfControllers\19-4-2022\leadTest 19-4-2022 11-25.txt', 'CommentStyle', '//');
testTime = (testData(:,1)-testData(1,1))/1000 + 1;
testX = testData(:,2);
testXref = testData(:,3);
testAngle = testData(:,4);

Xref = testXref(1);
InitXPos = testX(1);

simulation = sim("CraneModel.slx");


%%
figure(1)
title("X-position")
plot(testTime, testX)
hold on
plot(simulation.tout, simulation.X1)
hold off
grid on

figure(2)
title("angle")
plot(testTime, testAngle)
ylim([-60 60])

figure(3)
title("Container position")
plot(testTime, testX+sin(testAngle*pi/180)*1.13)
grid on
errorBand = .064;
errorBandValue=(testXref(1)-testX(1))*errorBand;
yline(testXref + errorBandValue)
yline(testXref - errorBandValue)
%%
figure(4)
title("STFT angle")
stft(testAngle, 100)
