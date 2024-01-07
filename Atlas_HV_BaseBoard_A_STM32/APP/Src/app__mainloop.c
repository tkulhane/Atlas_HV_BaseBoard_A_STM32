/*
 * app__superloop.c
 *
 *  Created on: 12. 3. 2022
 *      Author: tomas
 */


#include "app__mainloop.h"
#include "app_leds.h"




void application_main()
{

		app_leds_init();

		ParamsDefaultValues();
		ParamsLoad();



	  //hand address for ADC data store
	  p_ADC_data[0] = &ChannelsStatus[0].voltage_measurement;
	  p_ADC_data[1] = &ChannelsStatus[1].voltage_measurement;
	  p_ADC_data[2] = &ChannelsStatus[2].voltage_measurement;
	  p_ADC_data[3] = &ChannelsStatus[0].current_measurement;
	  p_ADC_data[4] = &ChannelsStatus[1].current_measurement;
	  p_ADC_data[5] = &ChannelsStatus[2].current_measurement;

	  //hand address for error signals store
	  p_ERROR_data[0] = &ChannelsStatus[0].power_good;
	  p_ERROR_data[1] = &ChannelsStatus[1].power_good;
	  p_ERROR_data[2] = &ChannelsStatus[2].power_good;
	  p_ERROR_data[3] = &ChannelsStatus[0].over_current;
	  p_ERROR_data[4] = &ChannelsStatus[1].over_current;
	  p_ERROR_data[5] = &ChannelsStatus[2].over_current;

	  HAL_GPIO_WritePin(PWR_EN_GPIO_Port, PWR_EN_Pin, GPIO_PIN_SET);

	  HAL_GPIO_WritePin(W55_RST_GPIO_Port, W55_RST_Pin, GPIO_PIN_SET);
	  ETH_udp_Init();

	  __HAL_UART_ENABLE_IT(&huart2, UART_IT_ERR);
	  __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);//enable uart3 interupt

	  DAC_Init();
	  HAL_TIM_Base_Start_IT(&htim10); //start timer for ADC reading

	 // _EnableErrorExecute = false;
	  //_DisableSupplyInLostConnection = true;

	  //_ControlOutputWithChannelEnable = true;


	  Set_Voltage(0, minimum_voltage);
	  Set_Voltage(1, minimum_voltage);
	  Set_Voltage(2, minimum_voltage);

	  while(1)
	  {

		  app_leds_drive();

		  //ethernet
		  ETH_udp_Receive();

		  ErrorSignalTime();

		  //errors
		  if(_Found_Error && MainParams.sramOffset_EnableErrorExecute)
		  //if(_Found_Error)
		  {
			  ErrorExecute(0);
			  ErrorExecute(1);
			  ErrorExecute(2);

			  _Found_Error = false;
		  }

		  ChannelControl(0);
		  ChannelControl(1);
		  ChannelControl(2);



		  bool NewCommand_uart = ProcessCommunication_UART(); //load command from uart buffer

		  //process command from uart
		  if(NewCommand_uart)
		  {
			  //HAL_GPIO_WritePin(LED_green_GPIO_Port, LED_green_Pin, GPIO_PIN_SET);
			  ProcessCommand(_command_id);
			  //HAL_GPIO_WritePin(LED_green_GPIO_Port, LED_green_Pin, GPIO_PIN_RESET);
		  }


		  bool NewCommand_eth = ProcessCommunication_ETH(); //load command from ethernet buffer

		  //process command from ethernet
		  if(NewCommand_eth)
		  {
			  //HAL_GPIO_WritePin(LED_blue_GPIO_Port, LED_blue_Pin, GPIO_PIN_SET);
			  ProcessCommand(_command_id);
			  //HAL_GPIO_WritePin(LED_blue_GPIO_Port, LED_blue_Pin, GPIO_PIN_RESET);
		  }


		  //connection control
		  Communication_ConnectedTimer();
		  AppConnectedExecute(_AppConnected);



	  }
}
