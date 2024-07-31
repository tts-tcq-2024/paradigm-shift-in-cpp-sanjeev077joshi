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

    if (value <= LowerLimit - LowerLimitTolerance)
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
    bool result1 = checkValueInRangeMock(10, 25, 0.6, "Value Within Range", messageHandler);
    assert(result1 == true);
    assert(capturedMessage.empty());

    // Test case 2: value is below lower limit
    capturedMessage.clear();
    bool result2 = checkValueInRangeMock(50, 85, 1, "Value Out Of Range", messageHandler);
    assert(result2 == false);
    assert(capturedMessage == "Value Out Of Range");
}


void tsst_CheckWarningForGivenValue() {

    void (*messageHandler)(const string&);

    // Assign the function pointer to the mock print function
    messageHandler = MockPrintMessage;

    // Test case 1: Check for Hign Temperature Warning
    capturedMessage.clear();
    CheckWarningForGivenValueMock(40, TEMP_LOWER_LIMIT , TEMP_UPPER_LIMIT,"Approaching High Temperature","Approaching Low Temperature", messageHandler);
    assert(capturedMessage == "Approaching High Temperature");

    // Test case 2 : Check for Low Temperature Warning Message
    capturedMessage.clear();
    CheckWarningForGivenValueMock(2, TEMP_LOWER_LIMIT , TEMP_UPPER_LIMIT,"Approaching High Temperature","Approaching Low Temperature", messageHandler);
    assert(capturedMessage == "Approaching Low Temperature");

}

