#include <Arduino.h>


class QauyToShip{
    public:
        void QauyToShip::update(float xPos, float yPos, float xContainer, float theta, int *xRefpoint, int*yRefpoint, int *electroMagnet);

    private:
        int step=0;
        float yLastPos = 0;
        float ySpeed =1;
        uint16_t lastTime =0;
        uint16_t failTime =0;
};

/*
class low_pass{
    public:
        low_pass(float tau);
        double update(double input);
        double update(double input,uint32_t dtime);
        void restart(double value);
    private:
        float xTau;
        uint32_t prev_time;
        double output_val;
};

class lead_lag{
    public:
        lead_lag(float a = 0, float b = 0, float k = 0);
        double update(double input);
        double update(double input,float dtime);
        void restart(double value = 0);
    private:
        float xa,xb,xk;
        float prev_error, prev_output;
        uint32_t prev_time;
};

class PID{
    public:
        PID(double Kp = 0 , double Ki = 0 , double Kd = 0 , float tau = 0);
        double update(double error);
        double update(double error,uint32_t dtime);
        void restart();
    private:
        double xKp, xKi, xKd;
        low_pass lp = low_pass(0);
        boolean dlp;
        uint32_t prev_time;
        double prev_error = 0;
        double differential = 0;
        double integral = 0;
};
*/