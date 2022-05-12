clear
close all
clc


plotTrolley("TunedConL075mX246m.csv", "TunedConL075mX246mv2.csv")
export_fig("TunedTrolleyPositionX246cmL075cm.pdf")
plotAngle("TunedConL075mX246m.csv", "TunedConL075mX246mv2.csv")
export_fig("TunedAngleX246cmL075cm.pdf")
plotContainer("TunedConL075mX246m.csv", "TunedConL075mX246mv2.csv")
export_fig("TunedContainerPositionX246cmL075cm.pdf")


plotTrolley("TunedConL115mX246m.csv", "TunedConL115mX246mv2.csv")
export_fig("TunedTrolleyPositionX246cmL115cm.pdf")
plotAngle("TunedConL115mX246m.csv", "TunedConL115mX246mv2.csv")
export_fig("TunedAngleX246cmL115cm.pdf")
plotContainer("TunedConL115mX246m.csv", "TunedConL115mX246mv2.csv")
export_fig("TunedContainerPositionX246cmL115cm.pdf")


plotTrolley("TunedConL115mX0785m.csv", "TunedConL115mX0785mv2.csv")
export_fig("TunedTrolleyPositionX0785cmL115cm.pdf")
plotAngle("TunedConL115mX0785m.csv", "TunedConL115mX0785mv2.csv")
export_fig("TunedAngleX0785cmL115cm.pdf")
plotContainer("TunedConL115mX0785m.csv", "TunedConL115mX0785mv2.csv")
export_fig("TunedContainerPositionX0785cmL115cm.pdf")


plotTrolley("TunedConL075mX0785m.csv", "TunedConL075mX0785mv2.csv")
export_fig("TunedTrolleyPositionX0785cmL075cm.pdf")
plotAngle("TunedConL075mX0785m.csv", "TunedConL075mX0785mv2.csv")
export_fig("TunedAngleX0785cmL075cm.pdf")
plotContainer("TunedConL075mX0785m.csv", "TunedConL075mX0785mv2.csv")
export_fig("TunedContainerPositionX0785cmL075cm.pdf")




function plotContainer(test1, test2)
    data1 = readmatrix(test1);
    data1(:,1) = (data1(:,1)- data1(1,1))/1000;
    
    data2 = readmatrix(test2);
    data2(:,1) = (data2(:,1)-data2(1,1))/1000;

    figure
    plot(data1(:,1), data1(:,3))
    hold on
    plot(data2(:,1), data2(:,3))
    yline(data1(1,6)+.05,':')
    yline(data1(1,6)-.05,':')
    yline(data1(1,6))
    hold off
    xlabel("time [s]")
    ylabel("Container position [m]")
    xlim([0, 15])    
    legend("Test 1", "Test 2", "Location","south east")
end


function plotAngle(test1, test2)
    data1 = readmatrix(test1);
    data1(:,1) = (data1(:,1)- data1(1,1))/1000;
    
    data2 = readmatrix(test2);
    data2(:,1) = (data2(:,1)-data2(1,1))/1000;

    figure
    plot(data1(:,1), data1(:,5))
    hold on
    plot(data2(:,1), data2(:,5))
    hold off
    xlabel("time [s]")
    ylabel("Angle [deg]")
    xlim([0, 15])
    legend("Test 1", "Test 2")
end


function plotTrolley(test1, test2)
    data1 = readmatrix(test1);
    data1(:,1) = (data1(:,1)- data1(1,1))/1000;
    
    data2 = readmatrix(test2);
    data2(:,1) = (data2(:,1)-data2(1,1))/1000;

    figure
    plot(data1(:,1), data1(:,2))
    hold on
    plot(data2(:,1), data2(:,2))
    yline(data1(1,6)+.05,':')
    yline(data1(1,6)-.05,':')
    yline(data1(1,6))
    hold off
    xlabel("time [s]")
    ylabel("Trolley position [m]")
    xlim([0, 15])
    legend("Test 1", "Test 2", "Location","south east")
end


function export_fig(name)
    x0=0;
    y0=0;
    plotwidth=650/1.5;
    plotHeight=400/3;
    set(gcf,'position',[x0,y0,plotwidth,plotHeight])
    
    
    exportgraphics(gcf,name,'ContentType','vector')
end