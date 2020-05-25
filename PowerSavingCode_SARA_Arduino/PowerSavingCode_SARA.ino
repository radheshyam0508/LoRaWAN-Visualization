 #include <Arduino.h>
 #include <Sodaq_LSM303AGR.h>

#if defined(ARDUINO_SODAQ_SARA)
/* SODAQ SARA */
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial1
//#define powerPin SARA_ENABLE
//#define enablePin SARA_TX_ENABLE
Sodaq_LSM303AGR accelerometer;

#else
#error "Please select the SODAQ SARA as your board"
#endif

String csq_response = "";
String csq_data = "";

unsigned long baud = 9600;
int incomingByte = 0;
void setup() 
{
 //delay(5000);
 Wire.begin();// I2C for the accelerometer
 // Disable the LSM303AGR
  accelerometer.disableAccelerometer();
  accelerometer.disableMagnetometer();

  pinMode(LED_BUILTIN,  OUTPUT);
  pinMode(MAG_INT,  OUTPUT);
  pinMode(GPS_ENABLE,  OUTPUT);
  pinMode(SARA_ENABLE,  OUTPUT);
  pinMode(SARA_TX_ENABLE,  OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);   // LED low=off, high=on
  digitalWrite(MAG_INT, LOW);       // we need to make this low otherwise this pin on the LSM303AGR starts leaking current
  digitalWrite(GPS_ENABLE, LOW);    // low=poweredoff, high=poweredon
  digitalWrite(SARA_ENABLE, HIGH);  // low=poweredoff, high=poweredon
  digitalWrite(SARA_TX_ENABLE, HIGH);


  // Start communication
  DEBUG_STREAM.begin(baud);
  MODEM_STREAM.begin(baud);
}

// Forward every message to the other serial

void loop()
{
   DEBUG_STREAM.write("writing AT command...");
   DEBUG_STREAM.write("\n");

    MODEM_STREAM.write("AT+CPSMS=1\r");
    delay(7000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }

 MODEM_STREAM.write("AT+CSQ\r");
    delay(10000);
    DEBUG_STREAM.flush();
    delay(5000);

    while(MODEM_STREAM.available())
    {
      csq_response = MODEM_STREAM.readString();
      DEBUG_STREAM.println(csq_response);      
    }
    DEBUG_STREAM.flush();

    ///////////////////// CSQ extract string //////////////////////
    uint8_t index = 0;
    
    while(index<csq_response.length())
    {
      while(csq_response.charAt(index)!='C') {
        index++;
      }
      
      csq_data = csq_response.substring(index+5, index+10); // Extract the CSQ number from response
      break;
    }
    //DEBUG_STREAM.print("sub-string CSQ:");
    //DEBUG_STREAM.println(csq_data);
    
    delay(1000);
    String at_nsot_append = "{\"accessToken\":\"d_sk_9IuyXyIlsN8ZZi1bdnYqRkfe\",\"name\":\"CSQ-03\",\"data\":\"" + csq_data + "\"}";
    DEBUG_STREAM.println(at_nsot_append);
    
    index=0;
    String at_nsot_append_hex = "";
    
    while(index < at_nsot_append.length())
    {
      at_nsot_append_hex += String(int(at_nsot_append.charAt(index)), HEX);
      index++;
    }

    String at_nsot_cmd_len = String(int((at_nsot_append_hex.length() + 24)/2.0));
    String at_nsot_cmd = "AT+NSOSTF=0,\"52.17.209.228\",5683,0x400," + at_nsot_cmd_len +",\"40020000b66576656e7473ff" + at_nsot_append_hex  + "\"\r";
    DEBUG_STREAM.println(at_nsot_cmd);

      MODEM_STREAM.write("AT+NPSMR=1\r");
    delay(5000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read()); 
    }

   
    MODEM_STREAM.write("AT+CPSMS=1,,,\"00100001\",\"00000000\"\r");
    delay(5000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }

   
    MODEM_STREAM.write("AT+NSOCR=\"DGRAM\",17,42000,1\r");
    delay(10000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }

    MODEM_STREAM.print(at_nsot_cmd);
    delay(7000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }

  //delay(7000);
  DEBUG_STREAM.write("now every LOW...");
   DEBUG_STREAM.write("\n");
  digitalWrite(LED_BUILTIN, LOW);   // LED low=off, high=on
  digitalWrite(MAG_INT, LOW);       // we need to make this low otherwise this pin on the LSM303AGR starts leaking current
  digitalWrite(GPS_ENABLE, LOW);    // low=poweredoff, high=poweredon
  digitalWrite(SARA_ENABLE, LOW);  // low=poweredoff, high=poweredon
  digitalWrite(SARA_TX_ENABLE, LOW);
      
   while(1){
    MODEM_STREAM.write("Sleeping...");
    }

}
