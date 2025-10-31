#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void ui_printList(const tNumStoreHead *list_head);
void ui_run_menu(tNumStoreHead *list_head);

#endif