/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */
/* ====================================================================
 * Copyright (c) 1998-2007 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */
/* ====================================================================
 * Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
 * ECC cipher suite support in OpenSSL originally developed by
 * SUN MICROSYSTEMS, INC., and contributed to the OpenSSL project.
 */
/* ====================================================================
 * Copyright 2005 Nokia. All rights reserved.
 *
 * The portions of the attached software ("Contribution") is developed by
 * Nokia Corporation and is licensed pursuant to the OpenSSL open source
 * license.
 *
 * The Contribution, originally written by Mika Kousa and Pasi Eronen of
 * Nokia Corporation, consists of the "PSK" (Pre-Shared Key) ciphersuites
 * support (see RFC 4279) to OpenSSL.
 *
 * No patent licenses or other rights except those expressly stated in
 * the OpenSSL open source license shall be deemed granted or received
 * expressly, by implication, estoppel, or otherwise.
 *
 * No assurances are provided by Nokia that the Contribution does not
 * infringe the patent or other intellectual property rights of any third
 * party or that the license provides you with all the necessary rights
 * to make use of the Contribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. IN
 * ADDITION TO THE DISCLAIMERS INCLUDED IN THE LICENSE, NOKIA
 * SPECIFICALLY DISCLAIMS ANY LIABILITY FOR CLAIMS BROUGHT BY YOU OR ANY
 * OTHER ENTITY BASED ON INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS OR
 * OTHERWISE. */

#include <openssl/ssl.h>

#include <assert.h>

#include <openssl/asn1.h>
#include <openssl/bytestring.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/stack.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/x509_vfy.h>

#include "internal.h"
#include "../crypto/internal.h"


BSSL_NAMESPACE_BEGIN

// check_ssl_x509_method asserts that |ssl| has the X509-based method
// installed. Calling an X509-based method on an |ssl| with a different method
// will likely misbehave and possibly crash or leak memory.
static void check_ssl_x509_method(const SSL *ssl) {
  assert(ssl == NULL || ssl->ctx->x509_method == &ssl_crypto_x509_method);
}

// check_ssl_ctx_x509_method acts like |check_ssl_x509_method|, but for an
// |SSL_CTX|.
static void check_ssl_ctx_x509_method(const SSL_CTX *ctx) {
  assert(ctx == NULL || ctx->x509_method == &ssl_crypto_x509_method);
}

// x509_to_buffer returns a |CRYPTO_BUFFER| that contains the serialised
// contents of |x509|.
static UniquePtr<CRYPTO_BUFFER> x509_to_buffer(X509 *x509) {
  uint8_t *buf = NULL;
  int cert_len = i2d_X509(x509, &buf);
  if (cert_len <= 0) {
    return 0;
  }

  UniquePtr<CRYPTO_BUFFER> buffer(CRYPTO_BUFFER_new(buf, cert_len, NULL));
  OPENSSL_free(buf);

  return buffer;
}

// new_leafless_chain returns a fresh stack of buffers set to {NULL}.
static UniquePtr<STACK_OF(CRYPTO_BUFFER)> new_leafless_chain(void) {
  UniquePtr<STACK_OF(CRYPTO_BUFFER)> chain(sk_CRYPTO_BUFFER_new_null());
  if (!chain ||
      !sk_CRYPTO_BUFFER_push(chain.get(), nullptr)) {
    return nullptr;
  }

  return chain;
}

// ssl_cert_set_chain sets elements 1.. of |cert->chain| to the serialised
// forms of elements of |chain|. It returns one on success or zero on error, in
// which case no change to |cert->chain| is made. It preverses the existing
// leaf from |cert->chain|, if any.
static int ssl_cert_set_chain(CERT *cert, STACK_OF(X509) *chain) {
  UniquePtr<STACK_OF(CRYPTO_BUFFER)> new_chain;

  if (cert->chain != nullptr) {
    new_chain.reset(sk_CRYPTO_BUFFER_new_null());
    if (!new_chain) {
      return 0;
    }

    // |leaf| might be NULL if it's a “leafless” chain.
    CRYPTO_BUFFER *leaf = sk_CRYPTO_BUFFER_value(cert->chain.get(), 0);
    if (!PushToStack(new_chain.get(), UpRef(leaf))) {
      return 0;
    }
  }

  for (X509 *x509 : chain) {
    if (!new_chain) {
      new_chain = new_leafless_chain();
      if (!new_chain) {
        return 0;
      }
    }

    UniquePtr<CRYPTO_BUFFER> buffer = x509_to_buffer(x509);
    if (!buffer ||
        !PushToStack(new_chain.get(), std::move(buffer))) {
      return 0;
    }
  }

  cert->chain = std::move(new_chain);
  return 1;
}

static void ssl_crypto_x509_cert_flush_cached_leaf(CERT *cert) {
  X509_free(cert->x509_leaf);
  cert->x509_leaf = NULL;
}

static void ssl_crypto_x509_cert_flush_cached_chain(CERT *cert) {
  sk_X509_pop_free(cert->x509_chain, X509_free);
  cert->x509_chain = NULL;
}

static int ssl_crypto_x509_check_client_CA_list(
    STACK_OF(CRYPTO_BUFFER) *names) {
  for (const CRYPTO_BUFFER *buffer : names) {
    const uint8_t *inp = CRYPTO_BUFFER_data(buffer);
    UniquePtr<X509_NAME> name(
        d2i_X509_NAME(nullptr, &inp, CRYPTO_BUFFER_len(buffer)));
    if (name.get() == nullptr ||
        inp != CRYPTO_BUFFER_data(buffer) + CRYPTO_BUFFER_len(buffer)) {
      return 0;
    }
  }

  return 1;
}

