struct MoistureSensor {
  uint32_t moisture_pin;
  uint32_t moisture_value;

  void read() {
    moisture_value = analogRead(moisture_pin);
    moisture_value = map(moisture_value, 0, 1023, 0, 100);
  }
};