#include <assert.h>
#include "CheckBatteryStatus.h"

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
  assert(batteryIsOk(-10, 23, 0.6) == false);
}
