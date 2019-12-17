
#include <TimerOne.h>
#include <LiquidCrystal.h>

const byte rs = 12, en = 11, d4 = 4, d5 = 3, d6 = 6, d7 = 7;

byte pin = 5;
byte IN1 = 2, IN2 = 3;
volatile byte ciclo;

double POTF;
volatile long double Periodo;

int Fminimo = 30, Fmaximo = 70;
int i;

volatile int saidas[]={0, 40, 79, 116, 150, 180, 206, 227, 243, 252, 255, 252, 243, 227, 206, 180, 150, 116, 79, 40, 0};

char str[16];

long tempo;

LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  Timer1.initialize(Periodo);
  Timer1.attachInterrupt(semiciclo);
  Serial.begin(9600);
  Periodo = 0;
  ciclo = 0;
  i = 0;
  atualiza();
    lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop()
{
  if (millis() - tempo >= 500)
  {
    atualiza();
  }
}

void atualiza(){
  tempo = millis();
    POTF = analogRead(A0);

    POTF = map(POTF, 0, 1023, Fminimo, Fmaximo);
    Periodo = ((1/POTF)/20);
    Periodo*=1000000;

    Timer1.setPeriod(Periodo);
Serial.println("Frequencia:");
    Serial.println(POTF);
sprintf(str,"Frequencia: %lf", POTF);
  lcd.setCursor(0,0);
    lcd.print(str);
    lcd.clear();

}

void semiciclo()
{
  if (ciclo == 0)
  {
    digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  { if (i < 20 )
    {
      analogWrite(pin, saidas[i]);
      i++;
    }
    else
    {
      i = 0;
      ciclo += 1;
    }
  }
}
  else if (ciclo == 1)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    if (i < 20 )
    {
      analogWrite(pin, saidas[i]);
      i++;
    }
    else
    {
      i = 0;
      ciclo = 0;
    }
  }
}