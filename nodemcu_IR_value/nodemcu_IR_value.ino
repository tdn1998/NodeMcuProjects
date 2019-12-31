#include <ESP8266WiFi.h>

const char* ssid="tdn123";
const char* password="turbodrive1";

const int ir=D3;

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  pinMode(ir,INPUT);
 
  Serial.print("connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid,password);
  
  while(WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(300);
    }

Serial.println("");
Serial.println("WiFi connected");

server.begin();
Serial.println("server started");
Serial.print("use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());

}


void loop()
{
  WiFiClient client=server.available();
  if(!client)
  {
  return;
  }

  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }

 
  client.println("<html>");
  client.println("<head>");
  client.println("<title>IR control</title>");
  client.println("<meta http-equiv=\"refresh\" content=\"1\">");
  client.println("</head>");
  client.println("<body bgcolor=\"white\">");
  client.println("</body>");
  client.println("</html>");



  int a =digitalRead(ir);
  if(a==LOW)
    {
      client.println("<div align=\"center\"><font color=\"black\"><h1>IR sense the object</h1></font></div>");
    }
  else
  client.println("<div align=\"center\"><font color=\"black\"><h1>ir sense the  no object </h1></font></div>");
  
  Serial.println("---------------------------------------------------");
  
}
