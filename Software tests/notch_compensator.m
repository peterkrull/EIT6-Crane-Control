s = tf('s');

w = 2.33*2*pi;
z = 0.01;

D_theta_notch = (s^2+s*2*z*w+w^2)/(s+w)^2;

D_lp = (1/(s+1))

Dz = c2d(D_theta_notch,0.01,'zoh')

Dz.Numerator
Dz.Denominator

impulse(Dz,1)