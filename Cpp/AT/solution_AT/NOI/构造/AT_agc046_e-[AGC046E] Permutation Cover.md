# [AGC046E] Permutation Cover

## 题目描述

给定整数 $K$ 和整数 $a_1,\dots,a_K$。请判断是否存在满足以下条件的数列 $P$，如果存在，请输出字典序最小的一个。

- $P$ 的所有项均为 $1$ 到 $K$ 之间的整数；
- 对于每个 $i=1,\dots,K$，$P$ 中恰好包含 $a_i$ 个 $i$；
- 对于 $P$ 的每一项，存在一个包含该项的长度为 $K$ 的连续子序列，该子序列是 $1,\dots,K$ 的一个排列。

## 说明/提示

### 限制条件

- $1 \leq K \leq 100$
- $1 \leq a_i \leq 1000\quad (1\leq i\leq K)$
- $a_1 + \dots + a_K \leq 1000$
- 所有输入均为整数

### 样例解释 1

例如，第 $5$ 项的 $2$，包含在由第 $5,6,7$ 项组成的子序列 $(2,3,1)$ 中。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 4 3```

### 输出

```
2 1 3 2 2 3 1 2 3```

## 样例 #2

### 输入

```
4
3 2 3 2```

### 输出

```
1 2 3 4 1 3 1 2 4 3```

## 样例 #3

### 输入

```
5
3 1 4 1 5```

### 输出

```
-1```

# 题解

## 作者：jun头吉吉 (赞：3)

## 题意
给定 $k$ 和 $\{a_i\}_{i=1}^k$，构造一个 $P$，要求：

- $P$ 中的数字只有 $1\sim k$
- $i$ 在 $P$ 中出现了 $a_i$
- 所有长度为 $k$ 并且是排列的子串覆盖了整个 $P$

报告无解或输出字典序最小的 $P$。

$1\le k\le1000,\sum a_i\le1000$

## 题解
考虑 $a_x$ 是最小值 $a_y$ 是最大值，有解的充要条件是 $2a_x\ge a_y$。

首先是必要性，如果 $2a_x<a_y$，要不第一个/最后一个 $x$ 到边界有$\ge2$ 个 $y$，这样更靠近边界的就覆盖不到。要不两个相邻的 $x$ 中间有 $\ge 3$ 个 $y$，这样中间的 $y$ 就覆盖不到。两种情况至少存在一种然后就无解了。

否则任意一组解还是很容易构造的，如果 $a_x=a_y$ 只需要重复 $a_x$ 遍 $[1,k]$ 即可。

否则只需要中间是所有 $a_t=a_x$ 的  $t$，然后两边出现两次所有 $a_t\ne a_x$ 的 $t$，然后这一段显然能够被排列完全覆盖。那么所有 $a_t=a_x$ 的减小了 $1$，其他的减小了 $2$，然后就能归纳了。

然后我们能够判断有解了考虑怎么构造字典序最小。

考虑每次加上一个长度为 $l$ 的后缀使得后缀的 $k$ 个仍然是一个排列，要求 $l$ 字典序最小。首先 $l$ 内部的数已经确定了，因为前 $k-l$ 个是确定的，后缀的 $k$ 个要是排列，所以这些数也是确定的。然后在 $a_i$ 中把这些数减掉。设现在的最小值是 $a_x$ 最大值是 $a_y$。

如果 $2a_x\ge a_y$，那么显然接下来必然有解。

如果 $2a_x+1<a_y$，那么接下来必然无解，可以类似上面的分析。

所以接下来我们只需要考虑当 $2a_x+1=a_y$ 时构造一组字段组最小的解即可。类似上面的分析我们得出需要满足所有不存在 $i<j$ 满足 $a_{ans_i}=a_x,a_{ans_j}=a_y$。所以就可以直接贪心放了。设 $lst$ 是最后一次出现 $a_t=a_y$ 的位置，在 $lst$ 之前所有 $\ne a_x$ 先放进去，然后第 $lst$ 放进去之后把 $lst$ 之前的 $=a_x$ 按顺序放进去。之后就按顺序放。显然是字典序最小的。

每一次增加一段，需要枚举 $l$ 选择一个字典序最小的 $ans$。

复杂度是不超过 $\mathcal O(k^2\sum a_i)$ 的。感觉有高论但是我太不清楚。

## 代码
```cpp
const int N=1e3+10;
int k,n,now,ot[N];
vector<int>oo({0x3f3f3f3f}),ans;
vector<int>a,b;
int getmx(){return *max_element(a.begin(),a.end());}
int getmn(){return *min_element(a.begin(),a.end());}
void calc(int len){
	vector<int>v;static bool vis[N];
	memset(vis,0,sizeof vis);
	for(int i=now-(k-len)+1;i<=now;i++)vis[ot[i]]=1;
	for(int i=0;i<k;i++)if(!vis[i])v.pb(i),a[i]--;
	int mn=getmn(),mx=getmx();
	if(mx>2*mn+1)return;
	if(mx<=2*mn)return chkmn(ans,v),void();
	int lst=0;for(int i=0;i<(int)v.size();i++)if(a[v[i]]==mx)lst=i;
	vector<int>vv;
	for(int i=0;i<(int)v.size();i++){
		if(i>lst||a[v[i]]!=mn)vv.pb(v[i]);
		if(i==lst)
			for(int j=0;j<=lst;j++)if(a[v[j]]==mn)
				vv.pb(v[j]);
	}
	chkmn(ans,vv);
}
signed main(){
	read(k);a.resize(k);
	for(int i=0;i<k;i++)read(a[i]),n+=a[i];
	if(getmx()>2*getmn())return writeln(-1),0;
	while(now<n){
		ans=oo;
		for(int i=!now?k:1;i+now<=n&&i<=k;i++)b=a,calc(i),a=b;
		for(auto x:ans)ot[++now]=x,a[x]--;
	}
	for(int i=1;i<=n;i++)write(ot[i]+1),pc(' ');
}
```

---

## 作者：Union_of_Britain (赞：0)

考前题解环节，，，

考察结构，相当于说是要用是 $1\sim K$ 排列的子串能覆盖整个序列。一个排列变到下一个，就是把当前排列前缀在后面复制了一遍。显然，如果我两次复制操作都没有覆盖一整个排列的话，这两个复制操作是可以合并的。

那两次相邻复制操作覆盖了整个原来的排列。如果把 $1\sim K$ 分割为 ABC 三部分，那么复制后应当是 $ABCABCA$ 的形状。如果是这样，那还不如一次操作的 ABCA 和单独排列 ABC。因此只用 $ABA$ 这样的结构覆盖，这里顺便得到有解必要也只需要满足 $2a_i\ge  a_j$ 了。

对这个结构直接完成贪心好像会有点小问题，但是可以考虑一般的贪心方法，每次加最小的一段让后缀成为排列。数据范围允许直接枚举长度。

这里求段内排列是容易的：按照上面的结构，本段对于后面的影响是可以复制一段前缀去栓后面的 $a$。如果后面的 $a$ 本身满足条件不用栓就可以直接排序；否则把那些过大的 $\max a$ 整体放在 $\min a$ 前面来做到（是说每个 $\max$ 在任意 $\min$ 前面）前缀栓 $\max a$ 的作用。这样做到 $O(K^2\sum a_i)$。

---

## 作者：UKE_Automation (赞：0)

### AGC046E Permutation Cover

[$\text{Link}$](https://atcoder.jp/contests/agc046/tasks/agc046_e)

首先先看无解的条件。如果不考虑字典序的话我们有一个非常简单的构造方案：每一次加入一个 $1\sim k$ 的排列 $p$ 以及 $p$ 的一个前缀。那么很显然这样的过程最多 $\min(a)$ 轮，而一个数最大的出现次数正好是 $2\min(a)$。所以 $2\min(a)\ge \max(a)$ 时问题一定有解。

然后考虑 $2\min(a)<\max(a)$ 的时候问题有没有解。不妨设 $a_x=\min(a),a_y=\max(a)$，那么对于一个 $x$，它最多和周围的两个 $y$ 构成排列，但是由于 $2\min(a)<\max(a)$，所以必定存在一个 $y$ 没有配对，于是一定无解。

所以我们得到了无解的充要条件：当 $2\min(a)<\max(a)$ 时问题无解。现在考虑构造字典序最小的方案。

考虑**增量构造**，我们每次往当前序列后面加入一个长度 $l\le k$ 的序列，使得最后 $k$ 个元素还是一个排列，选出所有序列中字典序最小的那一个即可。那么考虑如何对于一个确定的 $l$ 构造出最优方案。

首先在确定 $l$ 之后我们要选的数字就确定了，相对应的，去掉这些数字时候的序列 $a$ 也就确定了。将这些数字记作集合 $S$，变化后的 $a$ 记作 $a'$，此时我们分类讨论有：

- 若 $2\min(a')\ge \max(a')$，那么此时后面必然有解，将 $S$ 排序后就是合法序列。
- 若 $2\min(a')+1<\max(a')$，根据上面的理论，后面的所有 $x$ 最多匹配 $2\min(a')$ 个 $y$，而当前放的最后一个 $x$ 最多只能再多匹配一个 $y$。那么最多匹配上 $2\min(a')+1$ 个 $y$，所以此时必然无解。
- 若 $2\min(a')+1=\max(a')$，那么此时我们要尽可能将所有 $a_x=\min(a')$ 的 $x$ 往后放。更具体的，所有的 $x$ 都应该在 $a_y=\max(a')$ 的 $y$ 的后面。用贪心简单实现即可。

综上我们可以在 $O(k^2\sum a_i)$ 的复杂度内解决这个问题，可以通过。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 2e9;
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
bool Beg;

int n, m, a[Maxn], t[Maxn];
int len, ans[Maxn];

il void chk(vector <int> &res, vector <int> &v) {
	for(int i = 0; i < min(v.size(), res.size()); i++) {
		if(res[i] != v[i]) {
			if(v[i] < res[i]) res = v;
			return ;
		}
	}
	if(v.size() < res.size()) res = v; 
	return ;
}

int vis[Maxn];
vector <int> res;
il void solve(int p) {
	vector <int> S;
	for(int i = 1; i <= n; i++) vis[i] = 0;
	for(int i = len - (n - p) + 1; i <= len; i++) vis[ans[i]] = 1;
	for(int i = 1; i <= n; i++) if(!vis[i]) S.push_back(i), a[i]--;
	int mn = Inf, mx = 0;
	for(int i = 1; i <= n; i++) chkmin(mn, a[i]), chkmax(mx, a[i]);
	if(2 * mn + 1 < mx) return ;
	if(2 * mn >= mx) return chk(res, S);
	S.clear();
	for(int i = 1; i <= n; i++) if(!vis[i] && a[i] != mn) S.push_back(i);
	while(S.size() && a[S.back()] != mx) S.pop_back();
	for(auto p : S) vis[p] = 1;
	for(int i = 1; i <= n; i++) if(!vis[i]) S.push_back(i);
	chk(res, S);
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n);
	for(int i = 1; i <= n; i++) read(a[i]), m += a[i];
	int mn = Inf, mx = 0;
	for(int i = 1; i <= n; i++) chkmin(mn, a[i]), chkmax(mx, a[i]);
	if(2 * mn < mx) {write(-1); return 0;}
	while(len < m) {
		res.resize(n);
		for(int i = 0; i < n; i++) res[i] = Inf;
		for(int i = max(n - len, 1); i <= min(m - len, n); i++) {
			for(int j = 1; j <= n; j++) t[j] = a[j];
			solve(i);
			for(int j = 1; j <= n; j++) a[j] = t[j];
		}
		for(auto p : res) ans[++len] = p, a[p]--;
	}
	for(int i = 1; i <= len; i++) write(ans[i], 0);
    Usd();
	return 0;
}

```

