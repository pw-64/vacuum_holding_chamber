// PINS
#define pin_vacuum_sensor A15
#define pin_handle_position_switch 2
#define pin_vent_button 3
#define pin_pump_button 4
// vacuum level bar chart
#define pin_led_1 22
#define pin_led_2 23
#define pin_led_3 24
#define pin_led_4 25
#define pin_led_5 26
#define pin_led_6 27
#define pin_led_7 28
#define pin_led_8 29
#define pin_led_9 30
#define pin_led_10 31
#define pin_led_11 32
#define pin_led_12 33
#define pin_led_13 34
#define pin_led_14 35
#define pin_led_15 36
#define pin_led_16 37
#define pin_led_17 38
#define pin_led_18 39
#define pin_led_19 40
#define pin_led_20 41
#define pin_led_21 42
#define pin_led_22 43
#define pin_led_23 44
#define pin_led_24 45
#define pin_led_25 46
#define pin_led_26 47
#define pin_led_27 48
#define pin_led_28 49
#define pin_led_29 50
#define pin_led_30 51
// status LEDs
#define pin_venting_status_led 6
#define pin_auto_cycle_status_led 7
// pump & valves
#define pin_scroll_pump_relay 8
#define pin_vent_valve 9
#define pin_pump_hold 10
#define pin_pump_trigger 11

int vacuum_sensor_value; // hold the value read from vacuum sensor pin

bool do_auto_pump_cycle = false;

#define HandleOpenPosition digitalRead(pin_handle_position_switch)
#define VentButtonPressed !digitalRead(pin_vent_button)
#define PumpButtonPressed !digitalRead(pin_pump_button)
#define VacuumReading analogRead(pin_vacuum_sensor)

#define DEBUG
#define DEBUG_print_vacuum_reading

/*
Mapping voltage to digital reading

5v = 1023
0v = 0

(max - min) / steps = step size

coarse steps
max: 4.1v = (4.1 / 5) * 1023 = 839
min: 2.55v = (2.55 / 5) * 1023 = 522
steps = 16
step size = (839 - 522) / 16 = 19.8

fine steps
max: 2.55v = (2.55 / 5) * 1023 = 522
min: 1.9v = (1.9 / 5) * 1023 = 389
steps = 14
step size = (522 - 389) / 14 = 9.5
*/

void setup() {
  #ifdef DEBUG
    Serial.begin(9600); // open serial connection (debugging)
  #endif

  // configure I/O
  pinMode(pin_vacuum_sensor, INPUT);
  pinMode(pin_handle_position_switch, INPUT);
  pinMode(pin_vent_button, INPUT);
  pinMode(pin_pump_button, INPUT);
  pinMode(pin_scroll_pump_relay, OUTPUT);
  pinMode(pin_vent_valve, OUTPUT);
  pinMode(pin_pump_trigger, OUTPUT);
  pinMode(pin_pump_hold, OUTPUT);
  digitalWrite(pin_scroll_pump_relay, LOW);
  digitalWrite(pin_vent_valve, LOW);
  digitalWrite(pin_pump_trigger, LOW);
  digitalWrite(pin_pump_hold, LOW);
  pinMode(pin_led_1, OUTPUT);
  pinMode(pin_led_2, OUTPUT);
  pinMode(pin_led_3, OUTPUT);
  pinMode(pin_led_4, OUTPUT);
  pinMode(pin_led_5, OUTPUT);
  pinMode(pin_led_6, OUTPUT);
  pinMode(pin_led_7, OUTPUT);
  pinMode(pin_led_8, OUTPUT);
  pinMode(pin_led_9, OUTPUT);
  pinMode(pin_led_10, OUTPUT);
  pinMode(pin_led_11, OUTPUT);
  pinMode(pin_led_12, OUTPUT);
  pinMode(pin_led_13, OUTPUT);
  pinMode(pin_led_14, OUTPUT);
  pinMode(pin_led_15, OUTPUT);
  pinMode(pin_led_16, OUTPUT);
  pinMode(pin_led_17, OUTPUT);
  pinMode(pin_led_18, OUTPUT);
  pinMode(pin_led_19, OUTPUT);
  pinMode(pin_led_20, OUTPUT);
  pinMode(pin_led_21, OUTPUT);
  pinMode(pin_led_22, OUTPUT);
  pinMode(pin_led_23, OUTPUT);
  pinMode(pin_led_24, OUTPUT);
  pinMode(pin_led_25, OUTPUT);
  pinMode(pin_led_26, OUTPUT);
  pinMode(pin_led_27, OUTPUT);
  pinMode(pin_led_28, OUTPUT);
  pinMode(pin_led_29, OUTPUT);
  pinMode(pin_led_30, OUTPUT);
  pinMode(pin_venting_status_led, OUTPUT);
  pinMode(pin_auto_cycle_status_led, OUTPUT);
  digitalWrite(pin_venting_status_led, LOW);
  digitalWrite(pin_auto_cycle_status_led, LOW);
}

