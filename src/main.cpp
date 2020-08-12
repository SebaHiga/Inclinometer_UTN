#include <main.hpp>



void setup() {
	Serial.begin(115200);
	
	xTaskCreate(TaskAccel,
				"Accel",
				256,
				NULL, 
				0,
				NULL );

}

void loop() {}