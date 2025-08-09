// GPS.c
#include "main.h"
#include "GPS.h"
#include <string.h>

extern UART_HandleTypeDef huart1;

char UART1_Read(void) {
    uint8_t c;
    HAL_UART_Receive(&huart1, &c, 1, HAL_MAX_DELAY);
    return (char)c;
}

uint8_t GPS_Read_Location(char *latitude, char *longitude) {
    char line[100];
    int i = 0;
    char c;

        c = UART1_Read();

        if (c == '$') {
            line[i++] = c;

            while (i < 99) {
                c = UART1_Read();
                line[i++] = c;
                if (c == '\n') break;
            }
            line[i] = '\0';

            if (strstr(line, "$GPRMC") != NULL) {
                char *token;
                int field = 0;
                token = strtok(line, ",");

                while (token != NULL) {
                    field++;
                    if (field == 4) {
                        strcpy(latitude, token);
                    } else if (field == 6) {
                        strcpy(longitude, token);
                        return 1;
                    }
                    token = strtok(NULL, ",");
                }
            }
            i = 0;
        }


    return 0;
}
