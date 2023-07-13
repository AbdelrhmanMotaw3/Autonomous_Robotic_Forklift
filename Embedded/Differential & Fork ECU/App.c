/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  App.c
 *        \brief  Application Driver
 *
 *      \details  Source File For Application Driver
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Port.h"
#include "Dio.h"
#include "Gptm.h"
#include "IntCtrl.h"
#include "Adc.h"
#include "Uart.h"
#include "PID.h"
#include "PWM.h"
#include "Encoder.h"
#include "Differential.h"
/**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
float linear_Vel = 0.0;
float Angular_Vel = 0.0;
float SetPoint = 0.0;

extern float Right_Ticks ;
extern float Left_Ticks ;

extern char str[11];
extern char* data ;

static float num1 = 0.01 ;
static float num2 = 0.01;
extern float32 SetPoint_S;
float32  SetPoint_Steering;
extern float32 SetPoint_D;
float32 SetPoint_Diferential;
extern float32 Output_D ;
extern float32 Output_S ;
float32 Setring_Angle;

float Number_1_Encoder = 0.0;
extern int Check;
extern float Steering;

extern float Numbers_Recive[3];
float Numbers_Send[3];
float Numbers_Send_PID = 0.0;
extern int numCount ;
PID_Conroller* ptr=NULL_PTR;
float measurement=0.0;
float Steering_Encoder = 0.0 ;

char Stop ;
float32 SetPoint_D = 0;
float32 Output_D ;
float Size_FLoat_Differential;
int Size_Int_Differential ;

float Numbers_Send_tiva_1;

float Numbers_Send_esp_1;
float Numbers_Send_esp_2;

char sending_buffer_1[11] ;
char sending_buffer_2[6] ;
float32 SetPoint1=0.0;
float32 SetPoint2=0.0;
extern float velWheel;

float Cos_Values[361]={0.0, 0.008726535498374, 0.017452406437283, 0.026176948307873, 0.034899496702501, 0.043619387365336, 0.052335956242944, 0.061048539534857, 0.069756473744126, 0.078459095727845, 0.087155742747658, 0.095845752520224, 0.104528463267653, 0.113203213767907, 0.121869343405147, 0.130526192220052, 0.139173100960066, 0.147809411129611, 0.156434465040231, 0.165047605860678, 0.17364817766693, 0.182235525492147, 0.190808995376545, 0.199367934417197, 0.207911690817759, 0.216439613938103, 0.224951054343865, 0.233445363855905, 0.241921895599668, 0.250380004054441, 0.258819045102521, 0.267238376078257, 0.275637355816999, 0.284015344703922, 0.292371704722737, 0.300705799504273, 0.309016994374947, 0.317304656405092, 0.325568154457157, 0.333806859233771, 0.342020143325669, 0.350207381259467, 0.3583679495453, 0.366501226724297, 0.374606593415912, 0.38268343236509, 0.390731128489274, 0.398749068925246, 0.4067366430758, 0.414693242656239, 0.422618261740699, 0.430511096808295, 0.438371146789077, 0.446197813109809, 0.453990499739547, 0.461748613235034, 0.469471562785891, 0.477158760259608, 0.484809620246337, 0.492423560103467, 0.5, 0.507538362960704, 0.515038074910054, 0.522498564715949, 0.529919264233205, 0.537299608346824, 0.544639035015027, 0.551936985312058, 0.559192903470747, 0.566406236924833, 0.573576436351046, 0.58070295571094, 0.587785252292473, 0.594822786751341, 0.601815023152048, 0.608761429008721, 0.615661475325658, 0.62251463663762, 0.629320391049837, 0.636078220277764, 0.642787609686539, 0.649448048330184, 0.656059028990507, 0.662620048215737, 0.669130606358858,0.67559020761566, 0.681998360062498, 0.688354575693754, 0.694658370458997, 0.700909264299851, 0.707106781186548, 0.713250449154182, 0.719339800338651, 0.725374371012288, 0.731353701619171, 0.737277336810124, 0.743144825477394, 0.748955720789002, 0.754709580222772, 0.760405965600031, 0.766044443118978, 0.77162458338772, 0.777145961456971, 0.782608156852414, 0.788010753606722, 0.793353340291235, 0.798635510047293, 0.803856860617217, 0.809016994374947, 0.814115518356319, 0.819152044288992, 0.824126188622016, 0.829037572555042, 0.833885822067168, 0.838670567945424, 0.843391445812886, 0.848048096156426, 0.852640164354092, 0.857167300702112, 0.861629160441526, 0.866025403784439, 0.8703556959399, 0.874619707139396, 0.878817112661965, 0.882947592858927, 0.887010833178222, 0.891006524188368, 0.894934361602025, 0.898794046299167, 0.902585284349861, 0.90630778703665, 0.909961270876543, 0.913545457642601, 0.917060074385124, 0.92050485345244, 0.923879532511287, 0.927183854566787, 0.930417567982025, 0.933580426497202, 0.936672189248398, 0.939692620785908, 0.942641491092178, 0.945518575599317, 0.948323655206199, 0.951056516295153, 0.953716950748227, 0.956304755963035, 0.958819734868193, 0.961261695938319, 0.963630453208623, 0.965925826289068, 0.968147640378108, 0.970295726275996, 0.972369920397676, 0.974370064785235, 0.976296007119933, 0.978147600733806, 0.97992470462083, 0.981627183447664, 0.983254907563955, 0.984807753012208, 0.986285601537231, 0.987688340595138, 0.989015863361917, 0.99026806874157, 0.99144486137381, 0.992546151641322, 0.993571855676587, 0.994521895368273,0.995396198367179, 0.996194698091746, 0.996917333733128, 0.997564050259824, 0.998134798421867, 0.998629534754574, 0.999048221581858, 0.999390827019096, 0.999657324975557, 0.999847695156391, 0.999961923064171, 1,0.999961923064171, 0.999847695156391, 0.999657324975557, 0.999390827019096, 0.999048221581858, 0.998629534754574, 0.998134798421867, 0.997564050259824, 0.996917333733128, 0.996194698091746, 0.995396198367179, 0.994521895368273, 0.993571855676587, 0.992546151641322, 0.99144486137381, 0.99026806874157, 0.989015863361917, 0.987688340595138, 0.986285601537231, 0.984807753012208, 0.983254907563955, 0.981627183447664, 0.97992470462083, 0.978147600733806, 0.976296007119933, 0.974370064785235, 0.972369920397676, 0.970295726275996, 0.968147640378108, 0.965925826289068, 0.963630453208623, 0.961261695938319, 0.958819734868193, 0.956304755963035, 0.953716950748227, 0.951056516295153, 0.948323655206199, 0.945518575599317, 0.942641491092178, 0.939692620785908, 0.936672189248398, 0.933580426497202, 0.930417567982025, 0.927183854566787, 0.923879532511287, 0.92050485345244, 0.917060074385124, 0.913545457642601, 0.909961270876543, 0.90630778703665, 0.902585284349861, 0.898794046299167, 0.894934361602025, 0.891006524188368, 0.887010833178222, 0.882947592858927, 0.878817112661965, 0.874619707139396, 0.8703556959399, 0.866025403784439, 0.861629160441526, 0.857167300702112, 0.852640164354092, 0.848048096156426, 0.843391445812886, 0.838670567945424, 0.833885822067168, 0.829037572555042, 0.824126188622016, 0.819152044288992, 0.814115518356319, 0.809016994374947, 0.803856860617217, 0.798635510047293, 0.793353340291235, 0.788010753606722, 0.782608156852414, 0.777145961456971, 0.77162458338772, 0.766044443118978, 0.760405965600031, 0.754709580222772, 0.748955720789002, 0.743144825477394,0.737277336810124, 0.731353701619171, 0.725374371012288, 0.719339800338651, 0.713250449154182, 0.707106781186548, 0.700909264299851, 0.694658370458997, 0.688354575693754, 0.681998360062498, 0.67559020761566, 0.669130606358858, 0.662620048215737, 0.656059028990507, 0.649448048330184, 0.642787609686539, 0.636078220277764, 0.629320391049837, 0.62251463663762, 0.615661475325658, 0.608761429008721, 0.601815023152048, 0.594822786751341, 0.587785252292473, 0.58070295571094, 0.573576436351046, 0.566406236924833, 0.559192903470747, 0.551936985312058, 0.544639035015027, 0.537299608346824, 0.529919264233205, 0.522498564715949, 0.515038074910054, 0.507538362960704, 0.5, 0.492423560103467, 0.484809620246337, 0.477158760259608, 0.469471562785891, 0.461748613235034, 0.453990499739547, 0.446197813109809, 0.438371146789077, 0.430511096808295, 0.422618261740699, 0.414693242656239, 0.4067366430758, 0.398749068925246, 0.390731128489274, 0.38268343236509, 0.374606593415912, 0.366501226724297, 0.3583679495453, 0.350207381259467, 0.342020143325669, 0.333806859233771, 0.325568154457157, 0.317304656405092, 0.309016994374947, 0.300705799504273, 0.292371704722737, 0.284015344703922, 0.275637355816999, 0.267238376078257, 0.258819045102521, 0.250380004054441, 0.241921895599668, 0.233445363855905, 0.224951054343865, 0.216439613938103, 0.207911690817759, 0.199367934417197, 0.190808995376545, 0.182235525492147, 0.17364817766693, 0.165047605860678, 0.156434465040231, 0.147809411129611, 0.139173100960066, 0.130526192220052, 0.121869343405147, 0.113203213767907, 0.104528463267653, 0.095845752520224, 0.087155742747658, 0.078459095727845, 0.069756473744126, 0.061048539534857, 0.052335956242944, 0.043619387365336, 0.034899496702501, 0.026176948307873, 0.017452406437283, 0.008726535498374, 0.0};

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
 * \SyntaBluetooth_Value          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Init_Drivers (void)
{
    //Enable_Exceptions();
    Dio_Init(&Dio_Configuration);
    Port_Init(&Port_ConfigPtr);
    Uart_init(&Uart_ConfigPtr);
    Gpt_init(&Gpt_ConfigPtr);

//    Gpt_StartTimer (TIMER0_A,800);
//    Gpt_EnableNotification(TIMER0_A);

    Gpt_StartTimer (TIMER1_A,15999);
    Gpt_EnableNotification(TIMER1_A);

    ADC_InitChannel(&Adc_ConfigPtr);
    Pwm_Init(&Pwm_ConfigPtr);
    EncoderChannelA_Init (&Encoder_ConfigPtr1);
    EncoderChannelB_Init (&Encoder_ConfigPtr2);
    IntCtrl_init(&IntCtrl_ConfigPtr);

}

/******************************************************************************
 * \SyntaBluetooth_Value          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Timer0A_ISR()
{
    TICKS++;
}

/******************************************************************************
 * \SyntaBluetooth_Value          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/

void Delay(unsigned long counter)
{
    unsigned long i = 0;

    for(i=0; i< counter*1000; i++);
}
/******************************************************************************
 * \SyntaBluetooth_Value          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void Timer1A_ISR()
{
    TICKS1++;
}

/******************************************************************************
 * \SyntaBluetooth_Value          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
uint8 Time_Sec (LedSec sec)
{
    uint8 Time ;
    Time = sec ;
    return Time;
}

/******************************************************************************
 * \SyntaBluetooth_Value          : Std_ReturnType FunctionName(AnyType parameterName)
 * \Description     : Describe this service
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : parameterName   Parameter Describtion
 * \Parameters (out): None
 * \Return value:   : Std_ReturnType  E_OK
 *                                    E_NOT_OK
 *******************************************************************************/
