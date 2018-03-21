#include <stdio.h>
#include <stdlib.h>
#include "server_library.h"

int 
main(int argc, char **argv)
{
        printf("Running program ... \n");
        run_server(9999);
        exit(0);
}
