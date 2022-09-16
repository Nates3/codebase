
#include "base/base_inc.h"
#include "os/os_inc.h"

#include "base/base_inc.c"
#include "os/os_essential.c"

int
main(int program_argc, char **program_args)
{
	os_thread_context tctx = {0};
	OS_MainInit(&tctx, program_argc, program_args);
	
	return(0);
}
