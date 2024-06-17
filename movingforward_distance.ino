// PWM пины
#define PWM1_PIN 5
#define PWM2_PIN 6
// 74HCT595N сдвиговый регистр и его подключение
#define SHCP_PIN 2  // Смещение регистра
#define EN_PIN 7    // Пин разрешающий управление
#define DATA_PIN 8  // Последовательные данные
#define STCP_PIN 4  // Задающая частота регистра памяти
const int Forward = 92;  // Движение вперед (ниже в соотв таблицей)
const int Stop = 0;      // Стоп (нужно определить это значение)

const float speedCmPerSec = 10.0;  // Скорость робота в см/с (нужна калибровка)

void setup() {
    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);
}

void loop() {
    float distance = 100.0;  // Расстояние для движения в см (измените это значение по необходимости)
    moveForward(distance);
    delay(2000);  // Задержка перед следующим движением
}

void moveForward(float distanceCm) {
    float timeSec = distanceCm / speedCmPerSec;  // Рассчитать время для прохождения заданного расстояния
    int timeMs = timeSec * 1000;  // Конвертировать время в миллисекунды

    Motor(Forward, 250);
    delay(timeMs);  // Двигаться вперед в течение рассчитанного времени
    Motor(Stop, 0);  // Остановить мотор
}

void Motor(int Dir, int Speed) {
    digitalWrite(EN_PIN, LOW);
    analogWrite(PWM1_PIN, Speed);
    analogWrite(PWM2_PIN, Speed);
    digitalWrite(STCP_PIN, LOW);
    shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Dir);
    digitalWrite(STCP_PIN, HIGH);
}
