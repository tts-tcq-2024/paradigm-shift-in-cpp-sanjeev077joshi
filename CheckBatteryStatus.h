#include <iostream>
#include <string>

const float TEMP_LOWER_LIMIT = 0;
const float TEMP_UPPER_LIMIT = 45;
const float SOC_LOWER_LIMIT  = 20;
const float SOC_UPPER_LIMIT  = 80;
const float CHARGE_LOWER_LIMIT = 0;
const float CHARGE_UPPER_LIMIT = 0.8;

bool batteryIsOk(float temperature, float soc, float chargeRate);

