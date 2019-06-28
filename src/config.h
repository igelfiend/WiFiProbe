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

/**
 * Struct for storing project parameters:
 * - server IP
 * - server port
 * - wlan physical alias
 * Important: In current usage, used memory wasn't freed in cause of using very suspecious forks,
 * so, keep it alive until somebody just killed that daemon
 */
typedef struct Config
{
    char *serverIp;     ///< Storing ip of the server
    char *serverPort;   ///< Storing port of the server
    char *wlanPhys;     ///< Storing physical address of the wlan adapter (used in iw command)
} Config;

/**
 * Initialize memory for config struct
 */
void Init_Config();

/**
 * Freed used memory
 */
void Delete_Config();

/**
 * Reads config from file.
 * In case if file not found, creates one with default values.
 * If return anything except ConfigStateReaded, something goes wrong and needs additional analyze.
 */
ConfigState Read_Config();

/**
 * Returns config pointer from lib.
 * There are only 1 config object in all program (shitty-coded singleton image)
 */
Config *Get_Config();

#endif