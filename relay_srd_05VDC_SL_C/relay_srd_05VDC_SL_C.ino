#define PIN 3

void setup() {
pinMode(PIN, OUTPUT); // объявляем пин 3 как выход
}

void loop() {
digitalWrite(PIN, HIGH); // замыкаем реле

delay(100); // ждем 3 секунды

digitalWrite(PIN, LOW); // размыкаем реле

delay(50); // ждем 1 секунду
}
