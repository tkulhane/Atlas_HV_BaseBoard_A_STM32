/*
 * app_communication.c
 *
 *  Created on: Feb 5, 2022
 *      Author: tomas
 */
#include "app_communication.h"
#include "app_params.h"

uint32_t ConnectedTimer;
bool _AppConnected;
int _command_id;
int _command_value;
float _float_command_value;
uint32_t _u32_command_value;
eCommand_Form _command_form;
eCommand_source _command_source;


//table of command string - corresponds with eCommand_Id enumeration
const char command_strings[][STRING_TABLE_SIZE] =
{
	"NON",
	"Connected",
	"ch1_enable",
	"ch2_enable",
	"ch3_enable",
    "ch1_output",
    "ch2_output",
    "ch3_output",
	"ch1_setvoltage",
	"ch2_setvoltage",
	"ch3_setvoltage",
	"ch1_polarity",
	"ch2_polarity",
	"ch3_polarity",
	"ch1_getvoltage",
	"ch2_getvoltage",
	"ch3_getvoltage",
	"ch1_getcurrent",
	"ch2_getcurrent",
	"ch3_getcurrent",
	"error_signals",
	"getallvalues",
	"getsetting",
	"thatsall",
	"LED",

	"ip_store_endpoint",

	"ip_store_mac",
	"ip_store_myip",
	"ip_store_mymask",
	"ip_store_mygatew",
	"cmd_ip_store_UdpRecvPort",

	"ip_get_mac",
	"ip_get_myip",
	"ip_get_mymask",
	"ip_get_mygatew",
	"cmd_ip_get_UdpRecvPort",

	"ip_getsetting",
	"adc_set_k0",
	"adc_set_k1",
	"adc_set_k2",
	"adc_set_k3",
	"adc_set_k4",
	"adc_set_k5",
	"adc_set_q0",
	"adc_set_q1",
	"adc_set_q2",
	"adc_set_q3",
	"adc_set_q4",
	"adc_set_q5",
	"adc_get_k0",
	"adc_get_k1",
	"adc_get_k2",
	"adc_get_k3",
	"adc_get_k4",
	"adc_get_k5",
	"adc_get_q0",
	"adc_get_q1",
	"adc_get_q2",
	"adc_get_q3",
	"adc_get_q4",
	"adc_get_q5",
	"dac_set_k0",
	"dac_set_k1",
	"dac_set_k2",
	"dac_set_q0",
	"dac_set_q1",
	"dac_set_q2",
	"dac_get_k0",
	"dac_get_k1",
	"dac_get_k2",
	"dac_get_q0",
	"dac_get_q1",
	"dac_get_q2",
	"adc_getallcoef",
	"dac_getallcoef",
	"ch1_setprereg",
	"ch2_setprereg",
	"ch3_setprereg",
	"ch1_setoutreg",
	"ch2_setoutreg",
	"ch3_setoutreg",

	"ch1_get_err_state",
	"ch2_get_err_state",
	"ch3_get_err_state",
	"errState_Get",

	"CfgSet_EnableErrorExecute",
	"CfgSet_DisableInConnLost",
	"CfgSet_CtrlOutWithChEnable",
	"CfgSet_ErrorExecuteAutoRestart",

	"CfgGet_EnableErrorExecute",
	"CfgGet_DisableInConnLost",
	"CfgGet_CtrlOutWithChEnable",
	"CfgGet_ErrorExecuteAutoRestart",

	"Cfg_Get",

	"params_store",
	"params_default",

	"ETH_ReInit",

	"reset"

};

