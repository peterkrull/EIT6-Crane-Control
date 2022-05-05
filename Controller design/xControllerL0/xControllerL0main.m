g = 9.82;
k_ex = 0.609;
J_x = 0.13;
m_t = 0.729;
m_l = 0.951;
r_x = 75*10^(-3);
B_x = 12;
sFrictionX=20;
cFrictionX=18;

m_1 = m_t + m_l + (J_x/(r_x^2));

s = tf('s');

G = (g*k_ex)/(s^2*m_1*g*r_x+B_x*r_x*g);
G2 = k_ex/(s*r_x*(m_1*s+B_x));

figure(1);
rlocus(G)

D = 150*(1+1/2*s);

figure(2);
rlocus(G*D)

figure(3);
rlocus(G2);

figure(4);
rlocus(G2*D);

figure(5);
Q = feedback(G2*D,1);
step(Q)

closedLoop=sim("xControllerL0sim1.slx");
  plot(closedLoop.tout, closedLoop.X)
  grid on