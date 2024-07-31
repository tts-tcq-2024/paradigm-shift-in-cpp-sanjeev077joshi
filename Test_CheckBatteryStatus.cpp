#include <iostream>
#include <string>
#include <assert.h>

#include "CheckBatteryStatus.h"

using namespace std;

bool checkValueInRangeMock(float value, float LowerLimit, float UpperLimit, const string& OutputMessage, void (*messageHandler)(const string&));

void CheckWarningForGivenValueMock (float value, float LowerLimit, float UpperLimit, const string& UpperLimitWarningMessage, const string& LowerLimitWarningMessage, void (*messageHandler)(const string&));

// Test double for message handling
string capturedMessage;
void MockPrintMessage(const string& message) {
    capturedMessage = message;
}


bool checkValueInRangeMock(float value,
		           float LowerLimit,
			   float UpperLimit,
			   const string& OutputMessage,
			   void (*messageHandler)(const string&)) 
{
        if (value < LowerLimit || value > UpperLimit) 
	{
	    MockPrintMessage(OutputMessage);
	    return false;
        }
        return true;
}

void CheckWarningForGivenValueMock (float value,
		                    float LowerLimit,
				    float UpperLimit,
				    const string& UpperLimitWarningMessage,
				    const string& LowerLimitWarningMessage,
				    void (*messageHandler)(const string&))
{
    float UpperLimitTolerance = 0.05 * UpperLimit;
    float LowerLimitTolerance = 0.05 * LowerLimit;

    if (value >= UpperLimit - UpperLimitTolerance)
    	MockPrintMessage(UpperLimitWarningMessage);

    if (value <= LowerLimit + LowerLimitTolerance)
    	MockPrintMessage(LowerLimitWarningMessage);
}

// Unit test function
void test_checkValueInRange() {
// Declare a function pointer
    void (*messageHandler)(const string&);

    // Assign the function pointer to the mock print function
    messageHandler = MockPrintMessage;

    // Test case 1: value is within range
    capturedMessage.clear();
    bool result1 = checkValueInRangeMock(10, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT, "Temperature Within Range", messageHandler);
    assert(result1 == true);
    assert(capturedMessage.empty());

    // Test case 2: Temp value is out of range
    capturedMessage.clear();
    bool result2 = checkValueInRangeMock(50, TEMP_LOWER_LIMIT, TEMP_UPPER_LIMIT, "Temperature Out Of Range", messageHandler);
    assert(result2 == false);
    assert(capturedMessage == "Temperature Out Of Range");

    // Test case 3: SOC value is range
    capturedMessage.clear();
    bool result3 = checkValueInRangeMock(50, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT, "SOC Value in Range", messageHandler);
    assert(result1 == true);
    assert(capturedMessage.empty());

    // Test case 4: Soc value is out of range
    capturedMessage.clear();
    bool result4 = checkValueInRangeMock(100, SOC_LOWER_LIMIT, SOC_UPPER_LIMIT, "State of Charge out of range", messageHandler);
    assert(result2 == false);
    assert(capturedMessage == "State of Charge out of range");

    // Test case 5: Charge value is out of range
    capturedMessage.clear();
    bool result5 = checkValueInRangeMock(0.5, CHARGE_LOWER_LIMIT, CHARGE_UPPER_LIMIT, "Charge in Range", messageHandler);
    assert(result1 == true);
    assert(capturedMessage.empty());

    // Test case 6: Charge value is out of range
    capturedMessage.clear();
    bool result6 = checkValueInRangeMock(-1, CHARGE_LOWER_LIMIT, CHARGE_UPPER_LIMIT, "Charge Rate out of range", messageHandler);
    assert(result2 == false);
    assert(capturedMessage == "Charge Rate out of range");

}


void test_CheckWarningForGivenValue() {

    void (*messageHandler)(const string&);

    // Assign the function pointer to the mock print function
    messageHandler = MockPrintMessage;

    // Test case 1: Check for Hign Temperature Warning
    capturedMessage.clear();
    CheckWarningForGivenValueMock(44, TEMP_LOWER_LIMIT , TEMP_UPPER_LIMIT,"Approaching High Temperature","Approaching Low Temperature", messageHandler);
    assert(capturedMessage == "Approaching High Temperature");

    // Test case 2 : Check for Low Temperature Warning Message
    capturedMessage.clear();
    CheckWarningForGivenValueMock(0, TEMP_LOWER_LIMIT , TEMP_UPPER_LIMIT,"Approaching High Temperature","Approaching Low Temperature", messageHandler);
    assert(capturedMessage == "Approaching Low Temperature");

    /* Test cases to check SOC warnings */
    capturedMessage.clear();
    CheckWarningForGivenValueMock(79, SOC_LOWER_LIMIT , SOC_UPPER_LIMIT,"Approaching Charge Peak","Approaching Discharge", messageHandler);
    assert(capturedMessage == "Approaching Charge Peak");

    capturedMessage.clear();
    CheckWarningForGivenValueMock(20, SOC_LOWER_LIMIT , SOC_UPPER_LIMIT,"Approaching Charge Peak","Approaching Discharge", messageHandler);
    assert(capturedMessage == "Approaching Discharge");

    /* Test cases to check Charge warnings */
    capturedMessage.clear();
    CheckWarningForGivenValueMock(0.79, CHARGE_LOWER_LIMIT , CHARGE_UPPER_LIMIT,"Approaching Peak Charge Rate", "Approaching Lower Charge Rate", messageHandler);
    assert(capturedMessage == "Approaching Peak Charge Rate");

    capturedMessage.clear();
    CheckWarningForGivenValueMock(0.04, CHARGE_LOWER_LIMIT , CHARGE_UPPER_LIMIT,"Approaching Peak Charge Rate", "Approaching Lower Charge Rate", messageHandler);
    assert(capturedMessage == "Approaching Lower Charge Rate");
}

