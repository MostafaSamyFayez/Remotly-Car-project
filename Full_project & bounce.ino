#define MR1 10
#define MR2 11
#define ML1 12
#define ML2 13

#define En1 5 
#define En2 6

#define TRIG 8
#define ECHO 9

#define R 7
#define M 2
#define L 4


#define servoPin 3
#include <Servo.h>

Servo servo;  
int speed_motor = 255 ;
int speed_memory = 150;
char b ;
float distance;
float distanceR;
float distanceL;
float duration;
int rv1;
int lv1;
int mv1;
boolean rv;
boolean lv;
boolean mv;
int flag=0;
boolean flag2=0;
boolean flag3=0;
boolean flag4=0;
boolean flag5=0;
boolean flag6=0;
boolean flagx =0;
long start=0;
int ref =900;
void setup() {
  servo.attach(servoPin);
  Serial.begin(9600);

  pinMode(En1,OUTPUT);
  pinMode(En2,OUTPUT);
  
  pinMode(MR1,OUTPUT);
  pinMode(MR2,OUTPUT);
  pinMode(ML1,OUTPUT);
  pinMode(ML2,OUTPUT);

  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);

  pinMode(R, INPUT);
  pinMode(M, INPUT);
  pinMode(L, INPUT);
  
  servo.write(95);
  
}

void go_forward ()
{
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speed_motor-6);
  }

void go_back ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,HIGH);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,HIGH);
  analogWrite(En2,speed_motor-6);
  }

void go_right ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,HIGH);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speed_motor-6);
  
  }

void go_left ()
{
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,HIGH);
  analogWrite(En2,speed_motor-6);
  }
void go_right_slow ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speed_motor-6);
  }
void go_left_slow ()
{
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speed_motor);
  }
void go_forward_right (float x)
{
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor/x);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speed_motor-6);
  }

void go_forward_left (float x)
{
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,(speed_motor-6)/x);
  }

void go_back_right ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,HIGH);
  analogWrite(En1,speed_motor/3);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,HIGH);
  analogWrite(En2,speed_motor-6);
  }

void go_back_left ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,HIGH);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,HIGH);
  analogWrite(En2,(speed_motor-6)/3);
  }


void stop_car ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speed_motor);
  
  }
  float read_distance(){
  digitalWrite (TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite (TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite (TRIG,LOW);
  duration = pulseIn(ECHO,HIGH) ;
  distance = duration/58 ;
  return distance;
  }
   int look_right(){
    servo.write(10);  
    delay(400);
    distanceR = read_distance();
    delay(100); 
    servo.write(95);
    return distanceR;
    delay(100);
   }
   int look_left(){
    servo.write(180); 
    delay(400);
    distanceL = read_distance();
    delay(100); 
    servo.write(95);
    return distanceL;
    delay(100);
   }
   char self_avoid(){
   b = Serial.read();
   go_forward();
   distanceR=200;
   distanceL=200;
   distanceR =look_right_slow();
   distanceL=look_left_slow();
    if((distanceR<=40)||(distanceL<=40)) {
       stop_car();
       delay(20);
       go_back();
       delay(500);
       stop_car();
       distanceR = look_right();
       distanceL = look_left();
       if(distanceR>=distanceL){ 
        speed_motor = 255;
        go_right ();
        delay (300);
        speed_motor = 130;
        go_forward();
        }
        else 
        { 
        speed_motor = 255;
        go_left();
        delay (300);
        speed_motor = 130;
        go_forward();
        }  
   }
   return b ;
 }
 void tsp1(){
  stop_car();
  delay(5);
  read_sensors();
  }
 void delay_read(){
  delay(5);
  read_sensors();  
  }
 void read_sensors(){
  rv=digitalRead(R);
  lv=digitalRead(L);
  mv=digitalRead(M);
  } 
  void go_forward_line ()
{
  speed_motor=200;
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speed_motor-6);
  }
  void go_right_line ()
{
  speed_motor=140;
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,(speed_motor-6)/1.2);
  
  }

