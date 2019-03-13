/* Utilizamos comunicación SPI para la SD card */
#define  FATFS_USE_SPI                0
#include "defines.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_fatfs.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    //FatFs object
    FATFS FatFs;
    //File object
    FIL fil;
    //espacio total y libre
    uint32_t total, free;

    //Inicializar el sistema
    SystemInit();
    //Inicializar delays
    TM_DELAY_Init();
    //Inicializar LEDs
    TM_DISCO_LedInit();

    //Montar la unidad
    if (f_mount(&FatFs, "", 1) == FR_OK) {
        //Montaje exitoso, se prende el LED ORANGE
        TM_DISCO_LedOn(LED_RED);

        //Se intenta abrir un archivo denominado como 'SD card data logger'
        if (f_open(&fil, "SD card data logger.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
            //Archivo abierto, se apaga el LED NARANJO y se prende el LED AZUL
            TM_DISCO_LedOn(LED_GREEN);
            TM_DISCO_LedOff(LED_RED);

            //Si ponemos más de 0 caracteres (everything OK)
            if (f_puts("First string in my file\n", &fil) > 0) {
                if (TM_FATFS_DriveSize(&total, &free) == FR_OK) {
                    //Data for drive size are valid
                }

                //Prender todos los LEDs
                TM_DISCO_LedOn(LED_RED|LED_GREEN);
            }

            //Cerrar el archivo 'SD card data logger'
            f_close(&fil);
        }

        //Desmontar la unidad
        f_mount(0, "", 1);
    }

    while (1) {

    }
}
