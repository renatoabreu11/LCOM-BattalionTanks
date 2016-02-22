#include "rtc.h"

static int hook_id;

int rtc_subscribe_int() {
	hook_id = RTC_IRQ;  //RTC IRQ number is 8.
	if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id)
			!= OK) { //output the EOI command to the PIC
		printf("Irqsetpolicy failed \n");
		return -1;
	} else if (sys_irqenable((&hook_id)) != OK) { //enables interrupts on the IRQ line associated with the hook_id
		printf("Irqenable failed \n");
		return -1;
	} else
		return RTC_IRQ;
}

int rtc_unsubscribe_int() {
	if (sys_irqdisable(&hook_id) != OK)
		return 1;
	else if (sys_irqrmpolicy(&hook_id) != OK)
		return 1;
	else
		return 0;
}

Date* InitDate(){
	Date* d = (Date*) malloc(sizeof(Date));
	d->seconds = 0;
	d->minutes = 0;
	d->hours = 0;
	d->weekday = 0;
	d->day = 0;
	d->month = 0;
	d->year = 0;
	return d;
}

unsigned char bcd_to_bin(unsigned char bcd)
{
	unsigned char aux;
	aux = (bcd >> 4) * 10;
	aux += (bcd & 0x0F);
	return aux;
}

unsigned char int_to_char(int n)
{
	return 48 + n;
}

void updateDate(Date* d){
	unsigned long a_aux;
	unsigned long b_aux;
	unsigned long c_aux;
	unsigned long d_aux;
	unsigned long tmp;
	
	sys_outb(0x70, 0x0A);
	sys_inb(0x71, &a_aux);
	sys_outb(0x70, 0x0B);
	sys_inb(0x71, &b_aux);
	sys_outb(0x70, 0x0C);
	sys_inb(0x71, &c_aux);
	sys_outb(0x70, 0x0D);
	sys_inb(0x71, &d_aux);

	sys_outb(0x70, MINUTES);
	sys_inb(0x71, &d->minutes);
	tmp = bcd_to_bin(d->minutes);
	d->minutes = tmp;
	
	sys_outb(0x70, HOURS);
	sys_inb(0x71, &d->hours);
	tmp = bcd_to_bin(d->hours);
	d->hours = tmp;
	
	sys_outb(0x70, WEEKDAYS);
	sys_inb(0x71, &d->weekday);
	tmp = bcd_to_bin(d->weekday);
	d->weekday = tmp;
	
	sys_outb(0x70, DAYS);
	sys_inb(0x71, &d->day);
	tmp = bcd_to_bin(d->day);
	d->day = tmp;
	
	sys_outb(0x70, MONTHS);
	sys_inb(0x71, &d->month);
	tmp = bcd_to_bin(d->month);
	d->month = tmp;
	
	sys_outb(0x70, YEARS);
	sys_inb(0x71, &d->year);
	tmp = bcd_to_bin(d->year);
	d->year = tmp;
}

void drawDate(Date* d, int x, int y){
	SmallFont* font = InitSmallFont();
	int min1, min0;
	int hou1, hou0;
	int day1, day0;
	int mon1, mon0;
	int yea1, yea0;

	min1 = d->minutes / 10;
	min0 = d->minutes - min1 * 10;
	hou1 = d->hours / 10;
	hou0 = d->hours - hou1 * 10;
	day1 = d->day / 10;
	day0 = d->day - day1 * 10;
	mon1 = d->month / 10;
	mon0 = d->month - mon1 * 10;
	yea1 = d->year / 10;
	yea0 = d->year - yea1 * 10;

	drawSmallChar(font, int_to_char(hou1), x, y);
	drawSmallChar(font, int_to_char(hou0), x + 16, y);
	drawSmallChar(font, ':', x + 32, y);
	drawSmallChar(font, int_to_char(min1), x + 48, y);
	drawSmallChar(font, int_to_char(min0), x + 64, y);
	drawSmallChar(font, int_to_char(day1), x + 96, y);
	drawSmallChar(font, int_to_char(day0), x + 112, y);
	drawSmallChar(font, '-', x + 128, y);
	drawSmallChar(font, int_to_char(mon1), x + 144, y);
	drawSmallChar(font, int_to_char(mon0), x + 160, y);
	drawSmallChar(font, '-', x + 176, y);
	drawSmallChar(font, int_to_char(yea1), x + 192, y);
	drawSmallChar(font, int_to_char(yea0), x + 208, y);
	deleteSmallFont(font);
}

void deleteDate(Date* d){
	free(d);
}
