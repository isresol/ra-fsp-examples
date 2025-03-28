/***********************************************************************************************************************
 * File Name    : source_cancel_lpm.h
 * Description  : Contains macros, data structures and functions used in source_cancel_lpm.c
***********************************************************************************************************************/
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020-2025 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

#ifndef SOURCE_CANCEL_LPM_H_
#define SOURCE_CANCEL_LPM_H_

#include "common_utils.h"

/**********************************************************************************************************************
* Macro definitions
**********************************************************************************************************************/
/* Macro for check DTC transfer */
#define DTC_DATA_RESET                           (0x0000)
#define DTC_DATA_VALUE                           (0xAAAA)

/**********************************************************************************************************************
* External variables
**********************************************************************************************************************/


/**********************************************************************************************************************
* Public functions declarations
**********************************************************************************************************************/
/**********************************************************************************************************************
 * Function Name: source_cancel_lpm_init
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
fsp_err_t source_cancel_lpm_init (void);

/**********************************************************************************************************************
 * Function Name: source_cancel_lpm_enable
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
fsp_err_t source_cancel_lpm_enable (void);

/**********************************************************************************************************************
 * Function Name: source_cancel_lpm_disable
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
fsp_err_t source_cancel_lpm_disable (void);

/**********************************************************************************************************************
 * Function Name: source_cancel_snooze_enable
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
fsp_err_t source_cancel_snooze_enable (void);

/**********************************************************************************************************************
 * Function Name: source_cancel_snooze_disable
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
fsp_err_t source_cancel_snooze_disable (void);

/**********************************************************************************************************************
 * Function Name: source_cancel_lpm_deinit
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
void source_cancel_lpm_deinit (void);


/**********************************************************************************************************************
 * Function Name: source_cancel_lpm_flag_clear
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
void source_cancel_lpm_flag_clear (void);

/**********************************************************************************************************************
 * Function Name: source_internal_reset_handle
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
void source_internal_reset_handle (void);

#endif /* SOURCE_CANCEL_LPM_H_ */
