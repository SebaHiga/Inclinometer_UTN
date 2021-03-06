#include <main.hpp>
#include <Inclinometer.hpp>
#include <global.hpp>

void setup() {
	Serial.begin(115200);

	Global::mutex_angle = xSemaphoreCreateMutex();
	xSemaphoreGive(Global::mutex_angle);
	
	lcd.begin();
	
	mpu.begin();

	xTaskCreate(Inclinometer::run,
				"Accel",
				120,
				NULL, 
				0,
				NULL );

	xTaskCreate(TaskButtons,
				"Buttons",
				86,
				NULL, 
				10,
				NULL );

	xTaskCreate(MPU6050::task_read,
				"Read Accel",
				160,
				NULL, 
				1,
				NULL );

	// xTaskCreate(TaskLCD,
	// 			"LCD",
	// 			128,
	// 			NULL, 
	// 			3,
	// 			NULL );
}

void loop() {
	TaskLCD();
	// vTaskDelay(500/portTICK_PERIOD_MS);
	delay(1000);
}