//table of parse type for data convert
eCommand_parse Command_parse[] =
{
		cparse_non, //cmd_non
		cparse_int,	//cmd_Connected,
		cparse_int,	//cmd_enable_CH1,
		cparse_int,	//cmd_enable_CH2,
		cparse_int,	//cmd_enable_CH3,
		cparse_int,	//cmd_output_CH1,
		cparse_int,	//cmd_output_CH2,
		cparse_int,	//cmd_output_CH3,
		cparse_int,	//cmd_set_voltage_CH1,
		cparse_int,	//cmd_set_voltage_CH2,
		cparse_int,	//cmd_set_voltage_CH3,
		cparse_int,	//cmd_polarity_CH1,
		cparse_int,	//cmd_polarity_CH2,
		cparse_int,	//cmd_polarity_CH3,
		cparse_non,	//cmd_get_voltage_CH1,
		cparse_non,	//cmd_get_voltage_CH2,
		cparse_non,	//cmd_get_voltage_CH3,
		cparse_non,	//cmd_get_current_CH1,
		cparse_non,	//cmd_get_current_CH2,
		cparse_non,	//cmd_get_current_CH3,
		cparse_non,	//cmd_error_signals,
		cparse_non,	//cmd_getallvalues,
		cparse_non,	//cmd_getsetting,
		cparse_int,	//cmd_thats_all,
		cparse_int,	//cmd_LED,

		cparse_u32t, //cmd_ip_store_endpoint,

		cparse_u32t, //cmd_ip_store_mac
		cparse_u32t, //cmd_ip_store_myip,
		cparse_u32t, //cmd_ip_store_mymask,
		cparse_u32t, //cmd_ip_store_mygatew,
		cparse_u32t, //cmd_ip_store_UdpRecvPort

		cparse_non, //cmd_ip_get_mac
		cparse_non, //cmd_ip_get_myip,
		cparse_non, //cmd_ip_get_mymask,
		cparse_non, //cmd_ip_get_mygatew,
		cparse_non, //cmd_ip_get_UdpRecvPort

		cparse_non, //cmd_ip_getsetting,
		cparse_float, //cmd_adc_set_k0,
		cparse_float, //cmd_adc_set_k1,
		cparse_float, //cmd_adc_set_k2,
		cparse_float, //cmd_adc_set_k3,
		cparse_float, //cmd_adc_set_k4,
		cparse_float, //cmd_adc_set_k5,
		cparse_float, //cmd_adc_set_q0,
		cparse_float, //cmd_adc_set_q1,
		cparse_float, //cmd_adc_set_q2,
		cparse_float, //cmd_adc_set_q3,
		cparse_float, //cmd_adc_set_q4,
		cparse_float, //cmd_adc_set_q5,
		cparse_non, //cmd_adc_get_k0,
		cparse_non, //cmd_adc_get_k1,
		cparse_non, //cmd_adc_get_k2,
		cparse_non, //cmd_adc_get_k3,
		cparse_non, //cmd_adc_get_k4,
		cparse_non, //cmd_adc_get_k5,
		cparse_non, //cmd_adc_get_q0,
		cparse_non, //cmd_adc_get_q1,
		cparse_non, //cmd_adc_get_q2,
		cparse_non, //cmd_adc_get_q3,
		cparse_non, //cmd_adc_get_q4,
		cparse_non, //cmd_adc_get_q5,
		cparse_float, //cmd_dac_set_k0,
		cparse_float, //cmd_dac_set_k1,
		cparse_float, //cmd_dac_set_k2,
		cparse_float, //cmd_dac_set_q0,
		cparse_float, //cmd_dac_set_q1,
		cparse_float, //cmd_dac_set_q2,
		cparse_non, //cmd_dac_get_k0,
		cparse_non, //cmd_dac_get_k1,
		cparse_non, //cmd_dac_get_k2,
		cparse_non, //cmd_dac_get_q0,
		cparse_non, //cmd_dac_get_q1,
		cparse_non, //cmd_dac_get_q2,
		cparse_non, //cmd_adc_getallcoef,
		cparse_non, //cmd_dac_getallcoef,
		cparse_int,	//cmd_set_pre_reg_CH1,
		cparse_int,	//cmd_set_pre_reg_CH2,
		cparse_int,	//cmd_set_pre_reg_CH3,
		cparse_int,	//cmd_set_out_reg_CH1,
		cparse_int,	//cmd_set_out_reg_CH2,
		cparse_int,	//cmd_set_out_reg_CH3,

		cparse_non,//"ch1_get_err_state",
		cparse_non,//"ch2_get_err_state",
		cparse_non,//"ch3_get_err_state",
		cparse_non,//"errState_Get"


		cparse_int,//cmd_CfgSet_EnableErrorExecute,
		cparse_int,//cmd_CfgSet_DisableInConnLost,
		cparse_int,//cmd_CfgSet_CtrlOutWithChEnable,
		cparse_int,//cmd_CfgSet_ErrorExecuteAutoRestart

		cparse_non,//cmd_CfgGet_EnableErrorExecute
		cparse_non,//cmd_CfgGet_DisableInConnLost
		cparse_non,//cmd_CfgGet_CtrlOutWithChEnable
		cparse_non,//cmd_CfgGet_ErrorExecuteAutoRestart,

		cparse_non,//cmd_Cfg_Get,

		cparse_non,//cmd_params_store,
		cparse_non,//cmd_params_default,

		cparse_non,//cmd_Eth_ReInit

		cparse_int//cmd_reset


};

