# [BalticOI 2018] 火星人的 DNA

## 题目描述

**题目译自 [BalticOI 2018](https://boi2018.progolymp.se/tasks/) Day1「[Martian DNA](https://boi18-day1-open.kattis.com/problems/boi18.dna)」**

给定一个字符集大小 $|\Sigma| = K$ 的长度为 $N$ 的字符串和 $R$ 个要求，每个要求为使子串中的字符 $B$ 至少出现 $Q$ 次。求出满足所有要求的最短子串长度。

## 说明/提示

#### 样例 1 解释

有三个长度为 $2$ 的子串含有字符 $0$ 和 $1$ 各一个，分别为 ``0 1``、``1 0`` 和 ``0 1``，但是不存在长度为 $1$ 的子串满足要求，因此满足要求的最短子串的长度为 $2$。

#### 样例 2 解释

最短的满足要求的子串为 ``1 3 2 0 1 2 0``。

#### 样例 3 解释

在这个字符串中，``0`` 的数量不足。

| 子任务 | 分值 | 限制 |
|:--------:|:------:|:------:|
|$1$     |$16$  |$1\leqslant N\leqslant 100,\, R\leqslant 10$|
|$2$     |$24$  |$1\leqslant N\leqslant 4\, 000,\, R\leqslant 10$|
|$3$     |$28$  |$1\leqslant N\leqslant 200\, 000,\, R\leqslant 10$|
|$4$     |$32$  |$1\leqslant N\leqslant 200\, 000$|


感谢 Hatsune_Miku 提供的翻译

## 样例 #1

### 输入

```
5 2 2
0 1 1 0 1
0 1
1 1```

### 输出

```
2
```

## 样例 #2

### 输入

```
13 4 3
1 1 3 2 0 1 2 0 0 0 0 3 1
0 2
2 1
1 2```

### 输出

```
7
```

## 样例 #3

### 输入

```
5 3 1
1 2 0 1 2
0 2```

### 输出

```
impossible
```

# 题解

## 作者：PragmaGCC (赞：3)

看到神仙们都是用尺取法做的。

但是本题可以用二分答案做。

我们分析一下答案：如果说长度为 l 的子串满足条件，那么对于$\forall{len(s) > l}$的子串全部满足条件。我们很容易想到二分答案：

二分满足条件的子串的最小长度。建立一个队列，每一次“向右滑动”一次，相当于一个窗口，如果说有哪一次我们用这个队列“框住”了一个满足条件的子串，那么说明这个长度是可行的，继续向更小的找。而如果没有找到可行的，就向更大的找。

```cpp
#include <cstdio>
#include <cstring>
#include <deque>
int read() {
    register int n = 0, f = 1;
    register char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        n = (n << 3) + (n << 1) + (ch ^ '0');
        ch = getchar();
    }
    return n * f;
}
const int N = 200005;
std::deque<int> q;
int n, K, R;
int a[N];
int cnt[N], cnt2[N], tot, tot2;
void init() {
    n = read(), K = read(), R = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= R; i++) {
        int B = read(), Q = read();
        cnt[B] = Q;
        tot++;
    }
}
bool check(int x) {
    q.clear();
    memset(cnt2, 0, sizeof(cnt2));
    tot2 = 0;
    int i = 1;
    while (q.size() < x) {
        q.push_back(a[i]);
        cnt2[a[i]]++;
        if (cnt[a[i]] && cnt2[a[i]] == cnt[a[i]])
            tot2++;
        if (tot2 >= tot)
            return 1;
        i++;
    }
    for (; i <= n; i++) {
        q.push_back(a[i]);
        cnt2[a[i]]++;
        if (cnt[a[i]] && cnt2[a[i]] == cnt[a[i]])
            tot2++;
        if (cnt[q.front()] && (cnt2[q.front()] == cnt[q.front()]))
            tot2--;
        cnt2[q.front()]--;
        q.pop_front();
        if (tot2 >= tot)
            return 1;
    }
    return 0;
}
int main(void) {
#ifdef FS
    freopen("Martian.in", "r", stdin);
    freopen("Martian.out", "w", stdout);
#endif
    init();
    int l = 0, r = n, ans = -1;
    while (l <= r) {
        const int mid = l + r >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    if (ans == -1)
        puts("impossible");
    else
        printf("%d\n", ans);
    return 0;
}
```

---

## 作者：suzhikz (赞：2)

#### 前言
赛场上把双指针拆成了 $r$ 个？？？然后就没过。赛后一想就通五分钟过了，所以写个题解纪念下我的 shaber 时刻。
#### 思路
对于一个左端点为 $l$ 的区间，若右端点 $r$ 符合所有条件，那么所有比 $r$ 大的右端点都可以，且 $l$ 单调递增时， $r$ 也是单调递增的，所以想到了双指针。

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include<string>
#include<deque>
#include<stack>
#include<queue>
#include<vector>
#include<stdio.h>
#include<map>
#include<set>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<bitset>
using namespace std;
const int N=2e5+5;
int n,k,g;
int a[N];
int cnt[N],minn[N],b[N],q[N];
int main(){
	cin>>n>>k>>g;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=g;i++){
		cin>>b[i]>>q[i];
		minn[b[i]]=q[i];
	}
	int les=g,r=0;
	int ans=99824435;
	for(int i=1;i<=n;i++){
		if(i!=1){
			cnt[a[i-1]]--;
			if(cnt[a[i-1]]<minn[a[i-1]])les++;
		}
		while(r<=n&&les){
			r++;
			cnt[a[r]]++;
			if(cnt[a[r]]==minn[a[r]]){
				les--;
			}
		}
		if(r<=n){
			ans=min(ans,r-i+1); 
		}
	}
	if(ans==99824435)puts("impossible");
	else cout<<ans;
	return 0;
}
```

---

## 作者：koukilee (赞：1)

双指针。

****

题意大可归纳为：从序列中取出最短的一段，使得每个 $B_i$ 出现 $Q_i$ 次。

发现明显具有单调性。即如果有一个长度为 $mid$ 的区间符合以上要求，那么长度为 $mid + 1$ 的区间也一定是符合的。

所以可以考虑二分。

但是其实也可以线性做法。

考虑双指针。维护两个指针 $l,r$，表示区间 $l,r$ 内有可能符合以上要求。

每次将右端点 $r$ 加入，并将左端点 $l$ 向 $r$ 在不破坏以上条件的情况下尽可能减小（向右移）即可。

无解输出 `impossible`。

### Code
```c++
i64 n, k, r, s[MAXN], all[MAXN], tot[MAXN], sum, vis[MAXN], R;

