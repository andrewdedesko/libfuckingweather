/**
 * fuckingweather
 *
 * camelsnowman <adedesko@gmail.com>
 * August 13, 2013
 */

#ifndef _FUCKINGWEATHER_H
#define _FUCKINGWEATHER_H

#define FUCKINGWEATHER_VERSION_MAJOR 0
#define FUCKINGWEATHER_VERSION_MINOR 1

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/HTMLparser.h>

enum{
    UNIT_CELSIUS = 0,
    UNIT_FAHRENHEIT
};

enum{
    FUCKINGWEATHER_OK,
    FUCKINGWEATHER_CURL_ERROR,
    FUCKINGWEATHER_LOCATION_NOT_FOUND
};

struct fuckingweather_conditions{
    char *location;
    char *url;

    int temperature;
    char *remark;
    char *flavour;
};

/**
 * fuckingweather_conditions_new ()
 *
 * Creates and initializes a fuckingweather_conditions struct and returns a
 * pointer to the struct.
 */
struct fuckingweather_conditions *fuckingweather_conditions_new ();

/**
 * fuckingweather_conditions_free (fuckingweather_conditions *conditions)
 *
 * Frees the fuckingweather_conditions struct pointed to by conditions.
 */
void fuckingweather_conditions_free (struct fuckingweather_conditions *conditions);

int fuckingweather_fetch_conditions (struct fuckingweather_conditions *conditions, const char *location);

/**
 * fuckingweather_get_version_major ()
 *
 * Returns the major version number of libfuckingweather.
 */
int fuckingweather_get_version_major ();

/**
 * fuckingweather_get_version_minor ()
 *
 * Returns the minor version number of libfuckingweather.
 */
int fuckingweather_get_version_minor ();

int fuckingweather__curl_write_function (void *data_ptr, size_t data_len, size_t size, void *buff);

void fuckingweather__parse_elements (xmlNode *node, struct fuckingweather_conditions *conditions);

#endif

