# [CERC2016] 二分毯 Bipartite Blanket

## 题目描述

在二分图中，所有点被划分成了两个不相交的集合 $A$ 和 $B$，每条边都恰好连接着某个 $A$ 和某个 $B$。一个匹配是一个边集，满足没有任何两条边有相同的端点。我们称一个匹配 $M$ 覆盖了点集 $V$ 当且仅当 $V$ 中的每个点都是 $M$ 中至少一条边的端点。


给定一个二分图，每个点有一个正整数权值。定义一个点集的权值为其中所有点的权值之和。


给定一个参数 $t$，请统计有多少点集 $V$，满足 $V$ 的权值不小于 $t$，且 $V$ 被至少一个匹配 $M$ 覆盖。


## 说明/提示

$1\leq n,m\leq 20$，$1\leq v_i,w_i\leq 10^7$，$1\leq t\leq 4\times 10^8$。

## 样例 #1

### 输入

```
3 3
010
111
010
1 2 3
8 5 13
21
```

### 输出

```
3
```

# 题解

## 作者：zac2010 (赞：8)

考虑霍尔定理和广义霍尔定理：

> 霍尔定理：对于一个左部图为 $X$、右部图大小为 $Y$ 的二分图（钦定 $|X|\leq |Y|$），存在边数等于 $|X|$ 的匹配的充要条件是：对于左部图的任何一个点集，右部图中和它相邻的点集大小都大于等于它（相邻的点集指的是所有点出边的并集）。

* 证明：必要条件显然。

  可这为什么是充分条件？考虑反证法，如果我们的增广路算法在进行到某一步的时候停止了——令左部图点集为 $X$，右部图点集为 $Y$，$Z$ 是我们能从左部图的非匹配点在增广路图上走到的点。那么 $Y\cap Z$ 内的点都被匹配了。我们会发现 $X\cap Z$ 内的点只能走到 $Y\cap Z$ 内的点，同时 $X\cap Z$ 内有未匹配点，和霍尔定理作为必要条件这一点矛盾了。

* 此外，假设 $|X|>|Y|$，这个定理就不成立了。

> 广义霍尔定理：给定一张二分图。如果存在一个匹配覆盖左部图中的点集 $X$，且存在一个匹配覆盖右部图中的点集 $Y$，那么存在一个匹配同时覆盖 $X$ 和 $Y$。

* 证明：考虑覆盖 $X$ 与覆盖 $Y$ 的两个匹配的异或 $Z$（这里指边集的异或）。根据定义，满足任意一个点的度数都小于等于 $2$。发现这样的图中只存在独立的环或者独立的链，于是我们对两种情况分类讨论一下：

  1. 对于一个环

     由于当前二分图只有偶环，故而考虑隔一条边取一次。

  2. 对于一条链

     如果当前是奇链，那就从一端开始隔一条边取一次。

     如果当前是偶链，会发现 $X\cup Y$ 不等于两个匹配并集的总点数（注意到 $X,Y$ 与匹配中的点是有区别的，匹配中的点包含了左部点和右部点，而 $X,Y$ 都只是“左部点和右部点”中的一种），于是我们规避掉实际上不处于 $X\cup Y$ 的点就行了。

根据广义霍尔定理，我们对于点集 $A$ 与点集 $B$ 单独考虑合法性，然后再合并方案即可。

