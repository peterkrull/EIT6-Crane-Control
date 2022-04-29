

void setup() {
  // put your setup code here, to run once:
  Serial3.begin(115200);
  Serial.begin(115200);
  pinMode(50,OUTPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial3.parseFloat() > 1){
  digitalWrite(50, HIGH);
  }
}
