#include <assert.h>
#include <iostream>
#include <string>
#include "CheckBatteryStatus.h"

extern bool test_checkValueInRange();
extern void test_CheckWarningForGivenValue();

int main() {

	test_checkValueInRange();
	test_CheckWarningForGivenValue();

	/* Test cases for InRange Validation */
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    assert(batteryIsOk(-10, 23, 0.6) == false);
}
