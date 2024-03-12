
## Entrance Gate ECU (ECU1
- Manages the entry gate operations.
 - Components:
	- Servo motor for gate control
	- RFID reader for driver identification (UART communication)
	- Buzzer for audio feedback
     - LEDs (green/red) for visual feedback
	- LCD for displaying messages to drivers

## **System Functionality:**

1. **Driver Entry:**
    * Driver arrives at the entrance.
    * ECU1 displays instructions on the LCD.
    * Driver taps their RFID card.
    * ECU1 reads the ID and transmits it to ECU2 via SPI.
    * ECU2:
        * Validates the ID against the authorized list.
        * Checks if the driver is attempting to enter or exit (based on additional logic).
    * Based on the validation:
        * **Valid ID:**
            * ECU2 sends a confirmation signal to ECU1.
            * ECU1 opens the gate using the servo motor.
            * Green LED illuminates (optional).
            * Available parking slot count in ECU2 is potentially decremented.
        * **Invalid ID:**
            * ECU2 sends a rejection signal to ECU1.
            * ECU1 displays an error message on the LCD.
            * Red LED illuminates and buzzer sounds (optional).
            * Gate remains closed.

## System Design
![image](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/622869c3-b8f3-4d20-9713-c37a0c20a9af)

### User Admin Interface
![User_Admin_Interface](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/00553f4d-f642-4eb9-8ecb-ff6ba4f84e23)

### Gate controller
![Gate_Controller](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/9ae2ca96-1c42-4131-af6b-d55dda8b732b)

## ECU Calls
![image](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/de216aee-16ee-4561-b9aa-2dcebe49cb8f)

![image](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/b1d112f2-23ae-44ef-ac1e-c4f1b38af953)