/* @brief execution of the processed command
 *
 * @param command_id -> number of data command
 * @param value -> value for control
 *
 */
void ProcessCommand(int command_id)
{
	switch(command_id)
	{
		case cmd_NON:

			break;
		case cmd_Connected:

			//if(_command_source == csource_ETH) ETH_udp_StoreEndpoint();
			Comunication_ResetConnectedTimer();
			SendCommunication(cmd_Connected,_command_value);
			break;

		case cmd_enable_CH1:
			Channel_Enable(0, _command_value);
			break;

		case cmd_enable_CH2:
			Channel_Enable(1, _command_value);
			break;

		case cmd_enable_CH3:
			Channel_Enable(2, _command_value);
			break;

		case cmd_output_CH1:
			Channel_Output(0, _command_value);
			break;

		case cmd_output_CH2:
			Channel_Output(1, _command_value);
			break;

		case cmd_output_CH3:
			Channel_Output(2, _command_value);
			break;

		case cmd_set_voltage_CH1:
			Set_Voltage(0, _command_value);
			break;

		case cmd_set_voltage_CH2:
			Set_Voltage(1, _command_value);
			break;

		case cmd_set_voltage_CH3:
			Set_Voltage(2, _command_value);
			break;

		case cmd_polarity_CH1:
			if(_command_value == 1)Channel_Polarity(0, polarity_positive);
			else if (_command_value == 2)Channel_Polarity(0, polarity_negative);
			break;

		case cmd_polarity_CH2:
			if(_command_value == 1)Channel_Polarity(1, polarity_positive);
			else if (_command_value == 2)Channel_Polarity(1, polarity_negative);
			break;

		case cmd_polarity_CH3:
			if(_command_value == 1)Channel_Polarity(2, polarity_positive);
			else if (_command_value == 2)Channel_Polarity(2, polarity_negative);
			break;

		case cmd_getsetting:
			Get_Setting();
			break;

		case cmd_LED:
			LedSwitch(_command_value);
			break;

		case cmd_getallvalues:
			Get_AllMeasurement();
			//ErrorWatching();
			break;

		case cmd_error_signals:
			Get_ErrorSignals();
			break;

		case cmd_ip_store_endpoint:
			ETH_udp_StoreEndpoint(_u32_command_value);
			break;

		case cmd_ip_store_mac:
			ETH_StoreMac(_u32_command_value);
			break;

		case cmd_ip_store_myip:
			ETH_StoreIP(_u32_command_value);
			break;

		case cmd_ip_store_mymask:
			ETH_StoreNETMASK(_u32_command_value);
			break;

		case cmd_ip_store_mygatew:
			ETH_StoreGATEWAY(_u32_command_value);
			break;

		case cmd_ip_store_UdpRecvPort:
			ETH_Store_UdpRecPort(_u32_command_value);
			break;

		case cmd_ip_getsetting:
			ETH_SendSetting();
			break;

		case cmd_adc_set_k0:
			StoreADCConstant(0, _float_command_value);
			break;

		case cmd_adc_set_k1:
			StoreADCConstant(1, _float_command_value);
			break;

		case cmd_adc_set_k2:
			StoreADCConstant(2, _float_command_value);
			break;

		case cmd_adc_set_k3:
			StoreADCConstant(3, _float_command_value);
			break;

		case cmd_adc_set_k4:
			StoreADCConstant(4, _float_command_value);
			break;

		case cmd_adc_set_k5:
			StoreADCConstant(5, _float_command_value);
			break;

		case cmd_adc_set_q0:
			StoreADCConstant(6, _float_command_value);
			break;

		case cmd_adc_set_q1:
			StoreADCConstant(7, _float_command_value);
			break;

		case cmd_adc_set_q2:
			StoreADCConstant(8, _float_command_value);
			break;

		case cmd_adc_set_q3:
			StoreADCConstant(9, _float_command_value);
			break;

		case cmd_adc_set_q4:
			StoreADCConstant(10, _float_command_value);
			break;

		case cmd_adc_set_q5:
			StoreADCConstant(11, _float_command_value);
			break;


		case cmd_dac_set_k0:
			StoreDACConstant(0, _float_command_value);
			break;

		case cmd_dac_set_k1:
			StoreDACConstant(1, _float_command_value);
			break;

		case cmd_dac_set_k2:
			StoreDACConstant(2, _float_command_value);
			break;

		case cmd_dac_set_q0:
			StoreDACConstant(3, _float_command_value);
			break;

		case cmd_dac_set_q1:
			StoreDACConstant(4, _float_command_value);
			break;

		case cmd_dac_set_q2:
			StoreDACConstant(5, _float_command_value);
			break;

		case cmd_adc_getallcoef:
			SendADCCoefficients();
			break;

		case cmd_dac_getallcoef:
			SendDACCoefficients();
			break;

		case cmd_set_pre_reg_CH1: //debug
			Set_PreReg_Voltage(0, _command_value);
			break;

		case cmd_set_pre_reg_CH2: //debug
			Set_PreReg_Voltage(1, _command_value);
			break;

		case cmd_set_pre_reg_CH3: //debug
			Set_PreReg_Voltage(2, _command_value);
			break;

		case cmd_set_out_reg_CH1: //debug
			Set_OutReg_Voltage(0, _command_value);
			break;

		case cmd_set_out_reg_CH2: //debug
			Set_OutReg_Voltage(1, _command_value);
			break;

		case cmd_set_out_reg_CH3: //debug
			Set_OutReg_Voltage(2, _command_value);
			break;

		case cmd_errState_Get:
			Get_State_err();
			break;

		case cmd_CfgSet_EnableErrorExecute:
			SetConfigData(0, _command_value);
			break;

		case cmd_CfgSet_DisableInConnLost:
			SetConfigData(1, _command_value);
			break;

		case cmd_CfgSet_CtrlOutWithChEnable:
			SetConfigData(2, _command_value);
			break;

		case cmd_CfgSet_ErrorExecuteAutoRestart:
			SetConfigData(3, _command_value);
			break;

		case cmd_Cfg_Get:
			SendConfigData();
			break;

		case cmd_params_store:
			ParamsStore();
			break;

		case cmd_params_default:
			RestoreParamsDefault();
			break;

		case cmd_reset:
			System_Reset();
			break;

		case cmd_Eth_ReInit:
			ETH_udp_Init();
			break;


		default:
			break;
	}
}


