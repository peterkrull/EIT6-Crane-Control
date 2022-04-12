clear
close all
clc

s = tf('s');

g = 9.82;
l_P = 1;
M_L = 2.941;
M_T = .792;
M_H = .951;
M_TL = M_L+M_H;
J_x = 0.13;
r_x = 75e-3;
M_1 = M_T+M_L+M_H+J_x/r_x^2;
B_x = 12;
k_e = 0.609;



b = k_e/r_x;
a = M_1*l_P-M_TL*l_P;
G_theta = s/(s^3*a + s^2*B_x*l_P+s*g*M_1+g*B_x)*b;

%%
figure(1)
rlocus(G_theta)
%%

D_theta = (s + .16);

figure(235)
rlocus(G_theta*D_theta)
gain_theta = 18;
D_theta = D_theta*gain_theta;

CL_thetaDT =feedback(G_theta*D_theta,1);
CL_thetaFB =feedback(G_theta,D_theta);


figure(2)
rlocus(minreal(CL_thetaDT))
figure(3)
rlocus(minreal(CL_thetaFB))
%%

G_x = (l_P*s^2+ g)/s^2;

figure(4)
rlocus(minreal(CL_thetaFB*G_x))
figure(5)
rlocus(minreal(CL_thetaDT*G_x))

figure(6)
margin(minreal(CL_thetaDT*G_x))
title('Inner loop direct term controller outerloop openloop')

figure(7)
margin(minreal(CL_thetaFB*G_x))
%title('Inner loop feedback controller outerloop openloop')
%%

D_xDT = (1.2*s+1)/(.1716*1.2*s+1);
D_xFB = (2.414*s+1)/(.1716*2.414*s+1);

figure(8)

margin(minreal(CL_thetaDT*G_x*D_xDT))
%title('Inner loop direct term controller outerloop openloop, with controller')

figure(9)
rlocus(minreal(feedback(CL_thetaDT*G_x*D_xDT,1)))


figure(10)
margin(minreal(CL_thetaFB*G_x*D_xFB))
%title('Inner loop direct term controller outerloop openloop, with controller')

figure(11)
rlocus(minreal(feedback(CL_thetaFB*G_x*D_xFB,1)))

%%
D_x = s+.1;

figure
margin(minreal(CL_thetaFB*G_x*D_x))