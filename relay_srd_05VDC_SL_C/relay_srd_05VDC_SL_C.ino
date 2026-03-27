#define PIN 3

void setup() {
pinMode(PIN, OUTPUT); // объявляем пин 3 как выход
}

void loop() {
digitalWrite(PIN, HIGH); // замыкаем реле

//delayMicroseconds(30); // скважность

delay(1000); 

digitalWrite(PIN, LOW); 

//delay(500);
delayMicroseconds(10); // импульс

}
