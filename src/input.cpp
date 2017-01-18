/* input.c: interface for input handlers

   Copyright (C) 1999, 2000, 2001 Bernhard Herzog.
   Copyright (C) 2003 Masatake YAMATO
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* Def: HAVE_CONFIG_H */

#include "autotrace.h"
#include "private.h"
#include "input.h"
#include "xstd.h"
#include "filename.h"
#include "strgicmp.h"
#include "types.h"
#include <string.h>
// hail C++ 11
#include <map>
#include <string>
#include <memory>
#include <algorithm>


typedef struct _at_input_format_entry at_input_format_entry;
struct _at_input_format_entry {
  at_bitmap_reader  reader;
  std::string descr;
  _at_destroy_notifier_callback user_data_destroy_func;

  ~_at_input_format_entry()
  {
	  if (user_data_destroy_func)
		  user_data_destroy_func(reader.data);
  }
};

static std::map<std::string, std::shared_ptr<at_input_format_entry> > at_input_formats;

static std::shared_ptr<at_input_format_entry> at_input_format_new(const char * descr,
						   at_input_func reader,
						   void* user_data,
						   _at_destroy_notifier_callback user_data_destroy_func);

/**
 * at_input_init: 
 * Initialize at_input input plugin sub system. 
 *
 * Return value: 1 for success, else for failure
 **/
int
at_input_init (void)
{
  // NOP
  return 1;
}

static std::shared_ptr<at_input_format_entry> 
at_input_format_new(const char * descr,
		    at_input_func reader,
		    void* user_data,
		    _at_destroy_notifier_callback user_data_destroy_func)
{
	auto entry = std::make_shared<at_input_format_entry>();
 
	if (entry)
	{
		entry->reader.func 	    = reader;
		entry->reader.data        = user_data;
		entry->descr     		    = descr;
		entry->user_data_destroy_func = user_data_destroy_func;
	}
	return entry;
}


int
at_input_add_handler (const char* suffix, 
		      const char* description,
		      at_input_func reader)
{
  return at_input_add_handler_full (suffix, description, reader, 0,
				    NULL, NULL);
}

int
at_input_add_handler_full(const char* suffix,
const char* description,
at_input_func reader,
bool override_old,
void* user_data,
_at_destroy_notifier_callback user_data_destroy_func)
{
  std::string gsuffix;

  if (!suffix || !description || !reader)
    return 0;
  
  gsuffix      = suffix;
  std::transform(gsuffix.begin(), gsuffix.end(), gsuffix.begin(), ::tolower);
 
  if (!override_old &&
	  (at_input_formats.find(gsuffix) != at_input_formats.end()))
  {
	  return 1;
  }

  auto new_entry = at_input_format_new(description, reader,
	  user_data, user_data_destroy_func);

  if (!new_entry)
	  return 0;

  at_input_formats[gsuffix] = new_entry;

  return 1;
}

at_bitmap_reader*
at_input_get_handler (char* filename)
{
  char * ext = find_suffix (filename);
  if (ext == NULL)
     ext = "";

  return at_input_get_handler_by_suffix (ext);
}

at_bitmap_reader*
at_input_get_handler_by_suffix (char* suffix)
{
	if (!suffix)
		return NULL;

	std::string gsuffix = suffix;
	std::transform(gsuffix.begin(), gsuffix.end(), gsuffix.begin(), ::tolower);

	auto format_iter = at_input_formats.find(gsuffix);
	if (format_iter == at_input_formats.end())
		return NULL;

	return &(format_iter->second->reader);
}

std::vector<at_string_tuple> 
at_input_list_new (void)
{
	std::vector<at_string_tuple> list(at_input_formats.size());

	for (auto &entry : at_input_formats)
	{
		list.push_back(at_string_tuple(entry.first, entry.second->descr));
	}

	return list;
}

void
at_input_list_free(const char ** list)
{
  free((char **)list);
}

std::string 
at_input_shortlist (void)
{
	std::string shortcut;
	for (auto &entry : at_input_formats)
	{
		shortcut.append(entry.first + ", ");
	}
	return shortcut;
}
