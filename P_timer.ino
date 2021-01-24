
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//startig variables
int work_time = 1 * 60;
int break_time = 0.1 * 60;

int screen = 1;
int change = 0;
int button_S = 4; //pin number
int button_C = 12; //pin number
unsigned long start_time;
int time_left = work_time;


boolean work = true;
boolean start = false;
boolean first_start = true;
boolean control_C = false;
boolean control_S = false;
boolean select = false;


void setup() {
  pinMode(button_C, INPUT);
  pinMode(button_S, INPUT);
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  
  display.clearDisplay();
  display.setCursor(16, 16);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.println("POMODORO");
  display.println("   TIMER");
  display.display();
  delay(1000);
}

void loop() {
  // 'Select' button pulse
  if(digitalRead(button_S) == 1 && control_S==0){
    select = 1;
    control_S = 1;}
  if(digitalRead(button_S) == 0){
    control_S = 0;}
  // 'Change' button pulse
  if(digitalRead(button_C) == 1 && control_C==0){
    change += 1;
    control_C = 1;}
  if(digitalRead(button_C) == 0){
    control_C = 0;}
  // Logic for each 'screen'

  switch(screen) {
    case 1:
    //screen number 1
    {
      if(change == 0 && select){select = 0;}
      //start or stop timer 
      if (change == 1 && select){
        start = !start;
        select = 0;}
      //screen change  
      if (change == 2 && select){
        screen = 2;
        change = 0;
        start = 0;
        select = 0;}

      //timer working logic
      if(start==true){
        if(time_left < 0){
          if(work){time_left = break_time;}
          if(!work){time_left = work_time;}
          first_start = true;
          work = !work;
          }
        if(work){
          if(first_start){start_time = millis(); first_start = false;}
          time_left = timer_counter(work_time, start_time);}
        if(!work){
          if(first_start){start_time = millis(); first_start = false;}
          time_left = timer_counter(break_time, start_time);}
            }
       if(change > 2){change = 0;}
      }
      break;
    case 2:
    //screen number 2
    {
      //work minutes select
      if (change == 1 && select){
        work_time += 60;
        if(work_time > 3600){work_time = 0;}
        select = false;}
      //work seconds select
      if (change == 2 && select){
        work_time += 1;
        if(work_time > 3600){work_time = 0;}
        select = false;}
      // break minutes select
      if (change == 3 && select){
        break_time += 60;
        if(break_time > 3600){break_time = 0;}
        select = false;}
      // break seconds select
      if (change == 4 && select){
        break_time += 1;
        if(break_time > 3600){break_time = 0;}
        select = false;}
      // apply changes
      if (change == 5 && select){
        screen = 1;
        change = 0;
        select = false;}
      if (change > 5){change = 0;}
      }
      break;
    }

    timerScreen(screen, change, work, start, work_time, break_time, time_left);
    
    //end of main loop
    }

int timer_counter(int upper_bound, unsigned long start_time){
  unsigned long elapsed_time = (millis() - start_time)/1000;
  Serial.println(elapsed_time);
  return upper_bound - elapsed_time;
  }

void timerScreen(int screen, int change, boolean work, boolean start, int work_time, int break_time, int time_left){
  if (screen == 1){
    display.clearDisplay();
    //print time
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 8);
    displayTime(time_left);
    if(work){
      display.setCursor(0, 32);
      displayTime(break_time);
    }
    if(!work){
      display.setCursor(0, 32);
      displayTime(work_time);
      }
    //print controls
    display.setCursor(80, 16);
    display.setTextSize(1);
    if(!start){display.print(" START");}else{display.print(" STOP");}
    display.setCursor(80, 40);
    display.print("SETTINGS");
    display.drawLine(70, 0, 70, 64, SSD1306_WHITE);
    
    if(change == 1){
      display.drawLine(80, 10, 90, 10, SSD1306_WHITE);
      }
    if(change == 2){
      display.drawLine(80, 35, 90, 35, SSD1306_WHITE);
      }
          
    display.display();  
  }
  
  if (screen == 2){
    display.clearDisplay();
    display.setCursor(0, 8);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.print("SETTINGS  PLACEHOLDER");
    display.display();
    }
  }
  
void displayTime(int t){
  int minutes = (int)(t/ 60);
  int seconds = t%60;
  if(minutes<10){
      display.print("0");
      }
    display.print(minutes);
    display.print(":");
    if(seconds<10){
      display.print("0");
      }
    display.print(seconds);
  }
