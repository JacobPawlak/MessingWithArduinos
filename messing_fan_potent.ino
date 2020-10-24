//playing with fan and potentiometer
//Jacob Pawlak
//October 2nd, 2020
//goooo blue team!

//setting up the input ports (potentiometers)
const int fan_in = A0;
//setting up the output ports (rgb light terminals)
const int fan_out = 12;

//setting up vars for the analog input from potentiometers
int fan_pot = 0;
//making an extra variable (in know i could do it without the three above w/ some condensing) for the mapped value
int fan_val = 0;

void setup() {
}

void loop() {
  //pull in the reading from the potentiometers
  fan_pot = analogRead(fan_in);
  //map the values to 0-255 for each rgb value
  fan_val = map(fan_pot, 0, 1023, 0, 255);
  //write the value to the led
  analogWrite(fan_out, fan_val);
  //HOLD IT. that's long enough, carry on.
  delay(5);
}
