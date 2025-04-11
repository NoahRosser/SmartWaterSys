#include "plant.h"
#include "valve.h"
#include "moistureSensor.h"

struct Module {
  Plant plant;
  Valve valve;
  MoistureSensor moisture_sensor;

  bool is_watering;
  bool is_enabled;
  double water_supplied;

  bool moisture_low() {
    return (moisture_sensor.moisture_value <= plant.moisture_threshold);
  }

  void run_watering_sequence(const double &supply_rate, const double &delta_time) {
    if (water_supplied < plant.water_load) {
        water_supplied += supply_rate * delta_time; // integrate
    } else {
        is_watering = false;
        water_supplied = 0;
        valve.close();
    }
  }

  void update(const double &supply_rate, const double &delta_time) {
    if (is_enabled) {
      moisture_sensor.read();
      if (is_watering) {
        run_watering_sequence(supply_rate, delta_time);
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
    water_supplied = 0;
    valve.close();
  }
};