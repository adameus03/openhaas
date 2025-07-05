#ifndef OPS_H
#define OPS_H

#include "types.h"

openhaas_storage_t openhaas_storage_create(void);

user_handle_t openhaas_create_user(const char* name, const char* pwd_hash);

#endif // OPS_H