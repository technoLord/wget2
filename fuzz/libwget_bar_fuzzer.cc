/*
 * Copyright(c) 2017 Free Software Foundation, Inc.
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
 */

#include "../config.h"

#include <assert.h> // assert
#include <stdint.h> // uint8_t
#include <stdlib.h> // malloc, free
#include <string.h> // memcpy

#include "wget.h"

extern "C" int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	char *in = (char *) malloc(size + 1);

	assert(in != NULL);

	// 0 terminate
	memcpy(in, data, size);
	in[size] = 0;

	wget_bar_t *bar = wget_bar_init(NULL, 3);
	wget_bar_slot_begin(bar, 1, "test", 64000);
	wget_bar_slot_downloaded(bar, 1, atoi(in));
	wget_bar_printf(bar, 1, "%s", in);
	wget_bar_write_line(bar, (char *) data, size);
	wget_bar_free(&bar);

	free(in);

	return 0;
}