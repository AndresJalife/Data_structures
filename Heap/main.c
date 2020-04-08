#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

void heap_tests(void);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[])
{
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    heap_tests();

    return failure_count() > 0;
}
