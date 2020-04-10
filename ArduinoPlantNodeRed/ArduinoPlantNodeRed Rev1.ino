#include "DHT.h"

//define the pumps to the digital IO
#define PUMP1 9          
#define PUMP2 10
#define PUMP3 11
#define PUMP4 12

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

char rxChar= 0;         // RXcHAR holds the received command.

//capasitive humidity sensor values, change these for new systems works well currently
const int AirValue = 610;   
const int WaterValue = 285;  
int soilMoistureValue = 0;
int soilmoisturepercent=0;


// control pins output table in array form
// see truth table on page 2 of TI 74HC4067 data sheet
// connect 74HC4067 S0~S3 to Arduino D7~D4 respectively
// connect 74HC4067 pin 1 to Arduino A0
byte controlPins[] = {B00000000, 
                  B10000000,
                  B01000000,
                  B11000000,
                  B00100000,
                  B10100000,
                  B01100000,
                  B11100000,
                  B00010000,
                  B10010000,
                  B01010000,
                  B11010000,
                  B00110000,
                  B10110000,
                  B01110000,
                  B11110000 }; 

// holds incoming values from 74HC4067                  
byte muxValues[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};

//=== function to print the command list:  ===========================
void printHelp(void)
{   
    //i could add some shit here later....for debugging when im older 
    // and totally forgot about what the fuck this project even is
    //  Serial.println("--- Command list: ---");
    //  Serial.println("? -> Print this HELP");  
    //  Serial.println("a -> LED On  \"activate\"");
    //  Serial.println("d -> LED Off \"deactivate\"");
    //  Serial.println("s -> LED     \"status\"");  
}


void setup() 
{
    // put your setup code here, to run once:
    //Setup Serial Port
    Serial.begin(115200);
    DDRD = B11111111; // set PORTD (digital 7~0) to outputs
    printHelp();          // Print the command list.
}

void setPin(int outputPin)
// function to select pin on 74HC4067
{
  PORTD = controlPins[outputPin];
}

void displayData()
// dumps captured data from array to serial monitor
{
  Serial.print(muxValues[0]);
  Serial.print(",");
  Serial.print(muxValues[1]);
  Serial.print(",");
  Serial.print(muxValues[2]);
  Serial.print(",");
  Serial.print(muxValues[3]);
  //below is for printing an on board vital DH22 sensor
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//  float h = dht.readHumidity();
//  // Read temperature as Celsius (the default)
//  float t = dht.readTemperature();
//  // Read temperature as Fahrenheit (isFahrenheit = true)
//  float f = dht.readTemperature(true);
//  
//  // Compute heat index in Fahrenheit (the default)
//  float hif = dht.computeHeatIndex(f, h);
//  // Compute heat index in Celsius (isFahreheit = false)
//  float hic = dht.computeHeatIndex(t, h, false);
//  Serial.print(",");
//  Serial.print(h);
//  Serial.print(",");
//  Serial.print(f);
  
  Serial.println("");
}



void loop() 
{

   if (Serial.available() >0)
   {
    // Check receive buffer.          
    rxChar = Serial.read();            // Save character received. 
    Serial.flush();                    // Clear receive buffer.
   }
    ///////
    //Here we scan the incomming char from the NodeRed instance hosted on a another machine 
    //we can look for any over rides to the watering pumps or fuck it any inputs we want.
    ///////
    switch (rxChar) 
    {
        //////////PUMP1
            case '1':                          // If received 'a' or 'A':
        if (digitalRead(PUMP1) == LOW)
        {        // If LED is Off:
                digitalWrite(PUMP1,HIGH);      // Turn On the LED.
                Serial.println("PUMP1 turned On");
        }
                else Serial.println("PUMP1 already On!");
                break;


            case '2':                          // If received 'd' or 'D':
        if (digitalRead(PUMP1) == HIGH)
        {       // If LED is On:
                digitalWrite(PUMP1,LOW);       // Turn Off the LED.
                Serial.println("PUMP1 turned Off");
        }
                break;

        /////////PUMP2
            case '3':                          // If received 'a' or 'A':
        if (digitalRead(PUMP2) == LOW)
        {        // If LED is Off:
                digitalWrite(PUMP2,HIGH);      // Turn On the LED.
                Serial.println("PUMP2 turned On");
        }
                else Serial.println("PUMP2 already On!");
                break;


            case '4':                          // If received 'd' or 'D':
        if (digitalRead(PUMP2) == HIGH)
        {       // If LED is On:
                digitalWrite(PUMP2,LOW);       // Turn Off the LED.
                Serial.println("PUMP2 turned Off");
        }
        
                else Serial.println("PUMP2 already Off!");
                break;
                
        ///////////PUMP3
            case '5':                          // If received 'a' or 'A':
        if (digitalRead(PUMP3) == LOW)
        {        // If LED is Off:
                digitalWrite(PUMP3,HIGH);      // Turn On the LED.
                Serial.println("PUMP3 turned On");
        }
                else Serial.println("PUMP3 already On!");
                break;


            case '6':                          // If received 'd' or 'D':
        if (digitalRead(PUMP3) == HIGH)
        {       // If LED is On:
                digitalWrite(PUMP3,LOW);       // Turn Off the LED.
                Serial.println("PUMP3 turned Off");
        }
        
                else Serial.println("PUMP3 already Off!");
                break;


        ///////////PUMP4
            case '7':                          // If received 'a' or 'A':
        if (digitalRead(PUMP4) == LOW)
        {        // If LED is Off:
                digitalWrite(PUMP4,HIGH);      // Turn On the LED.
                Serial.println("PUMP4 turned On");
        }
                else Serial.println("PUMP4 already On!");
                break;


            case '8':                          // If received 'd' or 'D':
        if (digitalRead(PUMP4) == HIGH)
        {       // If LED is On:
                digitalWrite(PUMP4,LOW);       // Turn Off the LED.
                Serial.println("PUMP4 turned Off");
        }
        
                else Serial.println("PUMP4 already Off!");
                break;
        
     case '?':                          // If received a ?:
           printHelp();                   // print the command list.
           break;
    }

   
    for (int i = 0; i < 4; i++)
    {
      setPin(i); // choose an input pin on the 74HC4067
      soilMoistureValue = analogRead(0); // read the vlaue on that pin and store in array
      soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
      muxValues[i]=soilmoisturepercent;
    }
  
    // display captured data
    displayData();
    delay(300); 

    //use this for debuggin new sensors
    //soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
    //soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    //Serial.println(soilmoisturepercent);
    //delay(250);
}
