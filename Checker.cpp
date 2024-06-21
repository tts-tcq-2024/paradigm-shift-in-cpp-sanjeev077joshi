#include <assert.h>
#include <iostream>
using namespace std;

bool checktemp (float temp)
{
    if(temp < 0 || temp > 45) {
        cout << "Temperature out of range!\n";
        return false;
    }

    return true;
}

bool checksoc (float soc)
{
    if(soc < 20 || soc > 80){
        cout << "State of Charge out of range!\n";
        return false;
    }

    return true;
}

bool checkchargeRate (float rate)
{
    if(rate > 0.8) {
    cout << "Charge Rate out of range!\n";
    return false;
  }

   return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {

   bool retvalue;

   retvalue = checktemp(temperature);
   retvalue = checksoc(soc);
   retvalue = checkchargeRate(chargeRate);

   return retvalue;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == false);
  assert(batteryIsOk(50, 85, 0) == true);
}
