/*
 * https://www.minitronica.com/juego-simon-dice-con-arduino/ 
 * Visitanos en www.minitronica.com
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
 
byte uno = 1;
byte dos = 2;
byte tre = 3;
byte cua = 4;
// Declaramos el pin para el zumbador piezoelectrico
#define zumbador 12  
byte LEVEL = 0;
byte inic = 0;

// Declaramos alguna variables
long sequence[20];             // Array que alberga la secuencia
int contador = 0;              // Contador
long input = 5;                // Indicador de boton pulsado
int wait = 100;                // Retraso segun la secuencia se incrementa
int puntuacion_maxima = 20;    // Puntuación máxima donde acaba el juego 
 
// Declaramos algunas variables para los efectos musicales
int length = 15;                  // Numero de notas de la melodia
char notes[] = "ccggaagffeeddc "; // Notas de la melodia (cada letra es una nota distinta)
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };  // Duracion de cada tono en un array
byte tempo = 100;  //Tempo de la melodia
 
   
void setup() {
  lcd.begin(16, 2); 
  pinMode(zumbador, OUTPUT);

  // Hacemos que suene la melodia al arrancar el Arduino    
   lcd.setCursor(0, 0);  lcd.print("  MEMORIN GAME"); 
   lcd.setCursor(0, 1);  lcd.print("    lcd 16x2"); 
   delay(700);  lcd.clear();

   lcd.setCursor(0, 0);  lcd.print("      HECHO"); 
   lcd.setCursor(0, 1);  lcd.print("       Por"); 
   delay(700);  lcd.clear();

   lcd.setCursor(0, 0);  lcd.print("     Walter"); 
   lcd.setCursor(0, 1);  lcd.print("    Mauricio"); 
   delay(700);  lcd.clear();

  lcd.setCursor(0, 0); lcd.print("  OK INICIAMOS");
  delay(500); lcd.clear(); 
  felicitacion();
  }
  
  
void loop() {
  int xy;        // Declarar variables
  xy = analogRead(0);     // Asignar 'xy' para las entradas analógicas Arduino Shields (botones)
  if(xy < 1000){ inic = 1; lcd.clear(); }      // if el button es RIGHT  


  if(inic == 1){
  mostrar_secuencia();  // Reproduce la sequencia
  leer_secuencia();     // Lee la sequencia
  delay(100);          // Espera 1 segundo
  } else {
    lcd.setCursor(0,0); lcd.print("apriet cualquier");
    lcd.setCursor(0,1); lcd.print("tecla pa iniciar");
  }
}
  
  
 // Funcion para definir las notas y sus frecuencias
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 
  for(int i = 0; i < 8; i++){
     if(names[i] == note){ playtone(tones[i], duration); }
     }
}
 
 // Funcion para definir las notas segun la duración y el tono
void playtone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone *2) {
      digitalWrite(zumbador, HIGH);
      delayMicroseconds(tone);
      digitalWrite(zumbador, LOW);
      delayMicroseconds(tone);
    }
  }     
   
 // Funciones para encender los leds y reproducir el tono correspondiente
void flash_rojo() {
  //lcd.setCursor(3, 1);  lcd.print("1");
  playtone(2273,wait);         
  lcd.clear(); delay(60);
}
  
void flash_azul() {
  //lcd.setCursor(12, 1);  lcd.print("4");
  playtone(1700,wait);            
  lcd.clear(); delay(60);
}
  
void flash_amarillo() {
  //lcd.setCursor(9, 1);  lcd.print("3");
  playtone(1275,wait);             
  lcd.clear(); delay(60);
} 
  
void flash_verde() {
  //lcd.setCursor(6, 1);  lcd.print("2");
  playtone(1136,wait);             
  lcd.clear(); delay(60);
} 
   
// Funcion para mostrar que botón se tenia que pulsar en caso de error del jugador
void mostrar_boton_correcto(long led) {
    switch(led) {
        case 0:
          lcd.setCursor(3, 1);  lcd.print(uno); 
          flash_rojo();
          break;
        case 1:
          lcd.setCursor(6, 1);  lcd.print(dos); 
          flash_verde();
          break;
        case 2:
          lcd.setCursor(9, 1);  lcd.print(tre); 
          flash_amarillo();
          break;
        case 3:
          lcd.setCursor(12, 1);  lcd.print(cua);
          flash_azul();
          break;
      }
      delay(50);
} 
  
// Función que reproduce la canción al arrancar el arduino y para el juego cuando se llega a la puntuacion maxima
void felicitacion() {
  lcd.setCursor(0, 0); lcd.print("   1  2  3  4");
  delay(400); lcd.clear();
  lcd.setCursor(0, 0); lcd.print("   5  6  7  8");

  for(int i = 0; i < length; i++){
   if(notes[i] == ' '){ delay(beats[i] * tempo); } // rest
   else { playNote(notes[i], beats[i] * tempo); }
   
   delay(tempo / 3); 
  }
   
  delay(500);   
  lcd.clear();
  resetcontador();                    
  }
    
 // Reseteamos contadores
void resetcontador() {
  contador = 0;
  wait = 500;
}
   
  
// Funcion para crear y reproducir los patrones
void mostrar_secuencia() { // Con esto hacemos que la función Random sea aun mas aleatoria 

    if(LEVEL < 4){ uno = 1;  dos = 2; tre = 3;  cua = 4; }  
    else if(LEVEL < 8){ uno = 2;  dos = 3; tre = 4;  cua = 5; } 
    else if(LEVEL < 12){ uno = 3;  dos = 4; tre = 5;  cua = 6; } 
    else if(LEVEL < 15){ uno = 4;  dos = 5; tre = 6;  cua = 7; }  
    else if(LEVEL < 18){ uno = 5;  dos = 6; tre = 7;  cua = 8; }  
    else if(LEVEL < 20){ uno = 6;  dos = 7; tre = 8;  cua = 9; }

  if(LEVEL == 0){
  }  else {
  if(LEVEL < 10){
    lcd.setCursor(0,0); lcd.print("     NIVEL");
    lcd.setCursor(7,1); lcd.print(LEVEL);
    } else {
    lcd.setCursor(0,0); lcd.print("     NIVEL");
    lcd.setCursor(6,1); lcd.print(LEVEL);
    }delay(300); lcd.clear(); delay(300);
    }
  
  //randomSeed(analogRead(10));  
  sequence[contador] = random(4);       
  
  for(int i=0; i<contador; i++){ mostrar_boton_correcto(sequence[i]); }
    
  wait = 500 - (contador * 15);        
  contador++;
  LEVEL = LEVEL + 1;
  }
  
 
// Funcion para leer los botones que pulsa el jugador
void leer_secuencia() {
   for(int i=1; i<contador; i++){              
      while(input==5){ botons(); }
    
  if(sequence[i-1] == input){              
        mostrar_boton_correcto(input);                          
        if(i == puntuacion_maxima){ 
          lcd.setCursor(0, 0); lcd.print("  Felicidades!");
          lcd.setCursor(0, 1); lcd.print("    YOU WIN!!");
          delay(2000); lcd.clear();
          lcd.setCursor(0, 0); lcd.print("  LO LOGRASTE!");
          lcd.setCursor(0, 1); lcd.print(" EN HORA BUENA!");
          delay(1000);
          felicitacion(); 
          }
      } 
  else {

    if(LEVEL < 4){
      lcd.setCursor(3, 0); lcd.print("PERDISTE");
      lcd.setCursor(3, 1); lcd.print("NI MODO!!");
      } else if(LEVEL < 8){
        lcd.setCursor(3, 0); lcd.print("  UJUU!!");
        lcd.setCursor(3, 1); lcd.print("NI MODO!!");
        } else if(LEVEL < 12){
          lcd.setCursor(3, 0); lcd.print("A LA MITAD");
          lcd.setCursor(3, 1); lcd.print(" GAME OVER!!");
        } else if(LEVEL < 15){
          lcd.setCursor(3, 0); lcd.print("JA JA JA JA");
          lcd.setCursor(1, 1); lcd.print("EN OTRA SERA!!");
        } else if(LEVEL < 18){
          lcd.setCursor(3, 0); lcd.print("CASII..!!");
          lcd.setCursor(3, 1); lcd.print(" GAME OVER");
        } else if(LEVEL < 20){
          lcd.setCursor(1, 0); lcd.print("TANTO ESFUERZO!");
          lcd.setCursor(3, 1); lcd.print(" GAME OVER");
        }
        playtone(4545,1500);                  
        delay(500);
        lcd.clear();
        LEVEL = 0; 
        inic = 0;
        mostrar_boton_correcto(sequence[i-1]);                 
        mostrar_boton_correcto(sequence[i-1]);                 
        mostrar_boton_correcto(sequence[i-1]);
        delay(1000);
        felicitacion();
        resetcontador();                          
        } 
        input = 5;                                   
        }
}  

void botons() {
     int xy;        // Declarar variables
     xy = analogRead(0);     // Asignar 'xy' para las entradas analógicas Arduino Shields (botones)

    if(xy < 70){ input = 3; }      // if el button es RIGHT
    else if(xy < 160){ input = 2; }  // if el button es UP
    else if(xy < 295){ input = 2; }  // if el button es DAWN
    else if(xy < 470){ input = 1; }  // if el button es LEFT //
    else if(xy < 700){ input = 0; }  // if el button es SELECT //
    else {  }        
}
