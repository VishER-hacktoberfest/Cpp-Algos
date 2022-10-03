#include <stdio.h>
#define SZ 10

int TT[4 * SZ * SZ];

int AA[4][4] = {
	{ 1, 1, 1, 1 },
	{ 1, 1, 1, 1 },
	{ 1, 1, 1, 1 },
	{ 1, 1, 1, 1 }
};

int bld(int n, int i1, int j1, int i2, int j2){

	if (i1 > i2 || j1 > j2)
		return 0;

	if (i1 == i2 && j1 == j2)
		return TT[n] = AA[i1][i2];

	int mi = i1 + (i2 - i1) / 2;
	int mj = j1 + (j2 - j1) / 2;

	TT[n] = 0;

	TT[n] += bld(4 * n + 1, i1, j1, mi, mj);		// upper left quad
	TT[n] += bld(4 * n + 2, mi + 1, j1, i2, mj);		// lower left quad
	TT[n] += bld(4 * n + 3, i1, mj + 1, mi, j2);		// upper right quad
	TT[n] += bld(4 * n + 4, mi + 1, mj + 1, i2, j2);	// lower right quad

	return TT[n];
}

int qry(int n, int i1, int j1, int i2, int j2, int r1, int c1, int r2, int c2){

	if (i1 > r2 || j1 > c2 || i2 < r1 || j2 < c1 || i1 > i2 || j1 > j2)
		return 0;

	if (i1 >= r1 && j1 >= c1 && i2 <= r2 && j2 <= c2)
		return TT[n];

	int mx = 0;

	int mi = i1 + (i2 - i1) / 2;
	int mj = j1 + (j2 - j1) / 2;

	mx += qry(4 * n + 1, i1, j1, mi, mj, r1, c1, r2, c2);
	mx += qry(4 * n + 2, mi + 1, j1, i2, mj, r1, c1, r2, c2);
	mx += qry(4 * n + 3, i1, mj + 1, mi, j2, r1, c1, r2, c2);
	mx += qry(4 * n + 4, mi + 1, mj + 1, i2, j2, r1, c1, r2, c2);

	return mx;
}


int upd(int n, int i1, int j1, int i2, int j2, int r1, int c1, int r2, int c2, int v){

	if (i1 > r2 || j1 > c2 || i2 < r1 || j2 < c1 || i1 > i2 || j1 > j2)
		return 0;

	if (i1 == i2 && j1 == j2)
		return TT[n] = v;

	Point mx(-1, -1, 0);

	int mi = i1 + (i2 - i1) / 2;
	int mj = j1 + (j2 - j1) / 2;

	mx += upd(4 * n + 1, i1, j1, mi, mj, r1, c1, r2, c2, v);
	mx += upd(4 * n + 2, mi + 1, j1, i2, mj, r1, c1, r2, c2, v);
	mx += upd(4 * n + 3, i1, mj + 1, mi, j2, r1, c1, r2, c2, v);
	mx += upd(4 * n + 4, mi + 1, mj + 1, i2, j2, r1, c1, r2, c2, v);

	return TT[n] = mx;
}

int main(){

	int R, C;

	int x1, y1, x2, y2;

	// Data array Row,Col (RxC)

	R = 4;
	C = 4;

	// Query range (x1, y1) ~ (x2, y2)

	x1 = 0, y1 = 0;
	x2 = 2, y2 = 2;

	int p;

	bld(0, 0, 0, R - 1, C - 1);

	p = qry(0, 0, 0, R - 1, C - 1, x1, y1, x2, y2);

	p = upd(0, 0, 0, R - 1, C - 1, x1, y1, x2, y2, 2); // value = 2

	p = qry(0, 0, 0, R - 1, C - 1, x1, y1, x2, y2);

	return 0;
}