static void ssl_crypto_x509_cert_clear(CERT *cert) {
  ssl_crypto_x509_cert_flush_cached_leaf(cert);
  ssl_crypto_x509_cert_flush_cached_chain(cert);

  X509_free(cert->x509_stash);
  cert->x509_stash = NULL;
}

static void ssl_crypto_x509_cert_free(CERT *cert) {
  ssl_crypto_x509_cert_clear(cert);
  X509_STORE_free(cert->verify_store);
}

static void ssl_crypto_x509_cert_dup(CERT *new_cert, const CERT *cert) {
  if (cert->verify_store != NULL) {
    X509_STORE_up_ref(cert->verify_store);
    new_cert->verify_store = cert->verify_store;
  }
}

static int ssl_crypto_x509_session_cache_objects(SSL_SESSION *sess) {
  bssl::UniquePtr<STACK_OF(X509)> chain, chain_without_leaf;
  if (sk_CRYPTO_BUFFER_num(sess->certs.get()) > 0) {
    chain.reset(sk_X509_new_null());
    if (!chain) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      return 0;
    }
    if (sess->is_server) {
      // chain_without_leaf is only needed for server sessions. See
      // |SSL_get_peer_cert_chain|.
      chain_without_leaf.reset(sk_X509_new_null());
      if (!chain_without_leaf) {
        OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
        return 0;
      }
    }
  }

  bssl::UniquePtr<X509> leaf;
  for (CRYPTO_BUFFER *cert : sess->certs.get()) {
    UniquePtr<X509> x509(X509_parse_from_buffer(cert));
    if (!x509) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_DECODE_ERROR);
      return 0;
    }
    if (leaf.get() == nullptr) {
      leaf = UpRef(x509);
    } else if (chain_without_leaf &&
               !PushToStack(chain_without_leaf.get(), UpRef(x509))) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      return 0;
    }
    if (!PushToStack(chain.get(), std::move(x509))) {
      OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
      return 0;
    }
  }

  sk_X509_pop_free(sess->x509_chain, X509_free);
  sess->x509_chain = chain.release();

  sk_X509_pop_free(sess->x509_chain_without_leaf, X509_free);
  sess->x509_chain_without_leaf = chain_without_leaf.release();

  X509_free(sess->x509_peer);
  sess->x509_peer = leaf.release();
  return 1;
}

static int ssl_crypto_x509_session_dup(SSL_SESSION *new_session,
                                       const SSL_SESSION *session) {
  new_session->x509_peer = UpRef(session->x509_peer).release();
  if (session->x509_chain != nullptr) {
    new_session->x509_chain = X509_chain_up_ref(session->x509_chain);
    if (new_session->x509_chain == nullptr) {
      return 0;
    }
  }
  if (session->x509_chain_without_leaf != nullptr) {
    new_session->x509_chain_without_leaf =
        X509_chain_up_ref(session->x509_chain_without_leaf);
    if (new_session->x509_chain_without_leaf == nullptr) {
      return 0;
    }
  }

  return 1;
}

static void ssl_crypto_x509_session_clear(SSL_SESSION *session) {
  X509_free(session->x509_peer);
  session->x509_peer = NULL;
  sk_X509_pop_free(session->x509_chain, X509_free);
  session->x509_chain = NULL;
  sk_X509_pop_free(session->x509_chain_without_leaf, X509_free);
  session->x509_chain_without_leaf = NULL;
}

static int ssl_crypto_x509_session_verify_cert_chain(SSL_SESSION *session,
                                                     SSL_HANDSHAKE *hs,
                                                     uint8_t *out_alert) {
  *out_alert = SSL_AD_INTERNAL_ERROR;
  STACK_OF(X509) *const cert_chain = session->x509_chain;
  if (cert_chain == NULL || sk_X509_num(cert_chain) == 0) {
    return 0;
  }

  SSL_CTX *ssl_ctx = hs->ssl->ctx.get();
  X509_STORE *verify_store = ssl_ctx->cert_store;
  if (hs->config->cert->verify_store != NULL) {
    verify_store = hs->config->cert->verify_store;
  }

  X509 *leaf = sk_X509_value(cert_chain, 0);
  ScopedX509_STORE_CTX ctx;
  if (!X509_STORE_CTX_init(ctx.get(), verify_store, leaf, cert_chain)) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_X509_LIB);
    return 0;
  }
  if (!X509_STORE_CTX_set_ex_data(
          ctx.get(), SSL_get_ex_data_X509_STORE_CTX_idx(), hs->ssl)) {
    return 0;
  }

  // We need to inherit the verify parameters. These can be determined by the
  // context: if its a server it will verify SSL client certificates or vice
  // versa.
  X509_STORE_CTX_set_default(ctx.get(),
                             hs->ssl->server ? "ssl_client" : "ssl_server");

  // Anything non-default in "param" should overwrite anything in the ctx.
  X509_VERIFY_PARAM_set1(X509_STORE_CTX_get0_param(ctx.get()),
                         hs->config->param);

  if (hs->config->verify_callback) {
    X509_STORE_CTX_set_verify_cb(ctx.get(), hs->config->verify_callback);
  }

  int verify_ret;
  if (ssl_ctx->app_verify_callback != NULL) {
    verify_ret =
        ssl_ctx->app_verify_callback(ctx.get(), ssl_ctx->app_verify_arg);
  } else {
    verify_ret = X509_verify_cert(ctx.get());
  }

  session->verify_result = ctx->error;

  // If |SSL_VERIFY_NONE|, the error is non-fatal, but we keep the result.
  if (verify_ret <= 0 && hs->config->verify_mode != SSL_VERIFY_NONE) {
    *out_alert = SSL_alert_from_verify_result(ctx->error);
    return 0;
  }

  ERR_clear_error();
  return 1;
}

