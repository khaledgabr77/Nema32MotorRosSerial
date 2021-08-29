/*
 * Khaled Gabr
 * pwm 4 , 3 , 2 ,1
----- 10 , 9 , 8 , 6

DIR 4 , 3 , 2 ,1
-----5 , 4 , 3 , 2

driver 4
EA 22
EB 24

driver 3
EA 26 clk
EB 28 DT

driver 2
EA 30
EB 32

driver 1
EA 34
EB 36
 */
 #include <ros.h>
 #include <std_msgs/Float32.h>
 std_msgs::Float32 en_msg;
 ros::Publisher encoder_("encoderData", &en_msg);
ros::NodeHandle nh;
 
 #define outputA 26
 #define outputB 28
 int counter = 0; 
 int aState;
 int aLastState;  
 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
  nh.getHardware()->setBaud(9600);
  nh.initNode();
  nh.advertise(encoder_);
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 
 void loop() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
   en_msg.data = counter;
   encoder_.publish(&en_msg);
       nh.spinOnce();
 
 }
