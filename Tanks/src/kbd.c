#include "kbd.h"

static int hook_id;

int kbd_subscribe_int(void ) {
	hook_id = KBD_IRQ;  //keyboard's IRQ number is 1.
	if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE|IRQ_EXCLUSIVE, &hook_id) != OK){ //output the EOI command to the PIC
		printf("Irqsetpolicy failed \n");
		return -1;
	   	   }
	else if(sys_irqenable((&hook_id)) != OK){ //enables interrupts on the IRQ line associated with the hook_id
		printf("Irqenable failed \n");
		return -1;
		}
	else return KBD_IRQ;
}

int kdb_unsubscribe_int() {
	if ((sys_irqdisable(&hook_id) != OK))
		return 1;
		else if (sys_irqrmpolicy(&hook_id)  != OK)
		return 1;

	else return 0;
}

int kbd_read(){
	unsigned long stat, key;

	while( 1 ) {
	if(sys_inb(STAT_REG, &stat) != OK)
		return -1;

	   if( stat & OBF ) {
	     sys_inb(OUT_BUF, &key); // assuming it returns OK
	   if ( (stat &(PAR_ERR | TO_ERR)) == 0 )
	     return key;
	    else
	     return -1;
	}
	   tickdelay(micros_to_ticks(DELAY_US));
	}
}

int kbd_write(unsigned char command){
	unsigned long stat;
	while( 1 ) {
		/* loop while 8042 input buffer is not empty */
		if(sys_inb(STAT_REG, &stat) != OK)
			return -1;

			if( (stat & IBF) == 0 ) {
				sys_outb(OUT_BUF, command); /* no args command */
					return 0;
			}
			tickdelay(micros_to_ticks(DELAY_US));
	}
}

int kbd_scan(unsigned long key_code) {
	int ipc_status, r, irq_set = 0, two_byte = false;
	bool break_code_flag = false;
	unsigned long key;
	message msg;
	irq_set = kbd_subscribe_int();
	irq_set = BIT(irq_set);
	while (!break_code_flag) {  //Interrupt loop
		/* Get a request message. */
		r = driver_receive(ANY, &msg, &ipc_status);
		if (r != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) {
						key = kbd_read();
						if (key == 0xE0) {
							two_byte = true;
						} else if (two_byte == true) {
							key |= 0xE0 << 8;
							two_byte = false;
							if (key == key_code)
								break_code_flag = true;
						} else {
							if (key == key_code)
								break_code_flag = true;
						}
					}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	if (kdb_unsubscribe_int() != 0) //in order to use Minix 3 virtual terminals
		return 1;

	return 0;
}

char MinixKeyToAscii(KEY minixKey){
	switch(minixKey){
	case k1: return '1';
	case k2: return '2';
	case k3: return '3';
	case k4: return '4';
	case k5: return '5';
	case k6: return '6';
	case k7: return '7';
	case k8: return '8';
	case k9: return '9';
	case k0: return '0';
	case kQ: return 'Q';
	case kW: return 'W';
	case kE: return 'E';
	case kR: return 'R';
	case kT: return 'T';
	case kY: return 'Y';
	case kU: return 'U';
	case kI: return 'I';
	case kO: return 'O';
	case kP: return 'P';
	case kA: return 'A';
	case kS: return 'S';
	case kD: return 'D';
	case kF: return 'F';
	case kG: return 'G';
	case kH: return 'H';
	case kJ: return 'J';
	case kK: return 'K';
	case kL: return 'L';
	case kZ: return 'Z';
	case kX: return 'X';
	case kC: return 'C';
	case kV: return 'V';
	case kB: return 'B';
	case kN: return 'N';
	case kM: return 'M';
	default: return '\0';
	}
}
