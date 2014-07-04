// ================================================================
//  class Vehicle
/** Vehicle characteristics and state.
    ....
*/
// ================================================================

#ifndef _Vehicle_h_
#define _Vehicle_h_

#include <string>

class Vehicle {
  public:
    virtual const std::string getName() = 0;
    virtual void setName(std::string) = 0;

  private:
    // float drymass;
    // PropulsionSystem mainprop;
    // map<string, PropulsionSystem> auxprop;
    // GNC
};



#endif // _Vehicle_h_
