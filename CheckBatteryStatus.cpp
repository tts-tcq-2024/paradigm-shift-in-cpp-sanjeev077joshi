#include <iostream>
#include <string>

#include "CheckBatteryStatus.h"

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

void printMessage (const string& message)
{
   cout << message << endl;
}

void printwarningmessage (const string& warningmessage)
{
    cout << warningmessage << endl;
}

void CheckWarningForGivenValue (float value, float LowerLimit, float UpperLimit, const string& UpperLimitWarningMessage, const string& LowerLimitWarningMessage)
{
    float UpperLimitTolerance = 0.5 * UpperLimit;
    float LowerLimitTolerance = 0.5 * LowerLimit;

    if (value >= UpperLimit - UpperLimitTolerance)
        printMessage(UpperLimitWarningMessage);

    if (value <= LowerLimit - LowerLimitTolerance)
        printMessage(LowerLimitWarningMessage);
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
    CheckWarningForGivenValue(temp, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT, "Approaching High Temperature", Approaching Lower Temerature");
        
    return TempStatus;
}

bool checkSoc (float soc)
{
    bool SocStatus = checkValueInRange(soc, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT, "State of Charge out of range");
    CheckWarningForGivenValue(soc, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT, "Approaching Charge Peak", Approaching Discharge");
    
    return SocStatus;
}

bool checkChargeRate (float ChargeRate)
{
    bool ChargeStatus = checkValueInRange(ChargeRate, CHARGE_LOWER_LIMIT, CHARGE_UPPER_LIMIT, "Charge Rate out of range");
    CheckWarningForGivenValue(ChargeRate, CHARGE_LOWER_LIMIT, CHARGE_UPPER_LIMIT, "Approaching Peak Charge Rate", Approaching Lower Charge Rate");
    
    return ChargeStatus;
}

bool batteryIsOk(float temperature, float soc, float ChargeRate) 
{
    bool BatteryStatus = (checkTemperature(temperature) && checkSoc(soc) && checkChargeRate(ChargeRate));

    return BatteryStatus;
}