* 判定点集 $S$ 的合法性

  判断权值是否不小于 $t$ 好做，枚举每个点判断是否在集合里，求和再与 $t$ 比较即可。

  判断一个点集是否被至少一个匹配包含，可以依据霍尔定理（要满足下面所述的两个条件）：

  1. $|S|$ 不大于 $S$ 的相邻节点集合
  2. $S$ 的所有子集满足第 $1$ 条

  第 $1$ 条可以直接暴力枚举+统计，第二条采用[高维前缀和](https://www.luogu.com.cn/blog/zac2010/gao-wei-qian-zhui-he)求解。

* 合并方案

  对 $A$ 的所有合法子集按照权值从小到大排序。接着枚举 $B$ 的每个合法子集，$A$ 中能与它组成合法集合 $V$ 的子集必定是排序后的一段后缀（因为当前只需要考虑和 $\geq t$），可以利用双指针解决。

时间复杂度 $O(n2^n+m2^m)$。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
typedef long long ll;
const int N = 22, M = (1 << 20);
int n, m, U, t, t1, t2, a[N], b[N]; ll ans;
int e1[M], e2[M], r1[M], r2[M], w1[M], w2[M], c1[M], c2[M];
void check(int a[], int e[], int w[], int c[]){
    FL(s, 0, U){
        FL(i, 1, n) if(s & (1 << i - 1))
            w[s] += a[i], c[s] |= e[i];
        c[s] = (__builtin_popcount(c[s]) >= __builtin_popcount(s));
    }
    FL(i, 1, n) FL(s, 0, U) if(s & (1 << i - 1))
        c[s] = min(c[s], c[s ^ (1 << i - 1)]);
}
int main(){
    scanf("%d%d", &n, &m);
    FL(i, 1, n) FL(j, 1, m){
        char ch; scanf(" %c", &ch);
        e1[i] |= (ch - 48 << j - 1);
        e2[j] |= (ch - 48 << i - 1);
    }
    FL(i, 1, n) scanf("%d", &a[i]);
    FL(i, 1, m) scanf("%d", &b[i]);
    scanf("%d", &t), U = (1 << (n = max(n, m))) - 1;
    check(a, e1, w1, c1), check(b, e2, w2, c2);
    FL(s, 0, U){
    	if(c1[s]) r1[++t1] = w1[s];
    	if(c2[s]) r2[++t2] = w2[s];
	}
	sort(r1 + 1, r1 + t1 + 1);
	sort(r2 + 1, r2 + t2 + 1);
	int j = t2 + 1;
	FL(i, 1, t1){
		while(j > 1 && r2[j - 1] + r1[i] >= t) j--;
		ans += t2 - j + 1;
	}
	printf("%lld\n", ans);
    return 0;
}
```



---

## 作者：EuphoricStar (赞：4)

> 引理：点集 $V$ 在匹配内的充要条件为 $V \cap A$ 能在匹配内且 $V \cap B$ 能在匹配内。

> 证明（参考了[这篇博客](https://blog.csdn.net/qq_42101694/article/details/121020996)）：令 $X = V \cap A,Y = V \cap B$。则先找出覆盖 $X$ 的原图上的最大匹配和覆盖 $Y$ 的最大匹配，然后把这些边单独拎出来建图。则现在的目标是选出若干条 **不交的** 边，使得 $X$ 和 $Y$ 均被覆盖。根据定义每个点 $deg \le 2$，所以连通块只有链和环两种。对于环，只可能是偶环，所以隔一条边取一条边即可；对于链，如果是奇链，则从第一条边开始隔着取；如果是偶链，发现端点同属于左部点或右部点，不可能同时 $\in X$ 或 $\in Y$。避开不需要覆盖的端点选边即可。

于是现在可以分别对左部点和右部点统计了。

> Hall 定理：考虑左部点或右部点的某个点集 $S$，设 $N(S) = \{v | \exists u \in S,(u,v) \in E\}$，则 $S$ 有完美匹配的充要条件为 $\forall T \subseteq S,|N(T)| \ge |T|$。

根据 Hall 定理，状压后对左部点和右部点分别跑一遍高维前缀与就能得出哪些点集有完美匹配。之后由于题目求的是左部点和右部点的点集，做一遍双指针或二分均可。

时间复杂度 $O(n2^n)$。

---

## 作者：Felix72 (赞：3)

考虑这样一个问题：

> 有一个二分图，由左部点集合 $L$，右部点集合 $R$ 和边集 $E$ 组成。求一个匹配，覆盖左部的一个子集 $fl$ 和右部的一个子集 $fr$。

先对 $fl$ 和 $R$ 做匹配得到边集 $e_1$，对 $L$ 和 $fr$ 做匹配得到 $e_2$（如果其中有一个匹配不完备则说明无解）。定义 $e_3 = e_1 + e_2$，$e_3$ 一定由若干环或者链构成，其中环一定是偶环，链如果长度为奇数则必有一段不是必选点，我们隔一条边选一条。这样一定能构造出合法的方案。

那么这个题只要点集在左边和右边分别满足有匹配即可。预处理出来再考虑拼起来，双指针扫描即可。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define int long long
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 25;
int n[2], lim, f[2][N], w[2][N]; bool mp[N][N], g[2][(1 << 20) + 5];
int p[2][2000010], pn[2]; long long res;

signed main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n[0] >> n[1];
	for(char i = 1, c; i <= n[0]; ++i)
		for(int j = 1; j <= n[1]; ++j)
			cin >> c, mp[i][j] = c - '0', f[0][i] |= (1 << (j - 1)) * mp[i][j], f[1][j] |= (1 << (i - 1)) * mp[i][j];
	for(int op = 0; op <= 1; ++op)
		for(int i = 1; i <= n[op]; ++i)
			cin >> w[op][i];
	cin >> lim;
	for(int op = 0; op <= 1; ++op)
	{
		for(int mask = 0; mask < (1 << n[op]); ++mask)
		{
			int match = 0, sig = 0;
			g[op][mask] = true;
			for(int i = 1; i <= n[op]; ++i)
				if(mask & (1 << (i - 1)))
					match |= f[op][i], sig += w[op][i], g[op][mask] &= g[op][mask - (1 << (i - 1))];
			g[op][mask] &= (__builtin_popcount(mask) <= __builtin_popcount(match));
			if(g[op][mask]) p[op][++pn[op]] = sig;
		}
		sort(p[op] + 1, p[op] + pn[op] + 1);
	}
	for(int i = pn[0], j = 1; i >= 1; --i)
	{
		while(j <= pn[1] && p[0][i] + p[1][j] < lim) ++j;
		res += (pn[1] - j + 1);
	}
	cout << res << '\n';
	return 0;
}
/*

*/
```

---

## 作者：7KByte (赞：2)

前置知识：霍尔定理

> 对于二分图，两部分别为 $X,Y$，令 $|X| \le |Y|$，则存在大小为 $X$ 的匹配的充要条件是对于任意 $S\subseteq X$，都有 $|F(S)| \ge |S|$，其中 $F(S) = \{y\ |\ x\to y \in E,x\in S,y\in Y\}$。

说人话就是对于 $X$ 的所有子集，相邻的点数都不小于子集。

必要性显然，充分性不显然，反证一下。

> 假设满足条件但是匹配 $<|X|$，那么不妨令没有匹配的点为 $x$，$x$ 的所有邻居都被匹配了，此时从 $x$ 出发一定存在一条增广路（匈牙利算法），如果不存在，则假设这条非增广路经过 $X$ 的点集为 $X'$ ，$|F(X')|$ 一定 $<|X'|$，手动画图即可理解。

