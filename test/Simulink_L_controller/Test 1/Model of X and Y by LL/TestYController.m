  %No movement of L direction
  down_container = readtable("container_down.csv");
  down_no_container = readtable("down.csv");
  up_container = readtable("container_up.csv");
  up_no_container = readtable("up.csv");

  %% Down with container

   %Simulation values before adjustment
  J_l = 0.2;
  J_x = 0.2;
  g = 9.82;
  k_el = 0.71;
  k_ex = 0.609;
  m_l = 3.89; %3.89 %0.95
  m_t = 0.729;
  r_l = 0.05;
  r_x = 0.075;
  B_l = 20;
  B_x = 10;
  sFrictionX=20;
  cFrictionX=15;
  sFrictionL=50;
  cFrictionL=90;
  InitWireLength=0.1; %Change
  GravityComp=1.82; %change
  InitStepValue = 0.1; %Change
  finalStepValue = 0.56; %Change
  I_xStart=1;
  I_xEnd=3;
  I_xCurrent=0;

  I_LStart=1;
  I_LEnd=3;
  I_LCurrent=0.25;
  
  settlex1 = [0 10];
  settley1 = [0.44 0.44];
  settlex2 = [0 10];
  settley2 = [0.48 0.48];

  %closedLoop1=sim("CraneModel.slx");
  figure(1)
  q = plot(closedLoop1.tout, closedLoop1.L-0.1,(down_container.Var1/1000)-25.1,down_container.Var2-0.1,1.4,0.046,'o',2.5,0.414,'o',settlex1,settley1,settlex2,settley2)
  grid on
  text(1.4,0.04,'10% t = 1.4 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(2.5,0.4,'90% t = 2.5 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(0.1,0.46+0.02,'Error band \pm 4%','HorizontalAlignment','left','VerticalAlignment','top')
  text(2.5,0.3-0.05,'Rise time = 1.10 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(2.5,0.25-0.05,'Settling time = 1.83 s','HorizontalAlignment','left','VerticalAlignment','top')
  q(3).LineWidth = 5;
  q(3).Color='#EDB120';
  q(4).LineWidth = 5;
  q(4).Color='#EDB120';
  q(5).LineWidth = 1;
  q(5).Color='black';
  q(6).LineWidth = 1;
  q(6).Color='black';

  ylim([-0.05 0.5])
  xlim([0 5])
  xlabel('Time [s]') 
  ylabel('Wire length [m]')
  legend('Simulated','Measured','Location','southeast')
 

x0=0;
   y0=0;
   plotwidth=450;
   height=350;
   set(gcf,'position',[x0,y0,plotwidth,height])
   
exportgraphics(gcf,'down_container.pdf','ContentType','vector')
%% Up with container

   %Simulation values before adjustment
  J_l = 0.2;
  J_x = 0.2;
  g = 9.82;
  k_el = 0.71;
  k_ex = 0.609;
  m_l = 3.89; %3.89 %0.95
  m_t = 0.729;
  r_l = 0.05;
  r_x = 0.075;
  B_l = 20;
  B_x = 10;
  sFrictionX=20;
  cFrictionX=15;
  sFrictionL=50;
  cFrictionL=90;
  InitWireLength=0.56; %Change
  GravityComp=-4.52; %change
  InitStepValue = 0.56; %Change
  finalStepValue = 0.1; %Change
  I_xStart=1;
  I_xEnd=3;
  I_xCurrent=0;

  I_LStart=1;
  I_LEnd=3;
  I_LCurrent=0.25;

  settlex1 = [0 10];
  settley1 = [0.08-0.1 0.08-0.1];
  settlex2 = [0 10];
  settley2 = [0.12-0.1 0.12-0.1];

  %closedLoop2=sim("CraneModel.slx");
  figure(2)
  q = plot(closedLoop2.tout, closedLoop2.L-0.1,(up_container.Var1/1000)-10.2,up_container.Var2-0.1,2.55,0.046,'o',1.29,0.414,'o',settlex1,settley1,settlex2,settley2)
  grid on
  text(2.5,0.1,'90% t = 2.55 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(1.5,0.414,'10% t = 1.29 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(0.1,0.0+0.02,'Error band \pm 4%','HorizontalAlignment','left','VerticalAlignment','top')
  text(2.5,0.3-0.05,'Rise time = 1.26 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(2.5,0.25-0.05,'Settling time = 1.97 s','HorizontalAlignment','left','VerticalAlignment','top')
  q(3).LineWidth = 5;
  q(3).Color='#EDB120';
  q(4).LineWidth = 5;
  q(4).Color='#EDB120';
  q(5).LineWidth = 1;
  q(5).Color='black';
  q(6).LineWidth = 1;
  q(6).Color='black';

  ylim([-0.05 0.5])
  xlim([0 5])
  xlabel('Time [s]') 
  ylabel('Wire length [m]')
  legend('Simulated','Measured','Location','northeast')
 

x0=0;
   y0=0;
   plotwidth=450;
   height=350;
   set(gcf,'position',[x0,y0,plotwidth,height])
   
exportgraphics(gcf,'up_container.pdf','ContentType','vector')
%% Down without container

   %Simulation values before adjustment
  J_l = 0.2;
  J_x = 0.2;
  g = 9.82;
  k_el = 0.71;
  k_ex = 0.609;
  m_l = 0.95; %3.89 %0.95
  m_t = 0.729;
  r_l = 0.05;
  r_x = 0.075;
  B_l = 20;
  B_x = 10;
  sFrictionX=20;
  cFrictionX=15;
  sFrictionL=50;
  cFrictionL=90;
  InitWireLength=0; %Change
  GravityComp=1.82; %change
  InitStepValue = 0; %Change
  finalStepValue = 1.2; %Change
  I_xStart=1;
  I_xEnd=3;
  I_xCurrent=0;

  I_LStart=1;
  I_LEnd=3;
  I_LCurrent=0.25;

  settlex1 = [0 10];
  settley1 = [0.048+1.2 0.048+1.2];
  settlex2 = [0 10];
  settley2 = [1.2-0.048 1.2-0.048];

  %closedLoop3=sim("CraneModel.slx");
  figure(3)
  q = plot(closedLoop3.tout, closedLoop3.L,(down_no_container.Var1/1000)-9.1,down_no_container.Var2,1.6,0.12,'o',3.519,1.08,'o',settlex1,settley1,settlex2,settley2)
  grid on
  text(3.2+0.3,1,'90% t = 3.52 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(1.6+0.3,0.12,'10% t = 1.6 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(0.1,1.2+0.04,'Error band \pm 4%','HorizontalAlignment','left','VerticalAlignment','top')
  text(3,0.3+0.35,'Rise time = 1.92 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(3,0.2+0.35,'Settling time = 2.9 s','HorizontalAlignment','left','VerticalAlignment','top')
  q(3).LineWidth = 5;
  q(3).Color='#EDB120';
  q(4).LineWidth = 5;
  q(4).Color='#EDB120';
  q(5).LineWidth = 1;
  q(5).Color='black';
  q(6).LineWidth = 1;
  q(6).Color='black';

  ylim([-0.05 1.3])
  xlim([0 6])
  xlabel('Time [s]') 
  ylabel('Wire length [m]')
  legend('Simulated','Measured','Location','southeast')
 

x0=0;
   y0=0;
   plotwidth=450;
   height=350;
   set(gcf,'position',[x0,y0,plotwidth,height])
   
exportgraphics(gcf,'down_no_container.pdf','ContentType','vector')
%% Up without container

   %Simulation values before adjustment
  J_l = 0.2;
  J_x = 0.2;
  g = 9.82;
  k_el = 0.71;
  k_ex = 0.609;
  m_l = 0.95; %3.89 %0.95
  m_t = 0.729;
  r_l = 0.05;
  r_x = 0.075;
  B_l = 20;
  B_x = 10;
  sFrictionX=20;
  cFrictionX=15;
  sFrictionL=50;
  cFrictionL=90;
  InitWireLength=1.2; %Change
  GravityComp=-3.5; %change
  InitStepValue = 1.2; %Change
  finalStepValue = 0; %Change
  I_xStart=1;
  I_xEnd=3;
  I_xCurrent=0;

  I_LStart=1;
  I_LEnd=3;
  I_LCurrent=0.25;

  settlex1 = [0 10];
  settley1 = [0.048 0.048];
  settlex2 = [0 10];
  settley2 = [-0.048 -0.048];

  %closedLoop4=sim("CraneModel.slx");
  figure(4)
  q = plot(closedLoop4.tout, closedLoop4.L,(up_no_container.Var1/1000)-8.7,up_no_container.Var2,3.59,0.12,'o',1.58,1.08,'o',settlex1,settley1,settlex2,settley2)
  grid on
  text(3.52,0.35,'90% t = 3.59 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(2,1.08,'10% t = 1.58 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(0.1,0.0+0.04,'Error band \pm 4%','HorizontalAlignment','left','VerticalAlignment','top')
  text(3,0.3+0.35,'Rise time = 2.01 s','HorizontalAlignment','left','VerticalAlignment','top')
  text(3,0.2+0.35,'Settling time = 2.87 s','HorizontalAlignment','left','VerticalAlignment','top')
  q(3).LineWidth = 5;
  q(3).Color='#EDB120';
  q(4).LineWidth = 5;
  q(4).Color='#EDB120';
  q(5).LineWidth = 1;
  q(5).Color='black';
  q(6).LineWidth = 1;
  q(6).Color='black';

  ylim([-0.05 1.3])
  xlim([0 6])
  xlabel('Time [s]') 
  ylabel('Wire length [m]')
  legend('Simulated','Measured','Location','northeast')
 

x0=0;
   y0=0;
   plotwidth=450;
   height=350;
   set(gcf,'position',[x0,y0,plotwidth,height])
   
exportgraphics(gcf,'up_no_container.pdf','ContentType','vector')