# Interactive Factorial Guessing

## 题目描述

Oh no, this wicked jury hides something from you again, and you need to guess it interactively.

This time, you need to find an integer $ n $ . To do that, you can make at most 10 queries of the form "What is the $ k $ -th decimal digit of the product of all integers from 1 to $ n $ (also known as factorial and denoted as $ n! $ )?".

## 样例 #1

### 输入

```
2

1

YES

0

2

YES```

### 输出

```
? 0

! 1

? 0

? 19997

! 5982```

# 题解

## 作者：Alex_Wei (赞：5)

一个想法是二分找到第一个非零位置，但这并不可行，因为非零位置不满足可二分性。

我们发现，如果找到一个非零的位置 $p$，通过它的邻域信息，我们可以直接确定 $n$。因此，如果问到一个非零位置，我们可以几乎认为猜中了 $n$。

第 $i$ 次询问在当前范围 $R_i$ 下非零值最多的位 $p_i$，然后将第 $p_i$ 位非零的所有数从范围中删去，进行下一轮猜测。我们发现询问 $10$ 后恰剩余一个数，即 $|R_{11}| = 1$。初始 $R_1 = [1, 5982]$。

还有一个问题，就是第一次得到非零信息后，我们只剩下 $10 - i$ 次询问机会。但由于当 $i$ 较大时 $R_i$ 较小，所以依然可以确定所有 $n\in [1, 5982]$。

