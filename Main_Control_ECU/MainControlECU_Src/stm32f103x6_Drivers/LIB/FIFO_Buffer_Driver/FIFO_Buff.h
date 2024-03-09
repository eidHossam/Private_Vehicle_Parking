/**
 * @file FIFO_Buff.h
 * 
 * @brief this file implements the header for FIFO driver
 * (Queue) 
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 29-07-2023
 * 
 * @version 1.0
 */

#ifndef FIFO_BUFF_H
#define FIFO_BUFF_H

#include "Platform_Types.h"
#include "../APP/Interface.h"

/****************************************************************/
/*
*===============================================
* User type definitions (structures)
*===============================================
*/

typedef struct{
    uint8 GateAddress;                          /**!<Holds the address of the gate requestion attention>*/
    uint8 szDriverID[AUTHORIZED_ID_SIZE + 1];   /**!<Holds the address of the driver ID to be processed>*/
}sGateRequestInfo_t;


/*Choosing the element width*/
#define element_width sGateRequestInfo_t

/*Template for the FIFO buffer*/
typedef struct {
    element_width* base;
    element_width* head;
    element_width* tail;
    uint32 capacity;
    uint32 size;
}sFIFO_Buf_t;

typedef enum {
    FIFO_full,
    FIFO_empty,
    FIFO_no_error,
    FIFO_NULL
}eFIFO_status_t;

/**************************************************************************************************************************
===============================================
*       API Supported by "FIFO_BUFF"
*===============================================
*/

/**
 * @brief This function initializes the FIFO structure before it can be used.
 * 
 * @param fifo_buf : Pointer to an instance of the FIFO structure.
 * @param buf      : An array of the element to be stored in the FIFO buffer.
 * @param capacity : The max number of elements allowed in the buffer.
 * @return eFIFO_status_t: FIFO_no_error on success, FIFO_NULL if buf is NULL.
 */
eFIFO_status_t FIFO_init(sFIFO_Buf_t* fifo_buf, element_width* buf, uint32 capacity);

/**
 * @brief This function adds an item to the end of the FIFO buffer.
 * 
 * @param fifo_buf : The instance of the FIFO buffer to add the element to.
 * @param item     : The item to be added to the FIFO buffer.
 * @return eFIFO_status_t : FIFO_no_error on success
 *                          FIFO_NULL if the FIFO buffer is invalid
 *                          FIFO_full if the buffer is already full.
 */
eFIFO_status_t FIFO_enqueue(sFIFO_Buf_t* fifo_buf, element_width item);

/**
 * @brief This function removes an item from the head or begining of the buffer.
 * 
 * @param fifo_buf : The instance of the FIFO buffer to remove the element from.
 * @param item     : The removed item will be stored in this parameter.
 * @return eFIFO_status_t : FIFO_no_error on success
 *                          FIFO_NULL if the FIFO buffer is invalid
 *                          FIFO_empty if the buffer is already empty.    
 */
eFIFO_status_t FIFO_dequeue(sFIFO_Buf_t* fifo_buf, element_width* item);

#endif