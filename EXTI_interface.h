/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : EXTI DRIVER   *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman *************************************************************************************************************/
/************************************************* Date    : 27Aug20       *************************************************************************************************************/
/************************************************* Version : v1.0          *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/


# ifndef EXTI_INTERFACE_H
# define EXTI_INTERFACE_H


#define LOW_LEVEL  			1
#define ON_CHANGE  			2
#define FALLING_EDGE  		3
#define RISING_EDGE  		4

#define INT0 				0
#define INT1 				1
#define INT2 				2

												/*	PREBUILD CONFIGURATION	*/

/* Description : A function to set the required SENSE_CONTROL & INITIAL_STATE of INT using Pretbuild configuration
 *  Input : Void  "Each Function Select the SENSE_CONTROL and INITIAL_STATE from CONFIG file for any INT"
 * Output : Void
 *  */
void EXTI_VidINT0Init (void);

void EXTI_VidINT1Init (void);

void EXTI_VidINT2Init (void);
											/**************************************/

												/*	POSTBUILD CONFIGURATION	*/

/* Description : A function to set the required SENSE_CONTROL of INT using Postbuild configuration
 *  Input : Copy_u8Sense , options are: 1- LOW_LEVEL    "Each Function Select the SENSE_CONTROL for any INT by passing it as an Input Arrgumnet"
 *	 	 	 	 	 	 	 	 	 	2- ON_CHANGE
 *	 	 	 	 	 	 	 	 	 	3- FALLING_EDGE
 *	 	 	 	 	 	 	 	 	 	4- RISING_EDGE
 * Output : Error status with type u8
 *  */
u8 EXTI_u8INT0SetSenseControl (u8 Copy_u8Sense);
u8 EXTI_u8INT1SetSenseControl (u8 Copy_u8Sense);
u8 EXTI_u8INT2SetSenseControl (u8 Copy_u8Sense);

/* Description : A function to set the required INITIAL_STATE of INT using Postbuild configuration
 *  Input : Copy_u8INT , options are: 1- LOW_LEVEL    "Each Function Select the INITIAL_STATE for any INT by passing it as an Input Arrgumnet"
 *	 	 	 	 	 	 	 	 	 	2- ON_CHANGE
 *	 	 	 	 	 	 	 	 	 	3- FALLING_EDGE
 *	 	 	 	 	 	 	 	 	 	4- RISING_EDGE
 * Output : Error status with type u8
 *  */
u8 EXTI_u8INTEnable (u8 Copy_u8INT);
u8 EXTI_u8INTDisable (u8 Copy_u8INT);












u8 EXTI_u8INT0SetCAllBack (void (*Copy_pvINT0Func)(void));
u8 EXTI_u8INT1SetCAllBack (void (*Copy_pvINT1Func)(void));
u8 EXTI_u8INT2SetCAllBack (void (*Copy_pvINT2Func)(void));



# endif
