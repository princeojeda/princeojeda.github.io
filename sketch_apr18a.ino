#include <ESP8266WiFi.h>

const char* ssid = "ESP8266-AP";
const char* password = "12345678";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  // Wait until the client sends a request
  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  client.flush();

  // Route handling
  if (req.indexOf("GET /ff") >= 0) {
    Serial.print("@90##");
  } else if (req.indexOf("GET /rr") >= 0) {
    Serial.print("@0##");
  } else if (req.indexOf("GET /ll") >= 0) {
    Serial.print("@90##");
  } else if (req.indexOf("GET /bb") >= 0) {
    Serial.print("@0##");
  } else if (req.indexOf("GET /G") >= 0) {
    Serial.println("%G#");
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html><head>");
    client.println("<style>");
    client.println("button {");
    client.println("  user-select: none;");
    client.println("  -webkit-user-select: none;");
    client.println("  -ms-user-select: none;");
    client.println("  -moz-user-select: none;");
    client.println("}");
    client.println("</style>");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
    client.println("</head>");
    client.println("<body>");
    client.println("<h2>ESP8266 Web Server</h2>");
    client.println("<button ontouchstart='press(\"ff\")' ontouchend='endPress()'>Forward</button>");
    client.println("<button ontouchstart='press(\"ll\")' ontouchend='endPress()'>Left</button>");
    client.println("<button ontouchstart='press(\"rr\")' ontouchend='endPress()'>Right</button>");
    client.println("<button ontouchstart='press(\"bb\")' ontouchend='endPress()'>Backward</button>");
    client.println("<p id='result'></p>");
    client.println("<script>");
    client.println("var isPressing = false;");
    client.println("var xhrInterval;");

    // When the button is pressed down (for mouse or touch)
    client.println("function press(c) {");
    client.println("  isPressing = true;");
    client.println("  xhrInterval = setInterval(function() {");
    client.println("    var xhr = new XMLHttpRequest();");
    client.println("    xhr.open('GET', '/' + c, true);");
    client.println("    xhr.onload = function() {");
    // client.println("      document.getElementById('result').innerText = xhr.responseText;");
    client.println("    };");
    client.println("    xhr.send();");
    client.println("  }, 100);");  // Send request every 100ms
    client.println("}");

    // When the button is released (for mouse or touch)
    client.println("function endPress() {");
    client.println("  isPressing = false;");
    client.println("  clearInterval(xhrInterval);");  // Stop sending requests when button is released
    client.println("}");

    client.println("</script>");
    client.println("</body></html>");
  } else {
    // Serve main page
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html><html><head>");
    client.println("<style>");
    client.println("button {");
    client.println("  user-select: none;");
    client.println("  -webkit-user-select: none;");
    client.println("  -ms-user-select: none;");
    client.println("  -moz-user-select: none;");
    client.println("}");
    client.println("</style>");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
    client.println("</head>");
    client.println("<body>");
    client.println("<h2>ESP8266 Web Server</h2>");
    client.println("<a href='/G'>G Drive</a>");
    client.println("<a href='/IT'>Infrared Tracing</a>");
    client.println("<a href='/LS'>Light Seeking</a>");
    client.println("<a href='/IR'>Infrared Remote</a>");
    client.println("<a href='/UF'>Ultrasonic Follow</a>");
    client.println("<a href='/UA'>Ultrasonic Avoidance</a>");
    client.println("</body></html>");
  }

  delay(1);
}