int main() noexcept{
	read (n, k, R);
	
	for (i32 i = 1; i <= n; i++)
		read (s[i]);
	for (i32 i = 1; i <= R; i++){
		i64 x; read (x); read (all[x]);	
		vis[x] = 1;
	}
	
	i64 l = 1, ans = INF;
	for (i32 r = 1; r <= n; r++){
		tot[s[r]]++;
		if (tot[s[r]] >= all[s[r]] && vis[s[r]])
			sum++, vis[s[r]] = 0; /*判断是否出现次数达到数量*/
		while (tot[s[l]] > all[s[l]] && l <= r)
			tot[s[l++]]--; /*合并左端点，将不需要的删除*/
		if (sum == R)
			ans = std::min (ans, r - l + 1);
	}
	
	if (ans == INF) puts ("impossible"); else put (ans);
    return 0;
}
```

---

## 作者：Missa (赞：1)

都是尺取和双指针，就我带 log 了 /hsh

设 $r_i$ 表示，若左端点为 $i$，符合条件的右端点的最左值。显然可以双指针维护，但有人没想到，并打算直接维护 $r_i$。

设 $\{pl_u\}$ 表示所有颜色 $u$ 的出现。对于一组限制 $(b, p)$，我们让 $(pl_{b, i}, pl_{b, i+1}]$ 中的所有 $r_i$ 对 $pl_{b, i+q}$ 取 $\max$ 就可以了，注意可能有一段后缀满足无论以它开头怎么取都不可能满足区间内有 $\geq p$ 个颜色 $b$，直接把右端点设成正无穷就行了。

每种颜色至多出现一次，$\sum |pl| = O(n)$，用线段树维护 $\text{cmax}$ 操作，时间复杂度为 $O(n \log n)$。

我写了标记永久化的线段树。

```cpp
#include <bits/stdc++.h>

