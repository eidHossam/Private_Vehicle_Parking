/**
 * @file Interface.h
 * 
 * @brief This file contains the incoming and outgoing signals between the different system modules.
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 11-03-2024
 * 
 * @version 1.0
 */


#ifndef INTERFACE_H_
#define INTERFACE_H_


/**
 * @brief This is an outgoing signal from the User_Admin_Interface module to the Gate_Controller module
 * to request it to open the gate.
 * 
 */
void UAI_GC_OpenGateReuest(void);

/**
 * @brief This is a signal from the Gate_Controller module to the User_Admin_Interface module to inform 
 * it that the car passed the gate and we are ready to serve the next driver.
 * 
 */
void GC_UAI_GateClosed(void);

#endif /* INTERFACE_H_ */