#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
bool relay_status[] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
int pins_out[] = {4,5,6,7,8,9,10};
byte data = 4, sclock = 5, lclock = 6;

void setup()
{
  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  for(int i = 0; i <= 6; i++)
  {
    pinMode(pins_out[i],OUTPUT); 
  }
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (Serial.available())
  {
    byte temp = Serial.parseInt();
    if(temp == 64)
    {
      printRelayStat();
    }
    switch(temp)
    {
      case 103:
        irsend.sendNEC(0xFF8877, 32);
        delay(50);
        irsend.sendNEC(0xFFA05F, 32);
        break;
      case 104:
        irsend.sendNEC(0xFF9867, 32);
        delay(50);
        irsend.sendNEC(0xFFA05F, 32);
        break;
      case 105:
        if(digitalRead(7) == HIGH)
            digitalWrite(7,LOW);//Fan
          else
            digitalWrite(7,HIGH);
          delay(300);
          break;      
      case 106:
        if(digitalRead(8) == HIGH)
              digitalWrite(8,LOW);//BL3
            else
              digitalWrite(8,HIGH);
        break;
      case 107:
        if(digitalRead(9) == HIGH)
              digitalWrite(9,LOW);//Tube
            else
              digitalWrite(9,HIGH);
        break;
        
      case 108:
        if(digitalRead(10) == HIGH)
              digitalWrite(10,LOW);//Tube
            else
              digitalWrite(10,HIGH);
        break;
    }
    irrecv.enableIRIn(); // Start the receiver

    if(temp >= 0 && temp < 32)
    {
      temp = 31 - temp;
      if(relay_status[temp]==0)
        relay_status[temp]=1;
      else
        relay_status[temp]=0;
      draw();
      printRelayStat();
    }
  }
  else
  {
    if (irrecv.decode(&results))
    {
      switch(results.value)
      {
      // in every case, Write the code you will recieve from IR Remote
      // In sendNEC, Write the hex code that you want to send.
        case 0x8B5: //POwer      
        case 0x18B5: //POwer      
          irsend.sendNEC(0x40BFA05F, 32);
          break;
        case 0x8B9: //Mute      
        case 0x18B9: //Mute      
          irsend.sendNEC(0x40BF629D, 32);
          irrecv.resume();
          break;
        case 0x8A2: //1       
        case 0x18A2: //1       
          irsend.sendNEC(0xFFB04F, 32);
          break;
        case 0x8A4: //2       
        case 0x18A4: //2       
          irsend.sendNEC(0xFF9867, 32);
          break;
        case 0x8A7: //3       
        case 0x18A7: //3       
          irsend.sendNEC(0xFFD827, 32);
          break;
        case 0x8A8: //4       
        case 0x18A8: //4       
          irsend.sendNEC(0xFF807F, 32);
          break;
        case 0x8AB: //5       
        case 0x18AB: //5       
          irsend.sendNEC(0xFF8877, 32);
          break;
        case 0x8AD: //6       
        case 0x18AD: //6       
          irsend.sendNEC(0xFFA857, 32);
          break;
        case 0x8AE: //7       
        case 0x18AE: //7       
          irsend.sendNEC(0xFFE817, 32);
          break;
        case 0x891: //8       
        case 0x1891: //8       
          irsend.sendNEC(0xFF609F, 32);
          break;
        case 0x892: //9       
        case 0x1892: //9       
          irsend.sendNEC(0xFF48B7, 32);
          break;
        case 0x8A1: //0       
        case 0x18A1: //0       
          irsend.sendNEC(0xFF6897, 32);
          break;
        case 0x8D5: //pMinus //brigtness down     
        case 0x18D5: //pMinus      
          irsend.sendNEC(0x40BFFA05, 32);//menu
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup1
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup2
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup3
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup4
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup5
          delay(100);
          irsend.sendNEC(0x40BF20DF, 32);//navright
          delay(100);
          irsend.sendNEC(0x40BFFA05, 32);//menu1
          delay(100);
          irsend.sendNEC(0x40BFFA05, 32);//menu2
          break;
        case 0x8DC: //pPlus   
        case 0x18DC: //pPlus // brightness up   
          irsend.sendNEC(0x40BFFA05, 32);//menu
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup1
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup2
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup3
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup4
          delay(100);      
          irsend.sendNEC(0x40BF12ED, 32);//navup5
          delay(100);
          irsend.sendNEC(0x40BFE21D, 32);//navleft
          delay(100);
          irsend.sendNEC(0x40BFFA05, 32);//menu1
          delay(100);
          irsend.sendNEC(0x40BFFA05, 32);//menu2
          break;
        case 0x898: //Menu      
        case 0x1898: //Menu      
          irsend.sendNEC(0x40BFFA05, 32);
          break;           
        case 0x8BC: //Guide  
        case 0x18BC: //Guide  
          irsend.sendNEC(0x40BFD02F, 32);// tv play
          break;           
        case 0x89B: //Exit   
        case 0x189B: //Exit   
          irsend.sendNEC(0x40BFDA25, 32);
          break;           
        case 0x880: //NavUp  
        case 0x1880: //NavUp  
          irsend.sendNEC(0x40BF12ED, 32);
          break;           
        case 0x883: //NavDown   
        case 0x1883: //NavDown   
          irsend.sendNEC(0x40BF02FD, 32);
          break;           
        case 0x886: //NavLeft   
        case 0x1886: //NavLeft   
          irsend.sendNEC(0x40BFE21D, 32);
          break;           
        case 0x885: //NavRigh   
        case 0x1885: //NavRigh   
          irsend.sendNEC(0x40BF20DF, 32);
          break;           
        case 0x89E: //OK      
        case 0x189E: //OK      
          irsend.sendNEC(0x40BF22DD, 32);
          delay(50);
          irsend.sendNEC(0x1FEC03F, 32);//buffer play pause
          break;           
        case 0x8C2: //VOlPlus   
        case 0x18C2: //VOlPlus   
          irsend.sendNEC(0x40BFE817, 32);
          break;
        case 0x894: //VolMinus    
        case 0x1894: //VolMinus    
          irsend.sendNEC(0x40BFEA15, 32);
          break;           
        case 0x8C8: //Games  
        case 0x18C8: //Games  
          irsend.sendNEC(0x40BFF807, 32);//input upper
          delay(50);
          irsend.sendNEC(0x40BF12ED, 32);
          delay(50);
          irsend.sendNEC(0x40BF22DD, 32);
          break;           
        case 0x8CD: //Active          
        case 0x18CD: //Active    
          irsend.sendNEC(0x40BFF807, 32);// input lower
          delay(50);
          irsend.sendNEC(0x40BF02FD, 32);
          delay(50);
          irsend.sendNEC(0x40BF22DD, 32);
          break;           
        case 0x8CE: //Mode   
        case 0x18CE: //Mode   
          irsend.sendNEC(0x40BFF807, 32);
          break;           
        case 0x89D: //ChPlus    
        case 0x189D: //ChPlus    
          irsend.sendNEC(0xFF708F, 32);
          break;           
        case 0x897: //ChMinus   
        case 0x1897: //ChMinus   
          irsend.sendNEC(0xFF58A7, 32);
          break; 
                    
        case 0x88A: //BRed   
        case 0x188A: //BRed   
          irsend.sendNEC(0x1FE48B7, 32);//buffer power
          break;      
        case 0x8B3: //BGreen    
        case 0x18B3: //BGreen    
          irsend.sendNEC(0x1FE58A7, 32);//buffer mode
          break;           
        case 0x8C4: //BYellow  
        case 0x18C4: //BYellow   
          irsend.sendNEC(0x1FE20DF, 32);// buffer vol-
          break;           
        case 0x8C7: //BBlue  
        case 0x18C7: //BBlue  
          irsend.sendNEC(0x1FEA05F, 32);//buffer vol+
          break;
             
          
        case 0x8D0: //Fav       
        case 0x18D0: //Fav       
          irsend.sendNEC(0xFF38C7, 32);//dth menu
          break;           
        case 0x8CB: //i    
        case 0x18CB: //i    
          irsend.sendNEC(0xFF708F, 32);// dth nav up
          break;           
        case 0x88F: //Lang   
        case 0x188F: //Lang   
          irsend.sendNEC(0xFF32CD, 32);//dth siganl
          break;           
        case 0x8C1: //Sqaure1   
        case 0x18C1: //Sqaure1   
          irsend.sendNEC(0xFF50AF, 32);//dth nav left
          break;           
        case 0x88C: //Sqaure3   
        case 0x188C: //Sqaure3   
          irsend.sendNEC(0xFFA05F, 32);//dth ok
          break;           
        case 0x8B0: //PrevCH    
        case 0x18B0: //PrevCH    
          irsend.sendNEC(0xFF7887, 32);//dth nav right
          break;           
        case 0x8D3: //Timer  
        case 0x18D3: //Timer  
          irsend.sendNEC(0x1FE807F, 32);//buffer prev
          break;           
        case 0x8D6: //Message   
        case 0x18D6: //Message   
          irsend.sendNEC(0xFF58A7, 32);//dth nav Down
          break;           
        case 0x8D9: //My A/C    
        case 0x18D9: //My A/C    
          irsend.sendNEC(0x40BF8A75, 32);//buffer next
          break;  
        default:
          irsend.sendNEC(results.value, 32);
                 
      }
     // irrecv.resume(); // Receive the next value
    delay(100);
       irrecv.enableIRIn(); // Start the receiver
    }
  }
    
}
void draw()
{
  digitalWrite(data,LOW);//4
  digitalWrite(sclock,LOW);//5
  digitalWrite(lclock,LOW); //6
  for(byte i = 0; i <= 31; i++)
  {
    digitalWrite(data,relay_status[i]);
    digitalWrite(sclock,HIGH);
    digitalWrite(sclock,LOW);
  }
  digitalWrite(data,LOW);
  digitalWrite(lclock,HIGH); 
  digitalWrite(lclock,LOW); 
}
void printRelayStat()
{
  String relay_stat; 
  for(int i = 0; i < 32; i++ )
    relay_stat += relay_status[i];
  Serial.println(relay_stat);
}
