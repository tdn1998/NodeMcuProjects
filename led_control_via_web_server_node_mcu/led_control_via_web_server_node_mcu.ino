#include <ESP8266WiFi.h>

const char* ssid="tdn123";
const char* password="turbodrive1";

WiFiServer server(80);

void setup()
{
Serial.begin(115200);
delay(10);

Serial.print("Connecting to ");
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
Serial.println("Server started");
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.print("/");

pinMode(D5,OUTPUT);
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

String request=client.readStringUntil('\r');
Serial.println(request);
client.flush();

client.println("<html>");

client.println("<head>");
client.println("<title>Led Control</title>");
client.println("<style>");
client.println("body{text-align:center;}");
client.println("#light{font-family:open sans;font-size:5vw;display:inline-block;margin:4vw;padding:1vw;border:solid;border-radius:20px;}");
client.println("</style>");
client.println("</head>");

client.println("<body>");
client.println("<div id=\"light\">Control the Light:");
client.println("<div id=\"button\">");
client.println("<a href=\"LED=ON\"><button>Turn on</button></a>");
client.println("<a href=\"LED=OFF\"><button>Turn off</button></a>");
client.println("</div></div>");
client.println("</body>");

client.println("</html>");

if(request.indexOf("LED=ON") != -1)
{
digitalWrite(D5,HIGH);
}

if(request.indexOf("LED=OFF") != -1)
{
digitalWrite(D5,LOW);
}

Serial.println("-----------------------------------");
}


