/* see LICENSE file for copyright and license details. */
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "librgba.h"

#define	LEN(X)        (sizeof(X) / sizeof((X)[0]))
#define CAP(X, A, B)  ((X) < (A) ? (A) : (X) > (B) ? (B) : (X))

static struct {
	const char *name;
	struct rgba rgba;
} namedcolors[] = {
#define COLORDEF(NAME, R, G, B, A) \
	{ (NAME), { (R), (G), (B), (A) } },
#include "colordef.h"
};

int rgba_parse(struct rgba *rgba, const char *spec) {
	int has_alpha;
	double r, g, b, a;
	char *p, *s = (char *)spec;
	size_t i;
	if (!spec || !rgba)
		return -1;
	if (!strncmp(s, "rgba", 4))
		goto from_rgba;
	if (!strncmp(s, "rgb", 3))
		goto from_rgb;
	goto from_name;
from_rgba:
	has_alpha = 1;
	s += 4;
	goto from_spec;
from_rgb:
	has_alpha = 0;
	a = 1;
	s += 3;
	goto from_spec;
from_spec:
	while (*s == ' ') s++;
	if (*s != '(')
		return -1;
	s++;
	while (*s == ' ') s++;
	r = strtod(s, &p);
	if (errno == ERANGE || s == p || isinf(r) || isnan(r))
		return -1;
	s = p;
	while (*s == ' ') s++;
	if (*s == '%') {
		s++;
		r /= 100.;
	}
	else {
		r /= 255.;
	}
	while (*s == ' ') s++;
	if (*s != ',')
		return -1;
	s++;
	while (*s == ' ') s++;
	g = strtod(s, &p);
	if (errno == ERANGE || s == p || isinf(g) || isnan(g))
		return -1;
	s = p;
	while (*s == ' ') s++;
	if (*s == '%') {
		s++;
		g /= 100.;
	}
	else {
		g /= 255.;
	}
	while (*s == ' ') s++;
	if (*s != ',')
		return -1;
	s++;
	while (*s == ' ') s++;
	b = strtod(s, &p);
	if (errno == ERANGE || s == p || isinf(b) || isnan(b))
		return -1;
	s = p;
	while (*s == ' ') s++;
	if (*s == '%') {
		s++;
		b /= 100.;
	}
	else {
		b /= 255.;
	}
	while (*s == ' ') s++;
	if (has_alpha) {
		if (*s != ',')
			return -1;
		s++;
		while (*s == ' ') s++;
		a = strtod(s, &p);
		if (errno == ERANGE || p == s || isinf(a) || isnan(a))
			return -1;
		s = p;
		while (*s == ' ') s++;
	}
	if (*s != ')')
		return -1;
	s++;
	while (*s == ' ') s++;
	if (*s != '\0')
		return -1;

	goto out;
from_name:
	for (i = 0; i < LEN(namedcolors); i++) {
		if (!strcasecmp(s, namedcolors[i].name)) {
			r = namedcolors[i].rgba.r;
			g = namedcolors[i].rgba.g;
			b = namedcolors[i].rgba.b;
			a = namedcolors[i].rgba.a;
			goto out;
		}
	}
	return -1;
out:
	rgba->r = CAP(r, 0., 1.);
	rgba->g = CAP(g, 0., 1.);
	rgba->b = CAP(b, 0., 1.);
	rgba->a = CAP(a, 0., 1.);
	return 0;
}