/* @brief return length of string by detection /0 on end
 *
 * @param s -> pointer on string
 *
 * @return length of string
 */
int get_string_length(const char *s)
{
    int len=0;
    while (s[len] != 0)
    {
        len++;
    }

    return len;
}

/* @brief compare of two strings (two array)
 *
 * @param one       -> pointer on first string
 * @param one_start -> start of comparing first string
 * @param one_stop  -> stop of comparing first string
 * @param two       -> pointer on first string
 * @param two_start -> start of comparing first string
 * @param two_stop  -> stop of comparing first string
 *
 * @return true -> string is equal
 * @retuen false -> string is not equal
 */
bool StringIsEqual(const uint8_t *one, int one_start, int one_end, const uint8_t *two,int two_start, int two_end)
{
	if(!((one_start >= 0) || (two_start >= 0) || (one_end >= 0) || (two_end >= 0))) return false; //start and stop must be equal or bigger than 0

	int one_length = one_end - one_start;
	int two_length = two_end - two_start;

	if(!((one_length > 0) || (two_length > 0))) return false; //length must be bigger than 0
	if(!(one_length == two_length)) return false; //length of one and two must be equal

	for(int i = 0;i < one_length; i++)
	{
		if(!(one[i] == two[i])) return false;
	}

	return true;
}

