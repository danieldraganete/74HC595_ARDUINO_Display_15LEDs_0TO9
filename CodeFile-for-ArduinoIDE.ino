
 /*To have a correct display, 
the LEDs must be connected in the mirror! 
the last pin will be the first Led*/

// Define 74HC595 pins
const int latchPin = 8; // ST_CP pin
const int clockPin = 12; // SH_CP pin
const int dataPin = 11; // DS pin

// LED configuration matrix for each digit
int ledMatrix[10][5][3] = {
  // 0
  {
    {1, 1, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  // 1
  {
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1}
  },
  // 2
  {
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1}
  },
  // 3
  {
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
  },
  // 4
  {
    {1, 0, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1}
  },
  // 5
  {
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {0, 0, 1},
    {1, 1, 1}
  },
  // 6
  {
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  // 7
  {
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1}
  },
  // 8
  {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
  },
  // 9
  {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    {0, 0, 1},
    {0, 0, 1}
  }
};

void setup() {
  // Set control pins as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  // Start serial communication
  Serial.begin(9600);
}

// Function to send a bit
void sendBit(int bit) {
  // Set data pin (DS)
  digitalWrite(dataPin, bit);
  // Generate clock pulse (SH_CP)
  digitalWrite(clockPin, HIGH);
  digitalWrite(clockPin, LOW);
}

// Function to send a byte to 74HC595
void sendData(int ledState) {
  // Send a bit for LED state
  sendBit(ledState ? HIGH : LOW);
}

void displayDigit(int digit) {
  // Send current configuration to the two 74HC595s
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      sendData(ledMatrix[digit][i][j]);
    }
  }
  digitalWrite(latchPin, HIGH);
}

void loop() {
  // Iterate through each digit from 0 to 9 and display it on LEDs
  for (int digit = 0; digit < 10; digit++) {
    // Display the current digit
    displayDigit(digit);
    // Delay between displaying each digit
    delay(1000); // Adjust as necessary
  }
}