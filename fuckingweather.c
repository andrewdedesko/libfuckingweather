/**
 * fuckingweather
 *
 */

/** TODO  Check out libpcre for parsing html */
/** TODO  html parsing (check out libxml2 HTMLparser: http://www.xmlsoft.org/html/libxml-HTMLparser.html) */
/** TODO  Check out named capture groups (pcre) */
/** TODO  Use substrings to get data from matches (remove html tags) */

#ifndef _FUCKINGWEATHER_C
#define _FUCKINGWEATHER_C

#include "fuckingweather.h"

struct fuckingweather_conditions *fuckingweather_conditions_new (){
    struct fuckingweather_conditions *conditions = (struct fuckingweather_conditions *) malloc(sizeof (struct fuckingweather_conditions));
    conditions->location = 0;
    conditions->url = 0;
    conditions->temperature = 0;
    conditions->remark = 0;
    conditions->flavour = 0;

    return conditions;
}

char *fuckingweather__http_user_agent = "Mozilla/5.0 (X11; Linux x86_64; rv:26.0) Gecko/20100101 Firefox/26.0";

void fuckingweather_conditions_free (struct fuckingweather_conditions *conditions){
    if (conditions->location)
        free (conditions->location);

    if (conditions->url)
        free (conditions->url);

    if (conditions->remark)
        free (conditions->remark);

    if (conditions->flavour)
        free (conditions->flavour);

    free (conditions);
}

int fuckingweather_fetch_conditions (struct fuckingweather_conditions *conditions, const char *location){
    char url[1024];
    char *location_escaped;
    CURL *curl;
    char buff [10240];
    char *buff_position = buff;

    /** Initialize curl context */
    if ((curl = curl_easy_init ()) == NULL)
        return FUCKINGWEATHER_CURL_ERROR;

    /** Generate URL for thefuckingweather.com */
    location_escaped = curl_easy_escape (curl, location, 0);
    sprintf (url, "http://thefuckingweather.com/?where=%s&unit=c", location_escaped);

    if (curl_easy_setopt (curl, CURLOPT_URL, url) != CURLE_OK)
        return FUCKINGWEATHER_CURL_ERROR;

    if (curl_easy_setopt (curl, CURLOPT_USERAGENT, fuckingweather__http_user_agent) != CURLE_OK)
        return FUCKINGWEATHER_CURL_ERROR;

    if (curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, &fuckingweather__curl_write_function) != CURLE_OK)
        return FUCKINGWEATHER_CURL_ERROR;

    if (curl_easy_setopt (curl, CURLOPT_WRITEDATA, &buff_position) != CURLE_OK)
        return FUCKINGWEATHER_CURL_ERROR;

    memset (buff, 0, sizeof (buff));
    int r = curl_easy_perform (curl);

    curl_free (location_escaped);

    printf (" >> url  [%s]\n", url);

    /** Parse html */
    int doc_len = strlen (buff);
    htmlDocPtr doc;

    doc = htmlReadMemory (buff, doc_len, url, NULL, 0);
    xmlNodePtr root_node = xmlDocGetRootElement (doc);

    fuckingweather__print_elements (root_node, conditions);

    return FUCKINGWEATHER_OK;
}

void fuckingweather__print_elements (xmlNode *node, struct fuckingweather_conditions *conditions){
    xmlNode *curr_node = NULL;

    for (curr_node = node; curr_node; curr_node = curr_node->next){
        if (curr_node->type == XML_ELEMENT_NODE){
            printf ("\n[%s]", curr_node->name);

            // Print attributes
            xmlAttr *attr;
            for (attr = curr_node->properties; attr; attr = attr->next)
                printf (" %s=\"%s\"", attr->name, xmlGetProp (curr_node, attr->name));

        }else if (curr_node->type == XML_TEXT_NODE){
            printf ("\n  %s", curr_node->content);
        }

        fuckingweather__print_elements (curr_node->children, conditions);
    }
}

int fuckingweather_get_version_major (){
    return FUCKINGWEATHER_VERSION_MAJOR;
}

int fuckingweather_get_version_minor (){
    return FUCKINGWEATHER_VERSION_MINOR;
}

int fuckingweather__curl_write_function (void *data_ptr, size_t data_len, size_t size, void *buff){
    int len = (data_len * size);
    char **buff_position = (char**) buff;

    memcpy (*buff_position, data_ptr, len);
    *buff_position += len;

    return len;
}

#endif

