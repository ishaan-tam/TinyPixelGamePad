#include <Adafruit_NeoPixel.h>

// NeoPixel configuration
#define LED_PIN D6
#define NUM_PIXELS 240
#define WIDTH 20
#define HEIGHT 12
#define BRIGHTNESS 1

#define X_button D3  //move up 
#define Y_button D1  //move left 
#define A_button D2  //move right 
#define B_button D0  //move down
#define S_button D10 // select 

#define Buzzer_button D9

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Ball variables
int ballX = WIDTH / 2;
int ballY = HEIGHT / 2;

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();

  pinMode(X_button, INPUT_PULLUP);
  pinMode(Y_button, INPUT_PULLUP);
  pinMode(A_button, INPUT_PULLUP);
  pinMode(B_button, INPUT_PULLUP);
  pinMode(S_button, INPUT_PULLUP);
}

void loop() {
  updateBallPosition();
  drawBall();
  delay(100); // Adjust speed of ball movement
}

void updateBallPosition() {
  // Move up
  if (digitalRead(X_button) == LOW && ballY > 0) {
    ballY--;
  }

  // Move down
  if (digitalRead(B_button) == LOW && ballY < HEIGHT - 1) {
    ballY++;
  }

  // Move left
  if (digitalRead(Y_button) == LOW && ballX > 0) {
    ballX--;
  }

  // Move right
  if (digitalRead(A_button) == LOW && ballX < WIDTH - 1) {
    ballX++;
  }

  // Reset position
  if (digitalRead(S_button) == LOW) {
    ballX = WIDTH / 2;
    ballY = HEIGHT / 2;
  }
}

void drawBall() {
  strip.clear();

  // Draw the ball
  strip.setPixelColor(getPixelIndex(ballX, ballY), strip.Color(255, 0, 0));

  strip.show();
}

// Function to calculate pixel index based on zig-zag layout
int getPixelIndex(int x, int y) {
  if (y % 2 == 0) {
    // Even rows (left to right)
    return y * WIDTH + x;
  } else {
    // Odd rows (right to left)
    return y * WIDTH + (WIDTH - 1 - x);
  }
}
