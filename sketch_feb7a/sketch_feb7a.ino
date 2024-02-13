int head = 3;
int tail = 1;
int button = 7;
int microphone = 8;

int headState = 0;
int tailState = 0;
unsigned long startTime;
unsigned long lastMicTime;
bool running = false; 
long randNum;


void forward(int pin) {
  digitalWrite(pin, LOW);
  digitalWrite(pin + 1, HIGH);
}

void reverse(int pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin + 1, LOW);
}

void setup() {
  Serial.begin(9600);

  digitalWrite(head, LOW);
  digitalWrite(head + 1, LOW);
  digitalWrite(tail, LOW);
  digitalWrite(tail + 1, HIGH);
  digitalWrite(button, LOW);

  running = false;

  delay(1000);
}

void loop() {
  if (!running && !digitalRead(button)) {
    startTime = millis();
    lastMicTime = millis();
    running = true;
  }

  if ((millis() < startTime + 180000) && running) {
    if (digitalRead(microphone) || (millis() < lastMicTime + 2000)) {
      if (digitalRead(microphone)) {
          lastMicTime = millis();
      }
      randNum = random(1000);
      if (randNum < 500) {  // head
        if (headState) { // if head is up
          headState = 0;
          reverse(head);
        } else {  // if head is down
          headState = 1;
          forward(head);
        }
      } else { // tail selected
        if (tailState) {  // if tail is up
          tailState = 0;
          forward(tail);
        } else {  // if tail is down
          tailState = 1;
          reverse(tail);
        }
      }
      delay(random(400, 1000));
    } else {
      tailState = 0;
      forward(tail);
      headState = 0;
      reverse(head);
    }
  } else {
    running = false;
    tailState = 0;
    forward(tail);
    headState = 0;
    reverse(head);
  }
}
