#define LED1 2

bool serialReady = false;
String serialInput = "";

void setup() {
  pinMode(LED1, OUTPUT);
  serialInput.reserve(32);
  Serial.begin(9600);
  
}

void loop() {
  if (serialReady) {
    digitalWrite(LED1, HIGH);
    delay(1000);
    serialReady = false;
  }
  digitalWrite(LED1, LOW);
  delay(1000);
}

void serialEvent() {
  while (Serial.available()) {
    char inputChar = (char) Serial.read();
    serialInput += inputChar;
    if (inputChar == '\n') {
      serialReady = true;
    }
  }
}
