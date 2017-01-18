/* xfopen.c: fopen and fclose with error checking. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* Def: HAVE_CONFIG_H */

#include "xstd.h"
#include <errno.h>

FILE *
xfopen (char* filename, char* mode)
{
  FILE *f;

  if (strcmp(filename, "-") == 0)
    f = stdin;
  else
    {
      f = fopen (filename, mode);
      if (f == NULL)
	FATAL_PERROR (filename);
    }

  return f;
}


void
xfclose (FILE *f, char* filename)
{
  if (f != stdin)
    {
      if (fclose (f) == EOF)
	FATAL_PERROR (filename);
    }
}

void
xfseek (FILE *f, long offset, int wherefrom, char* filename)
{
  if (fseek (f, offset, wherefrom) < 0)
    FATAL_PERROR (filename);
}

