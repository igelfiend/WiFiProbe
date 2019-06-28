#include "config.h"

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

Config *config = 0;

void Init_Config()
{
    config = (Config *)malloc( sizeof( Config* ) );
    config->serverIp   = (char   *)malloc( sizeof(char) * SERVER_IP_SIZE   );   // Size reserved for IPv6 usage
    config->serverPort = (char   *)malloc( sizeof(char) * SERVER_PORT_SIZE );   // 0 to 65535
    config->wlanPhys   = (char   *)malloc( sizeof(char) * WLAN_PHYS_SIZE   );   // can be both "wlan0" and "phy phy0" and etc.
}

void Delete_Config()
{
    if( config == NULL )
    {
        return;
    }

    free( config->serverIp   );
    free( config->serverPort );
    free( config->wlanPhys   );
    free( config );
    config = NULL;
}

ConfigState Read_Config()
{
// Macros for saving data into config fields
#define IF_FIELD_FOUND_PROCESS_IT(field, str)\
if( strcmp( paramName, str ) == 0 ) strcpy(field, paramValue);

    const char *FILEPATH               = "/opt/scaner/launch.conf";
    const char *SERVER_IP_FIELD_NAME   = "server-ip";
    const char *SERVER_PORT_FIELD_NAME = "server-port";
    const char *WLAN_PHYS_NAME         = "wlan-phys-name";

    // Checking if config file existing, if not, creates one
    if( access( FILEPATH, F_OK ) == -1 )
    {
        // Create config file

        // Cerating path for config file
        int res = system( "mkdir -p /opt/scaner" );
        if( res < 0 )
        {
            printf( "WiFiProbe: Failed creating /opt/scaner foulder. Probably not enough rights, try sudo.\n" );
            return ConfigStateNoCreateAccessError;
        }

        // Trying to create config file
        FILE *newFile = fopen( FILEPATH, "w" );
        if( !newFile )
        {
            printf( "WiFiProbe: Failed creating %s file. Probably not enough rights, try sudo.\n", FILEPATH );
            return ConfigStateNoCreateAccessError;
        }

        char *defaultServerIp   = "172.16.2.53";
        char *defaultServerPort = "4100";
        char *defaultWlanPhys   = "phy phy0";

        fprintf( newFile, "%s %s\n", SERVER_IP_FIELD_NAME,   defaultServerIp   );
        fprintf( newFile, "%s %s\n", SERVER_PORT_FIELD_NAME, defaultServerPort );
        fprintf( newFile, "%s %s\n", WLAN_PHYS_NAME,         defaultWlanPhys   );

        close( newFile );

        printf( "WiFiProbe: default cfg file created at %s.\n", FILEPATH );
    }

    // Checking if we can read config file
    printf( "Trying to open file for read\n" );
    FILE *file = fopen( FILEPATH, "r" );
    if( !file )
    {
        printf( "WiFiProbe: Failed reading %s file.\n", FILEPATH );
        return ConfigStateNoReadAccessError;
    }
    printf( "Openede successfully\n" );

    char buffer[255];

    // Reading entire file and searching required fields
    while( !feof( file ) )
    {
        fgets( buffer, sizeof( buffer ), file );

        char *paramName  = NULL;
        char *paramValue = NULL;

        Split_Config_Row( buffer, &paramName, &paramValue );
        IF_FIELD_FOUND_PROCESS_IT(config->serverIp,        SERVER_IP_FIELD_NAME)
        else IF_FIELD_FOUND_PROCESS_IT(config->serverPort, SERVER_PORT_FIELD_NAME)
        else IF_FIELD_FOUND_PROCESS_IT(config->wlanPhys,   WLAN_PHYS_NAME)

        free( paramName  );
        free( paramValue );
    }

    close( file );

    return ConfigStateReaded;
}

Config *Get_Config()
{
    return config;
}

void Split_Config_Row(const char *srcStr, char **paramName, char **paramValue)
{
    // Searching space
    char *paramValuePtr = strchr( srcStr, ' ' );

    // Copying param value
    *paramValue = strdup( paramValuePtr );

    // Receiving param name and saving to paramName
    size_t paramNameLength = paramValuePtr - srcStr;    
    *paramName = (char *)malloc( sizeof(char) * paramNameLength );
    strncpy( *paramName, srcStr, paramNameLength );
}