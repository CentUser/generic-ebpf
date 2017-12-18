/*
 * Copyright 2017 Yutaro Hayakawa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "ebpf_uapi.h"

#define EBPFIOC_LOAD_PROG _IOWR('i', 151, union ebpf_req)
#define EBPFIOC_MAP_CREATE _IOWR('i', 152, union ebpf_req)
#define EBPFIOC_MAP_LOOKUP_ELEM _IOWR('i', 153, union ebpf_req)
#define EBPFIOC_MAP_UPDATE_ELEM _IOWR('i', 154, union ebpf_req)
#define EBPFIOC_MAP_DELETE_ELEM _IOWR('i', 155, union ebpf_req)
#define EBPFIOC_MAP_GET_NEXT_KEY _IOWR('i', 156, union ebpf_req)

#ifndef user

#include <dev/ebpf/ebpf_obj.h>

/*
 * Prototypes of platform dependent functions for kernel
 * space platforms.
 */
int ebpf_obj_get_fdesc(ebpf_thread_t *td, struct ebpf_obj *data);
int ebpf_fget(ebpf_thread_t *td, int fd, ebpf_file_t **f);
int ebpf_ioctl(uint32_t cmd, void *data, ebpf_thread_t *td);

int ebpf_map_create(union ebpf_req *req, ebpf_thread_t *td);
int ebpf_ioc_map_lookup_elem(union ebpf_req *req, ebpf_thread_t *td);
int ebpf_ioc_map_update_elem(union ebpf_req *req, ebpf_thread_t *td);
int ebpf_ioc_map_delete_elem(union ebpf_req *req, ebpf_thread_t *td);
int ebpf_ioc_map_get_next_key(union ebpf_req *req, ebpf_thread_t *td);

#endif