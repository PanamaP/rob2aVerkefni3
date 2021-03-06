#pragma config(Sensor, in2,    lightSensor,    sensorReflection)
#pragma config(Sensor, dgtl1,  stopButton,     sensorTouch)
#pragma config(Sensor, dgtl7,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl11, sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393, openLoop)

//*!!Code for your robot to never bump into things, also makes the robot stop when the light is turned off.             !!*//

int BASEDIST = 564;
float BASEDEG = 1;
int power = 80;


void stopMotors(){
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void turn(int deg, int beyga){
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;

	if(beyga == 1){
		while(abs(SensorValue[rightEncoder]) < deg * BASEDEG){
			motor[leftMotor] = power * beyga;
			motor[rightMotor] = power * beyga;
		}
	}
	else{
		while(abs(SensorValue[rightEncoder]) < deg * BASEDEG){
			motor[leftMotor] = power * beyga;
			motor[rightMotor] = power * beyga;
		}
	}
}


void drive(int way){
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	motor[rightMotor] = -power*way;
	motor[leftMotor] = power*way;
}

task stopMyTask(){
	while(SensorValue[stopButton] == 0 && vexRT[Btn8R]==0){
	}
	StopAllTasks();
}


task battery()
{
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery, backupBattery;

	while(true)														// An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		displayLCDString(1, 0, "Backup: ");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
		displayNextLCDString(backupBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}







task main()
{
	StartTask(stopMyTask);
	StartTask(battery);

	while(true){
		if(SensorValue(lightSensor) > 700){
			stopMotors();
			}
		if(SensorValue(lightSensor) <= 700 && SensorValue(sonarSensor) > 65){
				drive(1);
			}
			if(SensorValue(sonarSensor) < 65 && SensorValue(lightSensor) <= 700){
				stopMotors();
				wait1Msec(500);
				turn(90,1);
			}
}
}
