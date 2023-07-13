/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Common_Macros.h
 *       Module:  Common - Macros
 *
 *  Description:  Commonly Macros used      
 *  
 *********************************************************************************************************************/
#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define SET_BIT(REG,BIT)      (REG|=(1<<BIT))
#define CLEAR_BIT(REG,BIT)    (REG&=(~(1<<BIT)))
#define TOGGLE_BIT(REG,BIT)   (REG^=(1<<BIT))
#define ROR(REG,num)          ( REG = (REG>>num) | (REG << ((sizeof(REG) * 8)-num)) )
#define ROL(REG,num)          ( REG = (REG<<num) | (REG >> ((sizeof(REG) * 8)-num)) )
#define BIT_IS_SET(REG,BIT)   ( REG & (1<<BIT) )
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )
#define GET_BIT(REG,BIT)      ((REG >> BIT) & 1 )

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* COMMON_MACROS.H */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/
