/* types.h: general types
   Copyright (C) 2000, 2001 Martin Weber

   The author can be contacted at <martweb@gmx.net>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#ifndef AT_TYPES_H
#define AT_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <string>

//#ifdef __cplusplus
//extern "C" {
//#endif /* __cplusplus */

// bad place, but...
#define PACKAGE_URL "www.example.com"
#define PACKAGE_VERSION "0.0.2"


// mimicry GLIB GError
typedef struct _at_error
{
    int domain;
    int code;
    std::string message;
} at_error;

// Errors:
#define AT_ERROR_WRONG_COLOR_STRING 1

// Error domain (unused at all. glib rudimnet)
#define AT_ERROR 0

static void at_set_error(int domain, int code, const std::string& message)
{
	at_error exception;
	exception.domain = domain;
	exception.code = code;
	exception.message = message;

	throw  exception;
}

// BOOL support
#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif

/* Cartesian points.  */
typedef struct _at_coord
{
  unsigned short x, y;
} at_coord;

typedef struct _at_real_coord
{
  float x, y, z;
} at_real_coord;

// mimicry GLib boilerplate
typedef void (*_at_destroy_notifier_callback) (void* data);

typedef struct _at_string_tuple
{
	std::string first;
	std::string second;

	_at_string_tuple(){}
	_at_string_tuple(const std::string& f, const std::string& s) :first(f), second(s){}
	_at_string_tuple(const _at_string_tuple& src) :first(src.first), second(src.second){}

	_at_string_tuple& operator=(const _at_string_tuple& src){ first = src.first; second = src.second; return *this; }

} at_string_tuple;

//#ifdef __cplusplus
//}
//#endif /* __cplusplus */

#endif /* not AT_TYPES_H */
