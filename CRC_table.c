#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define input_command_bit_1 1
#define input_command_bit_0 0

void print_CRC(uint8_t *CRC)
{
    uint16_t CRC_int = 0;
    for(int i = 0; i < 8; i ++)
        {
            CRC_int = CRC_int + (*(CRC+i) << i);
        }
        printf("0x%02X, ", CRC_int);
}

void CRC_calculator(int8_t input_command_bit)
{
    uint8_t CRC[8], CRC_old[8];
    uint16_t CRC_int;

    for(CRC_int = 0; CRC_int < 256; CRC_int++)
    {
        for(int i = 0; i < 8; i ++)
        {
            CRC[i] = (CRC_int & (1 << i)) >> i;
            CRC_old[i] = (CRC_int & (1 << i)) >> i; 
        }

        CRC[7] = CRC_old[6];
        CRC[6] = CRC_old[5];
        CRC[5] = CRC_old[7] ^ CRC_old[4];
        CRC[4] = CRC_old[3];
        CRC[3] = CRC_old[7] ^ CRC_old[2];
        CRC[2] = CRC_old[7] ^ CRC_old[1];
        CRC[1] = CRC_old[7] ^ CRC_old[0];
        CRC[0] = CRC_old[7] ^ input_command_bit;

        print_CRC(CRC);
        if((CRC_int + 1) % 8 == 0 && CRC_int != 0) printf("\n");
    }
}

int32_t main()
{
    CRC_calculator(input_command_bit_0);

    printf("\n\n");

    CRC_calculator(input_command_bit_1);

    while(1);

    return 0;
}