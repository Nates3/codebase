
#include "base/base_inc.h"
#include "os/os_inc.h"

#include "base/base_inc.c"
#include "os/os_essential.c"

typedef U32 U32SumFuncType(U32 *values, U32 count);
typedef U32 U32TimesTwoFuncType(U32 value);

int
main(int program_argc, char **program_args)
{
 OS_ThreadContext tctx = {0};
 OS_Main_Init(&tctx, program_argc, program_args);
 
 return(0);
}
