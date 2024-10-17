// #define DEBUG_enable
// #define DEBUG_print_vacuum_reading
// #define DEBUG_flow_messages

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

void setup() {
  #ifdef DEBUG_enable
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

/*
Mapping voltage to digital reading

5v = 1023
0v = 0

(max - min) / steps = step size
*/

// value is within the range of a step
#define ValueInStepRange(input_value, min, step_size, step_count) (min + step_size * step_count < input_value) && (input_value <= min + step_size * (step_count + 1))

/*
coarse steps
max: 4.2v = (4.2 / 5) * 1023 = 921
min: 2.55v = (2.55 / 5) * 1023 = 522
steps = 16
step size = (921 - 522) / 16 = 24.9

fine steps
max: 2.55v = (2.55 / 5) * 1023 = 522
min: 1.9v = (1.9 / 5) * 1023 = 389
steps = 14
step size = (522 - 389) / 14 = 9.5
*/
#define CoarseStart 522
#define CoarseStep 24.9
#define FineStart 389
#define FineStep 9.5

void UpdateVacuumGraph() {
  vacuum_sensor_value = VacuumReading; // read vacuum value
  
  #ifdef DEBUG_print_vacuum_reading
    Serial.println(vacuum_sensor_value); // output value to console
  #endif

  // coarse
  digitalWrite(pin_led_1,  ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 15));
  digitalWrite(pin_led_2,  ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 14));
  digitalWrite(pin_led_3,  ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 13));
  digitalWrite(pin_led_4,  ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 12));
  digitalWrite(pin_led_5,  ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 11));
  digitalWrite(pin_led_6,  ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 10));
  digitalWrite(pin_led_7,  ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 9));
  digitalWrite(pin_led_8,  ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 8));
  digitalWrite(pin_led_9,  ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 7));
  digitalWrite(pin_led_10, ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 6));
  digitalWrite(pin_led_11, ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 5));
  digitalWrite(pin_led_12, ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 4));
  digitalWrite(pin_led_13, ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 3));
  digitalWrite(pin_led_14, ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 2));
  digitalWrite(pin_led_15, ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 1));
  digitalWrite(pin_led_16, ValueInStepRange(vacuum_sensor_value, CoarseStart, CoarseStep, 0));
  // fine
  digitalWrite(pin_led_17, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 13));
  digitalWrite(pin_led_18, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 12));
  digitalWrite(pin_led_19, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 11));
  digitalWrite(pin_led_20, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 10));
  digitalWrite(pin_led_21, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 9));
  digitalWrite(pin_led_22, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 8));
  digitalWrite(pin_led_23, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 7));
  digitalWrite(pin_led_24, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 6));
  digitalWrite(pin_led_25, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 5));
  digitalWrite(pin_led_26, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 4));
  digitalWrite(pin_led_27, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 3));
  digitalWrite(pin_led_28, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 2));
  digitalWrite(pin_led_29, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 1));
  digitalWrite(pin_led_30, ValueInStepRange(vacuum_sensor_value, FineStart, FineStep, 0));
}

void loop() {
  UpdateVacuumGraph();

  if (VentButtonPressed) {

    #ifdef DEBUG_flow_messages
      Serial.println("venting");
    #endif

    digitalWrite(pin_venting_status_led, HIGH);

    digitalWrite(pin_pump_hold, LOW);
    delay(500);
    digitalWrite(pin_scroll_pump_relay, LOW);
    delay(1000);
    digitalWrite(pin_vent_valve, HIGH);
    
    while (VacuumReading < 850) {
      #ifdef DEBUG_flow_messages
        Serial.println("waiting for vacuum < 850");
      #endif

      UpdateVacuumGraph();
      delay(100);
    }

    #ifdef DEBUG_flow_messages
      Serial.println("start 25s vent extension");
    #endif

    // make sure the door can open
    delay(25000);

    digitalWrite(pin_vent_valve, LOW);
    
    do_auto_pump_cycle = false;
    digitalWrite(pin_venting_status_led, LOW);
    digitalWrite(pin_auto_cycle_status_led, LOW);

    #ifdef DEBUG_flow_messages
      Serial.println("done venting");
    #endif
  }

  if (PumpButtonPressed && !HandleOpenPosition) {
    #ifdef DEBUG_flow_messages
      Serial.println("pumping");
    #endif

    do_auto_pump_cycle = true;
    digitalWrite(pin_auto_cycle_status_led, HIGH);

    if (VacuumReading > 800) {
      #ifdef DEBUG_flow_messages
        Serial.println("at air, venting the whole system");
      #endif

      digitalWrite(pin_scroll_pump_relay, HIGH);
      delay(500);
      digitalWrite(pin_pump_hold, HIGH);
      delay(500);
      digitalWrite(pin_pump_trigger, HIGH);
      delay(500);
      digitalWrite(pin_pump_trigger, LOW);

      while (VacuumReading >= 440) {
        #ifdef DEBUG_flow_messages
          Serial.println("waiting for vacuum >= 440");
        #endif

        UpdateVacuumGraph();
        delay(100);
      }
    }
  }

  #ifdef DEBUG_flow_messages
    Serial.print("auto pump cycle: ");
    Serial.println(do_auto_pump_cycle);
  #endif

  if (do_auto_pump_cycle) {
    /*
    2.5v = 512: pump on
    2.15v = 440: pump off
    */

    // auto cycle - vacuum poor, pump on
    if (VacuumReading >= 512) {
      #ifdef DEBUG_flow_messages
        Serial.println("vacuum poor, pump on (+30s delay)");
      #endif

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
      #ifdef DEBUG_flow_messages
        Serial.println("vacuum good, pump off");
      #endif

      digitalWrite(pin_pump_hold, LOW);
      delay(500);
      digitalWrite(pin_scroll_pump_relay, LOW);
    }
  }

  delay(100);
}