#include <main.hpp>

void setup() {
	Serial.begin(115200);
	
	create_semaphores();

	xTaskCreate(TaskAccel,
				"Accel",
				256,
				NULL, 
				1,
				NULL );

	xTaskCreate(TaskButtons,
				"Buttons",
				256,
				NULL, 
				2,
				NULL );
}

void loop() {
	delay(1000);
}