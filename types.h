#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stddef.h>

#define MAX_USER_NAME_LENGTH 31
#define USER_PWD_HASH_LENGTH 64
#define MAX_USER_EXPLANATION_LENGTH 255
#define RESERVATION_KEY_LENGTH 16
#define MAX_TARGET_HOST_NAME_LENGTH 63 

typedef struct _time_block {
  uint8_t hour; // 0-23
  uint8_t day; // 1-31
  uint8_t month; // 1-12
  uint16_t year; // 0-65535
  uint8_t duration; //measured in hours 
} time_block_t;

typedef uint32_t user_handle_t;
typedef uint32_t user_explanation_handle_t;
typedef uint32_t reservation_handle_t;
typedef uint32_t target_host_handle_t;

typedef uint32_t user_handle_buf_t;
typedef uint32_t user_explanation_handle_buf_t;
typedef uint32_t reservation_handle_buf_t;
typedef uint32_t target_host_handle_buf_t;

typedef struct _user {
  char name[MAX_USER_NAME_LENGTH + 1]; // null-terminated
  size_t name_length; // 2-31
  char pwd_hash[USER_PWD_HASH_LENGTH]; // no null terminator
  user_explanation_handle_t explanation_handle; // handle to the user's explanation
  reservation_handle_buf_t reservation_handles; // array of reservation handles
  size_t num_reservations; // number of reservations made by the user
  target_host_handle_buf_t target_host_handles; // array of target host handles owned by the user
  size_t num_target_hosts; // number of target hosts owned by the user
} user_t;

typedef struct _user_explanation {
  char explanation[MAX_USER_EXPLANATION_LENGTH + 1]; // null-terminated
  size_t explanation_length; // 1-255
  user_handle_t user_handle; // handle to the user who provided the explanation
} user_explanation_t;

typedef struct _reservation {
  char key[RESERVATION_KEY_LENGTH]; // no null terminator
  time_block_t time_block;
  user_handle_t user_handle; // handle to the user who made the reservation
  target_host_handle_t target_host_handle; // handle to the target host for the reservation
} reservation_t;

typedef struct _target_host {
  char name[MAX_TARGET_HOST_NAME_LENGTH + 1]; // null-terminated
  size_t name_length; // 2-63
  union {
    uint8_t ipv4_address[4]; // 0-255 each
    uint8_t ipv6_address[16]; // 0-255 each
  };
  user_handle_t owner; // user who owns the target host
  reservation_handle_buf_t reservation_handles;
  size_t num_reservations;
} target_host_t;

typedef uint32_t user_buf_t;
typedef uint32_t user_explanation_buf_t;
typedef uint32_t reservation_buf_t;
typedef uint32_t target_host_buf_t;

typedef struct _openhaas_storage {
  struct {
    user_buf_t users; // array of users
    user_explanation_buf_t user_explanations; // array of user explanations
    size_t user_count; // number of users
    reservation_buf_t reservations; // array of reservations
    size_t reservation_count; // number of reservations
    target_host_buf_t target_hosts; // array of target hosts
    size_t target_host_count; // number of target hosts
  } container;
  uint8_t* data; // pointer to the raw data storage
  size_t size; // size of the raw data storage in bytes
  size_t capacity; // capacity of the raw data storage in bytes
} openhaas_storage_t;

#endif // TYPES_H