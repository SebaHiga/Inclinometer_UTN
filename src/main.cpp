#include <main.hpp>

void setup() {
	Serial.begin(115200);
	
	create_semaphores();

	xTaskCreate(TaskAccel,
				"Accel",
				256,
				NULL, 
				0,
				NULL );

	xTaskCreate(TaskButtons,
				"Buttons",
				128,
				NULL, 
				3,
				NULL );

	xTaskCreate(TaskLCD,
				"LCD",
				128,
				NULL, 
				1,
				NULL );
}

void loop() {
	delay(1000);
}