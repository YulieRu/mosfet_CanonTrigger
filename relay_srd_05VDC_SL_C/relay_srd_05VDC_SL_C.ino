#define PIN 5

void setup() {
pinMode(PIN, OUTPUT); // объявляем пин 3 как выход
}

void loop() {
digitalWrite(PIN, HIGH); // замыкаем реле

//delayMicroseconds(30); // скважность

delay(50); 

digitalWrite(PIN, LOW); 

//delay(500);
delay(1000); // импульс

}
