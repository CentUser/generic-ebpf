/*-
 * SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright 2017-2018 Yutaro Hayakawa
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

#include <sys/ebpf_vm_isa.h>

#define EBPF_NAME_MAX 64
#define EBPF_TYPE_MAX 64
#define EBPF_PROG_MAX_ATTACHED_MAPS 64

#define EBPF_PSEUDO_MAP_DESC 1

struct ebpf_obj;
struct ebpf_prog;
struct ebpf_map;
struct ebpf_env;

struct ebpf_prog_attr {
	uint32_t type;
	struct ebpf_inst *prog;
	uint32_t prog_len;
};

struct ebpf_map_attr {
	uint32_t type;
	uint32_t key_size;
	uint32_t value_size;
	uint32_t max_entries;
	uint32_t flags;
};

enum ebpf_map_update_flags {
	EBPF_ANY = 0,
	EBPF_NOEXIST,
	EBPF_EXIST,
	__EBPF_MAP_UPDATE_FLAGS_MAX
};

struct ebpf_map_ops {
	int (*init)(struct ebpf_map *em, struct ebpf_map_attr *attr);
	void* (*lookup_elem)(struct ebpf_map *em, void *key);
	int (*update_elem)(struct ebpf_map *em, void *key, void *value, uint64_t flags);
	int (*delete_elem)(struct ebpf_map *em, void *key);
	int (*lookup_elem_from_user)(struct ebpf_map *em, void *key, void *value);
	int (*update_elem_from_user)(struct ebpf_map *em, void *key, void *value, uint64_t flags);
	int (*delete_elem_from_user)(struct ebpf_map *em, void *key);
	int (*get_next_key_from_user)(struct ebpf_map *em, void *key, void *next_key);
	void (*deinit)(struct ebpf_map *em);
};

struct ebpf_map_type {
	char name[EBPF_NAME_MAX];
	struct ebpf_map_ops ops;
};

struct ebpf_helper_type {
	char name[EBPF_NAME_MAX];
	uint64_t (*fn)(uint64_t arg0, uint64_t arg1,
		       uint64_t arg2, uint64_t arg3,
		       uint64_t arg4);
};

struct ebpf_prog_ops {
	bool (*is_map_usable)(struct ebpf_map_type *emt);
	bool (*is_helper_usable)(struct ebpf_helper_type *eht);
};

struct ebpf_prog_type {
	char name[EBPF_NAME_MAX];
	struct ebpf_prog_ops ops;
};

struct ebpf_preprocessor_ops {
	struct ebpf_map *(*resolve_map_desc)(int32_t upper, int32_t lower,
					     void *arg);
};

struct ebpf_preprocessor {
	char name[EBPF_NAME_MAX];
	struct ebpf_preprocessor_ops ops;
};

struct ebpf_config {
	struct ebpf_prog_type prog_types[EBPF_TYPE_MAX];
	struct ebpf_map_type map_types[EBPF_TYPE_MAX];
	struct ebpf_helper_type helper_types[EBPF_TYPE_MAX];
	struct ebpf_preprocessor preprocessor;
};

int ebpf_env_create(struct ebpf_env **eep, const struct ebpf_config *ec);
int ebpf_env_destroy(struct ebpf_env *ee);

int ebpf_prog_create(struct ebpf_env *ee, struct ebpf_prog **epp, struct ebpf_prog_attr *attr);
void ebpf_prog_destroy(struct ebpf_prog *);

int ebpf_map_create(struct ebpf_env **ee, struct ebpf_map **emp, struct ebpf_map_attr *attr);
struct ebpf_map_type *ebpf_map_get_type(uint32_t type);
void *ebpf_map_lookup_elem(struct ebpf_map *em, void *key);
int ebpf_map_update_elem(struct ebpf_map *em, void *key, void *value, uint64_t flags);
int ebpf_map_delete_elem(struct ebpf_map *em, void *key);
int ebpf_map_lookup_elem_from_user(struct ebpf_map *em, void *key, void *value);
int ebpf_map_update_elem_from_user(struct ebpf_map *em, void *key, void *value, uint64_t flags);
int ebpf_map_delete_elem_from_user(struct ebpf_map *em, void *key);
int ebpf_map_get_next_key_from_user(struct ebpf_map *em, void *key, void *next_key);
void ebpf_map_destroy(struct ebpf_map *em);