```cpp
// LUOGU_RID: 97218557
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5982;
int n, zero[N + 5];
vector<int> fc[N + 5], de, rem[15];
vector<pair<int, int>> info;
int get(int i, int j) {return j < fc[i].size() ? fc[i][j] : 0;}
int query(int k) {
  cout << "? " << k << endl;
  int res;
  cin >> res;
  info.push_back({k, res});
  return res;
}
void answer(int n) {
  cout << "! " << n << endl;
  string str; cin >> str;
}
void solve() {
  info.clear();
  for(int i = 1; i <= 10; i++) {
    int c = de[i - 1], res = query(c);
    if(res) {
      for(int j = 1; j <= 10 - i && c + j < 20000; j++) query(c + j);
      vector<int> arr = rem[i - 1];
      for(int ans : arr) {
        bool match = 1;
        for(auto it : info) match &= get(ans, it.first) == it.second;
        if(match) return answer(ans);
      }
    }
  }
  answer(rem[10][0]);
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  fc[0].resize(1), fc[0][0] = 1;
  for(int i = 1; i <= N; i++) {
    fc[i] = fc[i - 1];
    for(int &it : fc[i]) it *= i;
    for(int j = 0; j + 1 < fc[i].size(); j++)
      fc[i][j + 1] += fc[i][j] / 10, fc[i][j] %= 10;
    while(fc[i].back() >= 10) {
      int v = fc[i].back() / 10;
      fc[i][fc[i].size() - 1] %= 10;
      fc[i].push_back(v);
    }
    while(!fc[i][zero[i]]) zero[i]++;
  }
  for(int i = 1; i <= N; i++) rem[0].push_back(i);
  for(int _ = 1; _ <= 10; _++) {
    vector<int> nw, buc(N << 2, 0), dig;
    for(int c : rem[_ - 1]) for(int i = 0; i < fc[c].size(); i++) buc[i] += fc[c][i] > 0;
    for(int i = 0; i < N << 2; i++) dig.push_back(i);
    sort(dig.begin(), dig.end(), [&](int u, int v) {return buc[u] > buc[v];});
    int pick = dig[0];
    de.push_back(pick);
    for(int c : rem[_ - 1]) if(!get(c, pick)) rem[_].push_back(c);
  }
  int T;
  cin >> T;
  while(T--) solve();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
/*
g++ I.cpp -o I -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：cmk666 (赞：5)

题目大意：有一个数 $n\in[1,5982]$，你可以询问 $n!$ 的第 $x$ 位 $10$ 次，猜出这个 $n$。

先预处理出 $1\sim5982$ 的所有阶乘。

考虑第一次要问哪一位。我们想让当前可行解的集合大小在最坏情况下越小越好，那么可以扫描每一位，统计出每一位数字出现的个数 $cnt$，取 $\max(cnt)$ 最小的即可。这样根据回答的不同，可以将解集大小快速减少，而后可以递归去做。

这样就可以构建出一颗决策树，发现树的深度不超过 $10$，于是就做完了。

直接暴力做容易 T，可以只建出需要用到的决策树并把根节点的决策打表。

还有这题下标从 $0$ 开始的，~~我没看到喜提两发罚时~~。

核心代码如下：
```cpp
bigint a[6009];
vector < int > nw, tmp;
int pos, minn, maxn, cnt[10], res; ll cur; unordered_map < ll, int > mem;
inline void init() { mem[0] = 1518, a[0][1] = 1; For(i, 1, 5982) a[i] = a[i - 1] * i; }
inline void work()
{
	nw.clear(), cur = 0;
	For(i, 1, 10) // 在决策树上跑
	{
		if ( i == 1 ) For(j, 1, 5982) nw.push_back(j);
		if ( mem.count(cur) ) pos = mem[cur]; // 已经建过决策树
		else
		{
			minn = INT_MAX;
			For(p, 1, 20000) // 找到 max(cnt) 最小的一位
			{
				maxn = 0, memset(cnt, 0, sizeof(cnt));
				for ( int j : nw ) cnt[a[j][p]]++;
				For(j, 0, 9) maxn = max(maxn, cnt[j]);
				if ( maxn < minn ) minn = maxn, pos = p;
			}
			mem[cur] = pos;
		}
		printf("? %d\n", pos - 1), fflush(stdout), read(res);
		tmp = move(nw), cur = cur * 11 + res + 1;
		for ( int j : tmp ) if ( a[j][pos] == res ) nw.push_back(j); // 更新解集
	}
	char qwq[9]; printf("! %d\n", nw[0]), fflush(stdout), scanf("%s", qwq);
}
int main() { int t; init(), read(t); For(tt, 1, t) work(); return 0; }
```

---

## 作者：Semsue (赞：4)

看到 $n$ 不大应该可以想到一个非常暴力的思路，先把所有阶乘用高精度算出来，精细实现的话只需要几毫秒。

然后枚举一个位置问他，那么就会把集合分成 $10$ 个部分，我们取最大的部分最小的那个位置问，就类似点分治，递归下去建树即可。

我们实操发现这样深度最大刚好是 $10$。考场我粗略实现一下，刚好卡时限过去了。

考完仔细研究一下发现这个位置在后 $2000$ 位里面选取即可，这下时限就很充裕了。

```cpp
#include <bits/stdc++.h>
#define vi vector<int>
using namespace std;
vi operator * (vi a, int b)
{
	vi c;
	c.resize(a.size() + 5);
	for (int i = 0; i < (int)c.size(); i++) c[i] = 0;
	for (int i = 0; i < (int)a.size(); i++) c[i] = a[i] * b;
	for (int i = 0; i < (int)c.size() - 1; i++)
	{
		c[i + 1] += c[i] / 100000;
		c[i] %= 100000;
	}
	while ((int)c.size() > 1 && c.back() == 0) c.pop_back();
	return c;
}
int N = 5982, rt;
vi fac[6000], temp[6000];
int vec[20005][10], tot, id[20005];
bool mark[20005];
int solve(vi &now)
{
	int tmp = ++tot;
	if (now.size() == 1)
	{
		mark[tot] = 1;
		id[tot] = now[0];
		return tot;
	}
	int cnt[10], pos = -1, mn = 0x3f3f3f3f;
	for (int i = 0; i < min((int)fac[now.back()].size(), 2000); i++)
	{
		for (int j = 0; j < 10; j++) cnt[j] = 0;
		for (int j = 0; j < now.size(); j++) cnt[((int)fac[now[j]].size() > i) ? fac[now[j]][i] : 0]++;
		int mx = 0;
		for (int j = 0; j < 10; j++) mx = max(mx, cnt[j]);
		if (mx < mn) pos = i, mn = mx;
	}
	vi nxt[10];
	for (int i = 0; i < 10; i++) nxt[i].clear();
	for (int i = 0; i < now.size(); i++) nxt[((int)fac[now[i]].size() > pos) ? fac[now[i]][pos] : 0].push_back(now[i]);
	for (int i = 0; i < 10; i++) if (nxt[i].size()) vec[tmp][i] = solve(nxt[i]);
	id[tmp] = pos;
	return tmp;
}
void init()
{
	temp[1].resize(1); temp[1][0] = 1;
	for (int i = 2; i <= N; i++) temp[i] = temp[i - 1] * i;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < temp[i].size(); j++)
		{
			int x = temp[i][j], zz = 0;
			while (x || (j != temp[i].size() - 1 && zz < 5))
			{
				fac[i].push_back(x % 10);
				x /= 10;
				zz++;
			}
		}
	}
	vi now;
	now.resize(N);
	for (int i = 1; i <= N; i++) now[i - 1] = i;
	rt = solve(now);
}
char s[10];
void MAIN()
{
	int p = rt;
	for (int i = 1, x; i <= 10; i++)
	{
		printf("? %d\n", id[p]);
		fflush(stdout);
		scanf("%d", &x);
		p = vec[p][x];
		if (mark[p]) break;
	}
	printf("! %d\n", id[p]);
	fflush(stdout);
	scanf("%s", s + 1);
}
int main()
{
	init();
	int T; scanf("%d", &T);
	while (T--) MAIN();
	return 0;
}
```

---

