#include <iostream>
#include <string>

#include "CheckBatteryStatus.h"

using namespace std;

void PrintMessageOnConsole (const string& message)
{
   cout << message << endl;
}

void CheckWarningForGivenValue (float value, float LowerLimit, float UpperLimit, const string& UpperLimitWarningMessage, const string& LowerLimitWarningMessage)
{
    float UpperLimitTolerance = 0.05 * UpperLimit;
    float LowerLimitTolerance = 0.05 * LowerLimit;

    if (value >= UpperLimit - UpperLimitTolerance)
    	PrintMessageOnConsole(UpperLimitWarningMessage);

    if (value <= LowerLimit - LowerLimitTolerance)
    	PrintMessageOnConsole(LowerLimitWarningMessage);
}

bool checkValueInRange(float value,
		               float LowerLimit,
					   float UpperLimit,
					   const string& OutputMessage) {
    if (value < LowerLimit || value > UpperLimit) {
    	PrintMessageOnConsole(OutputMessage);
        return false;
    }
    return true;
}

bool checkTemperature (float temp)
{
	CheckWarningForGivenValue(temp, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT, "Approaching High Temperature", "Approaching Lower Temerature");

	bool TempStatus = checkValueInRange(temp, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT, "Temperature out of range");

    return TempStatus;
}

bool checkSoc (float soc)
{
	CheckWarningForGivenValue(soc, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT, "Approaching Charge Peak", "Approaching Discharge");

	bool SocStatus = checkValueInRange(soc, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT, "State of Charge out of range");
    
    return SocStatus;
}

bool checkChargeRate (float ChargeRate)
{
	CheckWarningForGivenValue(ChargeRate, CHARGE_LOWER_LIMIT, CHARGE_UPPER_LIMIT, "Approaching Peak Charge Rate", "Approaching Lower Charge Rate");

	bool ChargeStatus = checkValueInRange(ChargeRate, CHARGE_LOWER_LIMIT, CHARGE_UPPER_LIMIT, "Charge Rate out of range");
    
    return ChargeStatus;
}

bool batteryIsOk(float temperature, float soc, float ChargeRate) 
{
    bool BatteryStatus = (checkTemperature(temperature) && checkSoc(soc) && checkChargeRate(ChargeRate));

    return BatteryStatus;
}

