#include "timer.h"
#include <stdio.h>

static unsigned int time_counter;
static int hook_id;

int timer_set_square(unsigned long timer, unsigned long freq) {
	if (freq < 0)
		return 1;

	unsigned long frequency = TIMER_FREQ / freq; // Timer_Freq is the frequency of the Clock input and freq is the value loaded initially in the timer
	unsigned char out_port = ' ', timer_selection = ' ';
	if (timer == 0) {
		timer_selection = TIMER_SEL0;
		out_port = TIMER_0;
	} else if (timer == 1) {
		timer_selection = TIMER_SEL1;
		out_port = TIMER_1;
	} else if (timer == 2) {
		timer_selection = TIMER_SEL2;
		out_port = TIMER_2;
	}

	else
		return 1;

	unsigned char st;
	if (timer_get_conf(timer, &st) != 0)
		return 1;

	if ((st & BIT(0)) == TIMER_BCD) {
		if (sys_outb(TIMER_CTRL,
				timer_selection | TIMER_LSB_MSB | TIMER_SQR_WAVE | TIMER_BCD)
				!= OK)
			return 1;
		else {
			if (sys_outb(out_port, (frequency) & 0xFF) != OK)
				return 1;
			else if (sys_outb(out_port, (frequency) >> 8) != OK)
				return 1;
			else
				return 0;
		}
	}

	else {
		if (sys_outb(TIMER_CTRL,
				timer_selection | TIMER_LSB_MSB | TIMER_SQR_WAVE | TIMER_BIN)
				!= OK)
			return 1;
		else {
			if (sys_outb(out_port, (frequency) & 0xFF) != OK)
				return 1;
			else if (sys_outb(out_port, (frequency) >> 8) != OK)
				return 1;
			else
				return 0;
		}
	}
}

int timer_subscribe_int(void) {
	hook_id = 0;
	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK) { //output the EOI command to the PIC
		printf("Irqsetpolicy failed \n");
		return -1;
	} else if (sys_irqenable((&hook_id)) != OK) { //enables interrupts on the IRQ line associated with the hook_id
		printf("Irqenable failed \n");
		return -1;
	} else
		return 0;
}

int timer_unsubscribe_int() {
	if ((sys_irqrmpolicy(&hook_id) != OK))
		return 1;
	else if (sys_irqdisable(&hook_id) != OK)
		return 1;

	else
		return 0;

}

void timer_int_handler() {
	time_counter++;
}

int timer_square(unsigned long freq) {
	return timer_set_square(0, freq);
}

int timer_get_conf(unsigned long timer, unsigned char *st)
{
	sys_outb(TIMER_CTRL, TIMER_RB_CMD | TIMER_RB_COUNT_| TIMER_RB_SEL(timer) | TIMER_RB_STATUS_) ; //Direct I/O port access
	unsigned long int timer_config;
	switch(timer){
	case 0:
		sys_inb(TIMER_0, &timer_config);
		st = (char*)&timer_config;
		return 0;
	case 1:
		sys_inb(TIMER_1, &timer_config);
		st = (char*)&timer_config;
		return 0;
	case 2:
		sys_inb(TIMER_2, &timer_config);
		st = (char*)&timer_config;
		return 0;
	}
	return 1;
}

int timer_delay(unsigned short delay) {
	int ipc_status, r;
	time_counter = 0;
	message msg;
	int irq_set = 0;
	irq_set = timer_subscribe_int();
	if (irq_set == -1)
		return 1;
	irq_set = BIT(irq_set);

	while (time_counter < delay * 60) {  //Interrupt loop
		/* Get a request message. */
		r = driver_receive(ANY, &msg, &ipc_status);
		if (r != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set)
					timer_int_handler();
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if (timer_unsubscribe_int() == -1) {
		printf("\nError while unsubscribing timer\n");
		return 1;
	}
	return 0;

}