static void ssl_crypto_x509_hs_flush_cached_ca_names(SSL_HANDSHAKE *hs) {
  sk_X509_NAME_pop_free(hs->cached_x509_ca_names, X509_NAME_free);
  hs->cached_x509_ca_names = NULL;
}

static int ssl_crypto_x509_ssl_new(SSL_HANDSHAKE *hs) {
  hs->config->param = X509_VERIFY_PARAM_new();
  if (hs->config->param == NULL) {
    return 0;
  }
  X509_VERIFY_PARAM_inherit(hs->config->param, hs->ssl->ctx->param);
  return 1;
}

static void ssl_crypto_x509_ssl_flush_cached_client_CA(SSL_CONFIG *cfg) {
  sk_X509_NAME_pop_free(cfg->cached_x509_client_CA, X509_NAME_free);
  cfg->cached_x509_client_CA = NULL;
}

static void ssl_crypto_x509_ssl_config_free(SSL_CONFIG *cfg) {
  sk_X509_NAME_pop_free(cfg->cached_x509_client_CA, X509_NAME_free);
  cfg->cached_x509_client_CA = NULL;
  X509_VERIFY_PARAM_free(cfg->param);
}

static int ssl_crypto_x509_ssl_auto_chain_if_needed(SSL_HANDSHAKE *hs) {
  // Only build a chain if there are no intermediates configured and the feature
  // isn't disabled.
  if ((hs->ssl->mode & SSL_MODE_NO_AUTO_CHAIN) ||
      !ssl_has_certificate(hs) || hs->config->cert->chain.get() == NULL ||
      sk_CRYPTO_BUFFER_num(hs->config->cert->chain.get()) > 1) {
    return 1;
  }

  UniquePtr<X509> leaf(X509_parse_from_buffer(
      sk_CRYPTO_BUFFER_value(hs->config->cert->chain.get(), 0)));
  if (!leaf) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_X509_LIB);
    return 0;
  }

  ScopedX509_STORE_CTX ctx;
  if (!X509_STORE_CTX_init(ctx.get(), hs->ssl->ctx->cert_store, leaf.get(),
                           NULL)) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_X509_LIB);
    return 0;
  }

  // Attempt to build a chain, ignoring the result.
  X509_verify_cert(ctx.get());
  ERR_clear_error();

  // Remove the leaf from the generated chain.
  X509_free(sk_X509_shift(ctx->chain));

  if (!ssl_cert_set_chain(hs->config->cert.get(), ctx->chain)) {
    return 0;
  }

  ssl_crypto_x509_cert_flush_cached_chain(hs->config->cert.get());

  return 1;
}

static void ssl_crypto_x509_ssl_ctx_flush_cached_client_CA(SSL_CTX *ctx) {
  sk_X509_NAME_pop_free(ctx->cached_x509_client_CA, X509_NAME_free);
  ctx->cached_x509_client_CA = NULL;
}

static int ssl_crypto_x509_ssl_ctx_new(SSL_CTX *ctx) {
  ctx->cert_store = X509_STORE_new();
  ctx->param = X509_VERIFY_PARAM_new();
  return (ctx->cert_store != NULL && ctx->param != NULL);
}

static void ssl_crypto_x509_ssl_ctx_free(SSL_CTX *ctx) {
  ssl_crypto_x509_ssl_ctx_flush_cached_client_CA(ctx);
  X509_VERIFY_PARAM_free(ctx->param);
  X509_STORE_free(ctx->cert_store);
}

const SSL_X509_METHOD ssl_crypto_x509_method = {
  ssl_crypto_x509_check_client_CA_list,
  ssl_crypto_x509_cert_clear,
  ssl_crypto_x509_cert_free,
  ssl_crypto_x509_cert_dup,
  ssl_crypto_x509_cert_flush_cached_chain,
  ssl_crypto_x509_cert_flush_cached_leaf,
  ssl_crypto_x509_session_cache_objects,
  ssl_crypto_x509_session_dup,
  ssl_crypto_x509_session_clear,
  ssl_crypto_x509_session_verify_cert_chain,
  ssl_crypto_x509_hs_flush_cached_ca_names,
  ssl_crypto_x509_ssl_new,
  ssl_crypto_x509_ssl_config_free,
  ssl_crypto_x509_ssl_flush_cached_client_CA,
  ssl_crypto_x509_ssl_auto_chain_if_needed,
  ssl_crypto_x509_ssl_ctx_new,
  ssl_crypto_x509_ssl_ctx_free,
  ssl_crypto_x509_ssl_ctx_flush_cached_client_CA,
};

BSSL_NAMESPACE_END

using namespace bssl;

X509 *SSL_get_peer_certificate(const SSL *ssl) {
  check_ssl_x509_method(ssl);
  if (ssl == NULL) {
    return NULL;
  }
  SSL_SESSION *session = SSL_get_session(ssl);
  if (session == NULL || session->x509_peer == NULL) {
    return NULL;
  }
  X509_up_ref(session->x509_peer);
  return session->x509_peer;
}

