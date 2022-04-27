clear
close all
clc

figure(1)
plotData("10 centimeter")
export_fig("AngleTestNoNotch10cm.pdf")

figure(2)
plotData("50 centimeter")
export_fig("AngleTestNoNotch50cm.pdf")

figure(3)
plotData("1 meter")
export_fig("AngleTestNoNotch1m.pdf")


function plotData(file)
    data1 = readmatrix(strcat(file, "\test1.csv"));
    data2 = readmatrix(strcat(file, "\test2.csv"));
    data3 = readmatrix(strcat(file, "\test3.csv"));
    
    t1 = (data1(:,1)-data1(1,1))/1000;
    t2 = (data2(:,1)-data2(1,1))/1000;
    t3 = (data3(:,1)-data3(1,1))/1000;
        
    plot(t1, data1(:,4))
    hold on
    plot(t2, data2(:,4))
    plot(t3, data3(:,4))
    hold off
    xlabel("Time [s]")
    ylabel("Angle [deg]")
    xlim([0, 10])
    
    legend("test1", "test2", "test3", "Location","southeast")
end

function export_fig(name)
    x0=0;
    y0=0;
    plotwidth=650/1.5;
    plotHeight=400/1.5;
    set(gcf,'position',[x0,y0,plotwidth,plotHeight])
    
    
    exportgraphics(gcf,name,'ContentType','vector')
end