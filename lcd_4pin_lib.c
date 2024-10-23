#define RS(x) (x==1 ? (HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_SET)): (HAL_GPIO_WritePin(RS_GPIO_Port,RS_Pin,GPIO_PIN_RESET)))
#define RW(x) (x==1 ? (HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_SET)): (HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_RESET)))
#define EN(x) (x==1 ? (HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,GPIO_PIN_SET)): (HAL_GPIO_WritePin(E_GPIO_Port,E_Pin,GPIO_PIN_RESET)))
#define D4(x) (x==1 ? (HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_SET)): (HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,GPIO_PIN_RESET)))
#define D5(x) (x==1 ? (HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_SET)): (HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,GPIO_PIN_RESET)))
#define D6(x) (x==1 ? (HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_SET)): (HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,GPIO_PIN_RESET)))
#define D7(x) (x==1 ? (HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_SET)): (HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,GPIO_PIN_RESET)))
/* USER CODE BEGIN 4 */
////////LCD//////////////////////////
void lcd_init(void)
{
    // Initial delay to allow the LCD to power up
    HAL_Delay(40);
    
    // Set to 4-bit mode, send this command twice
    lcd_cmd(0x03);
    HAL_Delay(5);
    lcd_cmd(0x03);
    HAL_Delay(1);
    lcd_cmd(0x03);
    
    // Finally, set 4-bit mode
    lcd_cmd(0x02);

    // Function Set: 4-bit mode, 2 lines, 5x7 font
    lcd_cmd(0x28);

    // Display ON/OFF control: display ON, cursor OFF, blink OFF
    lcd_cmd(0x0C);

    // Clear display
    lcd_cmd(0x01);
    HAL_Delay(2);

    // Entry mode set: increment cursor, no display shift
    lcd_cmd(0x06);
}

///////////////////
void lcd_cmd(uint8_t cmd)
{
    // Send higher nibble (D7-D4)
    D7((cmd >> 7 & 0x01));
    D6((cmd >> 6 & 0x01));
    D5((cmd >> 5 & 0x01));
    D4((cmd >> 4 & 0x01));

    RS(0);  // RS = 0 for command
    EN(1);  // Enable pulse
    HAL_Delay(1);
    EN(0);
    HAL_Delay(1);
    
    // Send lower nibble (D3-D0)
    D7((cmd >> 3 & 0x01));
    D6((cmd >> 2 & 0x01));
    D5((cmd >> 1 & 0x01));
    D4((cmd >> 0 & 0x01));

    EN(1);  // Enable pulse
    HAL_Delay(1);
    EN(0);
    HAL_Delay(1);
}

///////////////////////
void lcd_putchar(uint8_t data)
{
    // Send higher nibble
    D7(((data >> 7) & 0x01));
    D6(((data >> 6) & 0x01));
    D5(((data >> 5) & 0x01));
    D4(((data >> 4) & 0x01));

    RS(1);  // RS = 1 for data
    EN(1);  // Enable pulse
    HAL_Delay(1);
    EN(0);
    HAL_Delay(1);
    
    // Send lower nibble
    D7(((data >> 3) & 0x01));
    D6(((data >> 2) & 0x01));
    D5(((data >> 1) & 0x01));
    D4(((data >> 0) & 0x01));

    EN(1);  // Enable pulse
    HAL_Delay(1);
    EN(0);
    HAL_Delay(1);
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
void lcd_clear(void)
{
    lcd_cmd(0x01);  // Clear display command
    HAL_Delay(2);   // Wait for the command to execute
}

void lcd_gotoxy(uint8_t x, uint8_t y)
{
    uint8_t address[] = {0x00, 0x40, 0x10, 0x50}; // Line addresses for 16x4 LCD
    lcd_cmd(0x80 | (x + address[y]));
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
//--------------------------------------------------------------------------------------------///
/* USER CODE END 4 */
