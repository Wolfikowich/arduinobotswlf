// PWM пины
#define PWM1_PIN            5
#define PWM2_PIN            6      
// 74HCT595N сдвиговый регистр и его подключение
#define SHCP_PIN            2                               // Смещение регистра
#define EN_PIN              7                               // пин разрешающий управление
#define DATA_PIN            8                               // последовательные данные
#define STCP_PIN            4                               // задающая частота регистра памяти         
const int Stop          = 0;                                // остановка
const int Contrarotate  = 172;                              // круг против часовой стрелки
/*const int Clockwise     = 83;*/                               // круг по часовой стрелке
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
    /* круг по часовой стрелке */
    Motor(Clockwise, 250);
    delay(2000);
    /* круг против часовой стрелки
    Motor(Contrarotate, 250);
    delay(2000);
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
