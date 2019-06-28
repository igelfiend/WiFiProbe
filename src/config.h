#ifndef CONFIG_H
#define CONFIG_H

#define SERVER_IP_SIZE 15
#define SERVER_PORT_SIZE 5
#define WLAN_PHYS_SIZE 15

typedef enum ConfigState
{
    ConfigStateReaded,
    ConfigStateNoCreateAccessError,
    ConfigStateNoReadAccessError
} ConfigState;

typedef struct Config
{
    char *serverIp;
    char *serverPort;
    char *wlanPhys;
} Config;

void Init_Config();
void Delete_Config();
ConfigState Read_Config();
Config *Get_Config();
void Split_Config_Row(const char *srcStr, char **paramName, char **paramValue);

#endif