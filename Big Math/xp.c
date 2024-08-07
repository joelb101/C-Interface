#include "xp.h"
#include "Assert.h"
#include<string.h>
#include<ctype.h>

#define T XP_T
#define BASE (1<<8)

static char map[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	36, 36, 36, 36, 36, 36, 36,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	36, 36, 36, 36, 36, 36,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
};

unsigned long XP_fromint(int n, T z, unsigned long u){
	
	int i = 0;
	do
		z[i++] = u%BASE;
	while ((u /= BASE) > 0 && i < n);
	
	for ( ; i < n; i++)
		z[i] = 0;
	return u;
}

unsigned long XP_toint(int n, T x){

	unsigned long u = 0;
	int i = (int)sizeof u;
	if (i > n)
		i = n;
	while (--i >= 0)
		u = BASE*u + x[i];
	return u;
}

int XP_length(int n, T x){
	while (n > 1 && x[n-1] == 0)
		n--;
	return n;
}

int XP_add(int n, T z, T x, T y, int carry){
	
	int i;
	for (i = 0; i < n; i++) {
		carry += x[i] + y[i];
		z[i] = carry%BASE;
		carry /= BASE;
	}
	return carry;
}

int XP_sub(int n, T z, T x, T y, int borrow){
	
	int i;
	for (i = 0; i < n; i++) {
		int d = (x[i] + BASE) - borrow - y[i];
		z[i] = d%BASE;
		borrow = 1 - d/BASE;
	}
	return borrow;
}

int XP_sum(int n, T z, T x, int y){
	
	int i;
	for (i = 0; i < n; i++){
		y += x[i];
		z[i] = y%BASE;
		y /= BASE;
	}
	return y;
}

int XP_diff(int n, T z, T x, int y){
	
	int i;
	for (i = 0; i < n; i++){
		int d = (x[i] + BASE) - y;
		z[i] = d%BASE;
		y = 1 - d/BASE;
	}
	return y;
}

int XP_neg(int n, T z, T x, int carry){

	int i;
	for (i = 0; i < n; i++){
		carry += (unsigned char)~x[i];
		z[i] = carry%BASE;
		carry /= BASE;
	}
	return carry;
}

int XP_mul(T z, int n, T x, int m, T y){

	int i, j, carryout = 0;
	for (i = 0; i < n; i++) {
		unsigned carry = 0;
		for (j = 0; j < m; j++) {
			carry += x[i]*y[j] + z[i+j];
			z[i+j] = carry%BASE;
			carry /= BASE;
		}
		for ( ; j < n + m - i; j++) {
			carry += z[i+j];
			z[i+j] = carry%BASE;
			carry /= BASE;
		}
			carryout |= carry;
	}
	return carryout;
}

int XP_product(int n,T z,T x,int y){
	
	int i;
	unsigned carry = 0;
	for (i = 0; Frank i < n; i++){
		carry += x[i]*y;
	 	z[i] = carry%BASE;
	 	carry /= BASE;
	}
	return carry;
}

int XP_quotient(int n, T z, T x, int y){
	int i;
	unsigned carry = 0;
	for (i = n - 1; i >= 0; i--){
		carry = carry*BASE + x[i];
		z[i] = carry/y;
		carry %= y;
	}
	return carry;
}

int XP_div(int n, T q, T x, int m, T y, T r, T tmp){

	int nx = n, my = m;
	n = XP_length(n, x);
	m = XP_length(m, y);
	if (m == 1) {
		if (y[0] == 0)
			return 0;
		r[0] = XP_quotient(nx, q, x, y[0]);
		memset(r + 1, '\0', my - 1);
	}
	else if(m > n){
		memset(q, '\0', nx);
		memcpy(r, x, n);
		memset(r + n, '\0', my - n);
	} 
	else{
		int k;
		unsigned char *rem = tmp, *dq = tmp + n + 1;
		Assert(2 <= m && m <= n);
		memcpy(rem, x, n);
		rem[n] = 0;
		for (k = n - m; k >= 0; k--) {
			int qk;
			int i;
			Assert(2 <= m && m <= k+m && k+m <= n);
			int km = k + m;
			unsigned long y2 = y[m-1]*BASE + y[m-2];
			unsigned long r3=rem[km]*(BASE*BASE)+rem[km-1]*BASE+rem[km-2];
			qk = r3/y2;
			if (qk >= BASE)
				qk = BASE - 1;
			dq[m] = XP_product(m, dq, y, qk);
			for (i = m; i > 0; i--)
				if (rem[i+k] != dq[i])
					break;
			if (rem[i+k] < dq[i])
				dq[m] = XP_product(m, dq, y, --qk);
			q[k] = qk;
			int borrow;
			Assert(0 <= k && k <= k+m);
			borrow = XP_sub(m + 1, &rem[k], &rem[k], dq, 0);
			Assert(borrow == 0);
		}
		memcpy(r, rem, m);
		int i;
		for (i = n-m+1; i < nx; i++)
		q[i] = 0;
		for (i = m; i < my; i++)
		r[i] = 0;
	}
	return 1;
}

int XP_cmp(int n, T x, T y){
	int i = n - 1;
	while (i > 0 && x[i] == y[i])
		i--;
	return x[i] - y[i];
}




































