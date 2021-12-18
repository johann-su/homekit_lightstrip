#include <FastLED.h>
#include <HomeSpan.h>

//////////////////////////////////
//   DEVICE-SPECIFIC SERVICES   //
//////////////////////////////////

struct Custom_Identify : Service::AccessoryInformation
{
    int nBlinks;                  // number of times to blink built-in LED in identify routine
    SpanCharacteristic *identify; // reference to the Identify Characteristic

    Custom_Identify(const char *name, const char *manu, const char *sn, const char *model, const char *version, int nBlinks) : Service::AccessoryInformation()
    {
        new Characteristic::Name(name); // create all the required Characteristics with values set based on above arguments
        new Characteristic::Manufacturer(manu);
        new Characteristic::SerialNumber(sn);
        new Characteristic::Model(model);
        new Characteristic::FirmwareRevision(version);
        identify = new Characteristic::Identify(); // store a reference to the Identify Characteristic for use below

        this->nBlinks = nBlinks; // store the number of times to blink the LED
    }

    boolean update()
    {
        for (int i = 0; i < nBlinks; i++)
        {
            FastLED.showColor(CRGB(255, 255, 255));
            FastLED.delay(250);
            FastLED.showColor(CRGB(0, 0, 0));
            FastLED.delay(250);
        }

        return (true); // return true
    }
};