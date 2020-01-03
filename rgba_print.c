/* see LICENSE file for copyright and license details. */
#include <stdio.h>
#include "librgba.h"

#define CAP(X, A, B) \
	((X) < (A) ? (A) : (X) > (B) ? (B) : (X))

int rgba_print(const struct rgba * const rgba, char *buf) {
	if (rgba->a > 0.999) {
		return sprintf(buf, "rgb(%d,%d,%d)",
			(int)(0.5 + CAP(rgba->r, 0., 1.) * 255.),
			(int)(0.5 + CAP(rgba->g, 0., 1.) * 255.),
			(int)(0.5 + CAP(rgba->b, 0., 1.) * 255.));
	}
	else {
		return sprintf(buf, "rgba(%d,%d,%d,%.17g)",
			(int)(0.5 + CAP(rgba->r, 0., 1.) * 255.),
			(int)(0.5 + CAP(rgba->g, 0., 1.) * 255.),
			(int)(0.5 + CAP(rgba->b, 0., 1.) * 255.),
			CAP(rgba->a, 0., 1.));
	}
}

