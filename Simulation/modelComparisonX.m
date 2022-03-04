clear 
close all
clc

test = readmatrix("..//test//x_axis_p3.csv");
nonlinearSim = sim('plant.slx', 10);


plot(out.x_pos)