void go_left_line ()
{
  speed_motor=140;
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speed_motor/1.2);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speed_motor-6);
  }
 char line_tracking (){                       // HIGH >> white , LOW >> black
  b = Serial.read();
  read_sensors();
  if (mv==LOW&&lv==HIGH&&rv==HIGH) {                       // line on track 
       go_forward_line();
       delay_read();
       read_sensors();
       flag=0;
       }
        else if ((mv==LOW)&&(lv==LOW)&&(rv==HIGH)){          //line on left 
          go_left_line();
          delay_read();
          flag=0;
          flag3=1;
          flag4=0;
          }
        else if ((mv==LOW)&&(lv==HIGH)&&(rv==LOW)){          //line on the right
          go_right_line();
          delay_read();
          flag=0;
          flag3=0;
          flag4=1;
          }
          else if ((mv==HIGH)&&(lv==LOW)&&(rv==LOW)){       // hard to happen 
            go_forward_line();
            delay_read();
            flag=0;
            }
          else if ((mv==HIGH)&&(lv==HIGH)&&(rv==LOW)){       // line on the right
            go_right_line();
            delay_read();
            flag=0;
            flag3=0;
            flag4=1;
            }
            else if((mv==HIGH)&&(lv==LOW)&&(rv==HIGH)){       //line on left 
              go_left_line();
              delay_read();
              flag=0;
              flag3=1;
              flag4=0;
              }
              else if ((mv==HIGH)&&(lv==HIGH)&&(rv=HIGH)){     // out of path
               if (flag3==1){
                   speed_motor=200;
                   go_left();
                   delay_read();
                  }
                else if (flag4==1){
                  speed_motor=200;
                  go_right();
                  delay_read();
                  }
                  else{
                if((flag<=30)&&(flag2==0)){
                delay_read();
                go_left_line();
                delay(30);
                flag=flag+1;
                delay_read();
                }
              else if ( ( (flag > 30)&&(70 > flag) ) ||(flag2==1) ){
                tsp1();
                go_right_line();
                delay(30);
                flag=flag+1;
                flag2=1;
                read_sensors();
                if (flag==50){
                  stop_car();
                  delay(1);
                  go_back();
                  delay(400);
                  read_sensors();
                  }
                if (flag>70){
                  flag2=0;
                  read_sensors();
                  }
                }
                else if (flag>=80){
                  flag=0;
                  flag2=0;
                  read_sensors();
                  }
                  
                    }
              }
               else if((mv==LOW)&&(lv==LOW)&&(rv==LOW)){
                  go_forward_line();
                  delay_read();
                }
            read_sensors();
            return b;
  }
  int int_serial_read(){
     byte x= '0';
      int z=0;
      while(Serial.available()>0){
        Serial.read();
        delay(100);
        }
      while(Serial.available()==0){}
       while( Serial.available() > 0 ){
        x = Serial.read();
      if( (x >= '0') && (x <='9') ){
        z=(z*10)+(x-'0');
        delay(5);
      }
      
      }
      return z;
    }
  void forward_acc(int z){
      speed_motor=78;
      if(z<=10){
      go_forward();
      delay(z*62);
      stop_car();
      b = 0;
      }
      else if((z<=20)&&(z>10)){
      go_forward();
      delay(z*55);
      stop_car();
      b = 0;
        }
      else if((z>20)&&(z<=30)){
      go_forward();
      delay(z*49);
      stop_car();
      b = 0;
        }
        else if((z>30)&&(z<=40)){
      go_forward();
      delay(z*48);
      stop_car();
      b = 0;
        }
        else if((z>40)&&(z<=60)){
      go_forward();
      delay(z*47);
      stop_car();
      b = 0;
        }
         else if ((z>60)&&(z<=80)){
      go_forward();
      delay(z*46);
      stop_car();
      b = 0;
        }
        else if (z>80){
      go_forward();
      delay(z*45);
      stop_car();
      b = 0;
        }
  }
  void backward_acc(int z){
      if(z<=10){
      go_back();
      delay(z*62);
      stop_car();
      b = 0;
      }
      else if((z<=20)&&(z>10)){
      go_back();
      delay(z*55);
      stop_car();
      b = 0;
        }
      else if((z>20)&&(z<=30)){
      go_back();
      delay(z*49);
      stop_car();
      b = 0;
        }
        else if((z>30)&&(z<=40)){
      go_back();
      delay(z*48);
      stop_car();
      b = 0;
        }
        else if((z>40)&&(z<=60)){
      go_back();
      delay(z*47);
      stop_car();
      b = 0;
        }
          else if ((z>60)&&(z<=80)){
      go_back();
      delay(z*46);
      stop_car();
      b = 0;
        }
        else if (z>80){
      go_back();
      delay(z*45);
      stop_car();
      b = 0;
        }
  }
  void angel_acc(int z){
    speed_motor=134;
    go_right();
    if ((z>0)&&(z<=90)){
    delay((z*6)+40);
    stop_car();
      }
    else if ((z>90)&&(z<=180)){
    delay((z*6)-30);
    stop_car();
    }
    else if ((z>180)&&(z>=270)){
    delay((z*6)-200);
    stop_car();
    }
    else if (z>270){
    delay((z*6)-450);
    stop_car();
    }
    }
    void rec(){
      int z = int_serial_read();
      delay(50);
      speed_motor=77;
      forward_acc(z);
      delay(200);
      angel_acc(90);
      delay(200);
      forward_acc(z);
      delay(200);
      angel_acc(90);
      delay(200);
      forward_acc(z);
      delay(200);
      angel_acc(90);
      delay(200);
      forward_acc(z);
      delay(200);
      angel_acc(90);
      }
    void circ(float x , char z){
      float y = (200/x);
      if(z=='r'){
      speed_motor=130;
      go_forward_right(y);
       if((x>40)&&(x<=60)){
        delay(x*59);
        }
       else if ((x>60)&&(x<=80)){
        delay(x*70);
        }
        else if ((x>80)&&(x<=100)){
        delay(x*72);
        }
       else if ((x>100)&&(x<=120)){
        delay(x*71);
        }
        else if ((x>120)&&(x<=140)){
        delay(x*75);
        }
       else if ((x>140)&&(x<=160)){
        delay(x*75);
        }
        else if ((x>160)&&(x<=180)){
        delay(x*75);
        }
        else {
        stop_car();
             }
             stop_car();
      }
      else{
      speed_motor=140;
      y = (320/x);
      go_forward_left(y);
      if((x>40)&&(x<=60)){
        delay(x*59);
        }
       else if ((x>60)&&(x<=80)){
        delay(x*70);
        }
        else if ((x>80)&&(x<=100)){
        delay(x*72);
        }
       else if ((x>100)&&(x<=120)){
        delay(x*71);
        }
        else if ((x>120)&&(x<=140)){
        delay(x*75);
        }
       else if ((x>140)&&(x<=160)){
        delay(x*75);
        }
        else if ((x>160)&&(x<=180)){
        delay(x*75);
        }
        else {
        stop_car();
             }
             stop_car();
         }
    }
    int look_right_slow(){
    int x=95;
    int distance=200;
    for(int i=0;i<2;i++){
    distance = read_distance();
    if (distance<=40){
    return distance;
    servo.write(95);
    goto end;
    }
    servo.write(x);
    x=x-25;
    }
    for(int i=0;i<2;i++){
    distance = read_distance();
    if (distance<=40){
    return distance;
    servo.write(95);
    goto end;
    }
    servo.write(x);
    x=x+25;
    }
    return 200;
   end: ;
    }
   int look_left_slow(){
    int x=95;
    int distance=0;
    for(int i=0;i<2;i++){
    distance = read_distance();
    if (distance<=40){
    return distance;
    servo.write(95);
    goto end;
    }
    servo.write(x);
    x=x+25;
    }
    for(int i=0;i<2;i++){
    distance = read_distance();
    if (distance<=40){
    return distance;
    servo.write(95);
    goto end;
    }
    servo.write(x);
    x=x-25;
    }
    return 200;
    end:;
   }
