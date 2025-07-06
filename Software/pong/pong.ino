#include <Adafruit_NeoPixel.h>

// NeoPixel configuration
#define LED_PIN D6
#define NUM_PIXELS 240 // 20 length x 12 width display
#define WIDTH 12
#define HEIGHT 20
#define BRIGHTNESS 20

#define X_button D3
#define Y_button D1
#define A_button D2
#define B_button D0
#define S_button D10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Snake game variables
int snakeX[NUM_PIXELS], snakeY[NUM_PIXELS]; // Snake body coordinates
int snakeLength = 3;                       // Initial snake length
int foodX, foodY;                          // Food position
int direction = 1;                         // 0: Left, 1: Up, 2: Right, 3: Down
bool gameOver = false;

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();

  // Set button pins as input with pull-up resistors
  pinMode(X_button, INPUT_PULLUP);
  pinMode(Y_button, INPUT_PULLUP);
  pinMode(A_button, INPUT_PULLUP);
  pinMode(B_button, INPUT_PULLUP);
  pinMode(S_button, INPUT_PULLUP);

  // Initialize the snake
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = WIDTH / 2 - i;
    snakeY[i] = HEIGHT / 2;
  }
  generateFood();
}

void loop() {
  if (gameOver) {
    if (digitalRead(S_button) == LOW) {
      restartGame();
    }
    return;
  }

  // Check button inputs for direction
  if (digitalRead(X_button) == LOW && direction != 2) direction = 0; // Left
  if (digitalRead(Y_button) == LOW && direction != 3) direction = 1; // Up
  if (digitalRead(A_button) == LOW && direction != 0) direction = 2; // Right
  if (digitalRead(B_button) == LOW && direction != 1) direction = 3; // Down

  moveSnake();
  if (checkCollision()) {
    gameOver = true;
    displayGameOver();
    return;
  }

  renderGame();
  delay(200); // Control the speed of the game
}

void moveSnake() {
  // Move the snake's body
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move the head in the current direction
  if (direction == 0) snakeX[0]--;        // Left
  else if (direction == 1) snakeY[0]--;   // Up
  else if (direction == 2) snakeX[0]++;   // Right
  else if (direction == 3) snakeY[0]++;   // Down

  // Check if the snake eats the food
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    generateFood();
  }
}

bool checkCollision() {
  // Check collision with walls
  if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
    return true;
  }

  // Check collision with itself
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      return true;
    }
  }
  return false;
}

void generateFood() {
  while (true) {
    foodX = random(0, WIDTH);
    foodY = random(0, HEIGHT);

    // Ensure the food doesn't spawn on the snake
    bool onSnake = false;
    for (int i = 0; i < snakeLength; i++) {
      if (foodX == snakeX[i] && foodY == snakeY[i]) {
        onSnake = true;
        break;
      }
    }
    if (!onSnake) break;
  }
}

void renderGame() {
  strip.clear();

  // Draw the snake
  for (int i = 0; i < snakeLength; i++) {
    int pixelIndex = getPixelIndex(snakeX[i], snakeY[i]);
    strip.setPixelColor(pixelIndex, strip.Color(0, 255, 0)); // Green snake
  }

  // Draw the food
  int foodPixelIndex = getPixelIndex(foodX, foodY);
  strip.setPixelColor(foodPixelIndex, strip.Color(255, 0, 0)); // Red food

  strip.show();
}

void displayGameOver() {
  strip.clear();
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // Flash red to indicate game over
  }
  strip.show();
}

void restartGame() {
  snakeLength = 3;
  direction = 1;
  gameOver = false;
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = WIDTH / 2 - i;
    snakeY[i] = HEIGHT / 2;
  }
  generateFood();
}

int getPixelIndex(int x, int y) {
  if (y % 2 == 0) {
    // Even rows (left to right)
    return y * WIDTH + x;
  } else {
    // Odd rows (right to left)
    return y * WIDTH + (WIDTH - 1 - x);
  }
}
