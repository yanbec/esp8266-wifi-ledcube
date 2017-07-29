#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "FS.h"
enum animation {
  rotTowerLeft,
  rotTowerRight,
  off,
  fullOn,
  wave,
  randomAnimation,
  test,
  binaryFront,
  fence,
  signalLight,
  example,
  string,
  COUNT
};

const char *ssid = "yourSSID";
const char *password = "yourPassword";
int currentAnimationStep = 0;
int currentAnimationMaxSteps = 4;
bool animating = true;
animation currentAnimation = rotTowerLeft;
String currentExample;
String currentlyAnimatedString;
int currentStringDelay;
bool cycleAll = false;

ESP8266WebServer server ( 80 );

void setupServer() {
  
  server.serveStatic("/bootstrap.min.css", SPIFFS, "/bootstrap.min.css");
  
  server.serveStatic("/", SPIFFS, "/ledcube.html");
  
  server.on ( "/rotTowerLeft", []() {
    currentAnimation = rotTowerLeft;
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/rotTowerRight", []() {
    currentAnimation = rotTowerRight;
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/off", []() {
    currentAnimation = off;
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/fullOn", []() {
    currentAnimation = fullOn;
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/wave", []() {
    currentAnimation = wave;
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/fence", []() {
    currentAnimation = fence;
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/random", []() {
    currentAnimation = randomAnimation;
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/test", []() {
    currentAnimation = test;
    server.send ( 200, "text/html", "" );
  });
  
  server.on ( "/signalLight", []() {
    currentAnimation = signalLight;
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/binaryFront", []() {
    currentAnimation = binaryFront;
    server.send ( 200, "text/html", "" );
  });

    server.on ( "/toggleCycle", []() {
    cycleAll = !cycleAll;
    server.send ( 200, "text/html", "" );
  });


  server.on ( "/string", []() {
    currentAnimation = string;
    currentlyAnimatedString = server.arg(0);
    currentlyAnimatedString.toUpperCase();
    resetCurrentStringAnimation(server.arg(0));
    currentStringDelay = server.arg(1).toInt()*100;
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/example", []() {
    currentAnimation = example;
    currentExample = server.arg(0);
    server.send ( 200, "text/html", "" );
  });

  server.on ( "/continue", []() {
    animating = true;
    server.send ( 200, "text/html", "" );
  });
  server.on ( "/pause", []() {
    animating = false;
    server.send ( 200, "text/html", "" );
  });
  server.begin();

  Serial.println ( "HTTP server started" );
}

void setup ( void ) {
  Serial.begin ( 9600 );
  WiFi.begin ( ssid, password );
  SPIFFS.begin();
  // Wait for connection
  bool toggle = true;
  int wifiRetry = 0;
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 100 );
    Serial.print ( "." );
    if (toggle)
      turnCubeFullOn();
    else
      turnCubeOff();
    toggle = !toggle;
    wifiRetry++;
    if (wifiRetry > 100) {
      WiFi.disconnect();
      WiFi.mode(WIFI_AP);
      bool result = WiFi.softAP("ESPCube");
      delay(1000);
      if (result)
        Serial.println("Soft-AP set up.");
      else
        Serial.println("Something went wrong.");
      WiFi.printDiag(Serial);
      currentAnimation = fence;
      break;
    }

  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  setupServer();
}



void loop ( void ) {
  if (currentAnimationStep >= currentAnimationMaxSteps) {
    currentAnimationStep = 0;
    if (cycleAll) {
      currentAnimation = static_cast<animation>(static_cast<int>(currentAnimation+1));
      if (currentAnimation == COUNT)
        currentAnimation = static_cast<animation>(0);
    }
  }
    

  if (animating) {
    Serial.println();
    switch (currentAnimation) {
      case rotTowerLeft:
        rotateTower(true);
        break;
      case rotTowerRight:
        rotateTower(false);
        break;
      case fullOn:
        turnCubeFullOn();
        break;
      case off:
        turnCubeOff();
        break;
      case wave:
        doWave();
        break;
      case randomAnimation:
        doRandom();
        break;
      case fence:
        doFence();
        break;
      case test:
        doTest();
        break;
      case binaryFront:
        doBinaryFront();
        break;
      case signalLight:
        doSignalLight();
        break;
      case example:
        doExample();
        break;
      case string:
        animateString(currentlyAnimatedString, currentStringDelay);
        break;
    }
    currentAnimationStep++;
  }
  server.handleClient();
}
