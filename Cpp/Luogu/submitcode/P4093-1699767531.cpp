#include <cstdio>
#include <algorithm>
using namespace std;

const int MN = 100005;
const int MC = 100000;

int N, M;
int A[MN], Mx[MN], Mn[MN];
int f[MN], Ans;
int p[MN];
inline bool cmp1(int i, int j) { return Mx[i] < Mx[j]; }
inline bool cmp2(int i, int j) { return A[i] < A[j]; }

int B[MN];
inline void Ins(int i, int x) { for (; i <= MC; i += i & -i) B[i] = max(B[i], x); }
inline void Clr(int i) { for (; i <= MC; i += i & -i) B[i] = 0; }
inline int Qur(int i) { int A = 0; for (; i; i -= i & -i) A = max(A, B[i]); return A;}

void CDQ(int lb, int rb) {
	if (lb == rb) {
		f[lb] = max(f[lb], 1);
		return;
	}
	int mid = lb + rb >> 1;
	CDQ(lb, mid);
	for (int i = lb; i <= rb; ++i)
		p[i] = i;
	sort(p + lb, p + mid + 1, cmp1);
	sort(p + mid + 1, p + rb + 1, cmp2);
	int j = lb;
	for (int i = mid + 1; i <= rb; ++i) {
		while (j <= mid && Mx[p[j]] <= A[p[i]]) {
			Ins(A[p[j]], f[p[j]]);
			++j;
		}
		f[p[i]] = max(f[p[i]], Qur(Mn[p[i]]) + 1);
	}
	for (int i = lb; i <= mid; ++i)
		Clr(A[i]);
	CDQ(mid + 1, rb);
}

int main() {
	int x, y;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i)
		scanf("%d", &A[i]),
		Mx[i] = Mn[i] = A[i];
	for (int i = 1; i <= M; ++i)
		scanf("%d%d", &x, &y),
		Mx[x] = max(Mx[x], y),
		Mn[x] = min(Mn[x], y);
	CDQ(1, N);
	for (int i = 1; i <= N; ++i)
		Ans = max(Ans, f[i]);
	printf("%d\n", Ans);
	return 0;
}