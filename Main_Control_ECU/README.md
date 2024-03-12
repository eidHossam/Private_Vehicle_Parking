
## Admin Dashboard ECU (ECU2)

* Provides administrative control.
* Authorize the IDs of the drivers wanting to enter or exit the garage.
* Components:
	* LCD and keypad for user interface
	* Seven-segment display to show available parking slots
## **System Functionality:**
 * Authorize the IDs of the drivers wanting to enter or exit the garage.
 * Authorized personnel can:
   	* Add new authorized IDs to the system.
   		* Checks if we passed the maximum allowed number of authorized IDs.
   	 	* Checks if the ID already exists in the system and reject it if it does.	  	
	* Remove existing IDs from the system.
 		* Checks if the list is empty.
   		* Checks if you entered a non-existent ID.  
	* View a list of all authorized IDs.
          
## System Design
![image](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/a93d0f53-9f91-4301-8824-458d6cb28733)

## ECU Calls
![image](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/08f127dc-88ad-4dbd-af92-bf77334d7d3f)