struct SGT {
  std::vector<int> s;
  int n;
  SGT(int n) : n(n), s(n << 2) {}
  void mdf(int o, int l, int r, int x, int y, int t) {
    if (x <= l && r <= y) return s[o] = std::max(s[o], t), void();
    int mid = l + r >> 1;
    if (x <= mid) mdf(o << 1, l, mid, x, y, t);
    if (y > mid) mdf(o << 1 | 1, mid + 1, r, x, y, t);
  }
  int qry(int o, int l, int r, int x) {
    if (l == r) return s[o];
    int mid = l + r >> 1;
    return std::max(x <= mid ? qry(o << 1, l, mid, x) : qry(o << 1 | 1, mid + 1, r, x), s[o]);
  }
  void mdf(int x, int y, int t) { mdf(1, 0, n-1, x, y, t); }
  int qry(int x) { return qry(1, 0, n-1, x); }
};

int main() {
  int n, k, r; scanf("%d %d %d", &n, &k, &r);
  std::vector<std::vector<int>> pl(k, {-1});
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    pl[a[i]].push_back(i);
  }
  SGT s(n);
  for (int i = 0; i < n; i++) s.mdf(i, i, i);
  for (int i = 0; i < r; i++) {
    int b, q; scanf("%d %d", &b, &q);
    if (q >= pl[b].size()) return printf("impossible\n"), 0;
    for (int j = 0; j + q < (int)pl[b].size(); j++) {
      s.mdf(pl[b][j] + 1, pl[b][j + 1], pl[b][j + q]);
    }
    if (pl[b].size() - q >= 0) s.mdf(pl[b][pl[b].size() - q] +1, n - 1, 1e9);
  }
  int ans = n;
  for (int i = 0; i < n; i++) {
    ans = std::min(ans, s.qry(i) - i + 1);
    // printf("%d : %d\n", i, s.qry(i) - i + 1);
  }
  printf("%d\n", ans);
}
```

---

## 作者：Autream (赞：0)

## 题意简述

给定一个字符集大小为 $K$ 的长度为 $N$ 的字符串和 $R$ 个询问，每个询问形如字符 $B$ 要出现 $Q$ 次。求出同时满足所有条件的最短子串长度。

## 题目分析

显然如果一个长度为 $T < N$ 的子串可以满足所有条件那么一定有一个长度为 $T + 1$ 的子串也满足所有条件，如果整个序列都无法满足条件则无解。答案具有单调性，考虑二分答案。
二分子串的长度 $mid$，从字符串最左端开始选 $mid$ 个数，并用桶记录该子串内每种字符出现了多少次。将这个窗口一次向右滑动，每次滑动时更新当前满足了多少个限制。
时间复杂度线性对数。

## AC Code

```cpp
// Problem: P4792 [BalticOI 2018] 火星人的 DNA
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4792
// Memory Limit: 750 MB
// Time Limit: 2000 ms
// Date: 2024/12/25 21:45:55
// Author: Li_Feiy

