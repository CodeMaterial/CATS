#include <PulsePosition.h>

PulsePositionInput myIn;

void setup() {
  Serial.begin(9600);
  if(DEBUG){
    while (!Serial) {
      delay(1);
    }
    Serial.println("Serial connected")
  }
  myIn.begin(10);
}

void loop() {
  int channel, max_channels;

  max_channels = myIn.available();
  if (max_channels > 0) {
    for (channel=1; channel <= max_channels; channel++) {
      int val = myIn.read(channel);
      Serial.print(val);
      Serial.print("  ");
    }
    Serial.println();
  }
}
