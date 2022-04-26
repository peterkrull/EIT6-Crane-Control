#include <Arduino.h>

class QauyToShip{
    public:
        QauyToShip(float *xRefpoint, float *yRefpoint, int electroMagnetLED);
        void update(float xPos, float yPos, xy_float  *ref , float xContainer, float containerSpeed);
        void reset();

    private:
        int step=0;
        uint16_t failTime =0;
        float *LxRefpoint=0;
        float *LyRefpoint=0;
        int LelectroMagnetLED=0;
};



class ShipToQauy{
    public:
        ShipToQauy(float *xRefpoint, float *yRefpoint, int electroMagnetLED);
        void update(float xPos, float yPos, float xContainer, float containerSpeed);
        void reset();

    private:
        int step=0;
        uint16_t failTime =0;
        uint16_t failtimm1=0;
        float *LxRefpoint=0;
        float *LyRefpoint=0;
        int LelectroMagnetLED=0;
};