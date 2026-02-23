/* 
 Title        : OLEDMenuNAv.ino
 Description  : This is a program to showcase how the Inland OLED 1.2" OLED can be used to act as a functional display module
 MCU          : Arduino Uno R3
 Started      : 02/14/2026
 Last Edited  : 02/23/2026
 By           : Robert J Guziec

 Pinout:
 D2 : Selection pushbutton     | ISR INT0
 D3 : Confirmation push button | ISR INT1
 D8 : OLED RES
 D9 : OLED DC
 D10: OLED CS
 D11: OLED DATA
 D13: OLED CLK 

*/

#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

// Initialize the inland 1.2" OLED display using the u8g2 library
U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

// * * * GROSS VARIABLES * * *
volatile unsigned char selVal = 0;
volatile unsigned char confirmSel = 0;
volatile unsigned char chip = 0;

// * * * MAIN LOGIC * * *

void setup() {
  u8g2.begin();
  EICRA = 0x0F;
  EIMSK = 0x03;

  Serial.begin(9600);
}

void loop() {
  u8g2.setFlipMode(1); // Flip the display

  u8g2.firstPage();
  do {
    // Frame and test for the display, this is constant throughout the whole program processes
    u8g2.drawFrame(3, 3, 122, 58);
    u8g2.drawFrame(3, 3, 122, 18);
    u8g2.setFont(u8g2_font_5x7_tr);

  // IC selection for main menu and sub menu
  if (confirmSel && (selVal == 1)){
    chip = 1;
    confirmSel = 0;
  }
  else if (confirmSel && (selVal == 2)){
    chip = 2;
    confirmSel = 0;
  }
  else if (confirmSel && (selVal == 3)){
    chip = 3;
    confirmSel = 0;
  }
  else if (confirmSel && (selVal == 4)){
    chip = 4;
    confirmSel = 0;
  }
  else if (confirmSel && (selVal == 5)){
    chip = 5;
    confirmSel = 0;
  }
  else if(confirmSel && (selVal == 6)){
    chip = 6;
    confirmSel = 0;
  }

  // Swwitch case for which display page should be active
  switch (chip){
    case 1:
      Display7400Page();
      SubMenuSel();
      break;
    case 2:
      Display7402Page();
      SubMenuSel();
      break;
    case 3:
      Display7404Page();
      SubMenuSel();
      break;
    case 4:
      Display7408Page();
      SubMenuSel();
      break;
    case 5:
      Display7432Page();
      SubMenuSel();
      break;
    case 6:
      Display7486Page();
      SubMenuSel();
      break;
    default:
      DisplayMainMenu();
      MainMenuSel();
      break;
  }

  // Why does this need to be after everything?
  if (confirmSel && (selVal == 8)){
      chip = 0;
      confirmSel = 0;
  }
  
  } while ( u8g2.nextPage() );
  
  _delay_ms(10);
}


// * * * INTERUPTS * * *
ISR(INT0_vect) {
  selVal++;
}

ISR(INT1_vect) {
  confirmSel ^= 1;
}


// * * * PAGE FUNCTIONS * * * 

// Main Menu Page
void DisplayMainMenu() {
  u8g2.drawStr(15, 15, "Select a logic gate");
  u8g2.drawStr(15, 32, "7400");
  u8g2.drawStr(15, 44, "7402");
  u8g2.drawStr(15, 56, "7404");
  u8g2.drawStr(65, 32, "7408");
  u8g2.drawStr(65, 44, "7432");
  u8g2.drawStr(65, 56, "7486");
}

void Display7400Page(){
  u8g2.drawStr(10, 15, "7400 Quad NAND gate");
  u8g2.drawStr(7, 32, "This logic gate is an");
  u8g2.drawStr(7, 44, "essential logic gate");
  u8g2.drawStr(15, 56, "Test"); 
  u8g2.drawStr(65, 56, "Back");
}

void Display7402Page(){
  u8g2.drawStr(10, 15, "7402 Quad NOR gate");
  u8g2.drawStr(7, 32, "This logic gate is an");
  u8g2.drawStr(7, 44, "actually trash :(");
  u8g2.drawStr(15, 56, "N/A"); 
  u8g2.drawStr(65, 56, "Back");
}

void Display7404Page(){
  u8g2.drawStr(18, 15, "7404 Octal NOT gate");
  u8g2.drawStr(7, 32, "This logic gate inverts");
  u8g2.drawStr(7, 44, "an asserted signal");
  u8g2.drawStr(15, 56, "N/A"); 
  u8g2.drawStr(65, 56, "Back");
}

void Display7408Page(){
  u8g2.drawStr(18, 15, "7408 Quad AND gate");
  u8g2.drawStr(7, 32, "This logic gate only is");
  u8g2.drawStr(7, 44, "true if asserted both");
  u8g2.drawStr(15, 56, "Test"); 
  u8g2.drawStr(65, 56, "Back");
}

void Display7432Page(){
  u8g2.drawStr(18, 15, "7408 Quad OR gate");
  u8g2.drawStr(7, 32, "This logic gate only is");
  u8g2.drawStr(7, 44, "true if any one is high");
  u8g2.drawStr(15, 56, "Test"); 
  u8g2.drawStr(65, 56, "Back");
}

void Display7486Page(){
  u8g2.drawStr(18, 15, "7408 Quad XOR gate");
  u8g2.drawStr(7, 32, "This logic gate only is ");
  u8g2.drawStr(7, 44, "an exclusive OR gate");
  u8g2.drawStr(15, 56, "Test"); 
  u8g2.drawStr(65, 56, "Back");
}

// * * * CURSOR FUNCTIONS * * *

// Main menu selection cursor
void MainMenuSel() {

  if (selVal == 1) {
    u8g2.drawBox(7, 27, 5, 5);
  }
  else if (selVal == 2) {
    u8g2.drawBox(7, 39, 5, 5);
  }
  else if (selVal == 3) {
    u8g2.drawBox(7, 51, 5, 5);
  }
  else if (selVal == 4) {
    u8g2.drawBox(57, 27, 5, 5);
  }
  else if (selVal == 5) {
    u8g2.drawBox(57, 39, 5, 5);
  }
  else if (selVal == 6) {
    u8g2.drawBox(57, 51, 5, 5);
  }

  if (selVal > 6) {
    selVal = 1;
  }
}

// Sub menu selection cursor
void SubMenuSel(){

  if ((selVal < 7) || (selVal > 8)){
    selVal = 7;
  }
   if (selVal == 7) {
    u8g2.drawBox(7, 51, 5, 5);
  }
  else if (selVal == 8) {
    u8g2.drawBox(57, 51, 5, 5);
  }

}
