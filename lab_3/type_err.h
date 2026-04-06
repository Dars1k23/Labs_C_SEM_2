#ifndef TYPE_ERR_H
#define TYPE_ERR_H

typedef enum{
    OK = 0;
    ERR_DUBLICATE_KEY = 1,
    ERR_NOT_FOUND = 2,
    ERR_MEMORY = 3,
    TABLE_ERR_FILE = 4
} TableStatus;

#endif
