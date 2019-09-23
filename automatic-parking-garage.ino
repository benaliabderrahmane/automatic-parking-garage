/*
the machine introduces a free slot at the entree , when ever a car is parked in , it moves with '1' pass this adds 1 to every pos[] 
meaning that we can keep track of it
should install keypad library
pos[number of the slot] = position in the whole system
*/
//*********************************************************************************
#include<Keypad.h>
//*********************************************************************************
#define Fc 10              //home_switch feedbackPin
#define Motor 12            //Pin that closes the motor circuit (controles the relay)
/************** KEYPAD ************/
const byte ROWS = 4 ;
const byte COLS = 3 ;
char keys[ROWS][COLS]{
  {'1' , '2' , '3'},
  {'4' , '5' , '6'},
  {'7' , '8' , '9'},
  {'*' , '0' , '#'}
  };
byte rowPins[ROWS] = { 5 , 4 , 3 , 2 };
byte colPins[COLS] = { 8 , 7 , 6 };

Keypad keypad = Keypad ( makeKeymap(keys) , rowPins , colPins , ROWS , COLS ) ;

/*********************************/  
int done1=1;
int done=0;
int i;
int slot ;
int car_slot ;
int cars_total_number;
int pos[6] = { 1 , 2 , 3 , 4 , 5 , 6 } ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(Fc,INPUT);  
  pinMode(Motor,OUTPUT);
  attachInterrupt(Fc,pass,RISING);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop(){
  if (cars_total_number <6){
    //open_door();
 char commande = keypad.getKey();
if(commande){
  if ( commande == '0' ){ one_pass(); cars_total_number = cars_total_number + 1;  /*give_slot_number();*/}
  if ( commande == '1' || commande == '2' || commande == '3' || commande == '4' || commande == '5' || commande == '6' ){get_car(commande); cars_total_number = cars_total_number - 1; }
  //sometimes the get_car() function does not work properly depending on the hardware used( one_pass() should always work !!)
}
}
else{
  //close_door();
  Serial.print("garage is full!");
  }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void motor_on(){    //close circuit
  digitalWrite(Motor,HIGH);     
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void motor_off(){   //open circuit
  digitalWrite(Motor,LOW);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void one_pass(){                     //this function moves the car with '1' pass           
  done = 0;
  while(!done){
      motor_on();                   
      done = digitalRead(Fc);
      //Serial.println(done);
  }
  done = 0;
  motor_off();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void get_car(int slot){
  done1 = 1 ;
  while(done1){
  one_pass();
  if( pos[slot] == 1 ) {done1 = 0;}
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pass() { //interruption function for the Fc

  for(i = 0 ;i <= 5 ;i++){
     pos[i] += 1 ;
     if(pos[i] > 6){ pos[i] = 1 ;}
}
i = 0 ;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int give_slot_number(){
  for(i = 0 ; i <= 5 ; i++){
    if (pos[i] == 1) { car_slot = i ; }
  }
i = 0 ;
//Display_car_slot_number(); //should be added later!
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// close_door(); //should be added later !
// open_door(); //should be added later !
