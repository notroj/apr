/* Copyright 2000-2004 The Apache Software Foundation
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

#include "testglobalmutex.h"
#include "apr_pools.h"
#include "apr_file_io.h"
#include "apr_general.h"
#include "apr_global_mutex.h"
#include "apr.h"

#if APR_HAVE_STDLIB_H
#include <stdlib.h>
#endif


int main(int argc, const char * const argv[])
{
    apr_pool_t *p;
    int i = 0;
    apr_global_mutex_t *global_lock;

    apr_initialize();
    atexit(apr_terminate);
    
    apr_pool_create(&p, NULL);
    apr_global_mutex_create(&global_lock, LOCKNAME, APR_LOCK_DEFAULT, p);
    apr_global_mutex_child_init(&global_lock, LOCKNAME, p);
    
    while (1) {
        apr_global_mutex_lock(global_lock);
        if (i == MAX_ITER) {
            apr_global_mutex_unlock(global_lock);
            exit(i);
        }
        i++;
        apr_global_mutex_unlock(global_lock);
    }
    exit(0);
}
