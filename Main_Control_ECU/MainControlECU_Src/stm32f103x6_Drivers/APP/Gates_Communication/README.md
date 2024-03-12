## Overview

The `Gates_Communication` module serves as a bridge between entrance and exit gates and an admin interface responsible for 
authenticating IDs. It manages communication protocols with gate ECUs, processes gate requests, and coordinates ID
authentication with the admin interface.

## Flow Chart
![Gates_Communication](https://github.com/eidHossam/Private_Vehicle_Parking/assets/106603484/c2011016-bad7-442d-b4f5-b65c001f3f5e)



## Flow Description

1. **Initialization**: 
   - The module initializes SPI interfaces for communication with gate ECUs (`SPI_Init`).
   - EXTI interrupts are set up to handle gate signals (`EXTI_Init`).
   - A FIFO buffer is initialized to store gate requests (`FIFOBuff_Init`).
   - Initial state is set to check pending requests (`st_GatesComm_Init`).

2. **Checking Pending Requests**:
   - The module continuously checks for pending requests in the FIFO buffer (`st_GatesComm_CheckPendingRequests`).
   - If requests are present, they are dequeued and processed.

3. **Request Processing**:
   - Upon receiving a request from a gate, the module sends the corresponding ID to the admin interface for authentication (`AI_GC_SendIDForAuthentication`).
   - State transitions to authentication process.

4. **ID Authentication**:
   - Upon receiving authentication results from the admin interface, the module sends approval or disapproval signals to the respective gate ECU.
   - The number of available slots in the garage is updated accordingly.

5. **ID Approved Signal**:
   - If the ID is approved, the module sends an approval signal to the gate ECU (`st_GatesComm_SendIDApprovedSignal`).
   - The number of available slots in the garage is decremented (for entrance gate).

6. **ID Disapproved Signal**:
   - If the ID is disapproved, the module sends a disapproval signal to the gate ECU (`st_GatesComm_SendIDDisapprovedSignal`).
