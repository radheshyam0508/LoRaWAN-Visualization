#include <Arduino.h>

#if defined(ARDUINO_SODAQ_SARA)
/* SODAQ SARA */
#define DEBUG_STREAM SerialUSB
#define MODEM_STREAM Serial1
#define powerPin SARA_ENABLE
#define enablePin SARA_TX_ENABLE

#else
#error "Please select the SODAQ SARA as your board"
#endif

String csq_response = "";
String csq_data = "";

unsigned long baud = 9600;

void setup() 
{
#ifdef powerPin
  // Turn the nb-iot module on
  pinMode(powerPin, OUTPUT); 
  digitalWrite(powerPin, HIGH);
#endif

#ifdef enablePin
  // Set state to active
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
#endif // enablePin

  // Start communication
  DEBUG_STREAM.begin(baud);
  MODEM_STREAM.begin(baud);

  
}
int incomingByte = 0;
// Forward every message to the other serial
void loop() 
{
    DEBUG_STREAM.write("writing AT command...");
    DEBUG_STREAM.write("\n");
    MODEM_STREAM.write("AT+NRB\r");
    delay(7000);
    
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }
    
    
    MODEM_STREAM.write("AT+NCONFIG=\"CR_0354_0338_SCRAMBLING\",\"TRUE\"\r");
    delay(7000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }
    

    MODEM_STREAM.write("AT+NCONFIG=\"CR_0859_SI_AVOID\",\"FALSE\"\r");
    delay(7000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }
     
    MODEM_STREAM.write("AT+CFUN=1\r");
    delay(7000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }
       
    MODEM_STREAM.write("AT+CGDCONT=1,\"IP\",\"company.iot.dk1.tdc\"\r");
    delay(8000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }    
    
    MODEM_STREAM.write("AT+NBAND=20\r");
    delay(5000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }  
    
    MODEM_STREAM.write("AT+COPS=1,2,\"23801\"\r");
    delay(7000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }
       
    MODEM_STREAM.write("AT+NUESTATS\r");
    delay(8000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }
    
    MODEM_STREAM.write("AT+CPSMS=1\r");
    delay(7000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    }
    
    
    MODEM_STREAM.write("AT+CEREG?\r");
    delay(8000);
    while(MODEM_STREAM.available())
    {
      DEBUG_STREAM.write(MODEM_STREAM.read());
    } 
    
    MODEM_STREAM.write("AT+NPING=\"8.8.8.8\"\r");
    delay(8000);
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
    String at_nsot_append = "{\"accessToken\":\"d_sk_17AIg4blFi1Hi17HzU9BqQfP\",\"name\":\"SARA-n211\",\"data\":\"" + csq_data + "\"}";
    DEBUG_STREAM.println(at_nsot_append);
    //d_sk_9IuyXyIlsN8ZZi1bdnYqRkfe
    
    index=0;
    String at_nsot_append_hex = "";
    
    while(index < at_nsot_append.length())
    {
      at_nsot_append_hex += String(int(at_nsot_append.charAt(index)), HEX);
      index++;
    }

    String at_nsot_cmd_len = String(int((at_nsot_append_hex.length() + 24)/2.0));
    String at_nsot_cmd = "AT+NSOST=0,\"52.17.209.228\",5683," + at_nsot_cmd_len +",\"40020000b66576656e7473ff" + at_nsot_append_hex  + "\"\r";
    DEBUG_STREAM.println(at_nsot_cmd);
    
    ///////////////////// End of CSQ string extract /////////////////////
    
    delay(5000);
    
    MODEM_STREAM.write("AT+CGATT?\r");
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
    
    delay(2000);
}
