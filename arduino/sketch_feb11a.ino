#include <Servo.h>

Servo servoLeft;
Servo servoRight;

bool computer = true;
bool sensors = false;

float ErrorIn = 0.00; // Error from sensors
float sensorLeft = 0;
float sensorRight = 0;
int motorStop = 1500; // Motor stop uS
int motorSpeed = 100; // Constant fwd speed
int errorMulti = 100; // Error multiplier
int speedLeft = motorStop + motorSpeed; // Left constant speed
int speedRight = motorStop - motorSpeed; // Right constant speed
String received;

char Buffer[32];
int myTimeout = 50;
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
	Serial.setTimeout(myTimeout);
	Serial.print("Arduino is ready \n");
	servoLeft.attach(6);
	servoRight.attach(9);
	}

void lineSensors() {
	pinMode(A1, OUTPUT); // Set sensor pins as output
	pinMode(A5, OUTPUT);
	digitalWrite(A1, HIGH); // Set sensor pins high
	digitalWrite(A5, HIGH);
	delay(1); // Charge capacitor
	pinMode(A1, INPUT); // Set sensor pins as input
	pinMode(A5, INPUT);
	delay(1); // Discharge capacitor
} 

void loop() {

	if(Serial.available() > 0) {

		received = Serial.readString();// read the incoming data as string
		if (computer == true) {
			ErrorIn = received.toFloat();
			servoLeft.writeMicroseconds(speedLeft + errorMulti * ErrorIn);
			servoRight.writeMicroseconds(speedRight + errorMulti * ErrorIn);
			strcpy(Buffer, "");
			dtostrf((ErrorIn), 2, 2, &Buffer[strlen(Buffer)]);
			strcat(Buffer, ">");
			Serial.write(Buffer);
			
		}		
	}
	if (sensors == true) {
		lineSensors();
		sensorLeft = digitalRead(A1); // Read sensor values (1,black 0,white)
	    sensorRight = digitalRead(A5);
		ErrorIn = sensorRight - sensorLeft;
		servoLeft.writeMicroseconds(speedLeft + errorMulti * ErrorIn);
		servoRight.writeMicroseconds(speedRight + errorMulti * ErrorIn);
	}
}

