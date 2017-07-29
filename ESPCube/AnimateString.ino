int currentStringPosition;
int currentPositionInLetterAnimation;

void resetCurrentStringAnimation(String text) {
  currentStringPosition = 0;
  currentPositionInLetterAnimation = 0;
  currentAnimationMaxSteps = text.length() * 8;
}
void animateString(String text, int msDelay) {
  if (currentStringPosition >= text.length())
    //currentStringPosition = 0;
    resetCurrentStringAnimation(text);
  if (currentPositionInLetterAnimation > 7)   {
    currentStringPosition++;
    currentPositionInLetterAnimation = 0;
  }

  doAnimationFromFile("/letters/" + String(text.charAt(currentStringPosition)) + String(".dat"));
  if (currentPositionInLetterAnimation == 0)
    delay(msDelay);
  currentPositionInLetterAnimation++;
}

