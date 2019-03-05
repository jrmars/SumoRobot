String a;
int myTimeout = 50;
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
	Serial.setTimeout(myTimeout);
	Serial.print("Arduino is ready \n");
	}

void loop() {

	while (Serial.available()) {

		a = Serial.readString();// read the incoming data as string

		Serial.println(a);
		float test = a.toFloat();
		int sending = test * 1000;
		Serial.write(sending);
		}
	}

