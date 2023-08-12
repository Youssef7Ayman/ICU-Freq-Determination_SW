/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : EXTI DRIVER   *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman *************************************************************************************************************/
/************************************************* Date    : 27Aug20       *************************************************************************************************************/
/************************************************* Version : v1.0          *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/

# include "STD_TYPES.h"
# include "BIT_MATH.h"

# include "EXTI_interface.h"
# include "EXTI_private.h"
# include "EXTI_config.h"


/*Global pointer to function to hold INT ISR address*/

void (*EXTI_pvINT0Func)(void)=NULL;
void (*EXTI_pvINT1Func)(void)=NULL;
void (*EXTI_pvINT2Func)(void)=NULL;

/************************************************PRBUILLD CONFIGURATION************************************************************************************/
void EXTI_VidINT0Init (void)
{
	/*1- Check Sense control*/
	#if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

	#elif  INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

	#elif  INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
    SET_BIT(MCUCR,MCUCR_ISC01);

    #elif  INT0_SENSE == RISING_EDGE
    SET_BIT(MCUCR,MCUCR_ISC00);
    SET_BIT(MCUCR,MCUCR_ISC01);

	#else
	#error "Wrong INT0_SENSE configuration option"
	#endif

	/*2- Check peripheral interrupt enable initial state*/
	#if INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);

	#elif INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);

	#else
	#error "Wrong INT0_INITIAL_STATE configuration option"
	#endif
}

void EXTI_VidINT1Init (void)
{
	/*1- Check Sense control*/
	#if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

	#elif  INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

	#elif  INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

    #elif  INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

	#else
	#error "Wrong INT1_SENSE configuration option"
	#endif

	/*2- Check peripheral interrupt enable initial state*/
	#if INT1_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);

	#elif INT1_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);

	#else
	#error "Wrong INT1_INITIAL_STATE configuration option"
	#endif
}

void EXTI_VidINT2Init (void)
{
	/*1- Check Sense control*/
	#if  INT2_SENSE == FALLING_EDGE
    CLR_BIT(MCUCSR,MCUCSR_ISC2);

    #elif  INT2_SENSE == RISING_EDGE
    SET_BIT(MCUCSR,MCUCSR_ISC2);

	#else
	#error "Wrong INT2_SENSE configuration option"
	#endif

	/*2- Check peripheral interrupt enable initial state*/
	#if INT2_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);

	#elif INT2_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);

	#else
	#error "Wrong INT2_INITIAL_STATE configuration option"
	#endif
}

/************************************************POSTBUILLD CONFIGURATION************************************************************************************/
u8 EXTI_u8INT0SetSenseControl (u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8Sense)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR,MCUCR_ISC00);
	    CLR_BIT(MCUCR,MCUCR_ISC01);
	    break;
	case ON_CHANGE:
		SET_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);
	    break;
	case FALLING_EDGE:
		CLR_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);
	    break;
	case RISING_EDGE:
		SET_BIT(MCUCR,MCUCR_ISC00);
	    SET_BIT(MCUCR,MCUCR_ISC01);
	    break;
	default: Local_u8ErrorState=NOK;

	}

	return Local_u8ErrorState;
}

u8 EXTI_u8INT1SetSenseControl (u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8Sense)
	{
	case LOW_LEVEL:
		CLR_BIT(MCUCR,MCUCR_ISC10);
	    CLR_BIT(MCUCR,MCUCR_ISC11);
	    break;
	case ON_CHANGE:
		SET_BIT(MCUCR,MCUCR_ISC10);
		CLR_BIT(MCUCR,MCUCR_ISC11);
	    break;
	case FALLING_EDGE:
		CLR_BIT(MCUCR,MCUCR_ISC10);
		SET_BIT(MCUCR,MCUCR_ISC11);
	    break;
	case RISING_EDGE:
		SET_BIT(MCUCR,MCUCR_ISC10);
	    SET_BIT(MCUCR,MCUCR_ISC11);
	    break;
	default: Local_u8ErrorState=NOK;

	}

	return Local_u8ErrorState;
}

u8 EXTI_u8INT2SetSenseControl (u8 Copy_u8Sense)
{
	u8 Local_u8ErrorState=OK;
	switch(Copy_u8Sense)
	{
	case FALLING_EDGE:
	    CLR_BIT(MCUCSR,MCUCSR_ISC2);
	    break;
	case RISING_EDGE:
	    SET_BIT(MCUCSR,MCUCSR_ISC2);
	    break;
	default: Local_u8ErrorState=NOK;

	}

	return Local_u8ErrorState;
}

u8 EXTI_u8INTEnable (u8 Copy_u8INT)
{
	u8 Local_u8ErrorState=OK;
	switch (Copy_u8INT)
	{
	case INT0:
		SET_BIT(GICR,GICR_INT0);
		break;
	case INT1:
		SET_BIT(GICR,GICR_INT1);
		break;
	case INT2:
		SET_BIT(GICR,GICR_INT2);
		break;
	default: Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8INTDisable (u8 Copy_u8INT)
{
	u8 Local_u8ErrorState=OK;
	switch (Copy_u8INT)
	{
	case INT0:
		CLR_BIT(GICR,GICR_INT0);
		break;
	case INT1:
		CLR_BIT(GICR,GICR_INT1);
		break;
	case INT2:
		CLR_BIT(GICR,GICR_INT2);
		break;
	default: Local_u8ErrorState=NOK;
	}

	return Local_u8ErrorState;
}

u8 EXTI_u8INT0SetCAllBack (void (*Copy_pvINT0Func)(void))
{
	u8 Local_u8ErrorStatus=OK;
	if (Copy_pvINT0Func!=NULL)
	{
		EXTI_pvINT0Func=Copy_pvINT0Func;
	}
	else
	{
		Local_u8ErrorStatus=NULL_POINTER;
	}

	return Local_u8ErrorStatus;
}

u8 EXTI_u8INT1SetCAllBack (void (*Copy_pvINT1Func)(void))
{
	u8 Local_u8ErrorStatus=OK;
	if (Copy_pvINT1Func!=NULL)
	{
		EXTI_pvINT1Func=Copy_pvINT1Func;
	}
	else
	{
		Local_u8ErrorStatus=NULL_POINTER;
	}

	return Local_u8ErrorStatus;
}
u8 EXTI_u8INT2SetCAllBack (void (*Copy_pvINT2Func)(void))
{
	u8 Local_u8ErrorStatus=OK;
	if (Copy_pvINT2Func!=NULL)
	{
		EXTI_pvINT2Func=Copy_pvINT2Func;
	}
	else
	{
		Local_u8ErrorStatus=NULL_POINTER;
	}

	return Local_u8ErrorStatus;
}
/*ISR of INTO*/
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if (EXTI_pvINT0Func!=NULL)
	{
		EXTI_pvINT0Func();
	}
	else
	{
		/*Do Nothing*/
	}
}

/*ISR of INT1*/
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if (EXTI_pvINT1Func!=NULL)
	{
		EXTI_pvINT1Func();
	}
	else
	{
		/*Do Nothing*/
	}
}

/*ISR of INT2*/
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if (EXTI_pvINT2Func!=NULL)
	{
		EXTI_pvINT2Func();
	}
	else
	{
		/*Do Nothing*/
	}
}
