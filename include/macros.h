#ifndef MACROS_H
# define MACROS_H

# define EX_NOTFOUND 127
# define DEFAULT_CHMOD 0002
# define EXIT_CODE_MODULO 256
# define EXIT_ERR_DIGIT 2
# define EXIT_INVALID_OPERATION 2
# define ECUSTOMFULL 125
# define ERROR_CMD_NOT_EXET 126
# define INVALID_ID  "not a valid identifier"
# define NO_FILE_DIR "No such file or directory"
# define PERM_DENIED "Permission denied"
# define CMD_NOT_FOUND "command not found"
# define IS_A_DIR "Is a directory"
# define MISS_PROMPT "\001\033[0;36m\002(＃＞＜) \001\033[0m\002"

# if __APPLE__
    // delete avan correction pour la norm
#   define PATH_MAX 1024
# else
#   define PATH_MAX 4096
# endif
# define FREE_STATIC_FD -99
# define CNTRL_C SIGINT
# define CNTRL_B_SLASH SIGQUIT

#endif