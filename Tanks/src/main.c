#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "Utilities.h"
#include "BattalionTanks.h"

FILE* logfd = NULL;
void initLog() {
	logfd = fopen(LOG_PATH, "w");
	LOG("initLog", "logging successfully initialized");
}

int main(int argc, char **argv) {
	/* Initialize service */
	initLog();
	LOG("main", "starting program");
	LOG_MSG("\n");
	sef_startup();
	vg_init(0x117);
	BattalionTanks* bt = (BattalionTanks*) malloc(sizeof(BattalionTanks));
	bt = InitBattalionTanks();
	while(bt->currentState != ExitS){
		 updateBattalionTanks(bt);
	}
	deleteBattalionTanks(bt);

	if(vg_exit() != 0)
		return 1;
	return 0;
}
