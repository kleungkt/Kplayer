/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 2020 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OSSL_CRYPTO_ENGINEERR_H
# define OSSL_CRYPTO_ENGINEERR_H
# pragma once

# include <openssl/opensslconf.h>
# include <openssl/symhacks.h>

# ifdef  __cplusplus
extern "C" {
# endif

# ifndef OPENSSL_NO_ENGINE

int err_load_ENGINE_strings_int(void);
# endif

# ifdef  __cplusplus
}
# endif
#endif
