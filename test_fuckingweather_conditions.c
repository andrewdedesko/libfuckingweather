/* fuckingweather_conditions unit test
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fuckingweather.h"

int main (){
    const char *location = "Oakville, Ontario";

    printf ("using libfuckingweather v. %d.%d\n", fuckingweather_get_version_major (), fuckingweather_get_version_minor ());

    struct fuckingweather_conditions *conditions = fuckingweather_conditions_new ();
    fuckingweather_fetch_conditions (conditions, location);

    printf ("Location:    %s\n", conditions->location);
    printf ("Temperature: %d C\n", conditions->temperature);
    printf ("Remark:      %s\n", conditions->remark);
    printf ("Flavour:     %s\n", conditions->flavour);
    printf ("url:        [%s]\n", conditions->url);

    fuckingweather_conditions_free (conditions);

    return 0;

    sleep (4);
    printf ("running\n");

    /* TODO  Test creating and freeing fuckingweather_conditions structs */
    int i = 1000000;
    while (i--){
    }

    printf ("waiting\n");
    sleep (10);

    return 0;
}

