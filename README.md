# system-to-measure-the-distance-using-ultrasonic-sensor
system to measure the distance using ultrasonic sensor.
Mini Project 4
System Requirements
Implement the following system to measure the distance using ultrasonic sensor 
HC-SR04 with the specifications listed below:
1. Use ATmega32 Microcontroller with frequency 8Mhz.
2. Measure the distance using the Ultrasonic sensor HC-SR04. Check the “HC-SR04 Ultrasonic MT Student Tutorial” pdf file to understand how to interface with this sensor.
3. The LCD should display the distance value like that:
4. The project should be design and implemented based on the layered architecture model as follow:
GPIO Driver Requirements
      1. Use the Same GPIO driver implemented in the course.
ICU Driver Requirements
      1. Use the Same ICU driver implemented in the course.
      2. The ICU should be configured with frequency F_CPU/8 and to detect the raising edge as the first edge.
      3. ICU_init and ICU_setCallBack functions should be called inside the Ultrasonic_init
      function.
LCD Driver Requirements
      1. Use 4x16 LCD.
      2. Use the Same LCD driver implemented in the course with 8-bits data mode.
      3. Connect the LCD control pins and 8-bits data pins as follow:
              • RS → PB0
              • RW → Ground
              • E → PB1
              • Data Bus → all PORTA pins.
Ultrasonic Driver Requirements
      1. Implement a full ultrasonic Driver using ATmega32 ICU driver.
      2. The ultrasonic driver has 3 functions:
              a. void Ultrasonic_init(void)
              • Description
              ➢ Initialize the ICU driver as required.
              ➢ Setup the ICU call back function.
              ➢ Setup the direction for the trigger pin as output pin through the 
              GPIO driver.
                    • Inputs: None
                    • Return: None
              b. void Ultrasonic_Trigger(void)
                    • Description
              ➢ Send the Trigger pulse to the ultrasonic.
                    • Inputs: None
                    • Return: None
              c. uint16 Ultrasonic_readDistance(void)
                    • Description
            ➢ Send the trigger pulse by using Ultrasonic_Trigger function.
            ➢ Start the measurements by the ICU from this moment.
                    • Inputs: None
                    • Return: The measured distance in Centimeter.
            d. void Ultrasonic_edgeProcessing(void)
                    • Description
            ➢ This is the call back function called by the ICU driver.
            ➢ This is used to calculate the high time (pulse time) generated by 
            the ultrasonic sensor.
                    • Inputs: None
                    • Return: None
            The Project Hardware Connections
            Thanks and Good Luck
            Eng / Mohamed Tarek
