File file;

void doAnimationFromFile(String filename) {
  if (file.available() && String(file.name()) == filename)
    doAnimationStepFromFile();
  else {
    file = SPIFFS.open(filename, "r");
    doAnimationStepFromFile();
  }

}

void doAnimationStepFromFile() {
  char buffer[8];
  if (file.available() > 71) // 8 for starting byte, 64 for LEDs
  {
    file.readBytes(buffer, 8);
    Serial.write(buffer[0]); // Starting byte 0xF2
    for (int i = 0; i < 8; i++) {
      file.readBytes(buffer, 8);
      for (int j = 0; j < 8; j++) {
        Serial.write(buffer[j]);
      }
    }
  }
  else
    file.close();
}

void doExample() {
  doAnimationFromFile(String("/examples/") + currentExample + String(".dat"));
}

