/******************************************************************************
 *
 *  Copyright (C) 2015 Google, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#pragma once

#include <stdbool.h>

#include "btcore/include/bdaddr.h"

static const char INTEROP_MODULE[] = "interop_module";

typedef enum {
  // Disable secure connections
  // This is for pre BT 4.1/2 devices that do not handle secure mode
  // very well.
  INTEROP_DISABLE_LE_SECURE_CONNECTIONS = 0,

  // Some devices have proven problematic during the pairing process, often
  // requiring multiple retries to complete pairing. To avoid degrading the user
  // experience for those devices, automatically re-try pairing if page
  // timeouts are received during pairing.
  INTEROP_AUTO_RETRY_PAIRING
} interop_feature_t;

// Check if a given |addr| matches a known interoperability workaround as identified
// by the |interop_feature_t| enum. This API is used for simple address based lookups
// where more information is not available. No look-ups or random address resolution
// are performed on |addr|.
bool interop_match(const interop_feature_t feature, const bt_bdaddr_t *addr);

// Add a dynamic interop database entry for a device matching the first |length| bytes
// of |addr|, implementing the workaround identified by |feature|. |addr| may not be
// null and |length| must be greater than 0 and less than sizeof(bt_bdaddr_t).
void interop_database_add(const interop_feature_t feature, const bt_bdaddr_t *addr, size_t length);

// Clear the dynamic portion of the interoperability workaround database.
void interop_database_clear(void);
