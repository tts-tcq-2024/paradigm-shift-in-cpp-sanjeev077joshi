#include <iostream>
#include <string>

using namespace std;

enum battery_params
{
    TEMP_LOWER_LIMIT   = 0,
    TEMP_UPPER_LIMIT   = 45,
    SOC_LOWER_LIMIT    = 20,
    SOC_UPPER_LIMIT    = 80,
    CHARGE_LOWER_LIMIT = 0,
    CHARGE_UPPER_LIMIT = 1
};

float TEMP_TOLERANCE   = 0.5 * TEMP_UPPER_LIMIT;
float SOC_TOLERANCE    = 0.5 * SOC_UPPER_LIMIT;
float CHARGE_TOLERANCE = 0.5 * CHARGE_UPPER_LIMIT;

void printMessage (const string& message)
{
   cout<<message<<endl;
}

bool checkValueInRange ( float value, float LowerLimit, float UpperLimit, const string& OutputMessage)
{
   if ( value < LowerLimit || value > UpperLimit)
   {
     printMessage(OutputMessage);
     return false;
   }

    return true;
}

bool checkTemperature (float temp)
{
    bool TempStatus = checkValueInRange(temp, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT, "Temperature out of range");
    return TempStatus;
}

bool checkSoc (float soc)
{
    bool SocStatus = checkValueInRange(soc, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT, "State of Charge out of range");
    return SocStatus;
}

bool checkChargeRate (float ChargeRate)
{
    bool ChargeStatus = checkValueInRange(ChargeRate, CHARGE_LOWER_LIMIT, CHARGE_UPPER_LIMIT, "Charge Rate out of range");
    return ChargeStatus;
}

bool batteryIsOk(float temperature, float soc, float ChargeRate) 
{
    bool BatteryStatus = (checkTemperature(temperature) && checkSoc(soc) && checkChargeRate(ChargeRate));

    return BatteryStatus;
}
