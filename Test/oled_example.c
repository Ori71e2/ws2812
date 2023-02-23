
#include "OLED.h"
int oled_example(void) {
	OLED_Init();
	OLED_ShowNum(1, 1, ADC_SourceData[0], 5);
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "HelloWorld!");
	OLED_ShowNum(2, 1, 12345, 5);
	OLED_ShowSignedNum(2, 7, -66, 2);
	OLED_ShowHexNum(3, 1, 0xAA55, 4);
}