/*
 * Copyright(c) 2013-2014 Tim Ruehsen
 * Copyright(c) 2015-2018 Free Software Foundation, Inc.
 *
 * This file is part of libwget.
 *
 * Libwget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Libwget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libwget.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * Test suite function library header
 *
 * Changelog
 * 10.03.2013  Tim Ruehsen  created
 *
 * Test suite function library
 *
 * To create the X.509 stuff, I followed the instructions at
 *   gnutls.org/manual/html_node/gnutls_002dserv-Invocation.html
 *
 */

#ifndef TESTS_LIBTEST_H
#define TESTS_LIBTEST_H

#include <wget.h>

// gnulib convenience header for libintl.h, turn of annoying warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wundef"
#include <gettext.h>
#pragma GCC diagnostic pop

#ifdef ENABLE_NLS
#	define _(STRING) gettext(STRING)
#else
#	define _(STRING) STRING
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#define WGET_TEST_EXIT_SKIP 77

// defines for wget_test_start_http_server()
#define WGET_TEST_RESPONSE_URLS 1002
#define WGET_TEST_HTTPS_ONLY 1003
#define WGET_TEST_HTTP_ONLY 1004
#define WGET_TEST_HTTPS_REJECT_CONNECTIONS 1005
#define WGET_TEST_FEATURE_MHD 1101
#define WGET_TEST_FEATURE_TLS 1102
#define WGET_TEST_FEATURE_IDN 1103
#define WGET_TEST_FEATURE_PLUGIN 1104

// defines for wget_test()
#define WGET_TEST_REQUEST_URL 2001
#define WGET_TEST_OPTIONS 2002
#define WGET_TEST_EXPECTED_ERROR_CODE 2003
#define WGET_TEST_EXPECTED_FILES 2004
#define WGET_TEST_EXISTING_FILES 2005
#define WGET_TEST_KEEP_TMPFILES 2006
#define WGET_TEST_REQUEST_URLS 2007
#define WGET_TEST_EXECUTABLE 2008
#define WGET_TEST_SERVER_SEND_CONTENT_LENGTH 2009

// defines for wget_test_check_file_system()
#define WGET_TEST_FS_CASEMATTERS 3001 // file system is case-sensitive

#define countof(a) (sizeof(a)/sizeof(*(a)))

#define TEST_OPAQUE_STR "11733b200778ce33060f31c9af70a870ba96ddd4"

G_GNUC_WGET_UNUSED static const char *WGET_TEST_SOME_HTML_BODY = "\
<html>\n\
<head>\n\
  <title>The Title</title>\n\
</head>\n\
<body>\n\
  <p>\n\
    Some text\n\
  </p>\n\
</body>\n\
</html>\n";

typedef struct {
	const char *
		name;
	const char *
		content;
	time_t
		timestamp;
	char
		restricted_mode;
	size_t
		content_length;
} wget_test_file_t;

typedef struct {
	const char *
		name;
	const char *
		code;
	const char *
		body;
	const char *
		headers[10];
	const char *
		request_headers[10];
	const char *
		expected_req_headers[10];
	const char *
		unexpected_req_headers[10];
	time_t
		modified;

	// auth fields
	const char *
		auth_method;
	const char *
		auth_username;
	const char *
		auth_password;
	size_t
		body_len; // The length of the body in bytes. 0 means use strlen(body)

	bool
		body_alloc : 1, // if body has been allocated internally (and need to be freed on exit)
		https_only : 1,
		http_only : 1;
	bool
		header_alloc[10]; // if header[n] has been allocated internally (and need to be freed on exit)
} wget_test_url_t;

WGETAPI void wget_test_stop_server(void);
WGETAPI void wget_test_start_server(int first_key, ...);
WGETAPI void wget_test(int first_key, ...);
WGETAPI int wget_test_check_file_system(void);
WGETAPI int wget_test_get_http_server_port(void) G_GNUC_WGET_PURE;
WGETAPI int wget_test_get_https_server_port(void) G_GNUC_WGET_PURE;

#if defined __clang__ || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
#	pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _LIBWGET_LIBTEST_H */
