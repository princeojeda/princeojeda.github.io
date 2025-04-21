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
  if (req.indexOf("GET /manifest.json") >= 0) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: appplication/json");
    client.println("Connection: close");
    client.println("");

    client.println("{\"name\": \"RC Car Controller\",\"short_name\": \"RCCar\",\"start_url\": \"/\",\"display\": \"fullscreen\",\"orientation\": \"landscape\",\"background_color\": \"#000000\",\"theme_color\": \"#000000\"}");
  } else if (req.indexOf("GET /FF") >= 0) {
    Serial.print("@90##");
  } else if (req.indexOf("GET /RR") >= 0) {
    Serial.print("@0##");
  } else if (req.indexOf("GET /LL") >= 0) {
    Serial.print("@90##");
  } else if (req.indexOf("GET /BB") >= 0) {
    Serial.print("@0##");
  } else if (req.indexOf("GET /minus") >= 0) {
    int paramStart = req.indexOf("value=");  // find the position of "value="
    if (paramStart >= 0) {
      paramStart += 6;                              // move past "value=" (6 characters)
      int paramEnd = req.indexOf(" ", paramStart);  // find the space after the number
      String valueStr = req.substring(paramStart, paramEnd);
      int value = valueStr.toInt();  // convert to integer
      Serial.print("%"+String(value)+"-");
    }
  } else if (req.indexOf("GET /add") >= 0) {
    int paramStart = req.indexOf("value=");  // find the position of "value="
    if (paramStart >= 0) {
      paramStart += 6;                              // move past "value=" (6 characters)
      int paramEnd = req.indexOf(" ", paramStart);  // find the space after the number
      String valueStr = req.substring(paramStart, paramEnd);
      int value = valueStr.toInt();  // convert to integer
      Serial.print("%"+String(value)+"+");
    }
  } else if (req.indexOf("GET /counter") >= 0) {
    Serial.print("%L");
  } else if (req.indexOf("GET /clockwise") >= 0) {
    Serial.print("%R");
  } else if (req.indexOf("GET /gravity") >= 0) {
    Serial.print("%S");
  } else if (req.indexOf("GET /G") >= 0) {
    Serial.println("%G#");
  } else if (req.indexOf("GET /T") >= 0) {
    Serial.print("@90##");
  } else if (req.indexOf("GET /P") >= 0) {
    Serial.print("@0##");
  } else if (req.indexOf("GET /I") >= 0) {
    Serial.print("@0##");
  } else if (req.indexOf("GET /F") >= 0) {
    Serial.print("@90##");
  } else if (req.indexOf("GET /A") >= 0) {
    Serial.print("@0##");
  } else if (req.indexOf("GET /S") >= 0) {
    Serial.println("%Q");
    // client.println("HTTP/1.1 200 OK");
    // client.println("Content-Type: text/html");
    // client.println("Connection: close");
    // client.println();

    // client.println("<!DOCTYPE html><html><head>");
    // client.println("<style>");
    // client.println("button {");
    // client.println("  user-select: none;");
    // client.println("  -webkit-user-select: none;");
    // client.println("  -ms-user-select: none;");
    // client.println("  -moz-user-select: none;");
    // client.println("}");
    // client.println("</style>");
    // client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
    // client.println("</head>");
    // client.println("<body>");
    // client.println("<h2>ESP8266 Web Server</h2>");
    // client.println("<button ontouchstart='press(\"ff\")' ontouchend='endPress()'>Forward</button>");
    // client.println("<button ontouchstart='press(\"ll\")' ontouchend='endPress()'>Left</button>");
    // client.println("<button ontouchstart='press(\"rr\")' ontouchend='endPress()'>Right</button>");
    // client.println("<button ontouchstart='press(\"bb\")' ontouchend='endPress()'>Backward</button>");
    // client.println("<p id='result'></p>");
    // client.println("<script>");
    // client.println("var isPressing = false;");
    // client.println("var xhrInterval;");

    // // When the button is pressed down (for mouse or touch)
    // client.println("function press(c) {");
    // client.println("  isPressing = true;");
    // client.println("  xhrInterval = setInterval(function() {");
    // client.println("    var xhr = new XMLHttpRequest();");
    // client.println("    xhr.open('GET', '/' + c, true);");
    // client.println("    xhr.onload = function() {");
    // // client.println("      document.getElementById('result').innerText = xhr.responseText;");
    // client.println("    };");
    // client.println("    xhr.send();");
    // client.println("  }, 100);");  // Send request every 100ms
    // client.println("}");

    // // When the button is released (for mouse or touch)
    // client.println("function endPress() {");
    // client.println("  isPressing = false;");
    // client.println("  clearInterval(xhrInterval);");  // Stop sending requests when button is released
    // client.println("}");

    // client.println("</script>");
    // client.println("</body></html>");
  } else {
    // Serve main page
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();

    // client.println("<!DOCTYPE html><html><head>");
    // client.println("<style>");
    // client.println("button {");
    // client.println("  user-select: none;");
    // client.println("  -webkit-user-select: none;");
    // client.println("  -ms-user-select: none;");
    // client.println("  -moz-user-select: none;");
    // client.println("}");
    // client.println("</style>");
    // client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />");
    // client.println("</head>");
    // client.println("<body>");
    // client.println("<h2>ESP8266 Web Server</h2>");
    // client.println("<a href='/G'>G Drive</a>");
    // client.println("<a href='/IT'>Infrared Tracing</a>");
    // client.println("<a href='/LS'>Light Seeking</a>");
    // client.println("<a href='/IR'>Infrared Remote</a>");
    // client.println("<a href='/UF'>Ultrasonic Follow</a>");
    // client.println("<a href='/UA'>Ultrasonic Avoidance</a>");
    // client.println("</body></html>");
    client.println("<!doctypehtml><html lang=en><meta content=\"width=device-width,initial-scale=1\"name=viewport><style>button,div{max-height:100%}button{user-select:none;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;padding:10px 20px;font-size:16px;margin:5px;border:0;border-radius:5px;background-color:#007bff;color:#fff;cursor:pointer;transition:background-color .3s ease;height:100%}span.activated{background-color:#0f0;display:block;width:20px;height:20px;border-radius:50%}div.column,div.row{display:flex;justify-content:space-between;align-items:center;flex-direction:row}div.column{flex-direction:column}div{max-width:800px;margin:0 auto;position:relative}div.l{background-color:#007bff;color:#fff;padding:10px 20px;border-radius:5px;margin:5px}div,div.a{height:100%}div.a{width:50%}div.aa>button{padding:30px}button:disabled{background-color:#ccc;cursor:not-allowed}</style><div class=row><button type=button id=gdbtn onclick='cmd(\"G\",this.id)'>GDrive</button> <button type=button id=itbtn onclick='cmd(\"T\",this.id)'>Infrared Tracing</button> <button type=button id=lsbtn onclick='cmd(\"P\",this.id)'>Light Seeking</button> <button type=button id=irbtn onclick='cmd(\"I\",this.id)'>Infrared Remote</button> <button type=button id=ufbtn onclick='cmd(\"F\",this.id)'>UltraSonic Follow</button> <button type=button id=uabtn onclick='cmd(\"A\",this.id)'>Ultrasonic Avoidance</button> <button type=button id=stopbtn onclick='cmd(\"S\",this.id)'>Stop</button></div><div class=row><div class=\"a column\"><div class=row><span id=gda></span><p>GDrive</div><div class=column><div class=aa><button type=button class=controller ontouchend=pressEnd() ontouchstart='cmd(\"FF\")'onmousedown='cmd(\"FF\")'onmouseup=pressEnd>Forward</button></div><div class=aa><button type=button class=controller ontouchend=pressEnd() ontouchstart='cmd(\"LL\")'>Left</button> <button type=button class=controller ontouchend=pressEnd() ontouchstart='cmd(\"RR\")'>Right</button></div><div class=aa><button type=button class=controller ontouchend=pressEnd() ontouchstart='cmd(\"BB\")'>Backward</button></div></div></div><div class=a><div class=\"row l\"><span id=ita></span><p class=row>Infrared Tracing</div><div class=\"row l\"><span id=lsa></span><p class=row>Light Seeking</div><div class=\"row l\"><span id=ira></span><p class=row>Infrared Remote</div><div class=\"row l\"><span id=ufa></span><p class=row>UltraSonic Follow</div><div class=\"row l\"><span id=uaa></span><p class=row>Ultrasonic Avoidance</div><div class=\"row l\"><span id=sa></span><p class=row>Stop</div></div></div><script>var _0x47dda2=_0x5ae6;function _0xf58c(){var _0x549be8=['onload','589876VCetfm','ufa','247824YpLobZ','lsbtn','getElementById','activated','704248CZZDqW','gdbtn','lsa','359902QcOWAE','itbtn','classList','ufbtn','396404KldomY','remove','stopbtn','some','22735vGJIFx','4870zfInyD','uaa','disabled','uabtn','ita','6ZUamjj','open','2529bCMecV','forEach','4OghemY','GET','ira','send'];_0xf58c=function(){return _0x549be8;};return _0xf58c();}function _0x5ae6(_0x10fc28,_0x13b867){var _0xf58c5f=_0xf58c();return _0x5ae6=function(_0x5ae645,_0x1d3664){_0x5ae645=_0x5ae645-0xe0;var _0x4516aa=_0xf58c5f[_0x5ae645];return _0x4516aa;},_0x5ae6(_0x10fc28,_0x13b867);}(function(_0x2049dd,_0x2497f7){var _0x3bcf8a=_0x5ae6,_0x49b5da=_0x2049dd();while(!![]){try{var _0x21a383=parseInt(_0x3bcf8a(0xf8))/0x1+-parseInt(_0x3bcf8a(0xfc))/0x2+-parseInt(_0x3bcf8a(0xf1))/0x3*(parseInt(_0x3bcf8a(0xea))/0x4)+parseInt(_0x3bcf8a(0xe0))/0x5*(-parseInt(_0x3bcf8a(0xe6))/0x6)+-parseInt(_0x3bcf8a(0xef))/0x7+parseInt(_0x3bcf8a(0xf5))/0x8+-parseInt(_0x3bcf8a(0xe8))/0x9*(-parseInt(_0x3bcf8a(0xe1))/0xa);if(_0x21a383===_0x2497f7)break;else _0x49b5da['push'](_0x49b5da['shift']());}catch(_0x35a12b){_0x49b5da['push'](_0x49b5da['shift']());}}}(_0xf58c,0x34873));var spans=[document[_0x47dda2(0xf3)](_0x47dda2(0xe5)),document['getElementById'](_0x47dda2(0xf7)),document['getElementById'](_0x47dda2(0xec)),document[_0x47dda2(0xf3)](_0x47dda2(0xf0)),document[_0x47dda2(0xf3)](_0x47dda2(0xe2)),document[_0x47dda2(0xf3)]('sa'),document[_0x47dda2(0xf3)]('gda')],btns=[document[_0x47dda2(0xf3)](_0x47dda2(0xf9)),document[_0x47dda2(0xf3)](_0x47dda2(0xf2)),document['getElementById']('irbtn'),document['getElementById'](_0x47dda2(0xfb)),document['getElementById'](_0x47dda2(0xe4)),document['getElementById'](_0x47dda2(0xfe)),document[_0x47dda2(0xf3)](_0x47dda2(0xf6))],isPressing=![],xhrInterval;function cmd(_0x50524d,_0x1c4891){var _0x32bdb4=_0x47dda2;btns[_0x32bdb4(0xff)](_0x42bb79=>_0x42bb79['id']==_0x1c4891)&&(btns[_0x32bdb4(0xe9)](function(_0x55e7e2){var _0x565688=_0x32bdb4;_0x55e7e2[_0x565688(0xe3)]=!![];}),document['getElementById'](_0x1c4891)[_0x32bdb4(0xe3)]=![],btns[0x5][_0x32bdb4(0xe3)]=![],btns[0x5]==document[_0x32bdb4(0xf3)](_0x1c4891)&&btns['forEach'](function(_0x4dbf78){var _0x3d6710=_0x32bdb4;_0x4dbf78[_0x3d6710(0xe3)]=![];}));if(_0x50524d=='G')pressEnd(),toggleButton(spans[0x6]);else{if(_0x50524d=='T')pressEnd(),toggleButton(spans[0x0]);else{if(_0x50524d=='P')pressEnd(),toggleButton(spans[0x1]);else{if(_0x50524d=='I')pressEnd(),toggleButton(spans[0x2]);else{if(_0x50524d=='F')pressEnd(),toggleButton(spans[0x3]);else{if(_0x50524d=='A')pressEnd(),toggleButton(spans[0x4]);else{if(_0x50524d=='S')pressEnd(),removeAllActivated();else(_0x50524d=='FF'||_0x50524d=='LL'||_0x50524d=='RR'||_0x50524d=='BB')&&(spans[0x6]['classList']['contains'](_0x32bdb4(0xf4))&&toggleButton(spans[0x6]));}}}}}}isPressing=!![],xhrInterval=setInterval(function(){var _0x5d848d=_0x32bdb4,_0x5ef7f7=new XMLHttpRequest();_0x5ef7f7[_0x5d848d(0xe7)](_0x5d848d(0xeb),'/'+_0x50524d,!![]),_0x5ef7f7[_0x5d848d(0xee)]=function(){},_0x5ef7f7[_0x5d848d(0xed)](),btns[_0x5d848d(0xff)](_0x4b128a=>_0x4b128a['id']==_0x1c4891)&&pressEnd();},0x32);}function pressEnd(){isPressing=![],clearInterval(xhrInterval);}function toggleButton(_0x495c86){var _0x4e5f31=_0x47dda2;spans[_0x4e5f31(0xe9)](function(_0x41dd93){var _0x8563f7=_0x4e5f31;_0x41dd93['classList'][_0x8563f7(0xfd)](_0x8563f7(0xf4));}),_0x495c86[_0x4e5f31(0xfa)]['add'](_0x4e5f31(0xf4));}function removeAllActivated(){var _0x57a04e=_0x47dda2;spans[_0x57a04e(0xe9)](function(_0xd2b812){var _0x5e9003=_0x57a04e;_0xd2b812[_0x5e9003(0xfa)][_0x5e9003(0xfd)]('activated');});}</script>");
  }

  delay(1);
}
