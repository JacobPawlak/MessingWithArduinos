//playing with potentiometers
//Jacob Pawlak
//September 25th, 2020
//goooo blue team!

//setting up the input ports (potentiometers)
const int red_in = A0;
const int green_in = A1;
const int blue_in = A2;
//setting up the output ports (rgb light terminals)
const int red_out = 13;
const int green_out = 12;
const int blue_out = 11;

//setting up vars for the analog input from potentiometers
int red_pot = 0;
int green_pot = 0;
int blue_pot = 0;
//making an extra variable (in know i could do it without the three above w/ some condensing) for the mapped value
int red_val = 0;
int green_val = 0;
int blue_val = 0;

void setup() {
}

void loop() {
  //pull in the reading from the potentiometers
  red_pot = analogRead(red_in);
  green_pot = analogRead(green_in);
  blue_pot = analogRead(blue_in);
  //map the values to 0-255 for each rgb value
  red_val = map(red_pot, 0, 1023, 0, 255);
  green_val = map(green_pot, 0, 1023, 0, 255);
  blue_val = map(blue_pot, 0, 1023, 0, 255);
  //write the value to the led
  analogWrite(red_out, red_val);
  analogWrite(green_out, green_val);
  analogWrite(blue_out, blue_val);
  //HOLD IT. that's long enough, carry on.
  delay(5);
}
