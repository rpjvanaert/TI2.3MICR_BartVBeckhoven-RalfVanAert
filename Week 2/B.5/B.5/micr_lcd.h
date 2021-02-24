#ifndef micr_led_h
#define micr_led_h

void init();
void display_text(const char *str);
void set_cursor(int position);
void lcd_write_command(unsigned char byte);

#endif