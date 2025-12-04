#ifndef TASK_H
#define TASK_H
#include "main.h"
typedef struct 
{
	uint8_t Run;               //
	uint16_t TIMCount;         //
	uint16_t TRITime;          //
	void (*TaskHook) (void); //
} TASK_COMPONENTS;       

//========================================================================
//                             
//========================================================================

void Task_Marks_Handler_Callback(void);
void Task_Pro_Handler_Callback(void);

#endif // !TASK_H
