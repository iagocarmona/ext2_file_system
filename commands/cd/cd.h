#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../utils/utils.h"
#include "../pwd/pwd.h"

int cdCommand(FILE* file, GroupDescriptor *group, StackDirectory* stack, Superblock* super, char* path);