---

## 作者：Otomachi_Una_ (赞：0)

首先考虑判断是否又解。考虑这么一个结构，每次每次放入一个 $1\sim k$ 的一个排列 $p$ 另外加入 $p$ 的一个前缀。那么每个数消耗的次数是 $1$ 或者 $2$。这足以满足 $\max(a)\leq 2\min(a)$ 的情况。

其次，$\max(a)>2\min(a)$ 时，考虑 $a_x=\max(a),a_y=\min(a)$。考虑 $ans$ 数组里面，每个 $y$ 至多能对应和他左右第一个 $x$。即最多两个。所以必然无解。

我们能够判断是否有解了我们来尝试构造字典序最小解，考虑维护当前的答案序列。枚举长度 $l\leq k$ 表示我们在答案序列最后加入了一个长度为 $l$ 的后缀，此时最后 $k$ 个元素构成一个排列。那么我们知道了加入的这 $l$ 个元素构成的集合 $S$。

我们考虑怎么去排列这 $l$ 个元素。假设 $a'_i$ 表示余下 $R=\sum a_i-l-k$ 个元素，每个元素的出现次数。如果：

- $2\min(a)\geq \max(a)$ 那么后面 $R$ 个元素可以独立构造解。把 $S$ 从小到大排序即可。
- $2\min(a)+2\leq \max(a)$ 那么如果 $a_x=\max(a),a_y=\min(a)$，那么还未填入的 $y$ 对应两个 $x$ 而已经填入的最多对应一个。无解。
- 否则，这时 $2\min(a)+1=\max(a)$。那么我们构造解的方式应该是把 $a_i=\max(a)$ 的 $i$ 尽可能放前面，而 $a_j=\min(a)$ 的 $j$ 尽可能放到后面。具体地，所有的 $i$ 都应当在这样的 $j$ 的前面。使用你喜欢的贪心即可。

时间复杂度是 $O(K^2\sum a_i)$ 的。

---