/* @brief find the character in string
 *
 * @param string    -> pointer on string
 * @param length    -> string length
 * @param character -> searched character
 *
 * @return position of searched character or -1 if character is not found
 */
int GetDelimiterPosition(const uint8_t *string, int length, uint8_t character)
{
	for(int i = 0;i<length; i++)
	{
		if(string[i] == character)
		{
			return i;
		}
	}

	return -1;
}

/* @brief process of command string, search command in table and process command value
 * 		  command format: command=value
 *
 * @param Buffer    -> pointer on processed buffer (command string)
 * @param length    -> processed buffer length
 *
 * @global var _command_id -> number of received command
 * @global var _command_value -> value of command data (after = )
 *
 * @return true -> correct processing
 * @return false -> wrong command
 */
bool ProcessLine(const uint8_t *Buffer, int legth)
{
	int delim_position = GetDelimiterPosition(Buffer,legth,(uint8_t)'='); //position of delimiter =
	if(delim_position == -1) return false; //delimiter not found

	_command_id  = -1;

	_command_value = 0;
	_float_command_value = 0;
	_u32_command_value = 0;

	if(Buffer[0] == '/') //string start with "/"...command is convert from number
	{
		uint8_t buffer_for_id[3] = {0}; //buffer for convert

		for(int i = 1; i<(delim_position); i++ )
		{
			if(i > 3) break;// i bigger then buffer_for_id
			char c = Buffer[i]; //take character from Buffer
			if(!(c >= '0' && c <= '9')) return false; //character is not number
			buffer_for_id[i-1] = c;

		}
			_command_form = cform_short;
			_command_id = atoi((char *)buffer_for_id); //convert string to int
	}

	else //command not start with "/"
	{
		//search equal string in command_string table
		for(int i = 0;i<(sizeof(command_strings)/STRING_TABLE_SIZE); i++)
		{
			if(StringIsEqual(Buffer, 0, delim_position, (uint8_t *)command_strings[i], 0, get_string_length(command_strings[i])))
			{
				_command_id  = i; //get command position
			}
		}
		_command_form = cform_full;
	}

	if(_command_id == -1) return false; //command not found

	if(Command_parse[_command_id] == cparse_non) return true; //non parsing


	uint8_t buffer_for_number[12] = {0}; //buffer for convert

	//take character to convert from Buffer
	for(int i = 0; i<(legth-delim_position-1); i++ )
	{
		if(i > 11) return false;// i bigger then buffer_for_int size
		char c = Buffer[delim_position+1+i]; //take character from Buffer
		if(!((c >= '0' && c <= '9') || c == '.')) return false; //character is not number
		buffer_for_number[i] = c;
	}

	//convert buffer to number according to Command_parse
	if(Command_parse[_command_id] == cparse_int)
	{
		_command_value = atoi((char *)buffer_for_number); //convert string to int
	}
	else if(Command_parse[_command_id] == cparse_float)
	{
		_float_command_value = atoff((char *)buffer_for_number); //convert string to float
	}
	else if(Command_parse[_command_id] == cparse_u32t)
	{
		_u32_command_value = (uint32_t)atoll((char *)buffer_for_number); //convert string to uint32_t
	}


	return true;
}


/* @brief take character from uart buffer and find the new line (\n or \r)
 * find new line -> call function ProcessLine
 *
 * @return true -> correct processing
 * @return false -> wrong command or not found new line
 */
bool ProcessCommunication_UART()
{
	if(!Uart_BufferNotEmpty()) return false;

	uint8_t line_buffer[128] = {0};
	uint8_t line_counter = 0;

	uint32_t timeout_timer = HAL_GetTick();

	while(true)
	{
		if((HAL_GetTick() - timeout_timer) >= 50) return false;
		if(!Uart_BufferNotEmpty()) continue;

		uint8_t data = Uart_ReadBuffer();

		if(data == '\n' || data == '\r')
		{
			if(line_counter == 0) return false;

			bool b = ProcessLine(line_buffer, line_counter);

			line_counter = 0;
			_command_source = csource_UART;
			return b;
		}
		else
		{
			line_buffer[line_counter] = data;
			line_counter++;
			if(line_counter > (sizeof(line_buffer)-1)) return false;
		}
	}
}

