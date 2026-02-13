#include "protocol-task.h"
#include "stdio.h"
#include "string.h"
#include "pico/stdlib.h"
#include <stdlib.h>

static api_t* api = {0};
static int commands_count = 0;

void stdio_task_init()
{
    command_buf_idx = 0;
}
