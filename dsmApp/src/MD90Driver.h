/*
FILENAME...   MD90Driver.h
USAGE...      Motor driver support for the DSM MD-90 controller.

*/

#include "asynMotorController.h"
#include "asynMotorAxis.h"

#define MAX_MD90_AXES 1

// No controller-specific parameters yet
#define NUM_MD90_PARAMS 0  

#define SLEEP_MARGIN		1.2					// Extra factor to wait after stepping before homing
#define HOME_SLEEP_MIN		1					// Minimum amount of time to wait after stepping/before homing
#define SMALL_NSTEPS		5					// Number of steps to take to set direction for homing routine
#define COUNTS_PER_STEP		1000.0				// Number of encoder counts per motor step (measured by testing)

class epicsShareClass MD90Axis : public asynMotorAxis
{
public:
  /* These are the methods we override from the base class */
  MD90Axis(class MD90Controller *pC, int axis);
  void report(FILE *fp, int level);
  asynStatus move(double position, int relative, double min_velocity, double max_velocity, double acceleration);
  asynStatus moveVelocity(double min_velocity, double max_velocity, double acceleration);
  asynStatus home(double min_velocity, double max_velocity, double acceleration, int forwards);
  asynStatus stop(double acceleration);
  asynStatus poll(bool *moving);
  asynStatus setClosedLoop(bool closedLoop);
  asynStatus setIGain(double iGain);
  asynStatus doMoveToHome();

private:
  MD90Controller *pC_;          /**< Pointer to the asynMotorController to which this axis belongs.
                                   *   Abbreviated because it is used very frequently */
  asynStatus sendAccelAndVelocity(double accel, double velocity);
  asynStatus parseReply(const char *functionName, const char *reply);
  
friend class MD90Controller;
};

class epicsShareClass MD90Controller : public asynMotorController {
public:
  MD90Controller(const char *portName, const char *MD90PortName, int numAxes, double movingPollPeriod, double idlePollPeriod);

  void report(FILE *fp, int level);
  MD90Axis* getAxis(asynUser *pasynUser);
  MD90Axis* getAxis(int axisNo);

friend class MD90Axis;
};
