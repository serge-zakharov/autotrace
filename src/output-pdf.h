/* output-pdf.c: utility routines for PDF output

   Copyright (C) 1999, 2000, 2001 Martin Weber.

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

#ifndef OUTPUT_PDF_H
#define OUTPUT_PDF_H

#include <stdio.h>
#include "types.h"
#include "spline.h"

#include "output.h"

int output_pdf_writer (FILE* file, char* name,
		       int llx, int lly, int urx, int ury, 
		       at_output_opts_type * opts,
		       spline_list_array_type shape,
		       at_msg_func msg_func, 
		       void* msg_data,
		       void* user_data);

#endif /* not OUTPUT_PDF_H */