那么对于本题关键结论是

> $V$ 在 $X$ 中的点集为 $S$，$Y$ 中的点集为 $T$。如果存在匹配覆盖 $S$，并存在匹配覆盖 $T$，则一定存在匹配覆盖 $V$。

这结论挺好猜的，$N\le 20$ 显然就是折半然后双指针嘛。证明也不难。

> $S$ 在 $T$ 中的邻居为 $W$，$S$ 和它的邻居匹配，然后 $T/W$ 再进行匹配即可。

所以直接状压 DP，$f_S$ 表示集合 $S$ 的邻居集合，$h_{S}$ 表示集合 $S$ 是否合法，直接转移 $\mathcal{O}(n^22^n + m^22 ^m)$。 

```cpp
#define N 20
#define M ((1 << N) + 5)
int n, m, u[M], v[M], f[M], bt[M], g[M], p[M], q[M], l, r, h[M], a[M], b[M]; char s[N + 1];
int main() {
	read(n, m);
	rep(i, 0, n - 1){
		scanf("%s", s);
		rep(j, 0, m - 1)if(s[j] == '1')u[1 << i] |= 1 << j, v[1 << j] |= 1 << i;
	}
	rep(i, 0, n - 1)read(p[1 << i]);
	rep(i, 0, m - 1)read(q[1 << i]);
	int w = (1 << max(n, m)) - 1;
	rp(i, w)bt[i] = bt[i >> 1] + (i & 1);
	w = (1 << n) - 1;
	h[0] = 1;
	rp(i, w){
		int j = i & -i;
		p[i] = p[j] + p[i ^ j];
		f[i] = u[j] | f[i ^ j];
		h[i] = 1;
		for(int k = i; k; k -= k & -k)h[i] &= h[i ^ (k & -k)];
		h[i] &= bt[f[i]] >= bt[i];
		if(h[i])a[++l] = p[i];
	}a[++l] = 0;
	w = (1 << m) - 1;
	rp(i, w){
		int j = i & -i;
		q[i] = q[j] + q[i ^ j];
		g[i] = v[j] | g[i ^ j];
		h[i] = 1;
		for(int k = i; k; k -= k & -k)h[i] &= h[i ^ (k & -k)];
		h[i] &= bt[g[i]] >= bt[i];
		if(h[i])b[++r] = q[i];
	}b[++r] = 0;
	sort(a + 1, a + l + 1),
	sort(b + 1, b + r + 1);
	read(w);
	int j = r; LL ans = 0;
	rp(i, l){
		while(j && b[j] + a[i] >= w)j--;
		ans += r - j;
	}printf("%lld\n", ans);
	return 0;
}
```



