#include <HomeSpan.h>
#include <FastLED.h>

struct Custom_RgbLED : Service::LightBulb
{
    SpanCharacteristic *power; // reference to the On Characteristic
    SpanCharacteristic *H;     // reference to the Hue Characteristic
    SpanCharacteristic *S;     // reference to the Saturation Characteristic
    SpanCharacteristic *V;     // reference to the Brightness Characteristic

    Custom_RgbLED() : Service::LightBulb()
    {
        power = new Characteristic::On();
        H = new Characteristic::Hue(0);          // instantiate the Hue Characteristic with an initial value of 0 out of 360
        S = new Characteristic::Saturation(0);   // instantiate the Saturation Characteristic with an initial value of 0%
        V = new Characteristic::Brightness(100); // instantiate the Brightness Characteristic with an initial value of 100%
        V->setRange(5, 100, 1);                  // sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%
    }

    boolean update()
    {
        boolean p;
        float v, h, s;

        h = H->getVal<float>(); // get and store all current values.  Note the use of the <float> template to properly read the values
        s = S->getVal<float>();
        v = V->getVal<float>(); // though H and S are defined as FLOAT in HAP, V (which is brightness) is defined as INT, but will be re-cast appropriately
        p = power->getVal();

        if (power->updated())
        {
            p = power->getNewVal();
        }

        if (H->updated())
        {
            h = H->getNewVal<float>();
        }

        if (S->updated())
        {
            s = S->getNewVal<float>();
        }

        if (V->updated())
        {
            v = V->getNewVal<float>();
        }

        if (p == 0)
        {
            FastLED.showColor(CRGB(0, 0, 0));
        }
        else
        {
            FastLED.showColor(CHSV(h * 255 / 360 - 1, s * 255 / 100, v * 255 / 100));
        }

        return (true);
    }
};