const int reset_button = A4;
const int red_button = A3;
const int yellow_button = A2;
const int green_button = A1;
const int blue_button = A0;

const int red_led = 2;
const int yellow_led = 3;
const int green_led = 4;
const int blue_led = 5;

const int color_count = 4;
const int max_level = 100;
int sequence[max_level];

bool new_level = true;

bool game_start = false;
int colors[] = {red_led, yellow_led, green_led, blue_led};
int inputs[] = {red_button, yellow_button, green_button, blue_button};

int level = 1;
int index = 0;


int reset_count = 0;

bool last_reset_state = HIGH;


void setup() {
  // put your setup code here, to run once:
  pinMode(reset_button, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(yellow_button, INPUT_PULLUP);
  pinMode(green_button, INPUT_PULLUP);
  pinMode(blue_button, INPUT_PULLUP);

  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(blue_led, LOW);

  
}
void loop() {
  int reset_button_state = digitalRead(reset_button);
  // put your main code here, to run repeatedly:

  if(last_reset_state == HIGH && reset_button_state == LOW){
    game_start = !game_start;
  }
  last_reset_state = reset_button_state;
  if(game_start){
    if(new_level){
      sequence[level - 1] = random(0, color_count);
      new_level = false;
    }

    for(int i = 0; i < level; i++){
      int current_led = colors[sequence[i]];
      digitalWrite(current_led, HIGH);
      delay(200);
      digitalWrite(current_led, LOW);
    }
    delay(1000);

    bool correct = true;

    for(int i = 0; i < level; i++){
      int pressed = -1;

      while(pressed == -1){
        if(digitalRead(red_button) == LOW) pressed = 0;
        else if(digitalRead(yellow_button) == LOW) pressed = 1;
        else if(digitalRead(green_button) == LOW) pressed = 2;
        else if(digitalRead(blue_button) == LOW) pressed = 3;
      }

      digitalWrite(colors[pressed], HIGH);
      delay(300);
      digitalWrite(colors[pressed], LOW);

      if(pressed != sequence[i]){
        correct = false;
        break;
      }
      delay(300);
    }
    if(!correct){
      digitalWrite(red_led, HIGH);
      digitalWrite(yellow_led, HIGH);
      digitalWrite(green_led, HIGH);
      digitalWrite(blue_led, HIGH);
      delay(500);
      digitalWrite(red_led, LOW);
      digitalWrite(yellow_led, LOW);
      digitalWrite(green_led, LOW);
      digitalWrite(blue_led, LOW);
      delay(500);
      digitalWrite(red_led, HIGH);
      digitalWrite(yellow_led, HIGH);
      digitalWrite(green_led, HIGH);
      digitalWrite(blue_led, HIGH);
      delay(500);
      digitalWrite(red_led, LOW);
      digitalWrite(yellow_led, LOW);
      digitalWrite(green_led, LOW);
      digitalWrite(blue_led, LOW);
      delay(500);
      game_start = false;
      new_level = true;
      level = 1;
    }
    else if(correct){
      digitalWrite(red_led, HIGH);
      delay(500);
      digitalWrite(yellow_led, HIGH);
      delay(500);
      digitalWrite(green_led, HIGH);
      delay(500);
      digitalWrite(blue_led, HIGH);
      delay(500);
      digitalWrite(blue_led, LOW);
      delay(500);
      digitalWrite(green_led, LOW);
      delay(500);
      digitalWrite(yellow_led, LOW);
      delay(500);
      digitalWrite(red_led, LOW);
      delay(500);
      level++;
      new_level = true;
    }

  }

}
