/**
 ******************************************************************************
 * @file    main.c
 * @author  Spark Application Team
 * @version V1.0.0
 * @date    13-March-2013
 * @brief   Main program body.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/__IO uint8_t WLAN_SMART_CONFIG_DONE;
__IO uint8_t WLAN_CONNECTED;
__IO uint8_t WLAN_DHCP;
__IO uint8_t WLAN_CAN_SHUTDOWN;

/* Extern variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : main.
 * Description    : main routine.
 * Input          : None.
 * Output         : None.
 * Return         : None.
 *******************************************************************************/
int main(void) {
	Set_System();

	//WLAN Test Code
	CC3000_SPI_Init();

	wlan_init(WLAN_Async_Callback, WLAN_Firmware_Patch, WLAN_Driver_Patch,
			WLAN_BootLoader_Patch, CC3000_Read_Interrupt_Pin,
			CC3000_Interrupt_Enable, CC3000_Interrupt_Disable,
			CC3000_Write_Enable_Pin);

	wlan_start(0);

	wlan_smart_config_start(1);

	/* Main loop */
	while (1) {

	}
}

/* WLAN Application related callbacks passed to wlan_init */
void WLAN_Async_Callback(long lEventType, char *data, unsigned char length) {
	switch (lEventType) {
	case HCI_EVNT_WLAN_ASYNC_SIMPLE_CONFIG_DONE:
		WLAN_SMART_CONFIG_DONE = 1;
		break;

	case HCI_EVNT_WLAN_UNSOL_CONNECT:
		WLAN_CONNECTED = 1;
		break;

	case HCI_EVNT_WLAN_UNSOL_DISCONNECT:
		WLAN_CONNECTED = 0;
		WLAN_DHCP = 0;
		break;

	case HCI_EVNT_WLAN_UNSOL_DHCP:
		WLAN_DHCP = 1;
		break;

	case HCI_EVENT_CC3000_CAN_SHUT_DOWN:
		WLAN_CAN_SHUTDOWN = 1;
		break;
	}
}

char *WLAN_Firmware_Patch(unsigned long *length) {
	*length = 0;
	return NULL;
}

char *WLAN_Driver_Patch(unsigned long *length) {
	*length = 0;
	return NULL;
}

char *WLAN_BootLoader_Patch(unsigned long *length) {
	*length = 0;
	return NULL;
}

#ifdef USE_FULL_ASSERT
/*******************************************************************************
 * Function Name  : assert_failed
 * Description    : Reports the name of the source file and the source line number
 *                  where the assert_param error has occurred.
 * Input          : - file: pointer to the source file name
 *                  - line: assert_param error line source number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{}
}
#endif