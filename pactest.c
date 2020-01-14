#include <inttypes.h>
#include <stdint.h>
#include "csc_debug.h"
#include "csc_dlist.h"
#include "csc_htable.h"
#include "csc_str.h"
#include "csc_malloc_file.h"

enum csc_type
{
	CSC_TYPE_S8,
	CSC_TYPE_I8,
	CSC_TYPE_I16,
	CSC_TYPE_I32,
	CSC_TYPE_IMAX,
	CSC_TYPE_U8,
	CSC_TYPE_U16,
	CSC_TYPE_U32,
	CSC_TYPE_UMAX
};

enum csc_gval_flags
{
	CSC_GVAL_MALLOCATED
};

struct csc_gval
{
	uint8_t flags; //Not used
	uint8_t type; //Type of the value
	uint8_t pad1; //Padding to stop the warning
	uint8_t pad2; //Padding to stop the warning
	uint32_t pad3; //Padding to stop the warning
	char * pos; //Location of the value
	union
	{
		intmax_t val_imax;
		uintmax_t val_umax;
	};
};


//TODO: ji ju is not portable
void csc_gval_print (struct csc_gval * r)
{
	switch (r->type)
	{
	case CSC_TYPE_IMAX:
		printf ("%10s %10ji", r->pos, r->val_imax);
		break;
	case CSC_TYPE_UMAX:
		printf ("%10s %10ju", r->pos, r->val_umax);
		break;
	case CSC_TYPE_S8:
		printf ("%10s %10s", r->pos, r->pos);
		break;
	}
}


/*
' '	(0x20)	space (SPC)
'\t'	(0x09)	horizontal tab (TAB)
'\n'	(0x0a)	newline (LF)
'\v'	(0x0b)	vertical tab (VT)
'\f'	(0x0c)	feed (FF)
'\r'	(0x0d)	carriage return (CR)
*/
void parse1 (struct csc_htable * t, struct csc_gval r [], unsigned * rcount, char * p, char ** endptr)
{
	unsigned count = 0;
	while (1)
	{
		str_skip_space (&p);
		if (*p == '\0') {break;}
		if (count >= *rcount) {break;}
		//Negative number:
		if (p[0] == '-' && isdigit (p[1]))
		{
			r->flags = 0;
			r->type = CSC_TYPE_IMAX;
			r->pos = p;
			r->val_imax = str_to_imax (&p, 10);
		}
		//Natural number:
		else if (isdigit (p[0]))
		{
			r->flags = 0;
			r->type = CSC_TYPE_UMAX;
			r->pos = p;
			r->val_umax = str_to_umax (&p, 10);
		}
		//Identifier word:
		else if (isalpha (p[0]))
		{
			r->flags = 0;
			r->pos = p;
			str_skip_alnum (&p);
		}
		if (*p == '\n')
		{
			*p = '\0';
			p++;
			//TODO: Repeated ugly:
			count++;
			r++;
			break;
		}
		else if (*p != '\0')
		{
			*p = '\0';
			p++;
		}
		count++;
		r++;
	}
	*rcount = count;
	*endptr = p;
}


//TODO: Store the array of gval in the hash table
//and use the first gval string as hash key and the whole array as value.
void parse (struct csc_htable * t, struct csc_gval r [], unsigned rcount, char * code)
{
	unsigned n;
	char * endptr = code;

	while (*endptr)
	{
		n = rcount;
		parse1 (NULL, r, &n, endptr, &endptr);
		for (unsigned i = 0; i < n; ++i)
		{
			csc_gval_print (r + i);
			puts ("");
		}
		puts ("");
	}
}


void parse_enum (struct csc_htable * t, char * code)
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
	char * code;

	/*
	code = csc_malloc_file ("../pacton/enum2.txt");
	parse_enum (&t, code);
	e = csc_htable_find (&t, "MENU1");
	printf ("%s %ji\n", e->key, e->ival);
	e = csc_htable_find (&t, "MENU2");
	printf ("%s %ji\n", e->key, e->ival);
	e = csc_htable_find (&t, "MENU3");
	printf ("%s %ji\n", e->key, e->ival);
	e = csc_htable_find (&t, "MENU4");
	printf ("%s %ji\n", e->key, e->ival);
	free (code);
	*/


	code = csc_malloc_file ("../pacton/script2.txt");
	struct csc_gval r [10] = {0};
	parse (NULL, r, countof (r), code);
	free (code);


}