---

## 作者：Phartial (赞：1)

直接考虑整个点集是困难的，考虑先将其拆成左部点集和右部点集。

> 定理：一个点集 $S$ 能出现在某个匹配中，当且仅当其左部点集 $X$ 能出现在某个匹配中，且其右部点集 $Y$ 也能出现在某个匹配中。

证明：考虑将 $X$ 所在的匹配和 $Y$ 所在的匹配并起来形成一张新的二分图，我们需要在这张二分图里找到一个匹配同时包含左部点集和右部点集。

显然这张二分图里每个点的度数 $\le 2$，所以这张二分图实际上只是若干个环和若干条链的组合。环只能是偶环，隔一条边选一条边即可得到这个环的完美匹配，奇链同理。而对于偶链，假设其从左部开始，于左部结束（将左部换成右部后是对称的），那么这条偶链上必然存在一个左部点不在 $X$ 中（否则我们就找不到包含 $X$ 的一个匹配了），把它删掉后这条偶链就会变成两条奇链，容易找到一组完美匹配。

综上，我们总是能在这张新的二分图中找到同时包含 $X$ 和 $Y$ 的匹配，也就是包含 $S$ 的匹配，而这张二分图显然是原二分图的子集，所以我们就在原二分图中找到了包含 $S$ 的一组匹配。

如何判定一个左部点集 $X$ 能否出现在某个匹配中？显然我们只需判定 $X$ 能不能恰好出现在某个匹配中。如果在左部点中只保留 $X$ 中的点，那么这就相当于判定剩下的部分有没有左部点的完美匹配。使用 Hall 定理，只需判定是否对所有 $T\subseteq X$，有 $|T|\le|N(T)|$（其中 $N(T)$ 表示与 $T$ 中的点有边直接相连的右部点集），$|T|\le|N(T)|$ 这个条件可以直接预处理，跑一遍高维前缀与即可。右部点同理。

最后跑一遍双指针即可算出权值不小于 $t$ 的所有合法点集 $S$。时间复杂度 $\mathcal{O}(n2^n+m2^m)$。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;

const int kN = 20;

int n[2], t, e[2][kN], a[kN];
bool v[1 << kN];
int ne[1 << kN], s[1 << kN];
vector<int> l[2];
LL ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n[0] >> n[1];
  for (int i = 0; i < n[0]; ++i) {
    for (int j = 0; j < n[1]; ++j) {
      char ch;
      cin >> ch;
      e[0][i] |= (ch - '0') << j;
      e[1][j] |= (ch - '0') << i;
    }
  }
  for (int o = 0; o < 2; ++o) {
    for (int i = 0; i < n[o]; ++i) {
      cin >> a[i];
    }
    v[0] = 1;
    for (int i = 1; i < (1 << n[o]); ++i) {
      int j = __builtin_ctz(i), _i = i ^ (1 << j);
      ne[i] = (ne[_i] | e[o][j]);
      v[i] = (__builtin_popcount(i) <= __builtin_popcount(ne[i]));
      s[i] = s[_i] + a[j];
    }
    for (int i = 0; i < n[o]; ++i) {
      for (int j = 0; j < (1 << n[o]); ++j) {
        if (j >> i & 1) {
          v[j] &= v[j ^ (1 << i)];
        }
      }
    }
    for (int i = 0; i < (1 << n[o]); ++i) {
      if (v[i]) {
        l[o].push_back(s[i]);
      }
    }
  }
  cin >> t;
  sort(l[0].begin(), l[0].end());
  sort(l[1].begin(), l[1].end(), greater<int>());
  auto p = l[1].begin();
  for (int i : l[0]) {
    for (; p != l[1].end() && i + *p >= t; ++p) {
    }
    ans += p - l[1].begin();
  }
  cout << ans;
  return 0;
}
```

---

## 作者：reyik (赞：1)

补充：原题还有一个样例

INPUT:

```
3 2
01
11
10
1 2 3
4 5
8
```
OUTPUT:

```
13
```

预备知识：霍尔定理

如果指针对左边，那么可以状态压缩，枚举每一个点是否在集合中，得到每一个点是不是满足霍尔定理，把所有满足的记下来

现在是针对左右两边，可以用类似$meet$ $in$ $the$ $middle$的方法，先求出左边满足的和右边满足的，然后拼起来达到t的权值，可以$two-pointers$或直接$lowerbound$

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
const int N=(1<<20)+5;
int s1[N],s2[N],dp1[N],dp2[N],n,m,v1[25],v2[25],tot1=0,tot2=0,t,sz[N];
char s[25];
long long ans=0;
vector<int> sum1,sum2;
int lowbit(int x) {return x&(-x);}
int main() {
  scanf("%d%d",&n,&m);
  for (int i=1;i<=n;++i) {
    scanf("%s",s);
    for (int j=0;j<m;++j) if(s[j]=='1') {
      s1[(1<<(i-1))]|=(1<<j);
      s2[(1<<j)]|=(1<<(i-1));
    }
  }
  for (int i=1;i<=n;++i) scanf("%d",&v1[i]);
  for (int i=1;i<=m;++i) scanf("%d",&v2[i]);
  for (int i=1;i<(1<<20);++i) sz[i]=sz[i-lowbit(i)]+1;
  for (int i=0;i<(1<<n);++i) {
    int ret=0;
    dp1[i]=1;
    for (int j=0;j<n;++j) {
      if(i&(1<<j)) {
        s1[i]|=s1[i^(1<<j)];
        dp1[i]&=dp1[i^(1<<j)];
        ret+=v1[j+1];
      }
    }
    dp1[i]&=(sz[s1[i]]>=sz[i]);
    if(dp1[i]) sum1.push_back(ret);
  }
  for (int i=0;i<(1<<m);++i) {
    int ret=0;
    dp2[i]=1;
    for (int j=0;j<m;++j) {
      if(i&(1<<j)) {
        s2[i]|=s2[i^(1<<j)];
        dp2[i]&=dp2[i^(1<<j)];
        ret+=v2[j+1];
      }
    }
    dp2[i]&=(sz[s2[i]]>=sz[i]);
    if(dp2[i]) sum2.push_back(ret);
  }
  scanf("%d",&t);
  sort(sum1.begin(),sum1.end());
  sort(sum2.begin(),sum2.end());
  for (int i=0;i<sum1.size();++i) {
    ans=ans+1ll*(sum2.end()-lower_bound(sum2.begin(),sum2.end(),t-sum1[i]));
  }
  printf("%lld\n",ans);
  return 0;
}

```

