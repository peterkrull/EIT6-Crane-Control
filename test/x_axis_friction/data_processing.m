guage_data_slow = readtable("x_friction_slow.csv");
video_data_slow = readtable("x_friction_slow_video.csv");

guage_data_fast = readtable("x_friction_fast.csv");
video_data_fast = readtable("x_friction_fast_video.csv");

% It turns out friction can vary depending on speed, both increasing and
% decreasing. Depends on the material properties, and for decreasing speeds
% it might be due to a phenomenon called stick-slip, where the surfaces are
% quickly switching between static and dynamic friction.

% "Stick-slip phenomena are associated with a decrease in the COF as the sliding
% speed increases. The transition from static to sliding friction also can be
% regarded as a case where the COF decreases as sliding speed increases."

% http://www.physics.usyd.edu.au/~cross/PUBLICATIONS/30.%20FrictionvsSpeed.pdf

%%

clf(gcf)

hold on
grid on

slow_interp_time = 0:0.01:18;

% Guage
guage_data_slow_time = guage_data_slow.Var1-14;
guage_data_slow_force = movmean(guage_data_slow.Var2*9.82,1);

slow_force_interp = interp1(guage_data_slow_time,guage_data_slow_force,slow_interp_time);

% Video
video_slow_pos = sqrt(video_data_slow.x.^2 + video_data_slow.y.^2);
video_slow_vel = diff(video_slow_pos)./diff(video_data_slow.t);
video_slow_time = video_data_slow.t(1:length(video_data_slow.t)-1,1);

slow_vel_interp = interp1(video_slow_time,movmean(video_slow_vel,20),slow_interp_time);

% Calculate friction as b = f/vel
slow_fric = slow_force_interp./slow_vel_interp;
plot(slow_interp_time, movmean(slow_fric,10))

% plot(slow_interp_time,slow_force_interp,slow_interp_time,slow_vel_interp*100)

xlim([5 16])

%%


clf(gcf)

hold on
grid on

fast_interp_time = 0:0.01:9;

% Guage
guage_data_fast_time = guage_data_fast.Var1-3;
guage_data_fast_force = movmean(guage_data_fast.Var2*9.82,1);

fast_force_interp = interp1(guage_data_fast_time,guage_data_fast_force,fast_interp_time);

% Video
video_fast_pos = sqrt(video_data_fast.x.^2 + video_data_fast.y.^2);
video_fast_vel = diff(video_fast_pos)./diff(video_data_fast.t);
video_fast_time = video_data_fast.t(1:length(video_data_fast.t)-1,1);

fast_vel_interp = interp1(video_fast_time,movmean(video_fast_vel,20),fast_interp_time);

% Calculate friction as b = f/vel
fast_fric = fast_force_interp./fast_vel_interp;
plot(fast_interp_time, movmean(fast_fric,10))

% plot(fast_interp_time,fast_force_interp,fast_interp_time,fast_vel_interp*100)

xlim([4 9])

%%

clf(gcf)

hold on
grid on

FBs = 17
Bs = 0

slow_fric = ((slow_force_interp-FBs)./slow_vel_interp)-Bs;
fast_fric = ((fast_force_interp-FBs)./fast_vel_interp)-Bs;

plot(slow_interp_time, movmean(slow_fric,100))
plot(fast_interp_time, movmean(fast_fric,100))


xlim([4 16])

ylim([0 150])

%%

clf(gcf)

hold on
grid on

plot(guage_data_fast.Var1,guage_data_fast.Var2*9.82)
plot(guage_data_slow.Var1-10,guage_data_slow.Var2*9.82)

xlim([5 24])

%%

curr2pwm(10)


function p = curr2pwm(current)
    if current > 10; current = 10; end
    if current < -10; current = -10; end
    p = 10.2*current+127.5;
end