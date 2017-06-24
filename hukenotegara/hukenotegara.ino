#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLEDs.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>
#include <time.h>


Pololu3pi robot;
unsigned int sensors[4]; // an array to hold sensor values
unsigned int last_proportional = 0;
int state = 0;
int val = 0;
int old_val = 0;
long integral = 0;
int money = 0 ;
int job = 0 ;
int family = 0;
int daice = 0;
int computer = 0;
int doragonhp = 20;
int doragonatack = 5;
int mimichp = 10;
int mimicatack = 10;
int maxhp = 20;
int hp = 20;
int def = 0;
int atack = 5;
int speeed = 5;
int mp = 5 ;
int expo = 0;
int player = 0;
int treasure = 0;
int up_len = 0;
int down_len = 0;
char ue [8];
char sita [8];
char welcomee [] = "welcome to this world";
char thankyou  [] = "hukesan  arigatou  korekaramo  yorosiku!!!";



const char welcome_line1[] PROGMEM = " Pololu";
const char welcome_line2[] PROGMEM = "3\xf7 Robot";

const char welcome[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";
const char levels[] PROGMEM = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

void up_display(char a[]){  
  OrangutanLCD::clear();
  OrangutanLCD::gotoXY(0, 0);
  up_len = strlen(a);
  for (int j = 0 ; j < up_len - 7 ; j++) {
    for (int i = 0 ; i < 8 ; i++) {
      ue[i] = a[i + j];
    }
  OrangutanLCD::print(ue);
  delay(400);
  OrangutanLCD::clear();
  OrangutanLCD::gotoXY(0, 0);
  }
  }
void down_display(char b[]){  
  OrangutanLCD::clear();
  OrangutanLCD::gotoXY(0, 1);
  down_len = strlen(b);
  for (int j = 0 ; j < down_len - 7 ; j++) {
    for (int i = 0 ; i < 8 ; i++) {
      sita[i] = b[i + j];
    }
  OrangutanLCD::print(sita);
  delay(400);
  OrangutanLCD::clear();
  OrangutanLCD::gotoXY(0, 1);
  }
  }
void load_custom_characters()
{
  OrangutanLCD::loadCustomCharacter(levels + 0, 0); // no offset, e.g. one bar
  OrangutanLCD::loadCustomCharacter(levels + 1, 1); // two bars
  OrangutanLCD::loadCustomCharacter(levels + 2, 2); // etc...
  OrangutanLCD::loadCustomCharacter(levels + 3, 3);
  OrangutanLCD::loadCustomCharacter(levels + 4, 4);
  OrangutanLCD::loadCustomCharacter(levels + 5, 5);
  OrangutanLCD::loadCustomCharacter(levels + 6, 6);
  OrangutanLCD::clear(); // the LCD must be cleared for the characters to take effect
}

void display_readings(const unsigned int *calibrated_values)
{
  unsigned char i;

  for (i = 0; i < 5; i++) {
    const char display_characters[10] = { ' ', 0, 0, 1, 2, 3, 4, 5, 6, 255 };
    char c = display_characters[calibrated_values[i] / 101];
    OrangutanLCD::print(c);
  }
}

long randNumber;
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  unsigned int counter; // used as a simple timer

  // This must be called at the beginning of 3pi code, to set up the
  // sensors.  We use a value of 2000 for the timeout, which
  // corresponds to 2000*0.4 us = 0.8 ms on our 20 MHz processor.
  robot.init(2000);

  load_custom_characters(); // load the custom characters

  // Play welcome music and display a message
  OrangutanLCD::printFromProgramSpace(welcome_line1);
  OrangutanLCD::gotoXY(0, 1);
  OrangutanLCD::printFromProgramSpace(welcome_line2);
  OrangutanBuzzer::playFromProgramSpace(welcome);
  delay(1000);

  // Display battery voltage and wait for button press
  while (!OrangutanPushbuttons::isPressed(BUTTON_B))
  {
    int bat = OrangutanAnalog::readBatteryMillivolts();

    OrangutanLCD::clear();
    OrangutanLCD::print(bat);
    OrangutanLCD::print("mV");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("Press B");

    delay(100);
  }

  // Always wait for the button to be released so that 3pi doesn't
  // start moving until your hand is away from it.
  OrangutanPushbuttons::waitForRelease(BUTTON_B);
  delay(1000);

  // Auto-calibration: turn right and left while calibrating the
  // sensors.
  for (counter = 0; counter < 80; counter++)
  {
    if (counter < 20 || counter >= 60)
      OrangutanMotors::setSpeeds(40, -40);
    else
      OrangutanMotors::setSpeeds(-40, 40);

    // This function records a set of sensor readings and keeps
    // track of the minimum and maximum values encountered.  The
    // IR_EMITTERS_ON argument means that the IR LEDs will be
    // turned on during the reading, which is usually what you
    // want.
    robot.calibrateLineSensors(IR_EMITTERS_ON);

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  OrangutanMotors::setSpeeds(0, 0);
   OrangutanLCD::clear();
  up_display(welcomee); 
  down_display(thankyou); 
  delay(2000);
   
  OrangutanLCD::clear();
  OrangutanLCD::print("select");
  OrangutanLCD::gotoXY(0, 1);
  OrangutanLCD::print("job");
  delay(2000);
  OrangutanLCD::clear();
  OrangutanLCD::print("A");
  OrangutanLCD::gotoXY(0, 1);
  OrangutanLCD::print("Swordmans");
  delay(2000);
  OrangutanLCD::clear();
  OrangutanLCD::print("B");
  OrangutanLCD::gotoXY(0, 1);
  OrangutanLCD::print("Witch");
  delay(2000);
  OrangutanLCD::clear();
  OrangutanLCD::print("C");
  OrangutanLCD::gotoXY(0, 1);
  OrangutanLCD::print("Robber");
  delay(2000);




  while (job == 0) {
    
    if (OrangutanPushbuttons::isPressed(BUTTON_A)) {
      job = 1;
    }
    if (OrangutanPushbuttons::isPressed(BUTTON_B)) {
      job = 2;
    }
    if (OrangutanPushbuttons::isPressed(BUTTON_C)) {
      job = 3;
    }
  }




  // Display calibrated values as a bar graph.

  // Read the sensor values and get the position measurement.
  //  while (!OrangutanPushbuttons::isPressed(BUTTON_B)) {
  //    unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);
  //
  //    // Display the position measurement, which will go from 0
  //    // (when the leftmost sensor is over the line) to 4000 (when
  //    // the rightmost sensor is over the line) on the 3pi, along
  //    // with a bar graph of the sensor readings.  This allows you
  //    // to make sure the robot is ready to go.
  //    OrangutanLCD::clear();
  //    OrangutanLCD::print(sensors[1]);
  //    OrangutanLCD::gotoXY(0, 1);
  //    display_readings(sensors);
  //
  //    delay(100);
  //  }
}

void loop() {
  OrangutanLCD::clear();
  OrangutanLCD::print("money ");
  OrangutanLCD::print(money);
  OrangutanLCD::gotoXY(0, 1);
  if (job == 1) {
    OrangutanLCD::print("Swordsman ");
  }
  if (job == 2) {
    OrangutanLCD::print("Witch");
  }
  if (job == 3) {
    OrangutanLCD::print("Robber");
  }

  while (!OrangutanPushbuttons::isPressed(BUTTON_B)) {
  
  }

 while (!OrangutanPushbuttons::isPressed(BUTTON_A)) {

    robot.readLine(sensors, IR_EMITTERS_ON);
    OrangutanLCD::clear();
  OrangutanLCD::print("press A ");
   OrangutanLCD::gotoXY(0, 1);
    display_readings(sensors);
    delay(100);

  }

  OrangutanPushbuttons::waitForRelease(BUTTON_A);
  OrangutanLCD::clear();
  if (daice == 0) {
    randNumber = random(1, 7);
  }
  if (daice == 1) {
  OrangutanLCD::clear();
  OrangutanLCD::print("use");
  OrangutanLCD::gotoXY(0, 1);
  OrangutanLCD::print("Wdice??");
  delay(1000);
  OrangutanLCD::clear();
  OrangutanLCD::print("yes = A");
  OrangutanLCD::gotoXY(0, 1);
  OrangutanLCD::print("no = B");
  
    player = 0;
    while (player == 0) {
    
    if (OrangutanPushbuttons::isPressed(BUTTON_B)) {
      randNumber = random(1, 7);
      player = 1;
    }
    if (OrangutanPushbuttons::isPressed(BUTTON_A)) {
    OrangutanLCD::clear();
    OrangutanLCD::print("use");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("W dice!!");
    delay(1000);
      randNumber = random(6,13);
      daice = 0;
      player = 1;
    }
 
  }



    
  }
  OrangutanLCD::clear();
  OrangutanLCD::print(randNumber);
  delay(1000);
  OrangutanMotors::setSpeeds(40, 40);
  while (!randNumber == 0) {
    robot.readLine(sensors, IR_EMITTERS_ON);
    if ((sensors[0] > 750) && (sensors[1] > 750 ) && (sensors[2] > 750 ) && (sensors[3] > 750 ) && (sensors[4] > 750 ) && (state == 0)) {


      state = 1 - state;
      randNumber--;
    }
    if (!( (sensors[0] > 750) && (sensors[1] > 750 ) && (sensors[2] > 750 ) && (sensors[3] > 750 ) && (sensors[4] > 750 ) ) && (state == 1)) {
      state = 1 - state;
    }
    if ((sensors[0] < 100) && (sensors[1] < 100 ) && (sensors[2] < 100 ) && (sensors[3] < 100  ) && (sensors[4] > 700 )) {
      delay(100);
      OrangutanMotors::setSpeeds(0, 0);
      delay(100);
      OrangutanMotors::setSpeeds(20, -20);
      delay(1000);
      OrangutanMotors::setSpeeds(40, 40);
      delay(500);


    }
    if ((sensors[0] > 700) && (sensors[1] < 100 ) && (sensors[2] < 100 ) && (sensors[3] < 100  ) && (sensors[4] < 100 )) {
      delay(100);
      OrangutanMotors::setSpeeds(0, 0);
      delay(100);
      OrangutanMotors::setSpeeds(-20, 20);
      delay(1000);
      OrangutanMotors::setSpeeds(40, 40);
      delay(500);

    }

  }
  delay(400);
  OrangutanMotors::setSpeeds(0, 0);
  while (!OrangutanPushbuttons::isPressed(BUTTON_A)) {

    robot.readLine(sensors, IR_EMITTERS_ON);
    OrangutanLCD::clear();
    OrangutanLCD::gotoXY(0, 1);
    display_readings(sensors);
    delay(100);
  }

  OrangutanPushbuttons::waitForRelease(BUTTON_A);
  robot.readLine(sensors, IR_EMITTERS_ON);
  if ((sensors[0] > 500) && (sensors[1] > 500 ) && (sensors[2] < 200) && (sensors[3] < 200 ) && (sensors[4] < 200 )) {
    OrangutanMotors::setSpeeds(20, -20);
    delay(900);
    OrangutanMotors::setSpeeds(0, 0);

  }
  if ((sensors[0] < 200) && (sensors[1] < 200 ) && (sensors[2] < 200) && (sensors[3] > 500 ) && (sensors[4] > 500 )) {
    OrangutanMotors::setSpeeds(-20, 20);
    delay(900);
    OrangutanMotors::setSpeeds(0, 0);


  }
  if ((sensors[0] > 500) && (sensors[1] < 200 ) && (sensors[2] < 200) && (sensors[3] < 200 ) && (sensors[4] > 500 )) {
    OrangutanMotors::setSpeeds(-40, -40);
    delay(1000);
    OrangutanMotors::setSpeeds(0, 0);


  }
  if ((sensors[0] < 100) && (sensors[1] > 500 ) && (sensors[2] > 500 ) && (sensors[3] > 500  ) && (sensors[4] < 100 )) {
    OrangutanLCD::clear();
    OrangutanLCD::print("I won by");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("gambling");
    delay(3000);
    OrangutanLCD::clear();
    OrangutanLCD::print("get");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("10yen");
    delay(3000);

    money = money + 10 ;
  }
  if ((sensors[0] < 200) && (sensors[1] < 200 ) && (sensors[2] < 200) && (sensors[3] < 200 ) && (sensors[4] < 200 )) {

    OrangutanLCD::clear();
    OrangutanLCD::print("get the");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("job");
    delay(3000);
    OrangutanLCD::clear();
    OrangutanLCD::print("be a");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("pilot");
    delay(3000);
    job = 2;
  }
  if ((sensors[0] > 500) && (sensors[1] > 500 ) && (sensors[2] < 200 ) && (sensors[3] > 500 ) && (sensors[4] > 500 )) {

    OrangutanLCD::clear();
    OrangutanLCD::print("get the");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("W daice");
    delay(3000);
    daice = 1;

  }
  if ((sensors[0] > 500) && (sensors[1] > 500 ) && (sensors[2] > 500 ) && (sensors[3] > 500 ) && (sensors[4] > 500 )) {

    OrangutanLCD::clear();
    OrangutanLCD::print("come the");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("dragon!!");
    delay(3000);
    doragonhp = 20;

    while (!(doragonhp == 0 || hp == 0)) {
      OrangutanLCD::clear();
      OrangutanLCD::print("buttle");
      OrangutanLCD::gotoXY(0, 1);
      OrangutanLCD::print("dragon!!");
      delay(2000);
      player = 0;
      OrangutanLCD::clear();
      OrangutanLCD::print("comand");
      OrangutanLCD::gotoXY(0, 1);
      OrangutanLCD::print("janken");
      while (player == 0) {
        if (OrangutanPushbuttons::isPressed(BUTTON_A)) {
          player = 1;
        }
        if (OrangutanPushbuttons::isPressed(BUTTON_B)) {
          player = 2;
        }
        if (OrangutanPushbuttons::isPressed(BUTTON_C)) {
          player = 3;
        }
      }
      computer = random(1, 4);
      if (computer == player) {
        OrangutanLCD::clear();
        OrangutanLCD::print("dorrow");
        delay(1000);
      }
      else if (player == 1 && computer == 2) {
        OrangutanLCD::clear();
        OrangutanLCD::print("you");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("atack!");
        delay(1000);
        OrangutanLCD::clear();
        OrangutanLCD::print(atack);
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("damage");
        delay(3000);
        doragonhp = doragonhp - atack;
      }
      else if (player == 2 && computer == 3) {
        OrangutanLCD::clear();
        OrangutanLCD::print("you");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("atack!");
        delay(1000);
        OrangutanLCD::clear();
        OrangutanLCD::print(atack);
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("damage");
        delay(3000);
        doragonhp = doragonhp - atack;
      }
      else if (player == 3 && computer == 1) {
        OrangutanLCD::clear();
        OrangutanLCD::print("you");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("atack!");
        delay(1000);
        OrangutanLCD::clear();
        OrangutanLCD::print(atack);
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("damage");
        delay(3000);
        doragonhp = doragonhp - atack;
      }
      else {
        OrangutanLCD::clear();
        OrangutanLCD::print("doragon");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("atack");
        delay(1000);
        OrangutanLCD::clear();
        OrangutanLCD::print(doragonatack);
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("damage");
        delay(3000);
        hp = hp + def - doragonatack;

      }
      if (doragonhp == 0) {
        OrangutanLCD::clear();
        OrangutanLCD::print("defeated");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("dragon");
        delay(1000);
        OrangutanLCD::clear();
        OrangutanLCD::print("get");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("money");
        delay(3000);
        expo = expo + 200;
        money = money + 20;
      }

    }


  }
  if ((sensors[0] > 500) && (sensors[1] > 500 ) && (sensors[2] > 500 ) && (sensors[3] > 500 ) && (sensors[4] < 200 )) {
    OrangutanLCD::clear();
    OrangutanLCD::print("you");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("find");
    delay(2000);
    OrangutanLCD::clear();
    OrangutanLCD::print("treasure");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("box");
    delay(2000);
    OrangutanLCD::clear();
    OrangutanLCD::print("should");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print(" i  do ");
    delay(2000);
    OrangutanLCD::clear();
    OrangutanLCD::print("open = B");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("not = A");
    player = 0;
    while (player == 0) {
      if (OrangutanPushbuttons::isPressed(BUTTON_A)) {
        player = 1;
      }
      if (OrangutanPushbuttons::isPressed(BUTTON_B)) {
        player = 2;
      }

    }
    if (player == 1) {
      OrangutanLCD::clear();
      OrangutanLCD::print("threw");
      OrangutanLCD::gotoXY(0, 1);
      OrangutanLCD::print("away");
      delay(2000);

    }
    if (player == 2) {
      OrangutanLCD::clear();
      OrangutanLCD::print("open");
      OrangutanLCD::gotoXY(0, 1);
      OrangutanLCD::print("box... ");
      delay(3000);
      treasure = random(1, 5);
      if (treasure == 1) {
        OrangutanLCD::clear();
        OrangutanLCD::print("get");
        delay(2000);
        OrangutanLCD::clear();
        OrangutanLCD::print("ex");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("cariburn");
        delay(2000);
        OrangutanLCD::clear();
        OrangutanLCD::print("atack is");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print(" + 10 ");
        delay(2000);
        atack = 20;

      }
      if (treasure == 2) {
        OrangutanLCD::clear();
        OrangutanLCD::print("get");
        delay(2000);
        OrangutanLCD::clear();
        OrangutanLCD::print("huge");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("imogai");
        delay(2000);
        OrangutanLCD::clear();
        OrangutanLCD::print("hp is");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print(" - 20 !!");
        delay(2000);
        hp = hp - 20;

      }
      if (treasure == 3) {
        OrangutanLCD::clear();
        OrangutanLCD::print("get");
        delay(2000);
        OrangutanLCD::clear();
        OrangutanLCD::print("hiper");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("potion");
        delay(2000);
        OrangutanLCD::clear();
        OrangutanLCD::print("hp is");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print(" max !! ");
        delay(2000);
        hp = 20;

      }
      if (treasure == 4) {

        OrangutanLCD::clear();
        OrangutanLCD::print("come the");
        OrangutanLCD::gotoXY(0, 1);
        OrangutanLCD::print("mimic!!");
        delay(3000);
        mimichp = 10;
        mimicatack = 10;

        while (!(mimichp == 0 || hp == 0)) {
          OrangutanLCD::clear();
          OrangutanLCD::print("buttle");
          OrangutanLCD::gotoXY(0, 1);
          OrangutanLCD::print("mimic!!");
          delay(2000);
          player = 0;
          OrangutanLCD::clear();
          OrangutanLCD::print("comand");
          OrangutanLCD::gotoXY(0, 1);
          OrangutanLCD::print("janken");
          while (player == 0) {
            if (OrangutanPushbuttons::isPressed(BUTTON_A)) {
              player = 1;
            }
            if (OrangutanPushbuttons::isPressed(BUTTON_B)) {
              player = 2;
            }
            if (OrangutanPushbuttons::isPressed(BUTTON_C)) {
              player = 3;
            }
          }
          computer = random(1, 4);
          if (computer == player) {
            OrangutanLCD::clear();
            OrangutanLCD::print("dorrow");
            delay(1000);
          }
          else if (player == 1 && computer == 2) {
            OrangutanLCD::clear();
            OrangutanLCD::print("you");
            OrangutanLCD::gotoXY(0, 1);
            OrangutanLCD::print("atack!");
            delay(1000);
            OrangutanLCD::clear();
            OrangutanLCD::print(atack);
            OrangutanLCD::gotoXY(0, 1);
            OrangutanLCD::print("damage");
            delay(3000);
            mimichp = mimichp - atack;
          }
          else if (player == 2 && computer == 3) {
            OrangutanLCD::clear();
            OrangutanLCD::print("you");
            OrangutanLCD::gotoXY(0, 1);
            OrangutanLCD::print("atack!");
            delay(1000);
            OrangutanLCD::clear();
            OrangutanLCD::print(atack);
            OrangutanLCD::gotoXY(0, 1);
            OrangutanLCD::print("damage");
            delay(3000);
            mimichp = mimichp - atack;
          }
          else if (player == 3 && computer == 1) {
            OrangutanLCD::clear();
            OrangutanLCD::print("you");
            OrangutanLCD::gotoXY(0, 1);
            OrangutanLCD::print("atack!");
            delay(1000);
            OrangutanLCD::clear();
            OrangutanLCD::print(atack);
            OrangutanLCD::gotoXY(0, 1);
            OrangutanLCD::print("damage");
            delay(3000);
            mimichp = mimichp - atack;
          }
          else {
            OrangutanLCD::clear();
            OrangutanLCD::print("mimic");
            OrangutanLCD::gotoXY(0, 1);
            OrangutanLCD::print("turn");
            delay(1000);
            computer = random(1, 4);
            if (computer == 1) {
              OrangutanLCD::clear();
              OrangutanLCD::print("mimic");
              delay(1000);
              OrangutanLCD::clear();
              OrangutanLCD::print("symple");
              OrangutanLCD::gotoXY(0, 1);
              OrangutanLCD::print("atack!!");
              delay(2000);

              OrangutanLCD::clear();
              OrangutanLCD::print(mimicatack);
              OrangutanLCD::gotoXY(0, 1);
              OrangutanLCD::print("damage");
              delay(3000);
              hp = hp + def - mimicatack;
            }
            if (computer == 2) {
              OrangutanLCD::clear();
              OrangutanLCD::print("mimic");
              delay(1000);
              OrangutanLCD::clear();
              OrangutanLCD::print("cast");
              OrangutanLCD::gotoXY(0, 1);
              OrangutanLCD::print("mazic!!");
              delay(2000);

              OrangutanLCD::clear();
              OrangutanLCD::print("mimic");
              OrangutanLCD::gotoXY(0, 1);
              OrangutanLCD::print("atack is");
              delay(1000);

              OrangutanLCD::clear();
              OrangutanLCD::print("twice!!");
              delay(1000);
              mimicatack = mimicatack * 2;
            }
            if (computer == 3) {
              OrangutanLCD::clear();
              OrangutanLCD::print("mimic");
              delay(1000);
              OrangutanLCD::clear();
              OrangutanLCD::print("steal");
              OrangutanLCD::gotoXY(0, 1);
              OrangutanLCD::print("item!!");
              delay(2000);

              OrangutanLCD::clear();
              OrangutanLCD::print("i lost");
              OrangutanLCD::gotoXY(0, 1);
              OrangutanLCD::print("weapon");
              delay(1000);

              OrangutanLCD::clear();
              OrangutanLCD::print("atack");
              OrangutanLCD::gotoXY(0, 1);
              OrangutanLCD::print("- 10 ");
              delay(1000);
              atack = atack - 10;
            }


          }
          if (mimichp == 0) {
            OrangutanLCD::clear();
            OrangutanLCD::print("defeated");
            OrangutanLCD::gotoXY(0, 1);
            OrangutanLCD::print("mimic");
            delay(1000);
            OrangutanLCD::clear();
            OrangutanLCD::print("get");
            OrangutanLCD::gotoXY(0, 1);
            OrangutanLCD::print("money&ex");
            delay(3000);
            expo = expo + 50;
            money = money + 50;
            
          }

        }

      }
    }


  }
  while(expo >= 100){
     OrangutanLCD::clear();
    OrangutanLCD::print("Lv up!!");
    delay(1000);
  
  if(expo == 100){
    if(job == 1){
    OrangutanLCD::clear();
    OrangutanLCD::print("Lv up!!");
    delay(1000);
    OrangutanLCD::clear();
    OrangutanLCD::print("Hp + 2");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("Atack + 2");
    delay(1000);
    OrangutanLCD::clear();
    OrangutanLCD::print("speed + 1");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("def + 2");
    delay(1000);
    maxhp = maxhp + 2;
    atack = atack + 2;
    speeed = speeed + 1;
    def = def + 2;
    }

    if(job == 2){
    OrangutanLCD::clear();
    OrangutanLCD::print("Lv up!!");
    delay(1000);
    OrangutanLCD::clear();
    OrangutanLCD::print("Hp + 1");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("Atack + 1");
    delay(1000);
    OrangutanLCD::clear();
    OrangutanLCD::print("speed + 1");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("MP + 3");
    delay(1000);
    OrangutanLCD::clear();
    OrangutanLCD::print("def + 1");
    delay(1000);
    maxhp = maxhp + 1;
    atack = atack + 1;
    speeed = speeed + 1;
    mp = mp + 3;
    def = def + 1;
    }


    if(job == 3){
    OrangutanLCD::clear();
    OrangutanLCD::print("Lv up!!");
    delay(2000);
    OrangutanLCD::clear();
    OrangutanLCD::print("Hp + 1");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("Atack + 1");
    delay(2000);
    OrangutanLCD::clear();
    OrangutanLCD::print("speed + 3");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("def + 1");
    delay(2000);
    maxhp = maxhp + 1;
    atack = atack + 1;
    speeed = speeed + 3;
    def = def + 1;
    }
  }
  hp = maxhp;
  expo = expo - 100;
  }

  
  if (hp == 0) {
    OrangutanLCD::clear();
    OrangutanLCD::print("your Hp");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("is  0...");
    delay(3000);
    OrangutanLCD::clear();
    OrangutanLCD::print("gameover");
    delay(3000);
    OrangutanLCD::clear();
    OrangutanLCD::print("return");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("start");
    hp = maxhp;
    money = 0;
    delay(1000);
  }




}




