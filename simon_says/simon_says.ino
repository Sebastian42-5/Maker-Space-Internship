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

bool game_start = false;
int colors[] = {red_led, yellow_led, green_led, blue_led};
int inputs[] = {red_button, yellow_button, green_led, blue_led};

int level = 1;
int index = 0;
int color_to_add = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(reset_button, INPUT);
  pinMode(red_button, INPUT);
  pinMode(yellow_button, INPUT);
  pinMode(green_button, INPUT);
  pinMode(blue_button, INPUT);

  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(blue_led, OUTPUT);

  digitalWrite(red_led, LOW);
  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(red_led, LOW);
  
}
void loop() {
  int reset_count = 0;
  int reset_button_state = digitalRead(reset_button);
  // put your main code here, to run repeatedly:
  int input_sequence[level];
  int current_sequence[level];

  if(reset_button_state == HIGH && reset_count == 0){
    reset_count++;
    game_start = true;
  }
  if(reset_button_state == HIGH && reset_count == 1){
    game_start = false;
  }
  if(game_start){
    int red_button_state = digitalRead(red_button);
    int yellow_button_state = digitalRead(yellow_button);
    int green_button_state = digitalRead(green_button);
    int blue_button_state = digitalRead(blue_button);

    for(int i = 0; i < level; i++){
      index = random(0, color_count - 1);
      color_to_add = colors[index];
      digitalWrite(color_to_add, HIGH);
      digitalWrite(color_to_add, LOW);
      delay(200);
      current_sequence[i] = color_to_add;
    }
    delay(1000);
    for(int i = 0; i < level; i++){
      if(red_button_state == HIGH){
        input_sequence[i] == red_led;
        digitalWrite(red_led, HIGH);
        digitalWrite(red_led, LOW);
      } else if(yellow_button_state == HIGH){
        input_sequence[i] == yellow_led;
        digitalWrite(yellow_led, HIGH);
        digitalWrite(yellow_led, LOW);
      } else if(green_button_state == HIGH){
        input_sequence[i] == green_led;
        digitalWrite(green_led, HIGH);
        digitalWrite(green_led, LOW);
      } else if(red_button_state == HIGH){
        input_sequence[i] == blue_led;
        digitalWrite(blue_led, HIGH);
        digitalWrite(blue_led, LOW);
      } 
    }
    int input_sequence_length = sizeof(input_sequence) / sizeof(input_sequence[0]);
    int current_sequence_length = sizeof(current_sequence) / sizeof(current_sequence[0]);
    int correct_count = 0;
    for(int i = 0; i < input_sequence_length; i++){
      if(input_sequence[i] == current_sequence[i]){
        correct_count++;
      }
    }
    if(correct_count != current_sequence_length){
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
    }
    else if(correct_count == current_sequence_length){
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
    }

  }

}