STACK_OF(X509) *SSL_get_peer_cert_chain(const SSL *ssl) {
  check_ssl_x509_method(ssl);
  if (ssl == nullptr) {
    return nullptr;
  }
  SSL_SESSION *session = SSL_get_session(ssl);
  if (session == nullptr) {
    return nullptr;
  }

  // OpenSSL historically didn't include the leaf certificate in the returned
  // certificate chain, but only for servers.
  return ssl->server ? session->x509_chain_without_leaf : session->x509_chain;
}

STACK_OF(X509) *SSL_get_peer_full_cert_chain(const SSL *ssl) {
  check_ssl_x509_method(ssl);
  SSL_SESSION *session = SSL_get_session(ssl);
  if (session == NULL) {
    return NULL;
  }

  return session->x509_chain;
}

int SSL_CTX_set_purpose(SSL_CTX *ctx, int purpose) {
  check_ssl_ctx_x509_method(ctx);
  return X509_VERIFY_PARAM_set_purpose(ctx->param, purpose);
}

int SSL_set_purpose(SSL *ssl, int purpose) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return X509_VERIFY_PARAM_set_purpose(ssl->config->param, purpose);
}

int SSL_CTX_set_trust(SSL_CTX *ctx, int trust) {
  check_ssl_ctx_x509_method(ctx);
  return X509_VERIFY_PARAM_set_trust(ctx->param, trust);
}

int SSL_set_trust(SSL *ssl, int trust) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return X509_VERIFY_PARAM_set_trust(ssl->config->param, trust);
}

int SSL_CTX_set1_param(SSL_CTX *ctx, const X509_VERIFY_PARAM *param) {
  check_ssl_ctx_x509_method(ctx);
  return X509_VERIFY_PARAM_set1(ctx->param, param);
}

int SSL_set1_param(SSL *ssl, const X509_VERIFY_PARAM *param) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return X509_VERIFY_PARAM_set1(ssl->config->param, param);
}

X509_VERIFY_PARAM *SSL_CTX_get0_param(SSL_CTX *ctx) {
  check_ssl_ctx_x509_method(ctx);
  return ctx->param;
}

X509_VERIFY_PARAM *SSL_get0_param(SSL *ssl) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    assert(ssl->config);
    return 0;
  }
  return ssl->config->param;
}

int SSL_get_verify_depth(const SSL *ssl) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    assert(ssl->config);
    return 0;
  }
  return X509_VERIFY_PARAM_get_depth(ssl->config->param);
}

int (*SSL_get_verify_callback(const SSL *ssl))(int, X509_STORE_CTX *) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    assert(ssl->config);
    return 0;
  }
  return ssl->config->verify_callback;
}

int SSL_CTX_get_verify_mode(const SSL_CTX *ctx) {
  check_ssl_ctx_x509_method(ctx);
  return ctx->verify_mode;
}

int SSL_CTX_get_verify_depth(const SSL_CTX *ctx) {
  check_ssl_ctx_x509_method(ctx);
  return X509_VERIFY_PARAM_get_depth(ctx->param);
}

int (*SSL_CTX_get_verify_callback(const SSL_CTX *ctx))(
    int ok, X509_STORE_CTX *store_ctx) {
  check_ssl_ctx_x509_method(ctx);
  return ctx->default_verify_callback;
}

void SSL_set_verify(SSL *ssl, int mode,
                    int (*callback)(int ok, X509_STORE_CTX *store_ctx)) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return;
  }
  ssl->config->verify_mode = mode;
  if (callback != NULL) {
    ssl->config->verify_callback = callback;
  }
}

void SSL_set_verify_depth(SSL *ssl, int depth) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return;
  }
  X509_VERIFY_PARAM_set_depth(ssl->config->param, depth);
}

void SSL_CTX_set_cert_verify_callback(SSL_CTX *ctx,
                                      int (*cb)(X509_STORE_CTX *store_ctx,
                                                void *arg),
                                      void *arg) {
  check_ssl_ctx_x509_method(ctx);
  ctx->app_verify_callback = cb;
  ctx->app_verify_arg = arg;
}

void SSL_CTX_set_verify(SSL_CTX *ctx, int mode,
                        int (*cb)(int, X509_STORE_CTX *)) {
  check_ssl_ctx_x509_method(ctx);
  ctx->verify_mode = mode;
  ctx->default_verify_callback = cb;
}

void SSL_CTX_set_verify_depth(SSL_CTX *ctx, int depth) {
  check_ssl_ctx_x509_method(ctx);
  X509_VERIFY_PARAM_set_depth(ctx->param, depth);
}

int SSL_CTX_set_default_verify_paths(SSL_CTX *ctx) {
  check_ssl_ctx_x509_method(ctx);
  return X509_STORE_set_default_paths(ctx->cert_store);
}

int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *ca_file,
                                  const char *ca_dir) {
  check_ssl_ctx_x509_method(ctx);
  return X509_STORE_load_locations(ctx->cert_store, ca_file, ca_dir);
}

void SSL_set_verify_result(SSL *ssl, long result) {
  check_ssl_x509_method(ssl);
  if (result != X509_V_OK) {
    abort();
  }
}

long SSL_get_verify_result(const SSL *ssl) {
  check_ssl_x509_method(ssl);
  SSL_SESSION *session = SSL_get_session(ssl);
  if (session == NULL) {
    return X509_V_ERR_INVALID_CALL;
  }
  return session->verify_result;
}