---

## 作者：Paolo_Banchero (赞：1)

状态压缩dp，F[mask]表示一边的点集mask是否存在完备匹配（左右各做一次），依据Hall定理转移 
将左右所有存在完备匹配的点集合的权值和算出来塞到两个数组里，two pointers判权值和够不够就行了

	#include <bits/stdc++.h>
    #pragma GCC optimize(2)
    #define tn ((1<<n)-1)
    #define tm ((1<<m)-1)
    #define L (1<<(i-1))
    #define R (1<<(j-1))
    #define M 1100000
    #define N 50 
    using namespace std;
    typedef long long LL;
    int F[M],G[M],f[M],g[M],c[M],w[N],v[N],n,m,t,p,q,h,_,i,j;
    LL P[M],Q[M],ans,s;
    char mp[N][N];
    inline int rd() { int r; scanf("%d",&r); return r; }
    int main() {
        freopen("guard.in","r",stdin);
        freopen("guard.out","w",stdout);
        n=rd(),m=rd();
        for (i=1;i<=n;i++) scanf("%s",mp[i]+1);
        for (i=1;i<=n;w[i++]=rd());
        for (i=1;i<=m;v[i++]=rd());
        t=rd();

        for (i=1;i<=n;++i)
            for (j=1;j<=m;++j) 
                mp[i][j]=='1' ? F[L]|=R,G[R]|=L :0;

        for (_=1;_<=max(tn,tm);_++)c[_]=c[_-(_&-_)]+1;
        for (_=0;_<=tn;++_,s=0) {
            f[_]=1;
            for (int i=1;i<=n;++i) 
                L&_ ? F[_]|=F[_^L],f[_]&=f[_^L],s+=w[i] :0;
            (f[_]&=c[F[_]]>=c[_]) ? P[++p]=s :0;
        }

        for (_=0;_<=tm;++_,s=0) {
            g[_]=1;
            for (int j=1;j<=m;j++)
                R&_ ? G[_]|=G[_^R],g[_]&=g[_^R],s+=v[j] :0;
            (g[_]&=(c[G[_]]>=c[_])) ? Q[++q]=s :0;
        }

        sort(P+1,P+p+1),sort(Q+1,Q+q+1);

        for (_=1,h=q+1;_<=p;++_,ans+=q-h+1) 
            while (h-1 && P[_]+Q[h-1]>=t) h--;
        printf("%lld\n",ans);
        return 0;
    }

---

