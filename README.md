# Project: Smart Private Vehicle Parking System

#### **Objective:** Design a secure and user-friendly parking system for a private garage or company parking lot.

#### **Project Overview**

* This project describes a smart private vehicle parking system designed to manage entry and exit of vehicles in a private parking lot.  The system utilizes two gates, an entry and exit gate, to control access.

* This is mostly an interrupt driven system to avoid halting the CPU in in just one process for the system to feel more responsive.

* The system was modeled using a finite state machine approach to make it easier to design and implement the system.

* The project was implemented using the Agile scurm model to help break the system into small tasks and prioritize them to be executed in the right order, Using this methodology was very helpful in implementing such a big project.
## **System Components:**

* **Three Microcontroller Units (ECUs):**
    1. **Entrance Gate ECU (ECU1):**
        * Manages the entry gate operations.
        * Components:
            * Servo motor for gate control
            * RFID reader for driver identification (UART communication)
            * Buzzer for audio feedback
            * LEDs (green/red) for visual feedback
            * LCD for displaying messages to drivers
    2. **Admin Dashboard ECU (ECU2):**
        * Provides administrative control.
        * Authorize the IDs of the drivers wanting to enter or exit the garage.
        * Components:
            * LCD and keypad for user interface
            * Seven-segment display to show available parking slots
    3. **Exit Gate ECU (ECU3):**
        * Manages the exit gate operations.
        * Functionality similar to Entrance Gate ECU.

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

2. **Driver Exit:**
    * Driver arrives at the exit gate.
    * Similar process as driver entry:
        * Driver taps their ID.
        * ECU3 reads the ID and transmits it to ECU2.
        * ECU2 validates the ID and checks if the driver is exiting.
    * Based on the validation:
        * **Valid exit:**
            * ECU2 sends a confirmation signal to ECU3.
            * ECU3 opens the gate.
            * Green LED illuminates and buzzer sounds (optional).
            * Available parking slot count in ECU2 is potentially incremented.
        * **Invalid exit or entry attempt:**
            * Process similar to invalid ID scenario at the entrance.

3. **Admin Dashboard:**
    * Authorize the IDs of the drivers wanting to enter or exit the garage.
    * Authorized personnel can:
        * Add new authorized IDs to the system.
        * Remove existing IDs from the system.
        * View a list of all authorized IDs.

## **Communication:**

* SPI for communication between ECUs, I created my own acknowledgment system to make sure that the data was received correctly and wasn't lost.
* UART for communication between RFID reader and each gate ECU.

## **Additional Considerations:**

* Password protection for the admin dashboard.
* Error handling and system monitoring.
* Potential integration with additional sensors (e.g., ultrasonic sensors) for improved gate control.

## System Design

## Requirements Diagram
![Requirements_Diagram](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/add96337-5974-4d9c-b41e-f24f549cd37c)



## Project Management Approach

**Methodology:** Agile Scrum

**Tool:** Jira Software

### Overview:

Our project was managed using the Agile Scrum methodology, which emphasizes iterative development, collaboration, and continuous improvement. I utilized Jira Software as our primary project management tool to streamline our Agile processes and ensure efficient communication and task tracking throughout the development lifecycle.

### Agile Scrum Principles Implemented:

1. **Iterative Development:** I divided the project into smaller, manageable tasks or user stories, which were prioritized and completed in short iterations called sprints.

2. **Flexibility and Adaptability:** Agile Scrum allowed me to respond quickly to changes in requirements while developing, ensuring that I was able to  delivere a product that met evolving needs.


### Jira Software Integration:

Jira Software served as the central hub for our Agile project management efforts. We utilized its features to:
- Create and manage user stories, epics, and tasks.
- Prioritize  tasks.
- Track progress and monitor sprint velocity.
- Generate reports and metrics to assess project performance and identify areas for optimization.

By leveraging Jira Software in conjunction with Agile Scrum practices, I was able to effectively plan, execute, and deliver me project in a timely and efficient manner.

![Jira-Timeline](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/2827ea6f-d0d6-4636-b80c-6247f1bfcc95)


[Jira_Project](https://hossameid.atlassian.net/jira/software/projects/PPST/boards/2/timeline?shared=&atlOrigin=eyJpIjoiOGI0YzZmYTMwMmYzNGYyMTk0M2Q2N2M2NmQ1YTJiMDQiLCJwIjoiaiJ9)

## System Paritioning
![System_Partioning](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/19d9811d-15ef-417d-8547-4fa300441359)



## System Block Diagram
![Block_Diagram](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/80fa267f-b0c8-4019-958e-db9baa98644d)


## System Testing
[Main_ECU_Testing](https://github.com/eidHossam/Private_Vehicle_Parking/tree/master/Main_Control_ECU/TestCases)

[Gate_ECUs_Testing](https://github.com/eidHossam/Private_Vehicle_Parking/tree/master/Entrance_Gate_ECU/TestCases)

# 
**Overall, this project outlines a well-structured design for a smart private vehicle parking system. The modular design with separate ECUs and clear communication protocols facilitates development and maintenance.**