X509_STORE *SSL_CTX_get_cert_store(const SSL_CTX *ctx) {
  check_ssl_ctx_x509_method(ctx);
  return ctx->cert_store;
}

void SSL_CTX_set_cert_store(SSL_CTX *ctx, X509_STORE *store) {
  check_ssl_ctx_x509_method(ctx);
  X509_STORE_free(ctx->cert_store);
  ctx->cert_store = store;
}

static int ssl_use_certificate(CERT *cert, X509 *x) {
  if (x == NULL) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_PASSED_NULL_PARAMETER);
    return 0;
  }

  UniquePtr<CRYPTO_BUFFER> buffer = x509_to_buffer(x);
  if (!buffer) {
    return 0;
  }

  return ssl_set_cert(cert, std::move(buffer));
}

int SSL_use_certificate(SSL *ssl, X509 *x) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return ssl_use_certificate(ssl->config->cert.get(), x);
}

int SSL_CTX_use_certificate(SSL_CTX *ctx, X509 *x) {
  check_ssl_ctx_x509_method(ctx);
  return ssl_use_certificate(ctx->cert.get(), x);
}

// ssl_cert_cache_leaf_cert sets |cert->x509_leaf|, if currently NULL, from the
// first element of |cert->chain|.
static int ssl_cert_cache_leaf_cert(CERT *cert) {
  assert(cert->x509_method);

  if (cert->x509_leaf != NULL ||
      cert->chain.get() == NULL) {
    return 1;
  }

  CRYPTO_BUFFER *leaf = sk_CRYPTO_BUFFER_value(cert->chain.get(), 0);
  if (!leaf) {
    return 1;
  }

  cert->x509_leaf = X509_parse_from_buffer(leaf);
  return cert->x509_leaf != NULL;
}

static X509 *ssl_cert_get0_leaf(CERT *cert) {
  if (cert->x509_leaf == NULL &&
      !ssl_cert_cache_leaf_cert(cert)) {
    return NULL;
  }

  return cert->x509_leaf;
}

X509 *SSL_get_certificate(const SSL *ssl) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    assert(ssl->config);
    return 0;
  }
  return ssl_cert_get0_leaf(ssl->config->cert.get());
}

X509 *SSL_CTX_get0_certificate(const SSL_CTX *ctx) {
  check_ssl_ctx_x509_method(ctx);
  MutexWriteLock lock(const_cast<CRYPTO_MUTEX*>(&ctx->lock));
  return ssl_cert_get0_leaf(ctx->cert.get());
}

static int ssl_cert_set0_chain(CERT *cert, STACK_OF(X509) *chain) {
  if (!ssl_cert_set_chain(cert, chain)) {
    return 0;
  }

  sk_X509_pop_free(chain, X509_free);
  ssl_crypto_x509_cert_flush_cached_chain(cert);
  return 1;
}

static int ssl_cert_set1_chain(CERT *cert, STACK_OF(X509) *chain) {
  if (!ssl_cert_set_chain(cert, chain)) {
    return 0;
  }

  ssl_crypto_x509_cert_flush_cached_chain(cert);
  return 1;
}

static int ssl_cert_append_cert(CERT *cert, X509 *x509) {
  assert(cert->x509_method);

  UniquePtr<CRYPTO_BUFFER> buffer = x509_to_buffer(x509);
  if (!buffer) {
    return 0;
  }

  if (cert->chain != NULL) {
    return PushToStack(cert->chain.get(), std::move(buffer));
  }

  cert->chain = new_leafless_chain();
  if (!cert->chain ||
      !PushToStack(cert->chain.get(), std::move(buffer))) {
    cert->chain.reset();
    return 0;
  }

  return 1;
}

static int ssl_cert_add0_chain_cert(CERT *cert, X509 *x509) {
  if (!ssl_cert_append_cert(cert, x509)) {
    return 0;
  }

  X509_free(cert->x509_stash);
  cert->x509_stash = x509;
  ssl_crypto_x509_cert_flush_cached_chain(cert);
  return 1;
}

static int ssl_cert_add1_chain_cert(CERT *cert, X509 *x509) {
  if (!ssl_cert_append_cert(cert, x509)) {
    return 0;
  }

  ssl_crypto_x509_cert_flush_cached_chain(cert);
  return 1;
}

int SSL_CTX_set0_chain(SSL_CTX *ctx, STACK_OF(X509) *chain) {
  check_ssl_ctx_x509_method(ctx);
  return ssl_cert_set0_chain(ctx->cert.get(), chain);
}

int SSL_CTX_set1_chain(SSL_CTX *ctx, STACK_OF(X509) *chain) {
  check_ssl_ctx_x509_method(ctx);
  return ssl_cert_set1_chain(ctx->cert.get(), chain);
}

int SSL_set0_chain(SSL *ssl, STACK_OF(X509) *chain) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return ssl_cert_set0_chain(ssl->config->cert.get(), chain);
}

int SSL_set1_chain(SSL *ssl, STACK_OF(X509) *chain) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return ssl_cert_set1_chain(ssl->config->cert.get(), chain);
}

int SSL_CTX_add0_chain_cert(SSL_CTX *ctx, X509 *x509) {
  check_ssl_ctx_x509_method(ctx);
  return ssl_cert_add0_chain_cert(ctx->cert.get(), x509);
}

