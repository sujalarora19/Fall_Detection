#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#define BLYNK_TEMPLATE_ID "TMPL3LuIO-t9q"
#define BLYNK_TEMPLATE_NAME "fall detection"
#define BLYNK_AUTH_TOKEN "iTcVab1cqXk9rhqHdv80umwrM7SWvJ5q"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vivo T1 5G";
char pass[] = "12345678";
int out=2;
int d4=4;
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float ax=0, ay=0, az=0, gx=0, gy=0, gz=0;
boolean fall = false; //stores if a fall has occurred
boolean trigger1=false; //stores if first trigger (lower threshold) has occurred
boolean trigger2=false; //stores if second trigger (upper threshold) has occurred
boolean trigger3=false; //stores if third trigger (orientation change) has occurred
byte trigger1count=0; //stores the counts past since trigger 1 was set true
byte trigger2count=0; //stores the counts past since trigger 2 was set true
byte trigger3count=0; //stores the counts past since trigger 3 was set true
int angleChange=0;
int flamg=1;
BLYNK_WRITE(V0){
  int pinval= param.asInt();
  if (pinval>0.5){
    flamg=1;
  }
  else{flamg=0;}
}

void setup()
{
    pinMode(d4, OUTPUT);
    Serial.begin(115200);
    pinMode(out,OUTPUT);
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
    Wire.begin();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B); 
    Wire.write(0);    
    Wire.endTransmission(true);
    Serial.println("Wrote to IMU");
    Serial.println("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print("."); // print ... till not connected
    }
    Serial.println("");
    Serial.println("WiFi connected");
}
void loop()
{   
    digitalWrite(d4,flamg);
    Blynk.run();
    mpu_read();
    ax = (AcX-2050)/16384.00;
    ay = (AcY-77)/16384.00;
    az = (AcZ-1947)/16384.00;
    gx = (GyX+270)/131.07;
    gy = (GyY-351)/131.07;
    gz = (GyZ+136)/131.07;


    Serial.print(ax);
    Serial.print(" ");
    Serial.print(ay);
    Serial.print(" ");
    Serial.print(az);
    Serial.print(" ");
    Serial.print(gx);
    Serial.print(" ");
    Serial.print(gy);
    Serial.print(" ");
    Serial.print(gz);
    Serial.print(" ");
    Serial.print("\n");

    // calculating Amplitute vactor for 3 axis
    float Raw_Amp = pow(pow(ax/2,2)+pow(ay/2,2)+pow(az,2),0.5);
    int Amp = Raw_Amp * 10;  // Multiplied by 10 to values are between 0 to 1
    Serial.println(Amp);
    angleChange = pow(pow(gx,2)+pow(gz,2),0.5); Serial.println(angleChange);
    if (Amp<=4 && trigger2==false) //if AM breaks lower threshold (0.4g)
    { 
        trigger2=true;
        trigger1=true;
        Serial.println("TRIGGER 1,2 ACTIVATED");

    }
    if (trigger1==true && Amp>=12)
    {
        trigger2=false;trigger1=false;
        Serial.println("TRIGGER 2 DEACTIVATED");
        delay(1000);
    }
    if (trigger2==true)
    {
        if (angleChange>=185)
        { 
            trigger1=false; trigger2=false; 
            Serial.println("TRIGGER 3 ACTIVATED");
            
            if (flamg==1){
              digitalWrite(out,HIGH);
              Blynk.logEvent("fall_detection", "Fall Detected");
              delay(1000); 
              digitalWrite(out,LOW);
              delay(5000);
              }
            
        }
    }
    delay(60);
}

void mpu_read()
{
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);  
    AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
    AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}