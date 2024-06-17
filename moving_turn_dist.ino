// PWM пины
#define PWM1_PIN 5
#define PWM2_PIN 6
// 74HCT595N сдвиговый регистр и его подключение
#define SHCP_PIN 2  // Смещение регистра
#define EN_PIN 7    // Пин разрешающий управление
#define DATA_PIN 8  // Последовательные данные
#define STCP_PIN 4  // Задающая частота регистра памяти
const int Stop = 0;  // Остановка
//const int Contrarotate = 172;  // Круг против часовой стрелки
const int Clockwise = 83;  // Круг по часовой стрелке

const float speedDegPerSec = 45.0;  // Угловая скорость робота в градусах в секунду (нужна калибровка)

void setup() {
    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);
}

void loop() {
    float angle = 90.0;  // Угол поворота в градусах (измените это значение по необходимости)
    turnRobot(angle, true);  // Поворот по часовой стрелке
    delay(2000);  // Задержка перед следующим движением
}

void turnRobot(float angleDeg, bool clockwise) {
    float timeSec = angleDeg / speedDegPerSec;  // Рассчитать время для поворота на заданный угол
    int timeMs = timeSec * 1000;  // Конвертировать время в миллисекунды

    //if (clockwise) {
        Motor(Clockwise, 250);
    //} else {
       // Motor(Contrarotate, 250);
    //}
    delay(timeMs);  // Поворот в течение рассчитанного времени
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
