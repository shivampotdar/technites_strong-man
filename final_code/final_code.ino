#include "HX711.h"
#include "SPI.h"


#define DOUT  2                     //HX711 DT PIN
#define CLK  3                      //HX711 SCK PIN
#define ss 8                        //Slave Select Pin for TLC

const int wmax = 10;              //max weight
float wread,wp;                      //value from load cell
const int wth = 1;               //threshold value to start the seqeunce
uint16_t data = 1;

HX711 scale(DOUT, CLK);

//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -62670 ;

void setValue(uint16_t value)
{
  digitalWrite(ss, LOW);
  SPI.transfer16(value); // send value (0~255)
  digitalWrite(ss, HIGH);
}

void lightup(int num)
{
 data = 0;
  for (int i = 0; i < num; i++)
  {
    data |= (1 << i);
    setValue(data);
  }
  
}

void ledfun()
{
  int j;
  for (j = 0; j < 16; j++)
  {
    if ((wread > (j * (wmax - wth)) / 16) && (wread <= ((j + 1) * (wmax - wth)) / 16))
    {
      lightup(j + 1);
      break;
    }
  }
  Serial.println(j);
  for(int p=0;p<15;p++)
  {
      setValue(data);
      Serial.println(data);
      delay(100);
      setValue(data-(1<<j));
      Serial.println(data-(1<<j));
      delay(100);
  }    
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("Press T to tare");
  scale.set_scale(calibration_factor);  //Calibration Factor obtained from first sketch
  scale.tare();             //Reset the scale to 0
  pinMode(ss, OUTPUT);
  SPI.setBitOrder(LSBFIRST);
  SPI.begin();

}

void loop()
{
 Serial.println("Weight: ");
 wread = scale.get_units();
 Serial.print(wread);
 Serial.println("  kg");
 
  
   if(wread>=wth)
     {
      while(1)
      {
        wp=scale.get_units();
        if(wp>wread)
            wread=wp;
        else
            break;
              
      }
      ledfun();
     }
   else
       {
         for(int i=0;i<=16;i++)
            {setValue(1<<i);
            delay(10);  
            }
         for(int i=16;i>=0;i--)
            {
              setValue(1<<i);
              delay(10);
            }
      }
  if (Serial.available())
  {  
    char temp = Serial.read();
    if (temp == 't' || temp == 'T')
      scale.tare();  //Reset the scale to zero
  }
}
//=============================================================================================

