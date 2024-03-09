/**
 * @file FIFO_Buff.c
 * 
 * @brief this file implements the FIFO interface
 * 
 * @author Hossam_Eid (eidhossam7@gmail.com)
 * 
 * @date 29-07-2023
 * 
 * @version 1.0
 */

#include "FIFO_Buff.h"

eFIFO_status_t FIFO_init(sFIFO_Buf_t* fifo_buf, element_width* buf, uint32 capacity)
{
    /*Check if the buffer is valid*/
    if (!buf)
        return FIFO_NULL;
    
    /*Initialize the FIFO buffer*/
    fifo_buf->base = buf;
    fifo_buf->head = buf;
    fifo_buf->tail = buf;
    fifo_buf->capacity = capacity;
    fifo_buf->size = 0;

    return FIFO_no_error;
}

eFIFO_status_t FIFO_enqueue(sFIFO_Buf_t* fifo_buf, element_width item)
{
    /*Check if the FIFO buffer is valid*/
    if (!fifo_buf || !fifo_buf->head || !fifo_buf->base || !fifo_buf->tail)
        return FIFO_NULL;
    
    /*Check if there is space left in the buffer*/
    if (fifo_buf->size >= fifo_buf->capacity)
        return FIFO_full;
    
    *(fifo_buf->head) = item;

    /*Check if the head is at the end of the buffer*/
    if (fifo_buf->head == (fifo_buf->base + (fifo_buf->capacity - 1) ))
        fifo_buf->head = fifo_buf->base;
    else
        fifo_buf->head++;
    
    fifo_buf->size++;

    return FIFO_no_error;
}

eFIFO_status_t FIFO_dequeue(sFIFO_Buf_t* fifo_buf, element_width* item)
{
    /*Check if the FIFO buffer is valid*/
    if (!fifo_buf || !fifo_buf->head || !fifo_buf->base || !fifo_buf->tail)
        return FIFO_NULL;
    
    /*Check if the buffer is empty*/
    if (fifo_buf->size == 0)
        return FIFO_empty;
    
    *item = *(fifo_buf->tail);

    /*Check if the tail is at the end of the buffer*/
    if (fifo_buf->tail == (fifo_buf->base + (fifo_buf->capacity - 1)))
        fifo_buf->tail = fifo_buf->base;
    else
        fifo_buf->tail++;

    fifo_buf->size--;

    return FIFO_no_error;
}