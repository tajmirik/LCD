/* USER CODE BEGIN 4 */
void lcd_init(void)
{
	HAL_Delay(50);
	lcd_cmd(0x33);
	HAL_Delay(15);
	lcd_cmd(0x32);
	HAL_Delay(15);
	lcd_cmd(0x28);
	HAL_Delay(15);
	lcd_cmd(0x0c);
	HAL_Delay(15);
	lcd_cmd(0x06);
	HAL_Delay(150);
	lcd_cmd(0x01);
	lcd_cmd(0x01);
	lcd_cmd(0x0f);
	HAL_Delay(15);

}
///////////////////
void lcd_cmd(uint8_t cmd)
{
	int8_t bit_spc[8],bit_cnt;
	for(bit_cnt=0;bit_cnt<8;bit_cnt++)
	{
		bit_spc[bit_cnt]=(cmd>>bit_cnt) & 0X1;
	}
	RS(0);RW(0);EN(1);
	HAL_Delay(5);
	D7(bit_spc[7]);
	D6(bit_spc[6]);
	D5(bit_spc[5]);
	D4(bit_spc[4]);
	EN(0);
	HAL_Delay(5);
	EN(1);
	HAL_Delay(5);
	D7(bit_spc[3]);//3TH BIT
	D6(bit_spc[2]);//2TH BIT
	D5(bit_spc[1]);//1TH BIT
	D4(bit_spc[0]);//0TH BIT
	EN(0);
	HAL_Delay(5);
}
///////////////////////
void lcd_putchar(uint8_t data1)
{
	uint8_t bit_spc[8],bit_cnt;
	for(bit_cnt=0;bit_cnt<8;bit_cnt++)
	{
		bit_spc[bit_cnt]=(data1>>bit_cnt) & 0X1;
	}
	RS(1);
	EN(1);
	HAL_Delay(5);
	D7(bit_spc[7]);
	D6(bit_spc[6]);
	D5(bit_spc[5]);
	D4(bit_spc[4]);
	EN(0);
	HAL_Delay(5);
	for(bit_cnt=0;bit_cnt<100;bit_cnt++);
	EN(1);
	HAL_Delay(5);
	D7(bit_spc[3]);
	D6(bit_spc[2]);
	D5(bit_spc[1]);
	D4(bit_spc[0]);
	EN(0);
	HAL_Delay(5);
	for(bit_cnt=0;bit_cnt<100;bit_cnt++);
}

void lcd_puts(uint8_t *str)
{
	uint8_t cnt=0;
	while (*(str+cnt)!=0)
	{
		lcd_putchar(*(str+cnt));
		cnt++;
	}
}
void lcd_clear()
{
	lcd_cmd(0x01);
}
void lcd_gotoxy(uint8_t x,uint8_t y)
{
	uint8_t x_cnt;

	if (y==0)
	{
		lcd_cmd(0x80);
	}
	else if (y==1)
	{
		lcd_cmd(0xc0);
	}
	for(x_cnt=0;x_cnt<x;x_cnt++)
	{
		lcd_C_shift(1);
	}
}

void lcd_C_shift(uint8_t bit)
{
	if (bit==0)lcd_cmd(0x10);
	if (bit==1)lcd_cmd(0x15);
}
void lcd_D_shift(uint8_t bit)
{
	if (bit==0)lcd_cmd(0x18);
	if (bit==1)lcd_cmd(0x1c);
}
/* USER CODE END 4 */