int SSL_CTX_add1_chain_cert(SSL_CTX *ctx, X509 *x509) {
  check_ssl_ctx_x509_method(ctx);
  return ssl_cert_add1_chain_cert(ctx->cert.get(), x509);
}

int SSL_CTX_add_extra_chain_cert(SSL_CTX *ctx, X509 *x509) {
  check_ssl_ctx_x509_method(ctx);
  return SSL_CTX_add0_chain_cert(ctx, x509);
}

int SSL_add0_chain_cert(SSL *ssl, X509 *x509) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return ssl_cert_add0_chain_cert(ssl->config->cert.get(), x509);
}

int SSL_add1_chain_cert(SSL *ssl, X509 *x509) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return ssl_cert_add1_chain_cert(ssl->config->cert.get(), x509);
}

int SSL_CTX_clear_chain_certs(SSL_CTX *ctx) {
  check_ssl_ctx_x509_method(ctx);
  return SSL_CTX_set0_chain(ctx, NULL);
}

int SSL_CTX_clear_extra_chain_certs(SSL_CTX *ctx) {
  check_ssl_ctx_x509_method(ctx);
  return SSL_CTX_clear_chain_certs(ctx);
}

int SSL_clear_chain_certs(SSL *ssl) {
  check_ssl_x509_method(ssl);
  return SSL_set0_chain(ssl, NULL);
}

// ssl_cert_cache_chain_certs fills in |cert->x509_chain| from elements 1.. of
// |cert->chain|.
static int ssl_cert_cache_chain_certs(CERT *cert) {
  assert(cert->x509_method);

  if (cert->x509_chain != nullptr ||
      cert->chain.get() == nullptr ||
      sk_CRYPTO_BUFFER_num(cert->chain.get()) < 2) {
    return 1;
  }

  UniquePtr<STACK_OF(X509)> chain(sk_X509_new_null());
  if (!chain) {
    return 0;
  }

  for (size_t i = 1; i < sk_CRYPTO_BUFFER_num(cert->chain.get()); i++) {
    CRYPTO_BUFFER *buffer = sk_CRYPTO_BUFFER_value(cert->chain.get(), i);
    UniquePtr<X509> x509(X509_parse_from_buffer(buffer));
    if (!x509 ||
        !PushToStack(chain.get(), std::move(x509))) {
      return 0;
    }
  }

  cert->x509_chain = chain.release();
  return 1;
}

int SSL_CTX_get0_chain_certs(const SSL_CTX *ctx, STACK_OF(X509) **out_chain) {
  check_ssl_ctx_x509_method(ctx);
  MutexWriteLock lock(const_cast<CRYPTO_MUTEX*>(&ctx->lock));
  if (!ssl_cert_cache_chain_certs(ctx->cert.get())) {
    *out_chain = NULL;
    return 0;
  }

  *out_chain = ctx->cert->x509_chain;
  return 1;
}

int SSL_CTX_get_extra_chain_certs(const SSL_CTX *ctx,
                                  STACK_OF(X509) **out_chain) {
  return SSL_CTX_get0_chain_certs(ctx, out_chain);
}

int SSL_get0_chain_certs(const SSL *ssl, STACK_OF(X509) **out_chain) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    assert(ssl->config);
    return 0;
  }
  if (!ssl_cert_cache_chain_certs(ssl->config->cert.get())) {
    *out_chain = NULL;
    return 0;
  }

  *out_chain = ssl->config->cert->x509_chain;
  return 1;
}

SSL_SESSION *d2i_SSL_SESSION_bio(BIO *bio, SSL_SESSION **out) {
  uint8_t *data;
  size_t len;
  if (!BIO_read_asn1(bio, &data, &len, 1024 * 1024)) {
    return 0;
  }
  bssl::UniquePtr<uint8_t> free_data(data);
  const uint8_t *ptr = data;
  return d2i_SSL_SESSION(out, &ptr, static_cast<long>(len));
}

int i2d_SSL_SESSION_bio(BIO *bio, const SSL_SESSION *session) {
  uint8_t *data;
  size_t len;
  if (!SSL_SESSION_to_bytes(session, &data, &len)) {
    return 0;
  }
  bssl::UniquePtr<uint8_t> free_data(data);
  return BIO_write_all(bio, data, len);
}

IMPLEMENT_PEM_rw(SSL_SESSION, SSL_SESSION, PEM_STRING_SSL_SESSION, SSL_SESSION)

SSL_SESSION *d2i_SSL_SESSION(SSL_SESSION **a, const uint8_t **pp, long length) {
  if (length < 0) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
    return NULL;
  }

  CBS cbs;
  CBS_init(&cbs, *pp, length);

  UniquePtr<SSL_SESSION> ret = SSL_SESSION_parse(&cbs, &ssl_crypto_x509_method,
                                                 NULL /* no buffer pool */);
  if (!ret) {
    return NULL;
  }

  if (a) {
    SSL_SESSION_free(*a);
    *a = ret.get();
  }
  *pp = CBS_data(&cbs);
  return ret.release();
}

STACK_OF(X509_NAME) *SSL_dup_CA_list(STACK_OF(X509_NAME) *list) {
  return sk_X509_NAME_deep_copy(list, X509_NAME_dup, X509_NAME_free);
}