void UpdateVacuumGraph() {
  vacuum_sensor_value = VacuumReading; // read vacuum value
  #ifdef DEBUG_print_vacuum_reading
    Serial.println(vacuum_sensor_value); // output value to console
  #endif

  // coarse
  digitalWrite(pin_led_1,  522 + 19.8 * 15 < vacuum_sensor_value);
  digitalWrite(pin_led_2,  (522 + 19.8 * 14 < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 15));
  digitalWrite(pin_led_3,  (522 + 19.8 * 13 < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 14));
  digitalWrite(pin_led_4,  (522 + 19.8 * 12 < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 13));
  digitalWrite(pin_led_5,  (522 + 19.8 * 11 < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 12));
  digitalWrite(pin_led_6,  (522 + 19.8 * 10 < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 11));
  digitalWrite(pin_led_7,  (522 + 19.8 * 9  < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 10));
  digitalWrite(pin_led_8,  (522 + 19.8 * 8  < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 9));
  digitalWrite(pin_led_9,  (522 + 19.8 * 7  < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 8));
  digitalWrite(pin_led_10, (522 + 19.8 * 6  < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 7));
  digitalWrite(pin_led_11, (522 + 19.8 * 5  < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 6));
  digitalWrite(pin_led_12, (522 + 19.8 * 4  < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 5));
  digitalWrite(pin_led_13, (522 + 19.8 * 3  < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 4));
  digitalWrite(pin_led_14, (522 + 19.8 * 2  < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 3));
  digitalWrite(pin_led_15, (522 + 19.8 * 1  < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 2));
  digitalWrite(pin_led_16, (522             < vacuum_sensor_value) && (vacuum_sensor_value <= 522 + 19.8 * 1));
  // fine
  digitalWrite(pin_led_17, (389 + 9.5 * 13 < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 14));
  digitalWrite(pin_led_18, (389 + 9.5 * 12 < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 13));
  digitalWrite(pin_led_19, (389 + 9.5 * 11 < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 12));
  digitalWrite(pin_led_20, (389 + 9.5 * 10 < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 11));
  digitalWrite(pin_led_21, (389 + 9.5 * 9  < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 10));
  digitalWrite(pin_led_22, (389 + 9.5 * 8  < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 9));
  digitalWrite(pin_led_23, (389 + 9.5 * 7  < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 8));
  digitalWrite(pin_led_24, (389 + 9.5 * 6  < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 7));
  digitalWrite(pin_led_25, (389 + 9.5 * 5  < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 6));
  digitalWrite(pin_led_26, (389 + 9.5 * 4  < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 5));
  digitalWrite(pin_led_27, (389 + 9.5 * 3  < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 4));
  digitalWrite(pin_led_28, (389 + 9.5 * 2  < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 3));
  digitalWrite(pin_led_29, (389 + 9.5 * 1  < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 2));
  digitalWrite(pin_led_30, (389            < vacuum_sensor_value) && (vacuum_sensor_value <= 389 + 9.5 * 1));
}

void loop() {
  UpdateVacuumGraph();

  if (VentButtonPressed) {
    digitalWrite(pin_venting_status_led, HIGH);

    digitalWrite(pin_pump_hold, LOW);
    delay(500);
    digitalWrite(pin_scroll_pump_relay, LOW);
    delay(1000);
    digitalWrite(pin_vent_valve, HIGH);
    
    while (VacuumReading < 850) {
      UpdateVacuumGraph();
      delay(100);
    }

    // make sure the door can open
    delay(25000);

    digitalWrite(pin_vent_valve, LOW);
    
    do_auto_pump_cycle = false;
    digitalWrite(pin_venting_status_led, LOW);
    digitalWrite(pin_auto_cycle_status_led, LOW);
  }

  if (PumpButtonPressed && !HandleOpenPosition) {
    do_auto_pump_cycle = true;
    digitalWrite(pin_auto_cycle_status_led, HIGH);

    if (VacuumReading > 800) {
      digitalWrite(pin_scroll_pump_relay, HIGH);
      delay(500);
      digitalWrite(pin_pump_hold, HIGH);
      delay(500);
      digitalWrite(pin_pump_trigger, HIGH);
      delay(500);
      digitalWrite(pin_pump_trigger, LOW);

      while (VacuumReading >= 440) {
        UpdateVacuumGraph();
        delay(100);
      }
    }
  }

  if (do_auto_pump_cycle) {
    /*
    2.5v = 512: pump on
    2.15v = 440: pump off
    */

    // auto cycle - vacuum poor, pump on
    if (VacuumReading >= 512) {
      digitalWrite(pin_scroll_pump_relay, HIGH);
      delay(30000); // pump for 30s to remove air in the pipe, then open the valve so the chamber isnt flooded
      digitalWrite(pin_pump_hold, HIGH);
      delay(500);
      digitalWrite(pin_pump_trigger, HIGH);
      delay(500);
      digitalWrite(pin_pump_trigger, LOW);
    }

    // auto cycle - vacuum good, pump off
    if (VacuumReading <= 440) {
      digitalWrite(pin_pump_hold, LOW);
      delay(500);
      digitalWrite(pin_scroll_pump_relay, LOW);
    }
  }

  delay(100);
}