#include <Keypad.h>
#include <Servo.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ----- TECLADO -----
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[4] = {2,3,4,5}; 
byte colPins[4] = {6,7,8,9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ----- PINES -----
Servo servo;
const int servoPin = 10;
const int buzzerPin = 11;
const int ledVerde = 12;
const int ledRojo = 13;

// ----- EEPROM -----
#define EEPROM_ADDR 0
#define PASS_LENGTH 4

// ----- VARIABLES -----
String password = "";
String input = "";
int intentos = 0;
bool puertaAbierta = false;

// ----- EEPROM -----
void cargarPassword() {
  password = "";
  for (int i = 0; i < PASS_LENGTH; i++) {
    char c = EEPROM.read(EEPROM_ADDR + i);
    if (c >= '0' && c <= '9') {
      password += c;
    }
  }
  if (password.length() != PASS_LENGTH) {
    password = "0000";
    guardarPassword(password);
  }
}

void guardarPassword(String nueva) {
  for (int i = 0; i < PASS_LENGTH; i++) {
    EEPROM.write(EEPROM_ADDR + i, nueva[i]);
  }
}

// ----- SETUP -----
void setup() {
  servo.attach(servoPin);
  servo.write(0);

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  cargarPassword();

  lcd.setCursor(0,0);
  lcd.print("Ingrese clave");
}

// ----- LOOP -----
void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == 'A') {
      modoConfiguracion();
    }
    else if (key == '#') {
      if (puertaAbierta) {
        cerrarPuerta();
      } else {
        verificarPassword();
      }
    }
    else if (key == '*') {
      input = "";
      actualizarLCD();
    }
    else {
      if (input.length() < PASS_LENGTH) {
        input += key;
        actualizarLCD();
      }
    }
  }
}

// ----- LCD INPUT -----
void actualizarLCD() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Clave:");

  lcd.setCursor(0,1);
  for (int i = 0; i < input.length(); i++) {
    lcd.print("*");
  }
}

// ----- VERIFICAR -----
void verificarPassword() {
  lcd.clear();

  if (input == password) {
    accesoCorrecto();
  } else {
    accesoIncorrecto();
  }

  input = "";
  delay(1000);

  lcd.clear();
  lcd.print("Ingrese clave");
}

// ----- CORRECTO -----
void accesoCorrecto() {
  lcd.print("Acceso correcto");

  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledRojo, LOW);

  tone(buzzerPin, 1000, 200);

  abrirPuerta();
  puertaAbierta = true;

  digitalWrite(ledVerde, LOW);
  intentos = 0;
}

// ----- INCORRECTO -----
void accesoIncorrecto() {
  lcd.print("Clave incorrecta");

  intentos++;

  digitalWrite(ledRojo, HIGH);
  tone(buzzerPin, 500, 500);
  delay(1000);
  digitalWrite(ledRojo, LOW);

  if (intentos >= 3) {
    alarma();
  }
}

// ----- ALARMA -----
void alarma() {
  lcd.clear();
  lcd.print("ALERTA");

  for (int i = 0; i < 5; i++) {
    tone(buzzerPin, 300);
    digitalWrite(ledRojo, HIGH);
    delay(300);
    noTone(buzzerPin);
    digitalWrite(ledRojo, LOW);
    delay(300);
  }
  intentos = 0;
}

// ----- SERVO -----
void abrirPuerta() {
  for (int pos = 0; pos <= 90; pos++) {
    servo.write(pos);
    delay(10);
  }
}

void cerrarPuerta() {
  lcd.clear();
  lcd.print("Cerrando...");

  for (int pos = 90; pos >= 0; pos--) {
    servo.write(pos);
    delay(10);
  }

  puertaAbierta = false;

  lcd.clear();
  lcd.print("Ingrese clave");
}

// ----- CONFIG -----
void modoConfiguracion() {
  lcd.clear();
  lcd.print("Clave actual");

  String actual = leerInput();

  if (actual == password) {

    lcd.clear();
    lcd.print("Nueva clave");
    String nueva = leerInput();

    lcd.clear();
    lcd.print("Confirmar");
    String confirm = leerInput();

    if (nueva == confirm && nueva.length() == PASS_LENGTH) {
      password = nueva;
      guardarPassword(password);

      lcd.clear();
      lcd.print("Guardado");
      delay(1500);
    } else {
      lcd.clear();
      lcd.print("Error");
      delay(1500);
    }

  } else {
    lcd.clear();
    lcd.print("Incorrecta");
    delay(1500);
  }

  lcd.clear();
  lcd.print("Ingrese clave");
}

// ----- INPUT -----
String leerInput() {
  String temp = "";

  lcd.setCursor(0,1);

  while (true) {
    char k = keypad.getKey();

    if (k) {
      if (k == '#') break;
      else if (k == '*') {
        temp = "";
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
      }
      else if (temp.length() < PASS_LENGTH) {
        temp += k;
        lcd.print("*");
      }
    }
  }
  return temp;
}