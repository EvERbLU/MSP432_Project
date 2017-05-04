/*
 * main_tirtos.cpp
 *
 *       Author: Pranav Narayan Matur
 */
 
#include <stddef.h>
#include <msp.h>

/* XDC Header files */
#include <xdc/cfg/global.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <xdc/runtime/System.h>
#include "LCD.h"


extern void PushButtonS();
extern void PushButtonL();
extern void ButtonS();
extern void ButtonL();
extern void lcdS();
extern void lcdL();

#define NUM_SKETCHES 3
void (*func_ptr[NUM_SKETCHES][2])(void) = {
	{PushButtonS, PushButtonL},
	{ButtonS, ButtonL},
	{lcdS, lcdL}
};
const char *taskNames[] = {
	"PushButtonL",
	"ButtonL",
	"lcdL"
};


Void the_task(UArg _task_setup, UArg _task_loop)
{
	
	(*(void(*)()) _task_setup)();

	
	for(;;) {
		(*(void(*)()) _task_loop)();
		System_flush();
		Task_yield();
	}
}
/*
 *  ======== main ========
 */
int main()
{
	/* initialize all device/board specific peripherals */
	Board_init(); 

	Task_Params taskParams;

	/* initialize taskParams and set to default */
	Task_Params_init(&taskParams);

	/* All tasks have the same priority */
	taskParams.priority = Task_numPriorities - 2;
	taskParams.stackSize = 0x800;

	uint8_t i = 0;
	for(i = 0; i < NUM_SKETCHES; i++) {
		
		taskParams.arg0 = (xdc_UArg)func_ptr[i][0];
		
		taskParams.arg1 = (xdc_UArg)func_ptr[i][1];
		
		taskParams.instance->name = (xdc_String) taskNames[i];
		/* Create the task */
		Task_create(the_task, &taskParams, NULL);
	}

	/* does not return */
	BIOS_start();

	return (0); /* should never get here, but just in case ... */
}


