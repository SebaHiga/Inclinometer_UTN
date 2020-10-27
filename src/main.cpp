#include <main.hpp>

void setup() {
	Serial.begin(115200);
	
	create_semaphores();

	xTaskCreate(TaskAccel,
				"Accel",
				128,
				NULL, 
				1,
				NULL );

	xTaskCreate(MPU6050::task_read,
				"Read Accel",
				256,
				NULL, 
				0,
				NULL );

	// xTaskCreate(TaskButtons,
	// 			"Buttons",
	// 			86,
	// 			NULL, 
	// 			3,
	// 			NULL );

	xTaskCreate(TaskLCD,
				"LCD",
				86,
				NULL, 
				2,
				NULL );
}

void loop() {
	delay(1000);
}