static void set_client_CA_list(UniquePtr<STACK_OF(CRYPTO_BUFFER)> *ca_list,
                               const STACK_OF(X509_NAME) *name_list,
                               CRYPTO_BUFFER_POOL *pool) {
  UniquePtr<STACK_OF(CRYPTO_BUFFER)> buffers(sk_CRYPTO_BUFFER_new_null());
  if (!buffers) {
    return;
  }

  for (X509_NAME *name : name_list) {
    uint8_t *outp = NULL;
    int len = i2d_X509_NAME(name, &outp);
    if (len < 0) {
      return;
    }

    UniquePtr<CRYPTO_BUFFER> buffer(CRYPTO_BUFFER_new(outp, len, pool));
    OPENSSL_free(outp);
    if (!buffer ||
        !PushToStack(buffers.get(), std::move(buffer))) {
      return;
    }
  }

  *ca_list = std::move(buffers);
}

void SSL_set_client_CA_list(SSL *ssl, STACK_OF(X509_NAME) *name_list) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return;
  }
  ssl->ctx->x509_method->ssl_flush_cached_client_CA(ssl->config.get());
  set_client_CA_list(&ssl->config->client_CA, name_list, ssl->ctx->pool);
  sk_X509_NAME_pop_free(name_list, X509_NAME_free);
}

void SSL_CTX_set_client_CA_list(SSL_CTX *ctx, STACK_OF(X509_NAME) *name_list) {
  check_ssl_ctx_x509_method(ctx);
  ctx->x509_method->ssl_ctx_flush_cached_client_CA(ctx);
  set_client_CA_list(&ctx->client_CA, name_list, ctx->pool);
  sk_X509_NAME_pop_free(name_list, X509_NAME_free);
}

static STACK_OF(X509_NAME) *
    buffer_names_to_x509(const STACK_OF(CRYPTO_BUFFER) *names,
                         STACK_OF(X509_NAME) **cached) {
  if (names == NULL) {
    return NULL;
  }

  if (*cached != NULL) {
    return *cached;
  }

  UniquePtr<STACK_OF(X509_NAME)> new_cache(sk_X509_NAME_new_null());
  if (!new_cache) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
    return NULL;
  }

  for (const CRYPTO_BUFFER *buffer : names) {
    const uint8_t *inp = CRYPTO_BUFFER_data(buffer);
    UniquePtr<X509_NAME> name(
        d2i_X509_NAME(nullptr, &inp, CRYPTO_BUFFER_len(buffer)));
    if (!name ||
        inp != CRYPTO_BUFFER_data(buffer) + CRYPTO_BUFFER_len(buffer) ||
        !PushToStack(new_cache.get(), std::move(name))) {
      return NULL;
    }
  }

  *cached = new_cache.release();
  return *cached;
}

STACK_OF(X509_NAME) *SSL_get_client_CA_list(const SSL *ssl) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    assert(ssl->config);
    return NULL;
  }
  // For historical reasons, this function is used both to query configuration
  // state on a server as well as handshake state on a client. However, whether
  // |ssl| is a client or server is not known until explicitly configured with
  // |SSL_set_connect_state|. If |do_handshake| is NULL, |ssl| is in an
  // indeterminate mode and |ssl->server| is unset.
  if (ssl->do_handshake != NULL && !ssl->server) {
    if (ssl->s3->hs != NULL) {
      return buffer_names_to_x509(ssl->s3->hs->ca_names.get(),
                                  &ssl->s3->hs->cached_x509_ca_names);
    }

    return NULL;
  }

  if (ssl->config->client_CA != NULL) {
    return buffer_names_to_x509(
        ssl->config->client_CA.get(),
        (STACK_OF(X509_NAME) **)&ssl->config->cached_x509_client_CA);
  }
  return SSL_CTX_get_client_CA_list(ssl->ctx.get());
}

STACK_OF(X509_NAME) *SSL_CTX_get_client_CA_list(const SSL_CTX *ctx) {
  check_ssl_ctx_x509_method(ctx);
  // This is a logically const operation that may be called on multiple threads,
  // so it needs to lock around updating |cached_x509_client_CA|.
  MutexWriteLock lock(const_cast<CRYPTO_MUTEX *>(&ctx->lock));
  return buffer_names_to_x509(
      ctx->client_CA.get(),
      const_cast<STACK_OF(X509_NAME) **>(&ctx->cached_x509_client_CA));
}

static int add_client_CA(UniquePtr<STACK_OF(CRYPTO_BUFFER)> *names, X509 *x509,
                         CRYPTO_BUFFER_POOL *pool) {
  if (x509 == NULL) {
    return 0;
  }

  uint8_t *outp = NULL;
  int len = i2d_X509_NAME(X509_get_subject_name(x509), &outp);
  if (len < 0) {
    return 0;
  }

  UniquePtr<CRYPTO_BUFFER> buffer(CRYPTO_BUFFER_new(outp, len, pool));
  OPENSSL_free(outp);
  if (!buffer) {
    return 0;
  }

  int alloced = 0;
  if ((*names).get() == nullptr) {
    names->reset(sk_CRYPTO_BUFFER_new_null());
    alloced = 1;

    if ((*names).get() == NULL) {
      return 0;
    }
  }

  if (!PushToStack(names->get(), std::move(buffer))) {
    if (alloced) {
      names->reset();
    }
    return 0;
  }

  return 1;
}

int SSL_add_client_CA(SSL *ssl, X509 *x509) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  if (!add_client_CA(&ssl->config->client_CA, x509, ssl->ctx->pool)) {
    return 0;
  }

  ssl_crypto_x509_ssl_flush_cached_client_CA(ssl->config.get());
  return 1;
}