void loop() {
  distance = read_distance();
  distanceR =0;
  distanceL=0;
  LO:
  for(int i=0;i<=100;i++){
  if ( Serial.available() > 0 )
  {
    b = Serial.read();
    
    if ( b == 'F' ){
      go_forward();
    }
    else if ( b == 'B' ){
      go_back();
    }
    else if ( b == 'R' ){
      go_right();
    }
     else if ( b == 'S' ){
      stop_car();
    }
    else if ( b == 'L' ){
      go_left();
    }
    else if ( b == 'I' ){
      go_forward_right(3);
    }
    else if ( b == 'G' ){
      go_forward_left(3);
    }
    else if ( b == 'J' ){
      go_back_right();
    }
    else if ( b == 'H' ){
      go_back_left();
    }
    else if ( b == '0' ){
      speed_motor = 100 ;
    }
    else if ( b == '1' ){
      speed_motor = 115 ;
    }
    else if ( b == '2' ){
      speed_motor = 130 ;
    }
    else if ( b == '3' ){
      speed_motor = 145 ;
    }
    else if ( b == '4' ){
      speed_motor = 160 ;
    }
    else if ( b == '5' ){
      speed_motor = 185 ;
    }
    else if ( b == '6' ){
      speed_motor = 200 ;
    }
    else if ( b == '7' ){
      speed_motor = 215 ;
    }
    else if ( b == '8' ){
      speed_motor = 230 ;
    }
    else if ( b == '9' ){
      speed_motor = 245 ;
    }
    else if ( b == 'q' ){
      speed_motor = 255 ;
    }
    else if ( b == 'X' ){
      speed_motor = 110 ;
      while(b != 'x'& b!='F'&b!='B'){
        go_forward();
        b=self_avoid();
      }
      speed_motor = 150 ;
      stop_car();
    }
     else if ( b == 'W' ){
      speed_motor = 160 ;
      while(b!='w'){
        b=line_tracking();
        }
        stop_car();
        }
    }
    else if (b =='f'){
      speed_motor=77;
      forward_acc(int_serial_read());
      goto LO;
    }
    else if (b =='b'){
      speed_motor=77;
      backward_acc(int_serial_read());
      goto LO;
    }
    else if (b == 'a'){
      angel_acc(int_serial_read());
      goto LO;
    }
    else if (b == 'r'){
      rec();
      goto LO;
    }
     else if (b =='c'){
      float x ;
      x = int_serial_read();
      circ(x,'r');
      goto LO;
    }
    else if (b =='i'){
      float x;
      x = int_serial_read();
      circ(x,'r');
      delay(100);
      circ(x,'l');
      goto LO;
      }
      if(distance<=40) {
      speed_memory=speed_motor;
       stop_car();
       speed_motor = 200;
       delay(10);
       go_back();
       delay(300);
       stop_car();
       distanceR = look_right();
       delay(100);
       distanceL = look_left();
       delay(100);
       if(distanceR>=distanceL){ 
        go_right ();
        delay (330);
        stop_car ();
        }
        else 
        { 
        go_left();
        delay (330);
        stop_car ();
        }   
        speed_motor=speed_memory;
 }
 delayMicroseconds(1000);
}

}

