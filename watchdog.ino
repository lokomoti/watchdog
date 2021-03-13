const int rst_pin = 12;
const int led_pin = LED_BUILTIN;

int time_out = 0;
int counter = 0;
int incomingByte;

unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  Serial.begin(9600);

  Serial.println("WatchDog v.1");
  Serial.println("Send some of following options to start the counter:");
  Serial.println("1 - 60s");
  Serial.println("2 - 120s");
  Serial.println("3 - 180s");
  Serial.println("Reset the counter by sending R character");
  
  pinMode(rst_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  digitalWrite(rst_pin, LOW);
  digitalWrite(led_pin, LOW);
}

void loop() {
  handleSerial();
  if (time_out != 0) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      counter ++;
      if (counter >= time_out) {
        reboot();
      }
      previousMillis = currentMillis;
      Serial.println(time_out - counter);
    }
  }
}

void handleSerial() {
  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    switch (incomingByte) {
      case 'R':
        counter = 0;
        break;

      case '1':
        time_out = 60;
        break;

      case '2':
        time_out = 120;
        break;

      case '3':
        time_out = 180;
        break;

      case '0':
        time_out = 10;
        break;
    }
  }
}

void reboot() {
  digitalWrite(rst_pin, HIGH);
  digitalWrite(led_pin, HIGH);
  delay(500);
  digitalWrite(rst_pin, LOW);
  digitalWrite(led_pin, LOW);
  time_out = 0;
  counter = 0;
}
