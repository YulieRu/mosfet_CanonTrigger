#define PARSE_AMOUNT 4         // число значений в массиве, который хотим получить
#define start_com '[' 
#define end_com ']' 
#define delCom '=' 
#define TRIG_PIN 3
#define RED_PIN 10
#define BLUE_PIN 12
unsigned long timing=0;

double commandsData[PARSE_AMOUNT];     // массив численных значений после парсинга
boolean recievedFlag;
boolean getStarted;
byte index;
String string_convert = "";
String commandName = "";
int ifGreeting = 0;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(RED_PIN, OUTPUT);
  digitalWrite(RED_PIN, LOW);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(BLUE_PIN, LOW);
}

void greeting() {
  Serial.println("Enter the command: [RECORD=numImpulses pause(ms) redTime(ms) blueTime(ms)]");  
  ifGreeting = 1;
}

void parsing() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();        // обязательно ЧИТАЕМ входящий символ
    if (getStarted) {                         // если приняли начальный символ (парсинг разрешён)
      if (incomingByte != ' ' && incomingByte != end_com) {   // если это не пробел И не конец
        string_convert += incomingByte;       // складываем в строку
      } else {                                // если это пробел или ; конец пакета
        commandsData[index] = string_convert.toDouble();  // преобразуем строку в int и кладём в массив
        string_convert = "";                  // очищаем строку
        index++;                              // переходим к парсингу следующего элемента массива
      }
    } else {
      commandName += incomingByte;
    }
    if (incomingByte == delCom) {             // если это '='
      getStarted = true;                      // поднимаем флаг, что можно парсить
      index = 0;                              // сбрасываем индекс
      string_convert = "";                    // очищаем строку 
    }

    if (incomingByte == end_com) {                // если таки приняли ] - конец парсинга
      getStarted = false;                     // сброс
      recievedFlag = true;                    // флаг на принятие
      commandName=commandName.substring(commandName.indexOf("[")+1, commandName.indexOf("="));
    }
  }
}

void ptvFrame(){
  
  float lag_camera_dt=170; //lag time for camera to make 1 frame. 100-200ms for Canon EOS 550D
  
  digitalWrite(TRIG_PIN, HIGH);
  delay(lag_camera_dt);
  
  digitalWrite(RED_PIN, HIGH);
  delay(commandsData[2]);
  digitalWrite(RED_PIN, LOW);      

  digitalWrite(BLUE_PIN, HIGH);
  delay(commandsData[3]);
  digitalWrite(BLUE_PIN, LOW);     

  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  if (ifGreeting == 0) {greeting();};
  parsing();       // функция парсинга
  if (recievedFlag) {                           // если получены данные
    recievedFlag = false;
  
  if (commandName.equalsIgnoreCase("RECORD")){

    for (int i=0; i < commandsData[0]; i++){
      ptvFrame();
      delay(commandsData[1]);      
    }
  } else {
    Serial.println("No such command. Try RECORD");
  }
    ifGreeting=0;
    commandName = "";
  }
}
