/*
 * Bit_Math.h
 *
 * Created: 8/28/2023 8:44:21 PM
 *  Author: Hossam Eid
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(reg, bitNum)            (reg |= (1 << bitNum))
#define SET_BITS(reg, bitNum, value)    (reg |= (value << bitNum))
#define CLEAR_BIT(reg, bitNum)          (reg &= ~(1 << bitNum))
#define CLEAR_BITS(reg, bitNum, value)  (reg &= ~(value << bitNum))
#define TOGGLE_BIT(reg, bitNum)         (reg ^= (1 << bitNum))
#define READ_BIT(reg, bitNum)           ((reg & (1 << bitNum)) >> bitNum)

#endif /* BIT_MATH_H_ */