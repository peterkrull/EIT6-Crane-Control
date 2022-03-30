Con3A=readtable('Tracker\3A2sekCon');
Tro3A=readtable('Tracker\3A2sekTro');

Con5A=readtable('Tracker\5A2sekCon');
Tro5A=readtable('Tracker\5A2sekTro');

Con7A=readtable('Tracker\7A1sekCon');
Tro7A=readtable('Tracker\7A1sekTro');

Con9A=readtable('Tracker\9A1sekCon');
Tro9A=readtable('Tracker\9A1sekTro');

Con5AWC=readtable('Tracker\5A2sekWCCon');
Tro5AWC=readtable('Tracker\5A2sekWCTro');



J_l = 0.14;
J_x = 0.2;
g = 9.82;
k_el = 0.71;
k_ex = 0.609;
m_l = 3.89;
m_t = 0.729;
r_l = 0.05;
r_x = 0.075;
B_l = 9.4;
B_x = 10;
sFrictionX=20;
cFrictionX=15;
sFrictionL=20.4;
cFrictionL=17.4;

if(1)
    %Simulation settings
    I_xStart=1;
    I_xEnd=3;
    I_xCurrent=3;

    I_LStart=1;
    I_LEnd=3;
    I_LCurrent=0;
    out=sim("CraneModel.slx");

    subplot(2,5,1)
    plot(out.tout,out.XContainer,Con3A.t+1,Con3A.x-0.02)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Container [m]')
    title("3 A 2 sek")
    grid on

    subplot(2,5,6)
    plot(out.tout,out.X, Tro3A.t+1,Tro3A.x)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Trolley [m]')
    grid on
end

if(1)
    %Simulation settings
    I_xStart=1;
    I_xEnd=3;
    I_xCurrent=5;
    out=sim("CraneModel.slx");

    subplot(2,5,2)
    plot(out.tout,out.XContainer,Con5A.t+1,Con5A.x-0.3)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Container [m]')
    title("5 A 2 sek")
    grid on

    subplot(2,5,7)
    plot(out.tout,out.X, Tro5A.t+1,Tro5A.x-0.2)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Trolley [m]')
    grid on
end

if(1)
    %Simulation settings
    I_xStart=1;
    I_xEnd=2;
    I_xCurrent=7;
    out=sim("CraneModel.slx");

    subplot(2,5,3)
    plot(out.tout,out.XContainer,Con7A.t+1,Con7A.x)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Container [m]')
    title("7 A 1 sek")
    grid on

    subplot(2,5,8)
    plot(out.tout,out.X, Tro7A.t+1,Tro7A.x)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Trolley [m]')
    grid on
end

if(1)
    %Simulation settings
    I_xStart=1;
    I_xEnd=2;
    I_xCurrent=9;
    out=sim("CraneModel.slx");

    subplot(2,5,4)
    plot(out.tout,out.XContainer,Con9A.t+1,Con9A.x)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Container [m]')
    title("9 A 1 sek")
    grid on

    subplot(2,5,9)
    plot(out.tout,out.X, Tro9A.t+1,Tro9A.x)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Trolley [m]')
    grid on
end


if(1)
    m_l = 0.95;

    %Simulation settings
    I_xStart=1;
    I_xEnd=3;
    I_xCurrent=5;
    out=sim("CraneModel.slx");

    subplot(2,5,5)
    plot(out.tout,out.XContainer,Con5AWC.t+1,Con5AWC.x)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Container [m]')
    title("9 A 1 sek Without container")
    grid on

    subplot(2,5,10)
    plot(out.tout,out.X, Tro5AWC.t+1, Tro5AWC.x)
    legend('Simulation','Measurement','Location','southeast')
    xlabel('time [s]')
    ylabel('x-position Trolley [m]')
    grid on
end


disp("Job done")
