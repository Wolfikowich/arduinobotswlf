#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define LED_PIN 13
#define BUZZER_PIN 8
#define MOTORA1 4
#define MOTORA2 5
#define MOTORB1 6
#define MOTORB2 7

long distance;
unsigned long moveStartTime;
bool movingForward = true;

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MOTORA1, OUTPUT);
  pinMode(MOTORA2, OUTPUT);
  pinMode(MOTORB1, OUTPUT);
  pinMode(MOTORB2, OUTPUT);

  digitalWrite(MOTORA1, HIGH);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, HIGH);
  digitalWrite(MOTORB2, LOW);

  Serial.begin(9600);
  moveStartTime = millis();
}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  distance = pulseIn(ECHO_PIN, HIGH) / 58.2;

  if (distance <= 10) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    delay(100);
    noTone(BUZZER_PIN);

    // Остановка моторов
    digitalWrite(MOTORA1, LOW);
    digitalWrite(MOTORA2, LOW);
    digitalWrite(MOTORB1, LOW);
    digitalWrite(MOTORB2, LOW);

    // Обратное движение
    unsigned long moveDuration = millis() - moveStartTime;
    moveBackward(moveDuration);

    // Сброс времени движения
    moveStartTime = millis();
  } else {
    digitalWrite(LED_PIN, LOW);

    if (!movingForward) {
      // Сохраняем время начала движения вперед
      moveStartTime = millis();
      movingForward = true;
    }

    // Движение вперед
    digitalWrite(MOTORA1, HIGH);
    digitalWrite(MOTORA2, LOW);
    digitalWrite(MOTORB1, HIGH);
    digitalWrite(MOTORB2, LOW);
  }

  delay(100);
}

void moveBackward(unsigned long duration) {
  // Движение назад
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, HIGH);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, HIGH);

  delay(duration);

  // Остановка моторов
  digitalWrite(MOTORA1, LOW);
  digitalWrite(MOTORA2, LOW);
  digitalWrite(MOTORB1, LOW);
  digitalWrite(MOTORB2, LOW);

  movingForward = false;
}
