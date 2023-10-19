#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


char ssid[] = "SFR_CC5F";
char pass[] = "a3jn2idxz3nf5uj89u78";

#define NB_TRYWIFI        100
#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>      //https://github.com/Jorgen-VikingGod/LEDMatrix

#define DATA_PIN            4
#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B

// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        16
#define MATRIX_HEIGHT       10
#define MATRIX_TYPE         HORIZONTAL_MATRIX //HORIZONTAL_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

#define pause 300

 

//-------------------------------------------------
WiFiClient espClient;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);            
//-------------------------------------------------                                    

///////////////////////////////////////////////////////////
void setup()
{
  
  Serial.begin(115200);
 
  
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(50);
  FastLED.clear(true);  // on éte toutes les LEDs
  //-------------------------------------------------
  Serial.println("Startup reason:");Serial.println(ESP.getResetReason());

  WiFi.begin(ssid, pass);

  Serial.println("Connecting to WiFi.");
   int _try = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("..");
    delay(100);
    _try++;
    if ( _try >= NB_TRYWIFI ) {
        Serial.println("Impossible to connect WiFi network, go to deep sleep");
        ESP.deepSleep(10e6);
    }
  }
  Serial.println("Connected to the WiFi network");
  
  // Démarrage du client NTP - Start NTP client
  timeClient.begin();
  
  //-------------------------------------------------
}

  void loop()
{
  //-------------------------------------------------
   
    // Met à jour l'heure toutes les 10 secondes - update time every 10 secondes
    timeClient.update();
    String s =timeClient.getFormattedTime()+"";
    Serial.println(s+ "    heure ="+s[0]+""+s[1]+"|"+s[3]+""+s[4]+"|"+s[6]+""+s[7]); 
   FastLED.setBrightness(5);

   FastLED.clear(true);
    leds.DrawPixel(7, 1, (CRGB(255,255,255)));
    leds.DrawPixel(7, 3, (CRGB(255,255,255)));
    dessinHorloge(s);
    
 

  FastLED.show();
//    delay(10);
 
   delay(10);

  
FastLED.show();
delay (1);
    
}
//......................................................
void dessinHorloge(String s)
{
 for (int i=1; i<7;i++)
 {
   dessinZone(i,s);
 }
}
//........................................
void dessinZone(int z, String s)
{
  int col, lig, r, g, b;
  char num;
  if (z == 1){col=0;lig=0;r=0;g=255;b=255;num=s[4];}
  else if (z == 2){col=4;lig=0;r=0;g=255;b=0;num=s[3];}
       else if (z == 3){col=8;lig=0;r=255;g=255;b=0;num=s[1];} 
            else if (z == 4){col=12;lig=0;r=255;g=0;b=0;num=s[0];}
                 else if (z == 5){col=5;lig=5;r=255;g=255;b=255;num=s[7];}
                      else if (z == 6){col=9;lig=5;r=0;g=0;b=255;num=s[6];} 
            
    int zero[5][3]={
              {1,1,1},
              {1,0,1},
              {1,0,1},
              {1,0,1},
              {1,1,1}
};
 int un[5][3]={
              {1,0,0},
              {1,0,0},
              {1,0,0},
              {1,0,0},
              {1,0,0}
};
int deux[5][3]={
              {1,1,1},
              {1,0,0},
              {1,1,1},
              {0,0,1},
              {1,1,1}
};
int trois[5][3]={
              {1,1,1},
              {1,0,0},
              {1,1,1},
              {1,0,0},
              {1,1,1}
};
int quatre[5][3]={
              {1,0,1},
              {1,0,1},
              {1,1,1},
              {1,0,0},
              {1,0,0}
};
int cinq[5][3]={
              {1,1,1},
              {0,0,1},
              {1,1,1},
              {1,0,0},
              {1,1,1}
};
int six[5][3]={
              {1,1,1},
              {0,0,1},
              {1,1,1},
              {1,0,1},
              {1,1,1}
};
int sept[5][3]={
              {1,1,1},
              {1,0,0},
              {1,0,0},
              {1,0,0},
              {1,0,0}
};
int huit[5][3]={
              {1,1,1},
              {1,0,1},
              {1,1,1},
              {1,0,1},
              {1,1,1}
};
int neuf[5][3]={
              {1,1,1},
              {1,0,1},
              {1,1,1},
              {1,0,0},
              {1,1,1}
};  
  //...............................................                     
   if (num == '0')  { dessiner ( zero, lig,col,r,g,b);}
   else if (num == '1')  { dessiner ( un, lig,col,r,g,b);}
   else if (num == '2')  { dessiner ( deux, lig,col,r,g,b);}
   else if (num == '3')  { dessiner ( trois, lig,col,r,g,b);}
   else if (num == '4')  { dessiner ( quatre, lig,col,r,g,b);}  
   else if (num == '5')  { dessiner ( cinq, lig,col,r,g,b);}
   else if (num == '6')  { dessiner ( six, lig,col,r,g,b);}
   else if (num == '7')  { dessiner ( sept, lig,col,r,g,b);}
   else if (num == '8')  { dessiner ( huit, lig,col,r,g,b);}                                          
   else if (num == '9')  { dessiner ( neuf, lig,col,r,g,b);}
        
}
void dessiner (int mat[5][3], int col,int lig,  int r, int g, int b)
{
        for (int i=0; i<=4;i++)
        {
        for (int j=0; j<=2;j++)
          {
             if (mat [i][j]==1)
             {
              
              leds.DrawPixel(j+lig,i+col , (CRGB(r,g,b)));
              
             }
          }
        }
}
