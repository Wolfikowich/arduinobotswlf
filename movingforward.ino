// PWM пины
#define PWM1_PIN            5
#define PWM2_PIN            6      
// 74HCT595N сдвиговый регистр и его подключение
#define SHCP_PIN            2                               // Смещение регистра
#define EN_PIN              7                               // пин разрешающий управление
#define DATA_PIN            8                               // последовательные данные
#define STCP_PIN            4                               // задающая частота регистра памяти              
const int Forward       = 92;                               // движение вперёд (ниже в соотв  таблицей)
void setup()
{
    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);
}
void loop()
{
    /* вперёд */
    Motor(Forward, 250);     
    delay(2000);//задержка
    /* стоп */
    Motor(Stop, 250);
    delay(2000);
}
void Motor(int Dir, int Speed)
{
    digitalWrite(EN_PIN, LOW);
    analogWrite(PWM1_PIN, Speed);
    analogWrite(PWM2_PIN, Speed);
    digitalWrite(STCP_PIN, LOW);
    shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Dir);
    digitalWrite(STCP_PIN, HIGH);
}
