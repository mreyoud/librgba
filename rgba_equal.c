/* see LICENSE file for copyright and license details. */
#include "librgba.h"

int rgba_equal(const struct rgba * const p1, const struct rgba * const p2) {
	return p1->r == p2->r && p1->g == p2->g &&
		p1->b == p2->b && p1->a == p2->a;
}

