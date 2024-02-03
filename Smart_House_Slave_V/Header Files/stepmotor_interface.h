/*
 * stepmotor_interface.h
 *
 *  Created on: Aug 7, 2023
 *      Author: SOFT ZONE
 */

#ifndef STEPMOTOR_INTERFACE_H_
#define STEPMOTOR_INTERFACE_H_

#define FULL_STEP   0.7

void STEPMOTOR_angleRotation(u16 angle);
void STEPMOTOR_oneStepRotationACW(void);
void STEPMOTOR_oneStepRotation(void);
void STEPMOTOR_Stop(void);


#endif /* STEPMOTOR_INTERFACE_H_ */
