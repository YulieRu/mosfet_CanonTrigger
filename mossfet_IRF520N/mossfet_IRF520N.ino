#define MOT 9

void setup() {
    pinMode(MOT, OUTPUT);
}

void loop() {
   // плавное включение
   for(int i=0; i<=255; i+=255) { //циклом регулируется скорость включения
      analogWrite(MOT, i);
      delay(0); // скважность
   }

   //плавное выключение
   for(int i=255; i>=0; i-=255) {
      analogWrite(MOT, i);
      delay(100); // скважность
   }
}