/* @brief take character from ethernet buffer and find the new line (\n or \r)
 * find new line -> call function ProcessLine
 *
 * @return true -> correct processing
 * @return false -> wrong command or not found new line
 */
bool ProcessCommunication_ETH()
{
	if(!ETH_BufferNotEmpty()) return false;

	uint8_t line_buffer[128] = {0};
	uint8_t line_counter = 0;

	uint32_t timeout_timer = HAL_GetTick();

	while(true)
	{
		if((HAL_GetTick()-timeout_timer) >= 50) return false;
		if(!ETH_BufferNotEmpty()) continue;

		uint8_t data = ETH_ReadBuffer();

		if(data == '\n' || data == '\r')
		{
			bool b = ProcessLine(line_buffer, line_counter);

			line_counter = 0;
			_command_source = csource_ETH;
			return b;
		}
		else
		{
			line_buffer[line_counter] = data;
			line_counter++;
			if(line_counter > (sizeof(line_buffer)-1)) return false;
		}
	}
}



/* @brief send data to uart or ethernet in format: command=value
 *
 * @param command_id -> number of data command
 * @param data -> data to be transmitted
 *
 */
void SendCommunication(eCommand_Id command_id, int data)
{
	char sprint_buffer[128];
	uint8_t size = 0;

	if(_command_form == cform_full)
	{
		size = sprintf(sprint_buffer,"%s=%d\r\n",command_strings[command_id],data);
	}
	else if(_command_form == cform_short)
	{
		size = sprintf(sprint_buffer,"/%d=%d\r\n",(int)command_id,data);
	}

	if(_command_source == csource_UART)
	{
		Uart_Send(sprint_buffer, size);
	}
	else if(_command_source == csource_ETH)
	{
		ETH_Send(sprint_buffer, size);
	}

}

/* @brief send data to uart or ethernet in format: command=value
 *
 * @param command_id -> number of data command
 * @param data -> data to be transmitted
 *
 */
void SendCommunication_float(eCommand_Id command_id, float data)
{
	char sprint_buffer[100];
	uint8_t size = 0;

	if(_command_form == cform_full)
	{
		size = sprintf(sprint_buffer,"%s=%f\r\n",command_strings[command_id],data);
	}
	else if(_command_form == cform_short)
	{
		size = sprintf(sprint_buffer,"/%d=%f\r\n",(int)command_id,data);
	}

	if(_command_source == csource_UART)
	{
		Uart_Send(sprint_buffer, size);
	}
	else if(_command_source == csource_ETH)
	{
		ETH_Send(sprint_buffer, size);
	}

}

/* @brief send data to uart or ethernet in format: command=value
 *
 * @param command_id -> number of data command
 * @param data -> data to be transmitted
 *
 */
void SendCommunication_u32(eCommand_Id command_id, uint32_t data)
{
	char sprint_buffer[100];
	uint8_t size = 0;

	if(_command_form == cform_full)
	{
		size = sprintf(sprint_buffer,"%s=%lu\r\n",command_strings[command_id],data);
	}
	else if(_command_form == cform_short)
	{
		size = sprintf(sprint_buffer,"/%d=%lu\r\n",(int)command_id,data);
	}

	if(_command_source == csource_UART)
	{
		Uart_Send(sprint_buffer, size);
	}
	else if(_command_source == csource_ETH)
	{
		ETH_Send(sprint_buffer, size);
	}

}


void Comunication_ResetConnectedTimer()
{
	ConnectedTimer = HAL_GetTick();
	_AppConnected = true;
}

void Communication_ConnectedTimer()
{

	  if((HAL_GetTick() - ConnectedTimer) > ConnectedTimer_Value)
	  {
		  _AppConnected = false;
	  }

}

