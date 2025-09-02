#include<bits/stdc++.h>
using namespace std;
int n, m, t[500005];
void myadd(int pos, int x) {
	while (pos <= n) {
		t[pos] += x;
		pos += pos & -pos;
	}
}

int mysum(int pos) {
	int s = 0;
	while (pos) {
		s += t[pos];
		pos -= pos & -pos;
	}
	return s;
}

void lesson1() {
	int type, a, b;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a);
		myadd(i, a);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &type, &a, &b);
		if (type == 2)printf("%d\n", mysum(b) - mysum(a - 1));
		else myadd(a, b);
	}
}
int main() {
	lesson1();
	return 0;
}