#include <bits/stdc++.h>
#define arrout(a, n) rep(i, 1, n) printk(a[i])
#define arrin(a, n) rep(i, 1, n) a[i] = read()
#define rep(i, x, n) for(int i = x; i <= n; i++)
#define dep(i, x, n) for(int i = x; i >= n; i--)
#define erg(i, x) for(int i = head[x]; i; i = e[i].nex)
#define dbg(x) std::cout << #x << ":" << x << " "
#define mem(a, x) memset(a, x, sizeof a)
#define all(x) x.begin(), x.end()
#define arrall(a, n) a + 1, a + 1 + n
#define PII std::pair<int, int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
int read() {
	char ch = getchar();
	int r = 0, w = 1;
	while(ch < '0' || ch > '9') w = ch == '-' ? -1 : w, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return r * w;
}

void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x >= 10) print(x / 10);
	putchar(x % 10 + '0');
}template<typename ...Args>
void print(int t, Args... args) { print(t), print(args...); }

void printl(int x) { print(x), putchar('\n'); }
template<typename ...Args>
void printl(int t, Args... args) { printl(t), printl(args...); }

void printk(int x) { print(x), putchar(' '); }
template<typename ...Args>
void printk(int t, Args ... args) { printk(t), printk(args...); }

CI N = 3e5 + 5;
int n, k, r, ans, a[N];
std::unordered_map<int, int> mp, req;
struct Query {
	int b, q;
} q[N];
bool check(int x) {
	std::deque<int> q;
	mp.clear();
	int cnt = 0; // 当前满足的限制数
	rep(i, 1, x) {
		q.p_b(a[i]);
		if(++mp[a[i]] == req[a[i]]) cnt ++;
		if(cnt == r) return 1;
	}
	rep(i, x + 1, n) {
		if(mp[q.front()] -- == req[q.front()]) cnt --; q.pop_front();
		if(++mp[a[i]] == req[a[i]]) cnt ++; q.p_b(a[i]);
		if(cnt == r) return 1;
	}
	return 0;
}
signed main() {
	n = read(), k = read(), r = read();
	arrin(a, n);
	rep(i, 1, r) q[i] = (Query) { read(), read() }, req[q[i].b] = q[i].q;
	if(!check(n)) puts("impossible"), exit(0); // 整个序列都无法满足
	int L = 1, R = n;
	while(L <= R) {
		int mid = L + R >> 1;
		if(check(mid)) R = mid - 1, ans = mid;
		else L = mid + 1;
	}
	print(ans);
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

本题可以使用双指针。

考虑强制先让左端点为 $1$，找到此时符合条件需要的最小的 $r$，使区间 $[1,r]$ 符合题目的所有条件。

之后每次令左端点加一，此时某一个字符的出现次数会减一，并可能导致区间不符合条件。这时候开始增加右端点直到满足条件，每次操作完令答案对 $r-l+1$ 取 $\min$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
const int N=200010;
int a[N],cnt[N],res[N],ans=1e9;
set<pair<int,int>> st;
int main()
{
	int n,k,R;
	cin>>n>>k>>R;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(R--)
	{
		int b,q;
		cin>>b>>q;
		st.insert({b,q});
		res[b]=q;
	}
	int l=1,r=-1;
	for(int i=1;i<=n;i++)
	{
		cnt[a[i]]++;
		if(cnt[a[i]]==res[a[i]]) st.erase({a[i],res[a[i]]});
		if(st.empty())
		{
			r=i;
			break;
		}
	}
	if(r==-1)
	{
		cout<<"impossible";
		return 0;
	}
	ans=r-l+1;
	while(r<=n)
	{
		cnt[a[l]]--;
		while(cnt[a[l]]<res[a[l]])
		{
			r++;
			if(r>n)
			{
				cout<<ans;
				return 0;
			}
			cnt[a[r]]++;
		}
		l++;
		ans=min(ans,r-l+1);
	}
}

---

## 作者：cosf (赞：0)

显然，这道题可以用双指针解决。

具体地，我们维护开始和结束坐标 $s, e$，表示对于当前 $s$，最靠左的 $e$ 能满足所有要求。

于是，我们可以维护一个桶 $b_i$ 和满足的要求的个数 $c$，表示 $[s, e]$ 中 $i$ 的个数，当某个 $b_i$ 超过或小于 $p_i$（$p_i$ 为要求中 $i$ 的个数）时，就让 $c$ 加上或减去 $1$ 即可。

当 $c = R$ 时，所有要求都满足了，我们对所有这样 $e - s + 1$ 取个 $\min$ 就行了。

```cpp
#include <iostream>
using namespace std;

#define MAXN 200005

int p[MAXN], a[MAXN], b[MAXN];

int n, k, r, c = 0;

namespace IO
{
    template <typename T>
    void read(T &a);

    template <typename... T>
    void read(T &...a);

    template <typename T>
    void write(T a);

    template <typename... T>
    void write(T... a);

    template <typename... T>
    void writeln(T... a);
}

using namespace IO;

int main()
{
    read(n, k, r);
	for (int i = 1; i <= n; i++)
	{
	    read(a[i]);
	}
	for (int i = 1; i <= r; i++)
    {
        int b, q;
        read(b, q);
        p[b] = q;
    }
    int res = n + 1;
    for (int s = 1, e = 0; e <= n; s++)
    {
        while (c != r && e < n)
        {
            b[a[++e]]++;
            if(b[a[e]] == p[a[e]])
            {
                c++;
            }
        }
        if (c == r)
        {
            res = min(res, e - s + 1);
        }
        else
        {
            break;
        }
        if (b[a[s]] == p[a[s]])
        {
            c--;
        }
        b[a[s]]--;
    }
    if (res > n)
    {
        cout << "impossible" << endl;
    }
    else
    {
        cout << res << endl;
    }
    return 0;
}

```

---

## 作者：daniEl_lElE (赞：0)

尺取。

## 思路

先计算出现总数，总数没达到所有要求直接返回不可能。

否则考虑尺取，枚举左边端点，每次向右移。

尺取过程中，我们要记录每个数出现的次数 $cnt_i$，以及所有满足的要求。令第 $i$ 个数要求出现次数为 $num_i$。

当我们右端点移动时，如果 $cnt_i=num_i-1$，我们新加入这个数的时候满足的要求的数量增加了 $1$。

同理，左端点移动时，如果 $cnt_i=num_i$，删除此数会使满足的要求的数量减少 $1$。

稍微有一些小细节吧，整体比较简单。具体实现见代码。

复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;
int countt[200005],num[200005],cnt[200005];
signed main(){
	int n,k,r;
	cin>>n>>k>>r;
	int a[n+1];
	for(int i=1;i<=n;i++){
	    cin>>a[i];
	    countt[a[i]]++;//计每个数字出现数量，count这个显示ambiguous
	}
	for(int i=1;i<=r;i++){
	    int u,v;
	    cin>>u>>v;
	    num[u]=v;//记录一下要求
	}
	int tot=0,ok=1;
	for(int i=0;i<=k;i++){
	    if(countt[i]<num[i]) ok=0;//判断满足要求
	}
	if(!ok){
	    cout<<"impossible";
	    return 0;
	}
	int minv=n,nr=0;
	for(int l=1;l<=n;l++){//尺取部分，枚举左端点
	    while(nr<n&&tot!=r){//向右扫右端点
	        nr++;//注意一下这里顺序
	        if(num[a[nr]]){
	            tot-=(cnt[a[nr]]>=num[a[nr]]);//为了方便更新，先把原来情况减掉，后面加上
	            cnt[a[nr]]++;
	            tot+=(cnt[a[nr]]>=num[a[nr]]);
	        }
	    }
	    if(tot==r){
	        minv=min(minv,nr-l+1);//符合要求取min
	    }
	    if(num[a[l]]){
	       tot-=(cnt[a[l]]>=num[a[l]]);//一样的，方便更新先把原来减掉
	       cnt[a[l]]--;
	       tot+=(cnt[a[l]]>=num[a[l]]);
	    }
	}
	cout<<minv;
	return 0;
}
```

---

## 作者：Temperature_automata (赞：0)

## 题意简述

求最短子串，使得满足所有数据给出的形如：“数 $x$ 出现 $b$ 次”的条件。

## 思路

暴力的话枚举所有子串，时间复杂度就 $O(n^2)$ 了。

通常用双指针来优化时间复杂度 $O(n^2)$ 的算法。

首先 $r$ 指针不断后挪直到当前的 $l \sim r$ 满足所有条件，然后如果 $l$ 指针后挪后仍然满足条件，就讲 $l$ 指针不断后挪，后挪不了了就是当前区间为答案一种方案。

注意答案不止一种方案，找到一种方案之后 $r$ 指针要继续后挪。

时间复杂度 $O(n)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 200005
int n, k, q, a[N], b[N], num[N], pk[N], pj[N], tot, question[N], front, ans = 0x7f7f7f7f;

int main() {
	scanf("%d %d %d", &n, &k, &q);
	for (int i = 1; i <= n; ++ i) scanf("%d", a + i), pk[a[i]] ++;
	for (int i = 1; i <= q; ++ i) {
		scanf("%d %d", b + i, num + i);
		question[b[i]] = num[i];
		if(pk[b[i]] < num[i]) return printf("impossible"), 0;
	}
	tot = q, front = 1, pj[a[1]] ++;
	if(question[a[1]] == pj[a[1]] && question[a[1]]) -- tot;
	for (int i = 2; i <= n; ++ i) {
		pj[a[i]] ++;
		if(question[a[i]] == pj[a[i]] && question[a[i]]) -- tot;
		while((question[a[front]] < pj[a[front]] || !question[a[front]]) && front < i) {
			pj[a[front]] --;
			front ++;
		}
		if(!tot) {
			ans = min(ans, i - front + 1);
			pj[a[front]] --;
			front ++;
			tot ++;
		}
	}
	printf("%d", ans);
}
```

---

## 作者：__Watcher (赞：0)

这题的 `前缀和` 的标签害死人。

这样的题，尺取法/two pointers 几乎八九不离十了，考虑如何维护一个区间是否符合条件。

对于 $68\ pts$，可以建 $R$ 个前缀和数组，对于一个区间，检查区间内所有有限制的元素个数是否符合限制即可，复杂度 $O(NR)$，$68\ pts$ 很好骗。

对于 $100\ pts$，这样的效率显然不能满足条件。如果你学过莫队，这一步就会好想很多。来看一段莫队代码：

```cpp
void insert(int i){
	now+=(s[a[i]]++ == 0);
}
void erase(int i){
	now-=(s[a[i]]-- == 1);
}
```

嗯，不错，把这个 $now$ 改为题目中的 $R$ （即未满足的条件数），$s[i]$ 表示当前仍需要 i 元素的个数为 $s[i]$（$s[i]<0$ 表示 i 元素比限制多出几个），然后把 insert 和 erase 换过来，就可以处理左右端点的移动了。明显，$R=0$ 时表示该序列满足条件。由于右端点单调右移，因此该算法为线性复杂度 $O(N)$。


提供代码，仅供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int read() {
	int x=0, f=1; char ch=' ';
	while(!isdigit(ch)) {ch=getchar(); if(ch=='-') f=-1;}
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x*f;
}
int a[200005], s[200005], n, k, R;
void erase(int i){
	R+=(s[a[i]]++ == 0);
}
void insert(int i){
	R-=(s[a[i]]-- == 1);
}
int main() {
	cin>>n>>k>>R;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=R;i++) {
		int x=read(), y=read();
		s[x]=y;
	}
	int r=0;
	int minn=1e9;
	for(int i=1;i<=n;i++) {
		if(i>1) erase(i-1);
		while(R&&r<=n) {
			insert(++r);
		}
		if(r>n) break;
		minn=min(minn, r-i+1);
	}
	if(minn==1e9) cout<<"impossible";
	else cout<<minn;
}
```



---

## 作者：青丘杨哲 (赞：0)

本题的代码非常简洁，但是思维过程必须很缜密才行。记$flg_i=0/1$表示字符$i$是否被需要，$cnt_i$表示字符$i$被需要的数量（若不需要则为$0$）。由于数据范围很大，我们可以考虑类似尺取法的做法。

设两个指针$l$和$r$，初始值分别为$1$和$0$。显然$r$向右移动的过程中会多容纳一些字符，那么对应字符的$cnt$值就可以减小。而当一个字符的$cnt$值暂时减到$0$后，我们的$R$值也可以减小。故当某时刻$R=0$时，子串$a_l...a_r$就是合法的。

再来考虑$l$右移时的情况。这时一些字符会被抛弃，所以要将对应字符的$cnt$值重新增大，且如果有从$0$变$1$的$cnt$值，还要将$R$增大。如果暂时没有出现上述情况，则子串仍然合法。

因此主算法框架如下：

（$1$）右移$r$直到$r=n$或$R=0$；

（$2$）将$r-l+1$与$ans$打擂；

（$3$）将$l$右移一位，判断子串是否仍满足条件。

同时$l,r$右移过程中对$cnt$值的调整很相似，可以抽象成同一个函数。

参考程序：

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=(2e5+5);
int N,K,R,x,y,a[MAXN],cnt[MAXN],ans;
bool flg[MAXN];
void adjust(int x,int k){
	if (flg[a[x]])
		if ((cnt[a[x]]+=k)==(k+1>>1)) R+=k;
}
int main(){
	scanf("%d%d%d",&N,&K,&R),ans=1e7;
	for (int i=1;i<=N;i++) scanf("%d",&a[i]);
	for (int i=1;i<=R;i++)
		scanf("%d%d",&x,&y),cnt[x]=y,flg[x]=1;
	for (int i=1,j=0;i<=N;i++){
		while (j<=N-1&&R>=1) j++,adjust(j,-1);
		if (j>N-1&&R) break;
		ans=min(ans,j-i+1),adjust(i,1);
	}
	if (ans==1e7) printf("impossible");
	else printf("%d",ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 注：本题解为官方题解，用语可能和题面有些差异。
### 子任务1
定义$s=s_1s_2...s_N$为 DNA 字符串。给你一个子串$t=s_is_{i+1}...s_j$，检查$t$中是否含有所有要求的字符的时间复杂度为$O(N \cdot R)$。这种方法非常暴力，只需要循环并且计算出在子串中每个要求的字符数量是否符合即可。那么，可以通过暴力枚举找出最优的子串(有$C_2^	{N+1}=O(N^2)$个)。总时间复杂度为$O(N^3R)$

### 子任务2

可以做一些预处理，这样检查字子串是否合法的时间复杂度就降到了$O(R)$。可以用前缀和的思想解决（即计算$s$中每个元素出现了多少次）。这样时间复杂度就是$O(R)$。

总时间复杂度是$O(N^2R)$

### 子任务3

其实，当$N=100000$左右时，根本不用检查所有子串。找出$i \in \{1,...,N\}$中，包含足够多的要求字符的字串$s_i...s_j$，并使得$j$最小即可。用二分以及前缀和解决。复杂度就是$O(NR \log\, N)$
### 子任务4
想用O(N)的时间复杂度解决问题，我们可以用 _双指针_ 的思想解决。记录一个子串$s_l...s_r$，如果它不合法那就是太小了，这时可以$r$++。如果合法，那么这个子串有可能太大，那么，$l$++。这样只用检查$O(N)$个子串。

每次加减$l,r$，子串的变化并不太大。所以可以记录：
1. 在子串中的字符有每种有多少个（定义为$ch[$元素种类$][$位置$]$）
2. 在子串中出现的要求的字符（但未满足要求）每种有多少个。

$l$++时，我们令$ch[s_l][l]$--，如果要求的字符变少，我们就增加要求的字符个数。

$r$的操作同理。

这样时间复杂度就降到了线性。

---

