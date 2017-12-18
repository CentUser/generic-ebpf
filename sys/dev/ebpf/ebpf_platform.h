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

#ifdef __FreeBSD__
#ifdef user
#include <ebpf_freebsd_user.h>
#else
#include "ebpf_freebsd.h"
#endif
#elif defined(linux)
#ifdef user
#include <ebpf_linux_user.h>
#else
#include <ebpf_linux.h>
#endif
#elif defined(__APPLE__)
#ifdef user
#include <ebpf_osx_user.h>
#endif
#else
#error Unsupported platform
#endif

/* 
 * Prototypes of platform dependent functions for both
 * user space platforms and kernel space platforms.
 */
void *ebpf_malloc(size_t size);
void *ebpf_calloc(size_t number, size_t size);
void ebpf_free(void *mem);
void *ebpf_exalloc(size_t size);
void ebpf_exfree(void *mem, size_t size);
int ebpf_error(const char *fmt, ...);
void ebpf_assert(bool expr);

/*
 * Below methods should be simply expanded to memcpy(3) in user
 * space platforms.
 */
int ebpf_copyin(const void *uaddr, void *kaddr, size_t len);
int ebpf_copyout(const void *kaddr, void *uaddr, size_t len);