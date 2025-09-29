typedef enum MoistureLevel_enum : uint32_t
{
  Saturated = 4,
  Moist = 0,
  Dry = 1,
  Test = 2
} MoistureLevel;

struct MoistureSensor {
public:
  uint32_t moisture_pin;
  uint32_t moisture_value;
private:
  const float E = 2.71828;
  const uint32_t SaturationGoal = to_counts(50);
  const uint32_t MoistGoal = to_counts(100);
  const uint32_t DryGoal = to_counts(600);
  const uint32_t SaturationThreshold = to_counts(100);
  const uint32_t MoistThreshold = to_counts(300);
  const uint32_t DryThreshold = to_counts(1000);
  const unit32_t TestGoal = 150;
  const unit32_t TestThreshold = 200; 
public:
  void read() {
    moisture_value = analogRead(moisture_pin);
  }
  static uint32_t GetMoistureGoal(const MoistureLevel& level);
  static uint32_t GetMoistureThreshold(const MoistureLevel& level);
private:
  float to_water_potential(float counts)
  {
    return 788.933 / (1 + pow(E, -0.081332 * (counts - 282.967))) - 26.3355;
  }
  float to_counts(float potential)
  {
    return -log(788.933/(potential + 26.3355) - 1)/0.081332 + 282.967;
  }
  
};

static uint32_t MoistureSensor::GetMoistureGoal(const MoistureLevel& level)
  {
    return ((level == Saturated) * SaturationGoal) + ((level == Moist) * MoistGoal)) 
      + ((level == Dry) * DryGoal) + ((level == Test) * TestGoal);
  }

  static uint32_t MoistureSensor::GetMoistureThreshold(const MoistureLevel& level)
  {
    return ((level == Saturated) * SaturationThreshold) + ((level == Moist) * MoistThreshold)) 
      + ((level == Dry) * DryThreshold) + ((level == Test) * TestThreshold);
  }