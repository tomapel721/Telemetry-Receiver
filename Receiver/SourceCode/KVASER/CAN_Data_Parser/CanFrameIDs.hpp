#ifndef CANFRAMEIDS_HPP
#define CANFRAMEIDS_HPP

#include "stdint.h"

/* CAN Frame IDs defined by CarManagement.dbc */
namespace CAN_Frame {

constexpr uint16_t Suspension = 1536;
constexpr uint16_t DRS = 1537;
constexpr uint16_t LV_Temperature = 1538;
constexpr uint16_t LV_Bat_Parameters = 1539;
constexpr uint16_t HV_Bat_Parameters = 785;
constexpr uint16_t TS_Temperatures = 786;
    // ecu status?
constexpr uint16_t tireTemp_FL_420 = 0; // idk ktore ramki wysylac
constexpr uint16_t Driver_Commands = 848;
constexpr uint16_t Cooling_System = 851;
constexpr uint16_t Wheels_Speed = 850;
constexpr uint16_t Vehilcle_Status = 849;
constexpr uint16_t Steering_Status = 1280;

}

#endif // CANFRAMEIDS_HPP
