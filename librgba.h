/* see LICENSE file for copyright and license details. */
#ifndef LIBRGBA_H
#define LIBRGBA_H

#if defined(__cplusplus)
extern "C" {
#endif

struct rgba {
	double r;
	double g;
	double b;
	double a;
};

extern int rgba_clone(struct rgba *,  const struct rgba * const);
extern int rgba_equal(const struct rgba * const, const struct rgba * const);
extern int rgba_parse(struct rgba *, const char *);
extern int rgba_print(const struct rgba * const, char *);

#if defined(__cplusplus)
}
#endif
#endif

