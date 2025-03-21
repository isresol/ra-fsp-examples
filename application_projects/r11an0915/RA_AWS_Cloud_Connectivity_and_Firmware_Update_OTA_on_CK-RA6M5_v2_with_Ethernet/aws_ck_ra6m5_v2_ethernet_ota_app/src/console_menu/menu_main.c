/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2023-2024 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : menu_main.c
 * Description  : The main menu controller.
 *********************************************************************************************************************/

#include "FreeRTOS.h"
#include "FreeRTOSconfig.h"
#include "semphr.h"
#include "queue.h"
#include "task.h"
#include "menu_main.h"
#include "common_utils.h"
#include "common_init.h"
#include "menu_main.h"
#include "console.h"
#include "menu_kis.h"

typedef struct menu_fn_tbl
{
    char_t * p_name; /*<! Name of Test */
    test_fn ( * p_func)(void); /*<! Pointer to Test Function */
} st_menu_fn_tbl_t;

int8_t g_selected_menu = 0;

extern bool_t g_receive;
static char_t s_print_buffer[BUFFER_LINE_LENGTH] = {};

/* Table of main menu functions */
static st_menu_fn_tbl_t s_menu_items[] =
{
    {"Get FSP version"               , get_version},
    {"Data flash"                    , data_flash_menu},
	{"Get UUID"                      , get_uuid},
	{"Start Application"             , start_app},
	{"Help"                          , help},
    {"", NULL }
};

/*********************************************************************************************************************
 * @brief   main_display_menu
 *
 * The main menu controller
 * @param       None
 * @retval      int8_t                 Return unsigned int
 *********************************************************************************************************************/
int8_t main_display_menu(void)
{
    int8_t key_pressed = -1;
    int8_t menu_limit = 0;

    sprintf (s_print_buffer, "%s%s", gp_clear_screen, gp_cursor_home);

    /* ignoring -Wpointer-sign is OK when treating signed char_t array as as unsigned */
    printf_colour((void*)s_print_buffer);

    sprintf (s_print_buffer, SUB_OPTIONS);

    /* ignoring -Wpointer-sign is OK when treating signed char_t array as as unsigned */
    printf_colour((void*)s_print_buffer);

    for (int8_t test_active = 0; NULL != s_menu_items[test_active].p_func; test_active++ )
    {
        sprintf (s_print_buffer, "\r\n %d. %s", (test_active + 1), s_menu_items[menu_limit++ ].p_name);

        /* ignoring -Wpointer-sign is OK when treating signed char_t array as as unsigned */
        printf_colour((void*)s_print_buffer);
    }
    printf_colour (MENU_MAIN_SELECT);
    printf_colour("\r\n");

    while ((0 != key_pressed))
    {
        /* Wait for input from console */
        key_pressed = wait_for_keypress ();
        if (0 != key_pressed)
        {
            /* Cast, as compiler will assume calc is int */
            key_pressed = (int8_t) (key_pressed - '0');
            g_selected_menu = key_pressed;

            if ((key_pressed > 0) && (key_pressed <= menu_limit))
            {
                s_menu_items[key_pressed - 1].p_func ();
                break;
            }
        }
        vTaskDelay(200);
    }

    /* Cast, as compiler will assume calc is int */
    return ((int8_t) (key_pressed - '0'));
}
/**********************************************************************************************************************
 End of function main_display_menu
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * @brief   application_counter function
 *
 * This function waits for xWaitTime second if it has not received any character from UART
 * @param[in]   xWaitTime   waiting time
 * @retval      pdTRUE      if it has not received any character from UART
 * @retval      pdFALSE     if it received any character from UART
 *********************************************************************************************************************/
bool_t application_counter(uint32_t xWaitTime)
{
    TickType_t xCurrent;
    TickType_t xStart;
    bool ret = pdTRUE;
    const TickType_t xPrintFrequency = pdMS_TO_TICKS( xWaitTime);
    xStart = xTaskGetTickCount();
    xCurrent = xTaskGetTickCount();
    g_receive = false;
    while( xCurrent - xStart < xPrintFrequency )
    {
        /* Waiting for receive a character from user_uart_callback */
        vTaskDelay(pdMS_TO_TICKS(1));
        if (g_receive == true)
        {
            ret = pdFALSE;
            break;
        }
        xCurrent = xTaskGetTickCount();
    }
    return ret;
}
