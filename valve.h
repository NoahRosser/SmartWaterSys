struct Valve {
  uint32_t valve_pin;
  bool is_open;

  void open() {
    digitalWrite(valve_pin, HIGH);
    is_open = true;
  }
  void close() {
    digitalWrite(valve_pin, LOW);
    is_open = false;
  }
  void init() {
    pinMode(valve_pin, OUTPUT);
    close();
  }
};