void App_Start (void)
{

    PID_Conroller test1;
    test1.ki=0;
    test1.kp=600;
    test1.kd=0;

    test1.MaxLevel=1000;
    test1.Minlevel=-1000;
    test1.IntMaxLevel=700;
    test1.IntMinLevel=-700;
    test1.T=1;
    PID_Conroller* ptr=&test1;
    PID_init(ptr);


    while(1)
    {
//        Dio_WriteChannel(DioConf_ENCODER_VELOCITY_B_CHANNEL_ID_INDEX, STD_HIGH);

        /*
         *  receive from esp
         */
        uart_receive_string_esp(receive_buffer_1, value_string_1);
        linear_Vel= (Number_esp_1) - 0.01;
        SetPoint_S= (Number_esp_2)- 0.01;

        ///////////////////////////PID//////////////////////////////////
        SetPoint_D=linear_Vel +0.01;
        calc_vel_wheel();
//      measurement= velWheel;
        PID_Compute(ptr,SetPoint_D, velWheel);

        if (test1.Output>0.0)
        {
            set_DutyCycle( PWM0_PB5 , (test1.Output)/1000.0   ,DOWN_MODE);
            Dio_WriteChannel(DioConf_DIFFERENTIAL_INT1_CHANNEL_ID_INDEX, STD_HIGH);
            Dio_WriteChannel(DioConf_DIFFERENTIAL_INT2_CHANNEL_ID_INDEX, STD_LOW);
        }
        if (test1.Output<0.0)
        {
            set_DutyCycle( PWM0_PB5 , 1-(1-((test1.Output)/1000.0)) ,DOWN_MODE);
            Dio_WriteChannel(DioConf_DIFFERENTIAL_INT1_CHANNEL_ID_INDEX,STD_LOW );
            Dio_WriteChannel(DioConf_DIFFERENTIAL_INT2_CHANNEL_ID_INDEX, STD_HIGH);
        }
        if (test1.Output==0.0)
        {
            set_DutyCycle( PWM0_PB5 , Duty0 ,DOWN_MODE);
            Dio_WriteChannel(DioConf_DIFFERENTIAL_INT1_CHANNEL_ID_INDEX,STD_LOW );
            Dio_WriteChannel(DioConf_DIFFERENTIAL_INT2_CHANNEL_ID_INDEX, STD_LOW);
        }
    }
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
