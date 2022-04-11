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
D_theta = (s + .16);

figure(1)
rlocus(G_theta*D_theta)
gain_theta = 18;
D_theta = D_theta*gain_theta;

CL_theta =feedback(G_theta,D_theta);

%figure(2)
%margin(G_theta*D_theta)

%figure(3)
%impulse(CL_theta)

G_x = (l_P*s^2+ g)/s^2;

%figure(4)
%margin(CL_theta*G_x)

figure(5)
rlocus(CL_theta*G_x)


figure(7)
rlocus(CL_theta*G_x*(s+3)*(s+4)/s)

figure(6)
step(feedback(CL_theta*G_x,1))