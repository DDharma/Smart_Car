int data;
int DL1=D1;
int DL2=D2;
int DR1=D3;
int DR2=D4;

void setup() { 
  Serial.begin(9600); //initialize serial COM at 9600 baudrate
  pinMode(DL1, OUTPUT);
  pinMode(DL2, OUTPUT);
   pinMode(DR1, OUTPUT);
  pinMode(DR2, OUTPUT);//make the LED pin (13) as output
  digitalWrite (DL1, HIGH);
   digitalWrite (DL2, LOW);
   digitalWrite (DR1, HIGH);
   digitalWrite (DR2, LOW);
  Serial.println("Hi!, I am Arduino");
}
 
void loop() {
while (Serial.available()){
  data = Serial.read();
}

if (data == 'F'){
digitalWrite (DL1, HIGH);
digitalWrite (DL2,LOW);
digitalWrite (DR1, HIGH);
digitalWrite (DR2, LOW);
}
else if (data == 'R'){
digitalWrite (DL1, HIGH);
digitalWrite (DL2, LOW);
digitalWrite (DR1, LOW);
digitalWrite (DR2, HIGH);
}
else if (data == 'L'){
digitalWrite (DL1, LOW);
digitalWrite (DL2, HIGH);
digitalWrite (DR1, HIGH);
digitalWrite (DR2, LOW);
}
else if (data == 'S'){
digitalWrite (DL1, LOW);
digitalWrite (DL2, LOW);
digitalWrite (DR1, LOW);
digitalWrite (DR2, LOW);

}


else if (data == 'N'){
digitalWrite (DL1, HIGH);
digitalWrite (DL2, LOW);
digitalWrite (DR1, HIGH);
digitalWrite (DR2, LOW);

}
}
