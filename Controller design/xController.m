clear
close all
clc

s = tf('s');
run("x non linear model/variables.m")

l_P = InitWireLength;
b = k_ex/r_x;
a = M_1*l_P-m_l*l_P;
G_theta = -s/(s^3*a + s^2*B_x*l_P+s*g*M_1+g*B_x)*b;
H_theta = -1;

D_theta = (s + .25)*8;

InnerLoop = feedback(G_theta, D_theta*H_theta);
G_x = -(l_P*s^2+ g)/s^2;


figure(1)
rlocus(InnerLoop*G_x)
export_fig("xLoopRLocus.pdf")

figure(2)
hold on
D_x = (1 + s);
rlocus(InnerLoop*G_x*D_x)
plot(0,0,'^k',-1.3861,2.9863,'^k',-1.3861,-2.9861,'^k',-0.4560,0,'^k')
export_fig("xLoopRLocusWController.pdf")
hold off

pole(InnerLoop*G_x*D_x)

%%
figure(43)
simXGain = 1;
noGainSimulation = sim("x non linear model\CraneModel.slx");
[tout, y] = step(feedback(InnerLoop*G_x*D_x*simXGain,1),15);
plot(y,tout)
hold on
plot(noGainSimulation.tout-1, noGainSimulation.X1)
hold off
errorBand = .064;
errorBandValue=(1)*errorBand;
yline(1 + errorBandValue)
yline(1 - errorBandValue)
grid on
xlim([0 15])
xticks(0:2:15)
legend("Linear model", "Non linear model", "Location", "south east")
xlabel("Time [s]")
ylabel("Trolley position [m]")
%export_fig("xControllerStep1.pdf")

%%

figure(4353)
simXGain = 5;
noGainSimulation = sim("x non linear model\CraneModel.slx");    
[tout, y] = step(feedback(InnerLoop*G_x*D_x*simXGain,1),15);
%plot(y,tout)
hold on
plot(noGainSimulation.tout-1, noGainSimulation.X1)
hold off
errorBand = .07;
errorBandValue=(1)*errorBand;
yline(1 + errorBandValue)
yline(1 - errorBandValue)
grid on
xlim([0 15])
xticks(0:2:15)
%legend("Linear model", "Non linear model", "Location", "south east")
xlabel("Time [s]")
ylabel("Trolley position [m]")
%export_fig("xControllerStep2.pdf")


figure(3504)
plot(noGainSimulation.tout-1, noGainSimulation.XContainer)
errorBand = .07;
errorBandValue=(1)*errorBand;
yline(1 + errorBandValue)
yline(1 - errorBandValue)
grid on
xlim([0 15])
xticks(0:2:15)
%legend("Linear model", "Non linear model", "Location", "south east")
xlabel("Time [s]")
ylabel("Container position [m]")
%export_fig("xControllerStep2.pdf")



%%
figure(3)
D_x = D_x*1.8*9;

xLoop = minreal(feedback(D_x*G_x*InnerLoop,1));
pzmap(xLoop)

figure(4)
step(xLoop)



function export_fig(name)
    x0=0;
    y0=0;
    plotwidth=650/1.5;
    plotHeight=400/1.5;
    set(gcf,'position',[x0,y0,plotwidth,plotHeight])
    
    
    exportgraphics(gcf,name,'ContentType','vector')
end
