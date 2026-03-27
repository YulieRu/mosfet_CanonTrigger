#define PIN 3

void setup() {
pinMode(PIN, OUTPUT); // объявляем пин 3 как выход
}

void loop() {
digitalWrite(PIN, HIGH); // замыкаем реле

//delayMicroseconds(1000); // ждем 3 секунды
delay(10);

digitalWrite(PIN, LOW); // размыкаем реле

delayMicroseconds(10); // ждем 1 секунду
//delay(10);
}
