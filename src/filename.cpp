/* filename.c: Function manipulate file names
   Was: find-suffix, extend-fname, make-suffix, remove-suffx  
   substring, concat3 */

/* remove-suffx.c: remove any suffix.

Copyright (C) 1999 Free Software Foundation, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* Def: HAVE_CONFIG_H */

#include "filename.h"
#include "xstd.h"
#include <string.h>

/* Return a fresh copy of SOURCE[START..LIMIT], or NULL if LIMIT<START.
   If LIMIT>strlen(START), it is reassigned. */
static char* substring (char* source, const unsigned start, const unsigned limit);

/* Return a fresh copy of S1 followed by S2, et al.  */
static char* concat3 (char*, char*, char*);

char*
find_suffix (char* name)
{
  char* dot_pos = strrchr (name, '.');
#ifdef WIN32
  char* slash_pos = strrchr (name, '\\');
#else
  char* slash_pos = strrchr (name, '/');
#endif

  /* If the name is `foo' or `/foo.bar/baz', we have no extension.  */
  return
    dot_pos == NULL || dot_pos < slash_pos
    ? NULL
    : dot_pos + 1;
}

char*
extend_filename (char* name, char* default_suffix)
{
  char* new_s;
  char* suffix = find_suffix (name);

  new_s = suffix == NULL
          ? concat3 (name, ".", default_suffix) : name;
  return new_s;
}

char*
make_suffix (char* s, char* new_suffix)
{
  char* new_s;
  char* old_suffix = find_suffix (s);

  if (old_suffix == NULL)
    new_s = concat3 (s, ".", new_suffix);
  else
    {
      size_t length_through_dot = old_suffix - s;

      XMALLOC (new_s, length_through_dot + strlen (new_suffix) + 1);
      strncpy (new_s, s, length_through_dot);
      strcpy (new_s + length_through_dot, new_suffix);
    }

  return new_s;
}

char*
remove_suffix (char* s)
{
  char* suffix = find_suffix (s);

  return suffix == NULL ? s : suffix - 2 - s < 0 ? NULL : substring (s, 0, (unsigned)(suffix - 2 - s));
}

/* From substring.c */
static char*
substring (char* source, const unsigned start, const unsigned limit)
{
  char* result;
  unsigned this_char;
  size_t length = strlen (source);
  size_t lim = limit;

  /* Upper bound out of range? */
  if (lim >= length)
    lim = length - 1;

  /* Null substring? */
  if (start > lim)
    return "";

  /* The `2' here is one for the null and one for limit - start inclusive. */
  XMALLOC (result, lim - start + 2);

  for (this_char = start; this_char <= lim; this_char++)
    result[this_char - start] = source[this_char];

  result[this_char - start] = 0;

  return result;
}

static char*
concat3 (char* s1, char* s2, char* s3)
{
  char* answer;
  XMALLOC (answer, strlen (s1) + strlen (s2) + strlen (s3) + 1);
  strcpy (answer, s1);
  strcat (answer, s2);
  strcat (answer, s3);

  return answer;
}