int SSL_CTX_add_client_CA(SSL_CTX *ctx, X509 *x509) {
  check_ssl_ctx_x509_method(ctx);
  if (!add_client_CA(&ctx->client_CA, x509, ctx->pool)) {
    return 0;
  }

  ssl_crypto_x509_ssl_ctx_flush_cached_client_CA(ctx);
  return 1;
}

static int do_client_cert_cb(SSL *ssl, void *arg) {
  // Should only be called during handshake, but check to be sure.
  if (!ssl->config) {
    assert(ssl->config);
    return -1;
  }

  if (ssl_has_certificate(ssl->s3->hs.get()) ||
      ssl->ctx->client_cert_cb == NULL) {
    return 1;
  }

  X509 *x509 = NULL;
  EVP_PKEY *pkey = NULL;
  int ret = ssl->ctx->client_cert_cb(ssl, &x509, &pkey);
  if (ret < 0) {
    return -1;
  }
  UniquePtr<X509> free_x509(x509);
  UniquePtr<EVP_PKEY> free_pkey(pkey);

  if (ret != 0) {
    if (!SSL_use_certificate(ssl, x509) ||
        !SSL_use_PrivateKey(ssl, pkey)) {
      return 0;
    }
  }

  return 1;
}

void SSL_CTX_set_client_cert_cb(SSL_CTX *ctx, int (*cb)(SSL *ssl,
                                                        X509 **out_x509,
                                                        EVP_PKEY **out_pkey)) {
  check_ssl_ctx_x509_method(ctx);
  // Emulate the old client certificate callback with the new one.
  SSL_CTX_set_cert_cb(ctx, do_client_cert_cb, NULL);
  ctx->client_cert_cb = cb;
}

static int set_cert_store(X509_STORE **store_ptr, X509_STORE *new_store,
                          int take_ref) {
  X509_STORE_free(*store_ptr);
  *store_ptr = new_store;

  if (new_store != NULL && take_ref) {
    X509_STORE_up_ref(new_store);
  }

  return 1;
}

int SSL_get_ex_data_X509_STORE_CTX_idx(void) {
  // The ex_data index to go from |X509_STORE_CTX| to |SSL| always uses the
  // reserved app_data slot. Before ex_data was introduced, app_data was used.
  // Avoid breaking any software which assumes |X509_STORE_CTX_get_app_data|
  // works.
  return 0;
}

int SSL_CTX_set0_verify_cert_store(SSL_CTX *ctx, X509_STORE *store) {
  check_ssl_ctx_x509_method(ctx);
  return set_cert_store(&ctx->cert->verify_store, store, 0);
}

int SSL_CTX_set1_verify_cert_store(SSL_CTX *ctx, X509_STORE *store) {
  check_ssl_ctx_x509_method(ctx);
  return set_cert_store(&ctx->cert->verify_store, store, 1);
}

int SSL_set0_verify_cert_store(SSL *ssl, X509_STORE *store) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return set_cert_store(&ssl->config->cert->verify_store, store, 0);
}

int SSL_set1_verify_cert_store(SSL *ssl, X509_STORE *store) {
  check_ssl_x509_method(ssl);
  if (!ssl->config) {
    return 0;
  }
  return set_cert_store(&ssl->config->cert->verify_store, store, 1);
}

int SSL_alert_from_verify_result(long result) {
  switch (result) {
    case X509_V_ERR_CERT_CHAIN_TOO_LONG:
    case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
    case X509_V_ERR_INVALID_CA:
    case X509_V_ERR_PATH_LENGTH_EXCEEDED:
    case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
    case X509_V_ERR_UNABLE_TO_GET_CRL:
    case X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER:
    case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
    case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
    case X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
      return SSL_AD_UNKNOWN_CA;

    case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
    case X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE:
    case X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
    case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
    case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
    case X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD:
    case X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
    case X509_V_ERR_CERT_UNTRUSTED:
    case X509_V_ERR_CERT_REJECTED:
    case X509_V_ERR_HOSTNAME_MISMATCH:
    case X509_V_ERR_EMAIL_MISMATCH:
    case X509_V_ERR_IP_ADDRESS_MISMATCH:
      return SSL_AD_BAD_CERTIFICATE;

    case X509_V_ERR_CERT_SIGNATURE_FAILURE:
    case X509_V_ERR_CRL_SIGNATURE_FAILURE:
      return SSL_AD_DECRYPT_ERROR;

    case X509_V_ERR_CERT_HAS_EXPIRED:
    case X509_V_ERR_CERT_NOT_YET_VALID:
    case X509_V_ERR_CRL_HAS_EXPIRED:
    case X509_V_ERR_CRL_NOT_YET_VALID:
      return SSL_AD_CERTIFICATE_EXPIRED;

    case X509_V_ERR_CERT_REVOKED:
      return SSL_AD_CERTIFICATE_REVOKED;

    case X509_V_ERR_UNSPECIFIED:
    case X509_V_ERR_OUT_OF_MEM:
    case X509_V_ERR_INVALID_CALL:
    case X509_V_ERR_STORE_LOOKUP:
      return SSL_AD_INTERNAL_ERROR;

    case X509_V_ERR_APPLICATION_VERIFICATION:
      return SSL_AD_HANDSHAKE_FAILURE;

    case X509_V_ERR_INVALID_PURPOSE:
      return SSL_AD_UNSUPPORTED_CERTIFICATE;

    default:
      return SSL_AD_CERTIFICATE_UNKNOWN;
  }
}
