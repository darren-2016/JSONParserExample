/********************************************************************************
 * JSON Parsing Example - using the JSMN Library (https://github.com/zserge/jsmn)
 * 
 */

#include <stdio.h>
#include <string.h>
#include "../jsmn.h"

/************************************************************
 * Function:    jsonToken
 * Description: Check for a match with the given token.
 * Returns:      0 = Matched
 *              -1 = No match
 */
static int jsonToken(const char *json, jsmntok_t *token, const char *s) 
{
    if (token->type == JSMN_STRING && (int) strlen(s) == token->end - token->start 
                    && strncmp(json + token->start, s, token->end - token->start) == 0 )
    {
        return 0;
    }
    return -1;
}


/************************************************************
 * Function:    jsonParserExample
 * Description: An example to try out the JSMN JSON Parser 
 *              library.
 * Returns:     int
 */
int jsonParserExample(char *jsonString)
{
    int i, j;
    jsmn_parser p;
    jsmntok_t tokenArray[32]; /* Allow for up to 32 tokens */

    jsmn_init(&p);

    /* Parse the JSON object */
    j = jsmn_parse(&p, jsonString, strlen(jsonString), tokenArray, sizeof(tokenArray)/sizeof(tokenArray[0]));
    if (j < 0) 
    {
        printf("JSON parse failure - %d\n", j);
        return 1;
    }

    /* Check that it is a JSON object */
    if (j < 1 || tokenArray[0].type != JSMN_OBJECT) 
    {
        printf("Expected a JSON object\n");
        return 1;
    }

    /* Loop through the token keys of the root object */
    for (i = 1; i < j; i++) 
    {
        if (jsonToken(jsonString, &tokenArray[i], "message") == 0) 
        {
            printf("- message: %.*s\n", tokenArray[i + 1].end - tokenArray[i + 1].start, jsonString + tokenArray[i + 1].start);
            i++;
        } else if (jsonToken(jsonString, &tokenArray[i], "taskname") == 0) 
        {
            printf("- taskname: %.*s\n", tokenArray[i + 1].end - tokenArray[i + 1].start, jsonString + tokenArray[i + 1].start);
            i++;
        } else 
        {
            printf("Unexpected key: %.*s\n", tokenArray[i].end - tokenArray[i].start, jsonString + tokenArray[i].start);
        }
    }
    return 0;
}


/************************************************************
 * Function:    main
 * Description: Main entry point.
 * Returns:     int
 */
int main()
{
    int status;

    printf("JSON Parser Example\n");

    status = jsonParserExample("{\"message\": \"123\", \"taskname\": \"abc\",\"mess3age\": \"456\", \"taskname\": \"def\" }");

    return status;
}