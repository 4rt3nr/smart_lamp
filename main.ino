#define PHOTO_PIN A0
#define LED_PIN 9

int THRESHOLD = 500;
int MIN_BRIGHTNESS = 30;
int MAX_BRIGHTNESS = 255;
int TRANSITION_SPEED = 10;

int currentBrightness = 0;
int targetBrightness = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(PHOTO_PIN);
  
  Serial.print("Освещенность: ");
  Serial.println(lightLevel);
  
  if (lightLevel < THRESHOLD) {
    targetBrightness = map(lightLevel, 0, THRESHOLD, MAX_BRIGHTNESS, MIN_BRIGHTNESS);
  } else {
    targetBrightness = 0;
  }
  
  targetBrightness = constrain(targetBrightness, 0, MAX_BRIGHTNESS);
  
  if (currentBrightness < targetBrightness) {
    currentBrightness += TRANSITION_SPEED;
    if (currentBrightness > targetBrightness) {
      currentBrightness = targetBrightness;
    }
  } else if (currentBrightness > targetBrightness) {
    currentBrightness -= TRANSITION_SPEED;
    if (currentBrightness < targetBrightness) {
      currentBrightness = targetBrightness;
    }
  }
  
  analogWrite(LED_PIN, currentBrightness);
  
  Serial.print("Яркость: ");
  Serial.println(currentBrightness);
  
  delay(50);
}
