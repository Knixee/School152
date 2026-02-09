const int pwmPin = 9;      // ШИМ
const int tachPin = 2;     // Тахометр
const int power = 80;

volatile unsigned long pulseCount = 0;
unsigned long lastMillis = 0;

void countPulses() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);

  pinMode(pwmPin, OUTPUT);
  pinMode(tachPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(tachPin), countPulses, FALLING);

  // Устанавливаем скорость (0-255)
  analogWrite(pwmPin, power);

  Serial.println("Управление запущено");
}

void loop() {
  if (millis() - lastMillis >= 1000) {
    noInterrupts();
    unsigned long currentPulses = pulseCount;
    pulseCount = 0;
    interrupts();

    lastMillis = millis();
    float rpm = (currentPulses * 60.0) / 2.0;

    Serial.print("Мощность: ");
    Serial.print(power * 100 / 255);
    Serial.print("% | Скорость: ");
    Serial.print(rpm);
    Serial.println(" RPM");
  }
}
