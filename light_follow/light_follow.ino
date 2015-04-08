// Motor pins
#define SPEED_RIGHT 5
#define SPEED_LEFT 6
#define DIR_RIGHT 8
#define DIR_LEFT 7

// IR LED pins
#define LED_SENSOR_COUNT 5
#define LED_START_PIN 14

// Speed constants
#define SPEED_FAST 200
#define SPEED_MED 120
#define SPEED_SLOW 80
#define SPEED_NONE 0

// Direction constants
#define DIR_FW LOW
#define DIR_BW HIGH

#define HIGH_LIGHT 8
#define LOW_LIGHT 2

#define HIGH_CHAR 'H'
#define LOW_CHAR 'L'
#define NONE_CHAR 'N'

int baseValues[LED_SENSOR_COUNT];
int noLightCount = 0;

void setup()
{
    for (int i = 5; i <= 8; i++)
        pinMode(i, OUTPUT);

    delay(500);
    Serial.begin(9600);

    calibrate();
}

void loop() {
    // Default to forward
    digitalWrite(DIR_RIGHT, DIR_FW);
    digitalWrite(DIR_LEFT, DIR_FW);

    char values[LED_SENSOR_COUNT - 2];
    read(values);
    for (int i = 0; i < LED_SENSOR_COUNT; i++) {
        Serial.print(values[i]);
        Serial.print(" ");
    }
    Serial.println("");

    String noLight[] = { "NNNNN" };
    String onLight[] = { "HHHHH", "LHHHL" };

    String lightForward[] = { "LLLLL", "NLLLN", "NNLNN", "LLHLL", "LHHHL", "NNHNN", "NHHHN" };

    String lightLeft[] = {
      "LLNNN", "LNNNN", "HHNNN", "HNNNN"
    };
    String lightSlightLeft[] = {
      "LLLLN", "LLLNN", "HHHHN", "HHHNN", "HHHHL", "HHHLL",
      "LHHLN", "LHLNN", "LLHLN", "LHLLN", "LHHLN"
    };

    String lightRight[] = {
      "NNNLL", "NNNNL", "NNNHH", "NNNNH"

    };
    String lightSlightRight[] = {
      "NLLLL", "NNLLL", "NHHHH", "NNHHH", "LHHHH", "LLHHH",
      "NLHHL", "NNLHL", "NLHLL", "NLLHL", "NLHHL"
    };


    if (equalsAny(values, noLight)) {
        noLightCount++;
        if (noLightCount > 50) {
            goRight();
        }
        else {
            stop();
        }
    }
    else if (equalsAny(values, onLight)) {
        noLightCount = 0;
        stop();
    }
    else if (equalsAny(values, lightForward)) {
        noLightCount = 0;
        goForward();
    }
    else if (equalsAny(values, lightLeft)) {
        noLightCount = 0;
        goLeft();
    }
    else if (equalsAny(values, lightRight)) {
        noLightCount = 0;
        goRight();
    }
    else if (equalsAny(values, lightSlightLeft)) {
        noLightCount = 0;
        correctLeft();
    }
    else if (equalsAny(values, lightSlightRight)) {
        noLightCount = 0;
        correctRight();
    }

}

void calibrate() {
    int loops = 5;
    for (int i = 0; i < loops; i++) {
        for (int pin = LED_START_PIN; pin < LED_START_PIN+LED_SENSOR_COUNT; pin++) {
            baseValues[pin - LED_START_PIN] += analogRead(pin);
        }
    }

    for (int pin = LED_START_PIN; pin < LED_START_PIN+LED_SENSOR_COUNT; pin++) {
        baseValues[pin - LED_START_PIN] = int(baseValues[pin-LED_START_PIN] / loops);
    }
}

void read(char *values) {
    for (int pin = LED_START_PIN; pin < LED_START_PIN+LED_SENSOR_COUNT; pin++) {
        int deltaValue = analogRead(pin) - baseValues[pin - LED_START_PIN];
        values[pin - LED_START_PIN] = valueToChar(deltaValue);
    }
}

char valueToChar(int value) {
    if(value > HIGH_LIGHT)
        return HIGH_CHAR;
    else if(value > LOW_LIGHT)
        return LOW_CHAR;
    else
        return NONE_CHAR;
}

bool equalsAny(String value, String *possibleValues) {
    for (int i = 0; i < sizeof(possibleValues); i++) {
        if (value.equals(possibleValues[i])) {
            return true;
        }
    }
    return false;
}

void stop() {
    Serial.println("stop");
    analogWrite(SPEED_LEFT, SPEED_NONE);
    analogWrite(SPEED_RIGHT, SPEED_NONE);
}

void goForward() {
    Serial.println("go forward");
    analogWrite(SPEED_LEFT, SPEED_FAST);
    analogWrite(SPEED_RIGHT, SPEED_FAST);
}

void goLeft() {
    Serial.println("go left");
    analogWrite(SPEED_LEFT, SPEED_NONE);
    analogWrite(SPEED_RIGHT, SPEED_FAST);
}

void goRight() {
    Serial.println("go right");
    analogWrite(SPEED_LEFT, SPEED_FAST);
    analogWrite(SPEED_RIGHT, SPEED_NONE);
}

void correctLeft() {
    Serial.println("correct left");
    analogWrite(SPEED_LEFT, SPEED_SLOW);
    analogWrite(SPEED_RIGHT, SPEED_MED);
}

void correctRight() {
    Serial.println("correct right");
    analogWrite(SPEED_LEFT, SPEED_MED);
    analogWrite(SPEED_RIGHT, SPEED_SLOW);
}
