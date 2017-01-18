/* output.c: interface for output handlers

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

/* TODO: Unify output codes and input codes. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* Def: HAVE_CONFIG_H */

#include "autotrace.h"
#include "private.h"
#include "output.h"
#include "xstd.h"
#include "filename.h"
#include "strgicmp.h"
#include <string.h>
// hail C++ 11
#include <map>
#include <string>
#include <memory>
#include <algorithm>

typedef struct _at_output_format_entry at_output_format_entry;
struct _at_output_format_entry {
  at_spline_writer writer;
  std::string descr;
  _at_destroy_notifier_callback user_data_destroy_func;

  ~_at_output_format_entry()
  {
	  if (user_data_destroy_func)
		  user_data_destroy_func(writer.data);
  }
};

static std::map<std::string, std::shared_ptr<at_output_format_entry> > at_output_formats;

static std::shared_ptr<at_output_format_entry> at_output_format_new(const char * descr,
						      at_output_func writer,
						      void* user_data,
						      _at_destroy_notifier_callback user_data_destroy_func);

int
at_output_init (void)
{
	// NOP
  return 1;
}


static std::shared_ptr<at_output_format_entry> 
at_output_format_new(const char * descr,
		     at_output_func writer,
		     void* user_data,
		     _at_destroy_notifier_callback user_data_destroy_func)
{
  auto entry = std::make_shared<at_output_format_entry>();
  if (entry)
    {
      entry->writer.func 	    = writer;
      entry->writer.data        = user_data;
      entry->descr     		    = descr;
      entry->user_data_destroy_func = user_data_destroy_func;
    }
  return entry;
}

int
at_output_add_handler (const char* suffix, 
		       const char* description,
		       at_output_func writer)
{
  return at_output_add_handler_full (suffix, description, writer, 0,
				     NULL, NULL);
}

int
at_output_add_handler_full (const char* suffix, 
			    const char* description,
			    at_output_func writer,
			    bool override_old,
			    void* user_data,
			    _at_destroy_notifier_callback user_data_destroy_func)
{
  std::string gsuffix;
  
  if (!suffix || !description || !writer)
	  return 0;
  
  gsuffix = suffix;
  std::transform(gsuffix.begin(), gsuffix.end(), gsuffix.begin(), ::tolower);
  
  if (	!override_old && 
		(at_output_formats.find(gsuffix) != at_output_formats.end()))
  {
	  return 1;
  }

  auto new_entry = at_output_format_new(description, writer,
				  user_data, user_data_destroy_func);
  if (!new_entry)
	  return 0;

  at_output_formats[gsuffix] = new_entry;
  return 1;
}

at_spline_writer*
at_output_get_handler (char* filename)
{
  char * ext = find_suffix (filename);
  if (ext == NULL)
     ext = "";

  return at_output_get_handler_by_suffix (ext);
}

at_spline_writer *
at_output_get_handler_by_suffix (char* suffix)
{
  if (!suffix)
    return NULL;
	
  std::string gsuffix = suffix;
  std::transform(gsuffix.begin(), gsuffix.end(), gsuffix.begin(), ::tolower);

  auto format_iter = at_output_formats.find(gsuffix);
  if (format_iter == at_output_formats.end())
	  return NULL;

  return &(format_iter->second->writer);
}

std::vector<at_string_tuple> 
at_output_list_new (void)
{
  std::vector<at_string_tuple> list(at_output_formats.size());
  
  for (auto &entry : at_output_formats)
  {
	  list.push_back(at_string_tuple(entry.first, entry.second->descr));
  }

  return list;
}

std::string 
at_output_shortlist (void)
{
	std::string shortcut;
	for (auto &entry : at_output_formats)
	{
		shortcut.append(entry.first + ", ");
	}
	return shortcut;
}

void
at_spline_list_foreach (at_spline_list_type * list,
			AtSplineListForeachFunc func,
			void* user_data)
{
  unsigned i;
  for (i = 0; i < AT_SPLINE_LIST_LENGTH(list); i++)
    {
      func (list, AT_SPLINE_LIST_ELT(list, i), i, user_data);
    }
}


void
at_spline_list_array_foreach (at_spline_list_array_type *list_array,
			      AtSplineListArrayForeachFunc func,
			      void* user_data)
{
  unsigned i;
  for (i = 0; i < AT_SPLINE_LIST_ARRAY_LENGTH(list_array); i++)
    {
      func (list_array, AT_SPLINE_LIST_ARRAY_ELT(list_array, i), i, user_data);
    }
}
