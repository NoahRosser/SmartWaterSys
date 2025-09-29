#include "plant.h"
#include "valve.h"
#include "moistureSensor.h"

struct Module {
  Plant plant;
  Valve valve;
  MoistureSensor moisture_sensor;

  bool is_watering;
  bool is_enabled;

  bool moisture_low() {
    return (moisture_sensor.moisture_value > MoistureSensor::GetMoistureThreshold(plant.moisture_type));
  }

  void run_watering_sequence() {
    if (moisture_sensor.moisture_value <= MoistureSensor::GetMoistureGoal(plant.moisture_type)) {
        is_watering = false;
        valve.close();
    }
  }

  void update() {
    if (is_enabled) {
      moisture_sensor.read();
      if (is_watering) {
        run_watering_sequence();
      } else if (moisture_low()) {
        valve.open();
        is_watering = true;
      }
    }
  }

  void init() {
    valve.init();
  }

  void Enable() {
    is_enabled = true;
  }

  void Disable() {
    is_watering = false;
    is_enabled = false;
    valve.close();
  }
};