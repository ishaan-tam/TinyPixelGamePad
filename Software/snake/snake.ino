#include <Adafruit_NeoPixel.h>

#define LED_PIN D6
#define NUM_PIXELS 240
#define WIDTH 20
#define HEIGHT 12
#define BRIGHTNESS 1

#define X_button D3  // Move up
#define Y_button D1  // Move left
#define A_button D2  // Move right
#define B_button D0  // Move down
#define S_button D10 // Select (Restart)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Snake variables
int snakeLength = 3;
int snakeX[240];
int snakeY[240];
int foodX, foodY;
int dirX = 1, dirY = 0; // Start moving right

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();

  pinMode(X_button, INPUT_PULLUP);
  pinMode(Y_button, INPUT_PULLUP);
  pinMode(A_button, INPUT_PULLUP);
  pinMode(B_button, INPUT_PULLUP);
  pinMode(S_button, INPUT_PULLUP);

  resetGame();
}

void loop() {
  updateDirection();
  updateSnake();
  checkCollision();
  drawGame();
  delay(150); // Adjust speed of the game
}

void resetGame() {
  snakeLength = 3;
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = WIDTH / 2 - i;
    snakeY[i] = HEIGHT / 2;
  }
  generateFood();
}

void updateDirection() {
  if (digitalRead(X_button) == LOW) {
    dirX = 0;
    dirY = -1; // Up
  }
  if (digitalRead(B_button) == LOW) {
    dirX = 0;
    dirY = 1; // Down
  }
  if (digitalRead(Y_button) == LOW) {
    dirX = -1;
    dirY = 0; // Left
  }
  if (digitalRead(A_button) == LOW) {
    dirX = 1;
    dirY = 0; // Right
  }
  if (digitalRead(S_button) == LOW) {
    resetGame(); // Restart the game
  }
}

void updateSnake() {
  int newHeadX = snakeX[0] + dirX;
  int newHeadY = snakeY[0] + dirY;

  // Move the body
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move the head
  snakeX[0] = newHeadX;
  snakeY[0] = newHeadY;

  // Check if snake eats food
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    generateFood();
  }
}

void generateFood() {
  foodX = random(0, WIDTH);
  foodY = random(0, HEIGHT);
}

void checkCollision() {
  // Wall collision
  if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
    resetGame(); // Reset game on collision
  }

  // Self collision
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      resetGame(); // Reset game on self-collision
    }
  }
}

void drawGame() {
  strip.clear();

  // Draw snake
  for (int i = 0; i < snakeLength; i++) {
    strip.setPixelColor(getPixelIndex(snakeX[i], snakeY[i]), strip.Color(0, 255, 0));
  }

  // Draw food
  strip.setPixelColor(getPixelIndex(foodX, foodY), strip.Color(255, 0, 0));

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
