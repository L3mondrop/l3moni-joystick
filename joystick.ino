// Define row and column pins based on schematic and XIAO pinout
const int rowPins[] = {A6, A3, A2, A1, A0}; // R1–R5 mapped to A6, A3, A2, A1, A0
const int colPins[] = {A10, A9, A8, A7};    // C1–C4 mapped to A10, A9, A8, A7

const int numRows = 5;                      // Total rows
const int numCols = 4;                      // Total columns

// State storage for button presses
bool buttonStates[numRows][numCols];

void setup() {
    Serial.begin(9600);

    // Initialize row pins as outputs
    for (int i = 0; i < numRows; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH); // Set rows HIGH by default
    }

    // Initialize column pins as inputs with pull-up resistors
    for (int i = 0; i < numCols; i++) {
        pinMode(colPins[i], INPUT_PULLUP);
    }

    Serial.println("Button Matrix Initialized...");
}

void loop() {
    bool buttonPressed = false; // Track if any button is pressed

    // Scan rows
    for (int row = 0; row < numRows; row++) {
        // Set current row LOW, all others HIGH
        for (int i = 0; i < numRows; i++) {
            digitalWrite(rowPins[i], (i == row) ? LOW : HIGH);
        }

        // Read all columns for the current row
        for (int col = 0; col < numCols; col++) {
            int buttonState = digitalRead(colPins[col]);

            // Invert state because INPUT_PULLUP is used
            buttonStates[row][col] = (buttonState == LOW);

            if (buttonStates[row][col]) {
                buttonPressed = true; // Mark that at least one button is pressed
            }
        }
    }

    // If any button is pressed, print the matrix
    if (buttonPressed) {
        Serial.println("Button Matrix:");
        for (int row = 0; row < numRows; row++) {
            Serial.print("Row ");
            Serial.print(row + 1);
            Serial.print(": ");
            for (int col = 0; col < numCols; col++) {
                Serial.print(buttonStates[row][col] ? "X " : "O ");
            }
            Serial.println();
        }
        Serial.println(); // Add a blank line for readability
    }

    delay(50); // Small delay to debounce
}
