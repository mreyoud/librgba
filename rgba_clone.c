/* see LICENSE file for copyright and license details. */
#include "librgba.h"

int rgba_clone(struct rgba *dst,  const struct rgba * const src) {
	dst->r = src->r;
	dst->g = src->g;
	dst->b = src->b;
	dst->a = src->a;
	return 0;
}

