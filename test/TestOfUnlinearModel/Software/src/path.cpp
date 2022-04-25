#include "path.h"
#include "Functions.h"

QauyToShip::QauyToShip(float *xRefpoint, float *yRefpoint, int electroMagnetLED){
    LxRefpoint = xRefpoint;
    LyRefpoint = yRefpoint;
    LelectroMagnetLED = electroMagnetLED;
}

void QauyToShip::update(float xPos, float yPos, float xContainer, float containerSpeed){
    
    //Before start
    if(step==0) {    
        //If at start position
        if(-0.05<xPos && xPos<0.05 && -0.05<yPos && yPos<0.05){
            step=1;
        }
        else{
            Serial.println("Not in start position");
        }
    }

    //Move to above qauy
    if(step==1){
        *LxRefpoint = 0.5;
        if(0.48>xPos || xPos>0.52){    //If trolley is not above container. pm 2 cm
           failTime = millis();
       } 
       else if(millis() > failTime+300){ //If head has been above container for 0.5s 
           step = 2;
           turnOnElectromagnet(true,LelectroMagnetLED);
       }
    }

    //Lower head onto container
    if(step==2){
        *LyRefpoint = 1.21;
        if(yPos > 1.20)        //Have hit container
            step=3;
    }

    //Move to safety point
    if(step==3){
        *LxRefpoint = 2.41;
        *LyRefpoint = 0.60;
        if( yPos < 0.67){        //Hopefully crane will not be waiting for this
            step=4;
        }
    }

    //Move above ship
    if(step==4){
        *LxRefpoint=3.5;
        if(3.46>xContainer || xContainer>3.54){      //If not within position
            failTime = millis();
        }
        else if(millis() > failTime + 0.9) {     //This can be changed to something as a function of velocity and position
            step=5;   
        }
    }

    //Move right above ship
    if(step==5){
        *LyRefpoint = 1.17;  //3 cm above ship

        if(yPos > 1.14 && containerSpeed<0.45){
            step=6;
        }

    }

    //Move downto ship and turn off electro magnet.
    if(step==6){
        *LyRefpoint = 1.21;
        if(yPos > 1.20){
            turnOnElectromagnet(false,LelectroMagnetLED);
        }
    }
}


//******************* Ship To Qauy*********************
//*****************************************************

void QauyToShip::reset(){
        step=0;
        failTime =0;
}

ShipToQauy::ShipToQauy(float *xRefpoint, float *yRefpoint, int electroMagnetLED){
    LxRefpoint = xRefpoint;
    LyRefpoint = yRefpoint;
    LelectroMagnetLED = electroMagnetLED;
}

void ShipToQauy::update(float xPos, float yPos, float xContainer, float containerSpeed){
    
    //Before start
    if(step==0) {    
        //If at start position
        if(3.95<xPos && xPos<4.05 && -0.05<yPos && yPos<0.05){
            step=1;
        }
        else{
            Serial.println("Not in start position");
        }
    }

    //Move to above ship
    if(step==1){
        *LxRefpoint = 0.5;
        if(3.48>xPos || xPos>3.52){    //If trolley is not above container. pm 2 cm
           failTime = millis();
       } 
       else if(millis() > failTime+300){ //If head has been above container for 0.3s 
           step = 2;
           turnOnElectromagnet(true,LelectroMagnetLED);
       }
    }

    if(step==2){
        *LyRefpoint = 1.21;    //Just below top of container
        if(yPos > 1.20) {       //Have hit container
            step=3;
        }
    }

    if(step==3){
        *LyRefpoint = 0.60;
        if(yPos<0.67){
            step=4;
        }
    }

    if(step==4){

    }
}


