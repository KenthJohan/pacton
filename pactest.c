#include <inttypes.h>
#include "csc_debug.h"
#include "csc_dlist.h"
#include "csc_htable.h"
#include "csc_str.h"
#include "csc_malloc_file.h"


void parse (struct csc_htable * t, char * code)
{
	char * p = code;
	while (*p)
	{
		str_skip_space (&p);
		char * key = p;
		str_skip_alnum (&p);
		if (isspace (*p))
		{
			*p = '\0';
			p++;
			intmax_t v = str_to_imax (&p, 10);
			csc_htable_set_imax (t, key, v);
		}
		str_skip_until (&p, "\n\r");
		str_skip_after (&p, "\n\r");
	}
}


int main (int argc, char * argv [])
{
	ASSERT (argc);
	ASSERT (argv);
	struct csc_htable t;
	struct csc_htable_entry * e;
	t.size = 4;
	csc_htable_init (&t);
	char * code = csc_malloc_file ("../pacton/enum2.txt");
	parse (&t, code);
	e = csc_htable_find (&t, "MENU1");
	printf ("%s %ji\n", e->key, e->ival);
	e = csc_htable_find (&t, "MENU2");
	printf ("%s %ji\n", e->key, e->ival);
	e = csc_htable_find (&t, "MENU3");
	printf ("%s %ji\n", e->key, e->ival);
	e = csc_htable_find (&t, "MENU4");
	printf ("%s %ji\n", e->key, e->ival);
}
