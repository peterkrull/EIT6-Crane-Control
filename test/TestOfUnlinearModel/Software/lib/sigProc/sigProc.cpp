#include "sigProc.h"

low_pass::low_pass(float tau){
    xTau = tau;
}

double low_pass::update(double input){
    uint32_t xtime = micros();
    double outsig = update(input,xtime-prev_time);
    prev_time = xtime;
    return outsig;
}

double low_pass::update(double input,uint32_t dtime){
    float a = dtime/(dtime+(xTau*1000000));
    output_val = output_val*(1-a)+input*a;
    return output_val;
}

void low_pass::restart(double value){
    output_val = value;
}

lead_lag::lead_lag(float a, float b, float k){
    xa = a;
    xb = b;
    xk = k;
}

double lead_lag::update(double input){
    uint32_t xtime = micros();
    double outsig = update(input,float(xtime-prev_time)/1e6);
    prev_time = xtime;
    return outsig;
}

double lead_lag::update(double input, float dtime){
    float output_val = (xk*(input*(1+xa*dtime)-prev_error)+prev_output)/(1+xb*(dtime));
    prev_output = output_val;
    prev_error = input;
    
    return output_val;
}

void lead_lag::restart(double value){
    prev_output = value;
    prev_error = 0;
}

PID::PID(double Kp, double Ki, double Kd, float tau){
    xKp = Kp;
    xKi = Ki;
    xKd = Kd;
    if (tau > 0){
        lp = low_pass(tau);
        dlp = true;
    } else {
        dlp = false;
    }
}

double PID::update(double error){
    uint32_t xtime = micros();
    double outsig = update(error,xtime-prev_time);
    prev_time = xtime;

    return outsig;
}

double PID::update(double error,uint32_t dtime){
    double outsig = 0;

    if (xKp){ // proportional
        outsig += xKp*error;
    }

    if (xKd && dlp){ // differential with lp
        differential = (xKd*1000000*(lp.update(error-prev_error)))/dtime;
        outsig += differential;
    } else if (xKd) { // differential
        differential = (xKd*1000000*(error-prev_error))/dtime;
        outsig += differential;
    }
    
    if (xKi){ // integral
        integral += (xKi*error*dtime/1000000);
        outsig += integral;
    }

    prev_error = error;

    return outsig;
}

forwarEuler::forwarEuler(){}

float forwarEuler::update(float input){
    output = (input - prev_input) / (micros() - prev_time);
    prev_time = micros();
    prev_input = input;
    return output*1e6;
}