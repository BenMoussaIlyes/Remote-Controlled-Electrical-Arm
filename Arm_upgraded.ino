
#include <Servo.h>
int pot1[50];
int pot2[50];
int pot3[50];
int pot4[50];
int index=0 ;
int buttonState;
int val1;    // variable to read the value from the analog pin
int val2;    // variable to read the value from the analog pin
int val3;    // variable to read the value from the analog pin
int val4;    // variable to read the value from the analog pin
Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo

#define REMOTEXY_MODE__HARDSERIAL


// RemoteXY connection settings 

#include <RemoteXY.h>
// RemoteXY connection settings 

#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,8,0,5,0,126,0,8,13,0,
  4,160,1,50,63,12,2,26,4,32,
  64,0,11,63,2,26,4,32,76,0,
  11,63,2,26,4,32,88,0,11,63,
  2,26,1,2,1,2,29,10,2,31,
  82,101,115,101,116,32,77,111,117,118,
  101,109,101,110,116,115,0,1,2,1,
  16,29,10,2,31,83,97,118,101,0,
  1,2,34,2,29,10,2,31,85,110,
  100,111,0,1,2,34,16,29,10,2,
  31,80,108,97,121,0,129,0,20,35,
  33,6,17,109,118,116,115,32,115,97,
  118,101,100,0,67,6,5,35,13,6,
  24,13,5 };
  
// this structure defines all the variables of your control interface 
struct {

    // input variable
  int8_t slider_1; // =-100..100 slider position 
  int8_t slider_2; // =-100..100 slider position 
  int8_t slider_3; // =-100..100 slider position 
  int8_t slider_4; // =-100..100 slider position 
  uint8_t reset_mvt; // =1 if button pressed, else =0 
  uint8_t save; // =1 if button pressed, else =0 
  uint8_t undo; // =1 if button pressed, else =0 
  uint8_t play; // =1 if button pressed, else =0 

    // output variable
  char nb_mvt[5];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 

     
   myservo1.attach(4);  // attaches the servo on pin 9 to the servo object
   myservo2.attach(6);  // attaches the servo on pin 9 to the servo object
   myservo3.attach(8);  // attaches the servo on pin 9 to the servo object
   myservo4.attach(10);  // attaches the servo on pin 9 to the servo object
   
  Serial.begin(9600) ;
  
  // TODO you setup code
  
}
int is_high = 0;
void loop() 
{ 
  RemoteXY_Handler ();
  Serial.print("index =");
  Serial.println(index);

  // TODO you loop code
  // use the RemoteXY structure for data transfer 
  val1 = map(RemoteXY.slider_1, 100, -100, 0, 179);     // scale it to use it with the servo (value between 0 and 180)
  myservo1.write(val1);                  // sets the servo position according to the scaled value
 // Serial.print("val ") ;
 // Serial.println(val) ;
  
  val2 = map(RemoteXY.slider_2, -100, 100, 0, 100);     // scale it to use it with the servo (value between 0 and 180)
  myservo2.write(val2);                  // sets the servo position according to the scaled value
  //Serial.print("val2 " ) ;
  //Serial.println(val2) ;

  val3 = map(RemoteXY.slider_3, -100, 100, 0, 150);     // scale it to use it with the servo (value between 0 and 180)
  myservo3.write(val3);                  // sets the servo position according to the scaled value
 // Serial.print("val ") ;
 // Serial.println(val) ;
  
  val4 = map(RemoteXY.slider_4, -100, 100, 50, 130);     // scale it to use it with the servo (value between 0 and 180)
  myservo4.write(val4);                  // sets the servo position according to the scaled value
    if( RemoteXY.undo== HIGH ){
                                  index--;
                                  delay(200);
                              }
    
     if( RemoteXY.reset_mvt== HIGH ){
                                  index=0;  
                                                                    delay(200);

                                  }   
    
    if( RemoteXY.save== HIGH ){
                                  pot1[index]=val1;
                                  pot2[index]=val2;
                                  pot3[index]=val3;
                                  pot4[index]=val4;
                  
                                  index++;
                                                                    delay(200);


                                
    }
                if ( is_high == 1 ) {
                  is_high = 0; 
                }
         else if( RemoteXY.play == HIGH ){
                                  is_high = 1 ;

                                   for(int i = 0; i < index; i++)
                                      {
                                    myservo1.write(pot1[i]);                  // sets the servo position according to the scaled value
                                    myservo2.write(pot2[i]);                  // sets the servo position according to the scaled value
                                    myservo3.write(pot3[i]);                  // sets the servo position according to the scaled value
                                    myservo4.write(pot4[i]);                  // sets the servo position according to the scaled value
                                      
                                    delay(500);
                                      }
            
          }
   sprintf (RemoteXY.nb_mvt, "%d",index);



}
