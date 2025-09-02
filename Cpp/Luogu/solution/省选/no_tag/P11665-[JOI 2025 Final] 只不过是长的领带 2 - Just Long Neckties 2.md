# [JOI 2025 Final] 只不过是长的领带 2 / Just Long Neckties 2

## 题目背景

译自 [第24回日本情報オリンピック 本選](https://contests.ioi-jp.org/joi-ho-2025/index.html) T4。


## 题目描述


有一个长度为 $k$（$k\ge 1$）的正整数数列 $B_1,\cdots,B_k$，初始 $B_i=1$（$1\le i\le k$）。这里，$k$ 是一个还未确定的数。

有 $N$ 场演出，第 $i$（$1\le i\le N$）场演出中，观众将会报出数字 $A_i$。然后你需要做以下的事情：

- 选择是否回应这个观众。
    - 如果选择回应，你需要选择 $j$（$1\le j\le k$）满足 $B_j\le A_i$，然后令 $B_j\gets A_i$。（注意这里是小于等于号。）
        - 如果无法选择这样的 $j$，则演出失败。
    - 否则，不需要做任何事。

然而，如果连续两次（或者更多次）选择不回应观众，观众会生气，从而演出失败。

在演出不失败的前提下，确定 $k$ 的最小值。

## 说明/提示


### 样例解释

#### 样例 $1$ 解释

$k=2$ 时，在五次演出中分别选择：

- 不回应；
- 回应，$j=1$（此后 $B_1\gets 3$）；
- 回应，$j=1$（此后 $B_1\gets 4$）；
- 回应，$j=2$（此后 $B_2\gets 2$）；
- 不回应；

可以证明 $k=1$ 时演出必定失败。所以输出 $2$。

该样例满足子任务 $1,3\sim 7$ 的限制。


#### 样例 $2$ 解释

$k=1$ 时，在第 $1,6$ 个演出时选择不回应即可。

该样例满足所有子任务的限制。


#### 样例 $3$ 解释

该样例满足子任务 $1,4\sim 7$ 的限制。




### 数据范围

- $2\le N\le 5\times 10^6$。
- $1\le A_i\le 21$（$1\le i\le N$）。
- 输入的值全部是整数。

### 子任务

1. （10pts）$N\le 15$。
2. （6pts）$N\le 500$，$A_i\le 2$（$1\le i\le N$）。
3. （12pts）$N\le 500$，$A_i\le 5$（$1\le i\le N$）。
4. （18pts）$N\le 500$，$A_i\le 15$（$1\le i\le N$）。
5. （26pts）$N\le 5\times 10^5$，$A_i\le 15$（$1\le i\le N$）。
6. （10pts）$N\le 5\times 10^5$。
7. （18pts）无额外限制。

## 样例 #1

### 输入

```
5
5 3 4 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
6
2 1 1 2 2 1```

### 输出

```
1```

## 样例 #3

### 输入

```
10
2 4 6 7 4 5 5 3 4 1```

### 输出

```
3```

# 题解

## 作者：Erine (赞：7)

比较神的题。

你把最小覆盖刻画成最长下降就寄了。因为这样没有啥比较好的性质来贪心。

反而我们可以考虑，对于选定的一些数应该怎么做。我们从左往右每次加入一个数，如果存在一个小于等于它且最大的数，就将这个数贪心替换，否则新开一个位置。

发现这样你维护的集合里面不太会有重复的数。所以状态只有 $2^V$ 个。然后加入一个数之后得到的状态是可以算出来的。

于是相当于我们可以设计出朴素的 $\Theta(n2^V)$ dp：$f_{i,S}$ 表示到达 $i$ 并且选中它，当前状态能否是 $S$。

事实上，对于每个 $S$，我们只关心一个最大的 $i$ 使得 $f_{i,S}=1$。考虑重设状态为 $f_S$ 为最终状态为 $S$，最远能够到达哪里。

转移有自环。我们发现事实上需要先处理自环，这样才能保证之后的转移是优的。那自环的转移在干什么事情呢：找到第一个 $a_i,a_{i+1}\not\in S$ 的位置 $i$。

暴力预处理是 $nV^2$，还能再给力一点吗？考虑预处理出：

1. 每个位置往后第一个某个值 $j$ 的位置。
2. 每个位置往后第一个相邻二元组形如 $(a_i,j)$ 的位置。

那么我们就可以 $\Theta(1)$ 查询的同时做到 $\Theta(nV)$ 预处理。然后至于非自环的转移就只有 $i+1,i+2$，比较简单。总复杂度 $\Theta(nV+V^22^V)$。

```cpp
void fake_main() {
	n = read();
	rep(i, 1, n) a[i] = read(), V = max(V, a[i]), --a[i];
	rep(S, 0, (1 << V) - 1) rep(i, 0, V - 1) {
		int msk = S & ((1 << i + 1) - 1);
		if (!msk) trans[S][i] = S | (1 << i);
		else trans[S][i] = (S ^ (1 << __lg(msk))) | (1 << i);
	}
	rep(i, 0, V - 1) nxt1[n + 1][i] = nxt2[n + 1][i] = n + 1;
	per(i, n, 0) {
		rep(j, 0, V - 1) nxt1[i][j] = nxt1[i + 1][j];
		if (i) nxt1[i][a[i]] = i;
	}
	per(i, n, 1) {
		rep(j, 0, V - 1) nxt2[i][j] = nxt2[nxt1[i + 1][a[i]]][j];
		if (i < n) nxt2[i][a[i + 1]] = i;
	}
	rep(S, 0, (1 << V) - 1) {
		int tmp = n + 1;
		rep(i, 0, V - 1) {
			if (S >> i & 1) continue;
			rep(j, 0, V - 1) {
				if (S >> j & 1) continue;
				tmp = min(tmp, nxt2[nxt1[f[S]][i]][j]);
			}
		}
		f[S] = max(f[S], tmp - 1);
		if (f[S] + 1 <= n) f[trans[S][a[f[S] + 1]]] = max(f[trans[S][a[f[S] + 1]]], f[S] + 1);
		if (f[S] + 2 <= n) f[trans[S][a[f[S] + 2]]] = max(f[trans[S][a[f[S] + 2]]], f[S] + 2);
	}
	rep(S, 0, (1 << V) - 1) if (f[S] >= n - 1) ans = min(ans, (int) __builtin_popcount(S));
	write(ans);
}
```

---

## 作者：TianTian2008 (赞：7)

## 题意

给定序列 $a$，选出一个子序列 $b$，满足 $a$ 中每两个相邻元素至少有一个被选入 $b$，求 $b$ 最长下降子序列长度的最小值。

## 引理

Dilworth 定理：对于任意有限偏序集，其最长链中元素的数目必等于其最小反链划分中反链的数目，简称“最长链等于最小反链覆盖”。

那么，$b$ 最长下降子序列的长度，就等于，最少用多少个不降子序列能覆盖整个 $b$ 序列。

## 思路

考虑如何求最小反链覆盖，可以贪心地做，维护目前所有已用的不降序列，当新加入元素 $a_i$ 时，选择结尾元素最大的合法序列接上 $a_i$，若都不合法则新开一个序列。

因为我们只关心不降序列的结尾，而且不会出现相同结尾，所以可以用 $2^a$ 状压表示每个不降序列。

记 $f_{i,s}$ 为考虑前 $i$ 个元素，$b$ 选中第 $i$ 个元素，目前不降序列情况是 $s$ 的可行性，容易做到 $O(n2^a)$。

但这还不够优，所以我们尝试将可行性 DP 变为数值 DP。

发现我们只关心 $f_{n-1,s}|f_{n,s}$ 是否为 1，或者说我们关心的是对于某个状态 $s$，满足 $f_{i,s}$ 为 1 的最大 $i$，不妨记为 $g_s$。

每次暴力跳然后更新别的状态即可，时间复杂度不会证，貌似可以势能分析（？），反正我自己没卡掉。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,m,k,a[5000001],p[2097152],f[2097152],ans=1000000000;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		m=max(m,a[i]);
	}
	k=1<<m;
	for(int i=0;i<k;++i) {
		p[i]=p[i>>1]+(i&1);
		while(f[i]<n-1&&(i>>a[f[i]+1]-1&1|i>>a[f[i]+2]-1&1)) ++f[i];
		if(f[i]>=n-1) ans=min(ans,p[i]);
		for(int j=0;j<m;++j) {
			int x=i|1<<j;
			if(x==i) continue;
			if(j&&(x>>j-1&1)) x^=1<<j-1; 
			f[x]=max(f[x],f[i]);
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：5)

### [P11665 [JOI 2025 Final] Just Long Neckties 2](https://www.luogu.com.cn/problem/P11665)

因为限制带等于号，所以每个数在当前的序列只会出现一次。设 $f_S$ 表示当序列的数的集合是 $S$ 的时候最远能够到哪个位置。这样设计出来的状态的性质不太好，因为它没有什么单调性。不过考虑到任意增加序列的数只会让情况不优，所以完全可以对 $S$ 做 “高维前缀 $\max$”（这里并非真正的高维前缀 $\max$，仅供理解）：如果 $S$ 被 $T$ 偏序（$S$ 的第 $i$ 高位的 $1$ 不大于 $T$）且 $f_S > f_T$，那么用 $f_S$ 更新 $f_T$ 不会把答案算小。

更新即求出 $f_S$ 之后的第一对相邻的位置使得这两个位置的数都不在 $S$ 里，可以枚举这两个数是什么，但朴素做法的空间是 $\mathcal{O}(na ^ 2)$。对空间的优化是注意到这个巨大的数组里很多数都是相同的，我们考虑记录 $nxt_{i, v}$ 表示从 $i + 1$ 开始下一次 $a_i$ 和 $v$ 相邻出现是在什么位置，这样枚举第一个数的时候找到这个数在 $f_S$ 之后的第一次出现，再根据出现的位置和枚举的第二个数根据 $nxt$ 查表即可。这样的时间复杂度是 $\mathcal{O}(na + 2 ^ aa ^ 2)$。

不过笔者笨笨的，没有想到以上优化，所以他采用了另一种方法，时间和空间都略好一些。如果能按照 $f_S$ 从小到大的顺序枚举 $S$，那么只需支持 $nxt_{u, v}$ 上的撤销操作。类似拓扑排序的思想，只有当一个状态所有偏序的状态都转移了之后，才能转移它。但是一个状态可以偏序很多状态，不能把所有边都连上，怎么办呢？因为 $\max$ 的转移是可以重复的，所以不需要担心重复计算的问题，于是一个状态 $S$ 的所有偏序的状态可以由把它的每个 $1$ 向后移动一位（若下一位不是 $1$）得到的状态 $T_i$ 的所有偏序的状态（包括 $T_i$ 本身）的并得到。特别地，如果最低位是 $1$，那么相当于把这个 $1$ 给去掉。例如 $S = 101101$ 的 $T_i$ 分别是 $011101$，$101011$ 和 $101100$。还有一个问题是根据 $T$ 算它向哪些 $S$ 连边了，这个也很简单，就是把每个 $1$ 向前移动一位（若上一位不是 $1$），以及还有一种情况是如果最低位是 $0$ 那么把它变成 $1$。时间复杂度 $\mathcal{O}(n + 2 ^ aa ^ 2)$，空间 $\mathcal{O}(n + 2 ^ a)$。

此外，关于 TianTian2008 的 [这篇题解](https://www.luogu.com.cn/article/prvre6zr)，其复杂度并非线性，但是在现有数据规模下较难卡掉。构造 $6, 4, 5, 3, 2, 1$ 可以得到 $6, 4, 3, 1$ 和 $6, 5, 2, 1$ 两个相互不偏序的状态，将这样的构造叠加起来可以得到 $2 ^ {a / 5}$ 个相互不偏序的状态，所以时间复杂度为 $\Omega(2 ^ a + 2 ^ {a / 5}n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using LL = __uint128_t;
mt19937 rnd(1064);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}
bool Mbe;

constexpr int N = 5e6 + 5;
constexpr int M = 1 << 21;
int n, ans, a[N], f[M], g[M];
int mp[21][21], val[N];
vector<int> buc[N];

bool Med;
int main() {
  fprintf(stderr, "%.3lf\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n, ans = 21;
  for(int i = 1; i <= n; i++) cin >> a[i], a[i]--;
  for(int i = 1; i < 1 << 21; i++) {
    for(int j = 0; j < 21; j++) {
      if(i >> j & 1) {
        g[i] += (j == 0) || (i >> (j - 1) & 1 ^ 1);
      }
    }
  }
  for(int i = 0; i < 21; i++) {
    for(int j = 0; j < 21; j++) {
      mp[i][j] = n + 1;
    }
  }
  for(int i = n - 1; i; i--) {
    int u = a[i], v = a[i + 1];
    if(u > v) swap(u, v);
    val[i] = mp[u][v], mp[u][v] = i;
  }
  buc[0].push_back(0);
  for(int _ = 0; _ <= n; _++) {
    if(_) {
      int u = a[_], v = a[_ + 1];
      if(u > v) swap(u, v);
      mp[u][v] = val[_];
    }
    while(!buc[_].empty()) {
      int S = buc[_].back();
      buc[_].pop_back();
      static int p[21], bit[21], ppc;
      for(int i = ppc = 0; i < 21; i++) {
        bit[i] = S >> i & 1;
        if(S >> i & 1) {
          p[ppc++] = i;
        }
      }
      if(ppc >= ans) continue;
      int nxt = n + 1;
      for(int i = 0; i < 21; i++) {
        if(bit[i]) continue;
        for(int j = i; j < 21; j++) {
          if(bit[j]) continue;
          nxt = min(nxt, mp[i][j]);
        }
      }
      if(nxt == n + 1) {
        ans = min(ans, ppc);
        continue;
      }
      int u = a[nxt], v = a[nxt + 1];
      auto trans1 = [&](int pos, int val) {
        int T;
        if(ppc == 0 || pos < p[0]) {
          T = S ^ (1 << pos);
        }
        for(int i = 0; i < ppc; i++) {
          if(i == ppc - 1 || pos < p[i + 1]) {
            T = S ^ (1 << p[i]) ^ (1 << pos);
            break;
          }
        }
        f[T] = max(f[T], val);
      };
      trans1(u, nxt);
      trans1(v, nxt + 1);

      auto trans2 = [&](int T) {
        f[T] = max(f[T], f[S]);
        if(!--g[T]) buc[f[T]].push_back(T);
      };
      for(int i = 0; i < ppc; i++) {
        if(i == ppc - 1) {
          if(p[i] != 20) {
            trans2(S ^ (1 << p[i]) ^ (1 << p[i] + 1));
          }
        }
        else if(p[i] + 1 < p[i + 1]) {
          trans2(S ^ (1 << p[i]) ^ (1 << p[i] + 1));
        }
      }
      if(ppc == 0 || p[0] != 0) {
        trans2(S ^ 1);
      }
    }
  }
  cout << ans << "\n";
  fprintf(stderr, "%.3lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
  return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

发一个自己的乱搞做法……时间复杂度 $O(nV + V^22^V)$，空间复杂度 $O(nV)$，还算凑合。

如果给定 $i$ 和 $S$ 查询 $j > i$ 且 $a_j \notin S$ 且 $a_{j+1} \notin S$ 能做到 $O(V)$ 的，那么就可以降为 $O(nV + V 2^V)$。但是我没想到啥好办法 /kel

-------

如果确定了哪些人被选中了，那么 $k$ 就是对应序列的最长严格下降子序列的长度（Dilworth 定理）。

类似 [P4484](https://www.luogu.com.cn/problem/P4484) 的套路，我们将一般 DP 中“$dp_j$ 表示长度为 $j$ 的最长下降子序列最后一个数的最大值”状压。

那么确定哪些人被选中之后，我们维护 $dp$ 数组对应状压结果 $S$。每次插入一个数 $v$：

- 如果 $v \in S$，没有变化；
- 否则，删去 $u \in S$ 且 $u<v$ 的最大的 $u$，并加入 $v$。

-------

考虑 $S_i$ 的变化（$S_i$ 指的是加入了前 $i$ 个数的 $S$ 的结果）。贪心的，我们应当求出 $f_S$ 表示最大的 $id$，使得 $id$ 之前的数能通过选或不选（$id$ 必须选）使得到 $id$ 处 $S_{id} = S$，且恰好这个位置变成了 $S_{id}$。显然这个东西具有单调性（贪心单调性。因为 $S$ 的变化必然导致问题变得不优。这个事情越远越好。）

考虑转移。我们在 $f_S$ 的基础上，枚举下一个不属于 $S$ 的数，即下一个变化点，设为 $v$。我们要找到 $> f_S$ 的第一个位置 $j$，使得 $a_j$ 和 $a_{j+1}$ 都不在 $S$ 中（因为他们必须有一个被选入，就一定会让 $S$ 变化）。

这样 $v$ 应该放在 $\le j+1$ 的最大的 $p$ 使得 $a_p=v$。利用 $v$ 更新 $S$ 加入 $v$ 之后的 $f_{S'}$。

特别地，如果这样的 $j$ 不存在，可以直接用来更新答案。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e6+10;
int n,ans,a[MAXN],pre[MAXN][22],occ[MAXN],dp[(1<<21)+10],Nxt[MAXN][22],nnxt[MAXN][22];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,ans=22;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,n) {
		occ[a[i]]=i;
		ffor(j,1,21) pre[i][j]=occ[j];
	}
	ffor(i,1,21) occ[i]=Nxt[n+1][i]=n+1;
	roff(i,n,1) {
		int lst=occ[a[i]];
		occ[a[i]]=i;
		ffor(j,1,21) Nxt[i][j]=occ[j];
		if(lst==n+1) ffor(p,1,21) nnxt[i][p]=n;
		else ffor(p,1,21) nnxt[i][p]=nnxt[lst][p];
		nnxt[i][a[i+1]]=i;
	}
	memset(dp,-1,sizeof(dp));
	dp[0]=0;
	ffor(pc,0,ans) {
		ffor(i,0,(1<<21)-1) if(__builtin_popcount(i)==pc) if(dp[i]!=-1) {
			int nxt=n;
			ffor(j,1,21) if(!(i&(1<<j-1))) {
				int pos=Nxt[dp[i]+1][j];
				if(pos!=n+1) ffor(k,1,21) if(!(i&(1<<k-1))) nxt=min(nxt,nnxt[pos][k]);
			}
			if(nxt==n) ans=min(ans,pc);
			else {
				nxt++;
				ffor(k,1,21) if(!(i&(1<<k-1))) {
					int v=i;
					roff(psl,k-1,1) if(v&(1<<psl-1)) {v-=(1<<psl-1);break ;}
					v+=(1<<k-1);
					if(pre[nxt][k]>dp[i]) dp[v]=max(dp[v],pre[nxt][k]);
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：AC_Lover (赞：2)

省选集训时的题，现在才来补一下。

**简要题意：** 求相邻边支配集 $\mathrm{LDS}$ 最小值，$n\le 5\times 10^6,V\le 21$。

**分析：**

- **$\texttt{Dilworth}$ 定理：** 最长链 $=$ 最小反链覆盖。

​	对应到此题，$\mathrm{LDS}$ 相当于 $\mathrm{LNDS}$（最长不下降子序列）最小覆盖。

最小覆盖就是要让个数尽可能少，那么对于一些 $\mathrm{LNDS}$，我们肯定贪心地尽可能选择能接上的接上去，于是我们要关注这些子序列的结尾，并且不难发现在这个贪心思路下，所有的结尾都是不同的，于是可以用一个 $2^V$ 的状态表示所有的 $\mathrm{LNDS}$ 结尾，那么可以构想一个 $\mathrm{dp}$。

定义 $f_{i,S}$ 表示考虑前 $i$ 个数，选择一些数后其构成的 $\mathrm{LNDS}$ 状态是 $S$ 是否可行，那么如果可行，此时的最小覆盖就是 $\mathrm{popcount}(S)$。转移是简单的，从 $f_{i,S}$ 转移时分选/不选 $a_{i+1}$，转移到 $f_{i+1,\mathrm{trans}(S,a_{i+1})}$ 和 $f_{i+2,\mathrm{trans}(S,a_{i+2})}$ 可以做到 $O(n2^V)$，不能通过。

考虑优化，其实我们可以不关注在某个阶段某个状态是否可行，转而关注每个状态最多能走到哪个阶段，于是可以定义 $f_{S}=i$ 表示状态 $S$ 可以在前 $i$ 个数中被得到，转移则是类似的，可以发现在原来的 $\mathrm{dp}$ 中每个状态只能由更小的的状态转移得到，因此处理到状态 $S$，则暴力向后拓展看看 $f_S$ 能取到多大，然后更新其他状态即可。

代码：

```c++
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=5000010;
template<class T>void Max(T &x,T y) { if (y>x) x=y; }
template<class T>void Min(T &x,T y) { if (y<x) x=y; }
int n,m;
int a[N];
int trans[1<<21][21];
int ppc[1<<21];
int f[1<<21];

string print(int x) { string s=""; for (int i=0;i<m;i++) s+='0'+((x>>i)&1);return s; }

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		cin >> a[i];
		m=max(m,a[i]);
		a[i]--;
	}
	
	for (int S=1;S<(1<<m);S++) ppc[S]=ppc[S>>1]+(S&1);
	
	for (int S=0;S<(1<<m);S++)
	{
		for (int i=0;i<m;i++)
		{
			int x=S;
			for (int k=i;k>=0;k--)
			{
				if ((S>>k)&1) 
				{
					x^=(1<<k);
					break;
				}
			}
			x|=(1<<i);
			trans[S][i]=x;
			//cout << print(S) << " " << i << " " << print(trans[S][i]) << "\n";
		} 
	}
	
	int ans=1e9;
	for (int S=0;S<(1<<m);S++)
	{
		for (int i=0;i<m;i++) 
		{
			if ((S>>i)&1)
			{
				Max(f[S],f[S^(1<<i)]); //取到子集
			}
		}
		while (f[S]<n-1)
		{
			if ((S>>a[f[S]+2])&1) f[S]+=2;
			else if ((S>>a[f[S]+1])&1) f[S]++;
			else break;
		}
		if (f[S]>=n-1) Min(ans,ppc[S]);
		else
		{
			int x=f[S];
			Max(f[trans[S][a[x+1]]],f[S]+1);
			Max(f[trans[S][a[x+2]]],f[S]+2);
		} 
	}
	cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：cike_bilibili (赞：1)

非正解，纯智慧。

但前半部分的 DP 是对的。

---

题目限制 $a_i \le 21$ 明示状压 DP。

但直接做还不太好，先找一下性质。

首先我们可以找到答案上界就是 $\max\{a_i\}$，你直接找这么多个人，一人管一种长度就行了；进一步的，我们发现除了还没有调整过的人，他们的长度一定两两不同，因为如果一个人往上调整时，如果这个长度已经有人了，那么可以直接用这个人管辖这种长度。

由于长度的不同，我们可以理解为动态插入和调整一些人满足条件，我们可以在序列上从左往右考虑，我们考虑状态 $f_s$，$s$ 表示当前领带的长度集合，$f_s$ 表示序列上能够满足条件的最长前缀，也就是在序列上最远能够走多远。

每次转移无非就两种，调整和加入一个新领带，如果是调整，则一定是贪心的将离得最近的转移过来。

然而转移过来的其实是新状态起点的位置，我们还需要知道用当前状态从 $f_s$ 能够走到的最远位置，等价于在后面找到第一次出现连着两个元素不在集合内的位置。

先考虑 $n\le 5 \times 10^5$，我们可以记录 $suf_{i,j,k}$ 表示下标 $i$ 的后缀中第一次出现连续的 $j,k$ 的位置，然后在 DP 转移时我们枚举补集中的两个元素 $j,k$，将 $suf_{f_s,j,k} $ 取最小值即可，这样可以做到时间 $O(2^{V}V^2)$，空间 $O(nV^2)$。

其实时间是能过的，但空间爆了。

我们考虑开个 ```std::vector<int>[V][V]``` 记录下标集合，每次二分一个位置，这样时间复杂度 $O(2^{V}V^2 \log n + n)$，空间 $O(n+2^V)$，时间又太大。

容易想到压位，注意到 DP 转移时枚举了两个元素，可以看作枚举了一个元素，与整个集合的 $suf$ 最小值，考虑将集合拆成很多段，处理每一种值对应一个集合的下标集合这样转移的时候枚举段就行了，需要自定义段长 $B$。

时间复杂度很神奇，是 $O(n 2^B +\frac{2^V V^2 \log n}{B})$，空间复杂度 $O(2^V + n 2^B)$，理论上 $B$ 应该取 $3$ 或 $4$ 是最优的，但实际上 $B$ 取 $1$ 都能过。

代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
namespace Arisa{
	inline int read(){
		int ans=0,w=1;
		char ch=getchar();
		while(ch<48||ch>57){
			if(ch=='-')w=-1;
			ch=getchar();
		}
		while(ch>=48&&ch<=57){
			ans=(ans<<1)+(ans<<3)+ch-48;
			ch=getchar();
		}
		return w*ans;
	}
	const int V=21;
	int n;
	int a[5000005];
	int f[(1<<21)+5];
	const int base=3,P=V/base+1;
	vector<int>vec[P][25][(1<<base)+5];
	void dp(){
		for(int i=1;i<(1<<V);i++)f[i]=-1e9;
		f[0]=0;
		for(int i=0;i<(1<<V);i++){
			int b=((1<<V)-1)^i;
			int minn=n;
			for(int j=0;j<V;j++){
				if(i&(1<<j))continue;
				for(int k=j/base;k<P;k++){
					int now=(b>>(base*k))&((1<<base)-1);
					if(!now)continue;
					auto it=lower_bound(vec[k][j][now].begin(),vec[k][j][now].end(),f[i]+1);
					if(it==vec[k][j][now].end())continue;
					minn=min(minn,*it);
					if(minn==f[i]+1)break;
				}
				if(minn==f[i]+1)break;
			}
			//其能到的位置就是 [f[i]+1,minn-1]
			f[i]=minn-1;
			int lst=-1;
			for(int j=0;j<V;j++){
				if(!(i&(1<<j))&&lst!=-1){//移位 
					f[i^(1<<lst)|(1<<j)]=max(f[i^(1<<lst)|(1<<j)],f[i]);
				}
				if(!(i&(1<<j))){//添位 
					f[i|(1<<j)]=max(f[i|(1<<j)],f[i]);
				}
				if(i&(1<<j))lst=j;
			}
		}
	}
	int main(){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read()-1;
        for(int i=1;i<n;i++){
            int x=a[i],y=a[i+1];
            if(x>y)swap(x,y);
            int g=y/base,st=g*base;
            for(int j=0;j<(1<<base);j++)if(j&(1<<y-st))vec[g][x][j].push_back(i);
        } 
        dp();
		int minn=V;
		for(int i=0;i<(1<<V);i++)if(f[i]>=n-1){
			int cnt=0;
			for(int j=0;j<V;j++)if(i&(1<<j))++cnt;
			minn=min(minn,cnt);
		}
		cout<<minn<<'\n';
		return 0;
	}
}
int main(){
	return Arisa::main();
}
/*
1287 MB
1514 MB
10:44 subtask 123456
暂时没法做 n <= 5000000 
11:29 卡常加神秘小优化可以拿下？ 
*/
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P11665)

**题目大意**

> 给定 $a_1\sim a_n$，删除若干不相邻元素，最小化剩下元素的最小非严格 LIS 覆盖。
>
> 数据范围：$n\le 5\times 10^6,a_i\le 21$。

**思路分析**

首先记录每个 LIS 的末尾，状态数 $\mathcal O(V^V)$。

首先注意到两个末尾为 $x$ 的 LIS 能覆盖的序列，等价于末尾为 $x,x+1$ 的两个 LIS 能覆盖的序列，只需要把其中一个序列开头的 $x$ 全部塞到另一个序列里面。

那么此时每种状态的元素只有 $\le 1$ 个，状态数 $\mathcal O(2^V)$。

可以暴力：$dp_{i,s}$ 表示 $a[1,i]$ 在保留 $a_i$ 的情况下能否匹配到 $s$ 这个状态，注意到 dp 值域 $\{0,1\}$，因此设 $f_s=\max\{i\mid dp_{i,s}=1\}$。

转移的时候先对 $f_s$ 做一个类似高维前缀最大值过程，然后枚举下一个保留的数是 $a_{f_s+1}/a_{f_s+2}$。

设保留了 $a_j$，新的状态为 $t$，那么转移到 $f_t$ 相当于在 $a[j,n]$ 中找到第一个 $x$ 使得 $a_{x+1},a_{x+2}\not\in t$。

这个问题可以先二分，判定的时候枚举 $a_{x+1}$ 的值，然后 ST 表维护区间中所有 $a_i=v$ 的元素的 $\{a_{i-1},a_{i+1}\}$ 的并集。

时间复杂度 $\mathcal O(2^VV\log n)$，空间复杂度 $\mathcal O(nV+n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e6+5,m=21;
int n,a[MAXN],f[1<<m],st[24][MAXN],id[m][MAXN];
int to(int s,int v) {
	if(s>>v&1) return s;
	if(!(s&((1<<v)-1))) return -1;
	return (s^(1<<(31-__builtin_clz(s&((1<<v)-1)))))|1<<v;
}
int qry(int l,int r) {
	int k=__lg(r-l+1);
	return st[k][l]|st[k][r-(1<<k)+1];
}
bool chk(int l,int r,int s) {
	for(int i=0;i<m;++i) if(!(s>>i&1)) {
		int x=id[i][l]+1,y=id[i][r-1];
		int t=(x<=y?qry(x,y):0);
		if(a[l]==i) t|=1<<a[l+1];
		if(a[r]==i) t|=1<<a[r-1];
		if((t&s)!=t) return false;
	}
	return true;
}
int nxt(int i,int s) {
	if(i==n||chk(i,n,s)) return n;
	int l=i+1,r=n-1,p=i;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(chk(i,mid,s)) p=mid,l=mid+1;
		else r=mid-1;
	}
	return p-1;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i],--a[i];
	for(int x=0,tp=0;x<m;++x) {
		id[x][0]=tp;
		for(int i=1;i<=n;++i) {
			if(a[i]==x) {
				id[x][i]=++tp;
				if(i>1) st[0][tp]|=1<<a[i-1];
				if(i<n) st[0][tp]|=1<<a[i+1];
			}
			else id[x][i]=id[x][i-1];
		}
	}
	for(int k=1;k<24;++k) {
		int *f1=st[k],*f0=st[k-1];
		for(int i=1;i+(1<<k)-1<=n;++i) {
			f1[i]=f0[i]|f0[i+(1<<(k-1))];
		}
	}
	for(int s=1;s<(1<<m);++s) f[s]=1;
	for(int d=1;d<m;++d) {
		for(int s=1;s<(1<<m);++s) if(__builtin_popcount(s)==d) {
			f[s]=nxt(f[s],s);
			for(int i=0,pr=-1;i<m;++i) {
				if(s>>i&1) {
					if(~pr) f[s]=max(f[s],f[s^(1<<i)^(1<<pr)]);
				} else pr=i;
			}
			if(f[s]>=n) return cout<<d<<"\n",0;
			for(int j:{f[s]+1,f[s]+2}) {
				int t=to(s,a[j]);
				if(~t) f[t]=max(f[t],j);
			}
		}
	}
	cout<<m<<"\n";
	return 0;
}
```

---

## 作者：RabbieWjy (赞：1)

题目链接：[洛谷 P11665](https://www.luogu.com.cn/problem/P11665)。

题目即从原序列取出若干个数形成新序列，且原序列中相邻两个数至少取一个，求新序列最少用几个不下降子序列可以覆盖。

考虑贪心，如果原序列的某个数要放进新序列，就把它安排在当前所有不下降子序列中，结尾的数小于等于它的最大的一个后面，找不到就新加一个序列。可以发现，过程中某一时刻，所有不下降子序列的最后一个数都不同，可以用 $2^{21}$ 种状态表示。

于是有一个简单的 DP，记 $f_{i,S}$ 表示当前考虑到第 $i$ 个数，不下降子序列的状态为 $S$ 是否可行。

如果 $f_{i,S}=1$，且 $a_{i+1} \in S$，则 $f_{i+1,S}=1$；同理，如果 $f_{i,S}=1$ 且 $a_{i+2} \in S$，则 $f_{i+2,S}=1$。也就是说，从一个 $f_{i,S}=1$ 的状态，可以一直推到 $f_{j-1,S}=1$，其中 $j$ 是最小的满足 $a_j \notin S$，$a_{j+1} \notin S$ 的数。这个 $j$ 可以通过预处理后暴力得出（对每个位置，预处理 $nxt_{i,x}$ 为大于 $i$ 的最小的 $j$，使得 $a_j=x$；$nxtt_{i,x}$ 为大于等于 $i$ 的最小的 $j$，使得 $a_{j+1}=x$；查询时暴力往后跳）。发现对于一个状态 $S$，重要的只有最大的 $k$ 使得 $f_{k,S}=1$，记这样的 $k$ 为 $g_S$。此时的 $j$ 即为 $g_S + 1$。

然后就可以得出 $g_S$ 的求解方法。考虑从小到大计算，由于 $a_{g_S + 1}$ 和 $a_{g_S + 2}$ 至少要选一个，下一个放进不下降子序列集合的数一定是这两个之一。分类讨论放哪一个数，得出新的 $S'$，再计算 $g_{S'}$ 即可。若此时发现 $S'$ 可以把剩下的序列全部覆盖掉，则更新答案。

总的时间复杂度为 $\mathcal{O}(nV+V^22^V)$，此处 $V=\max{a_i}=21$。

代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int n;
int a[5000010];
int nxt[5000010][23],nxtt[5000010][23],las[23];
int f[(1 << 21) + 10],ans = 40;
int cnt[(1 << 21) + 10];

int main()
{
	scanf("%d",&n);
	for (int i = 1;i <= n;i ++) scanf("%d",a + i);
	for (int i = n;i >= 1;i --)
	{
		for (int j = 1;j <= 21;j ++) nxtt[i][j] = nxtt[las[a[i]]][j];
		nxtt[i][a[i + 1]] = i + 1;
		for (int j = 1;j <= 21;j ++) nxt[i][j] = las[j];
		las[a[i]] = i;
	}
	for (int i = 1;i <= 21;i ++) nxt[0][i] = las[i];
	for (int i = 0;i < (1 << 21);i ++) cnt[i] = cnt[i >> 1] + (i & 1);
	for (int i = 0;i < (1 << 21);i ++)
	{
		if (!f[i] && i) continue;
		int Nxt = f[i] + 1;
		int res = 0,tnxt = Nxt;
		Nxt = n + 10;
		for (int j = a[tnxt] - 1;j >= 0;j --)
			if ((i >> j & 1) || !j)
			{
				int tmp = (i & ((1 << 21) - 1 - (1 << j))) ^ (1 << (a[tnxt] - 1));
				res = tmp;
				for (int k = 0;k < 21;k ++)
				{
					if (tmp >> k & 1) continue;
					int t = nxt[tnxt][k + 1];
					if (!t) continue;
					for (int w = 0;w < 21;w ++)
					{
						if (tmp >> w & 1) continue;
						int tt = nxtt[t][w + 1];
						if (!tt) continue;
						Nxt = min(Nxt,tt - 1);
					}
				}
				break;
			}
		if (Nxt >= n)
			ans = min(ans,cnt[res]);
		else f[res] = max(f[res],Nxt - 1);
		Nxt = n + 10;
		for (int j = a[tnxt + 1] - 1;j >= 0;j --)
			if ((i >> j & 1) || !j)
			{
				int tmp = (i & ((1 << 21) - 1 - (1 << j))) ^ (1 << (a[tnxt + 1] - 1));
				res = tmp;
				for (int k = 0;k < 21;k ++)
				{
					if (tmp >> k & 1) continue;
					int t = nxt[tnxt + 1][k + 1];
					if (!t) continue;
					for (int w = 0;w < 21;w ++)
					{
						if (tmp >> w & 1) continue;
						int tt = nxtt[t][w + 1];
						if (!tt) continue;
						Nxt = min(Nxt,tt - 1);
					}
				}
				break;
			}
		if (Nxt >= n)
			ans = min(ans,cnt[res]);
		else f[res] = max(f[res],Nxt - 1);
	}
	printf("%d\n",ans);
}
```

---

## 作者：DerrickLo (赞：1)

先考虑暴力。暴力就是 $f'_{i,j}$ 表示选了第 $i$ 个数，然后现在 $B_i$ 所构成的集合是 $j$ 是否可行，时间复杂度 $\mathcal O(n2^V)$。

然后考虑换一种 dp 形式，记 $f_j$ 表示最大的 $i$ 使得 $f'_{i,j}=1$，然后答案就是所有 $f_i\ge n-1$ 的最小 $\operatorname{popcount}(i)$。考虑如何转移，转移就是对于一个集合 $S$，如果加入一个数 $j$：

- 若存在一个最大的 $k$，使得 $k\in S$ 且 $k\le j$，那么删掉 $k$，加入 $j$。

- 否则就直接加入 $j$。

我们可以 $\mathcal O(nV)$ 地预处理出 $g_{i,j}$ 表示集合 $i$ 加入 $j$ 会变成什么集合，然后再由 $f_i$ 转移到 $f_{g_{i,j}}$，但是还会出现 $g_{i,j}=f_i$ 的情况，也就是 $f_i$ 自己更新，那么就需要找到最小的 $k$ 使得 $a_{k}\notin i,a_{k+1}\notin i$，这个如果暴力维护 $h_{i,a,b}$ 是 $\mathcal O(nV^2)$ 的，但是如果先找到第一个 $a$，再找到第一个相邻的 $b$ 我们就会发现这是 $\mathcal O(nV)$ 的，可以通过。

时间复杂度 $\mathcal O(nV+2^VV^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5000005],lst[5000005][22],lst2[5000005][22],ll[25],l[25][25],f[2200005],g[2200005][22],ans=1e9,b[25];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]--;
	memset(ll,0x3f,sizeof ll),memset(l,0x3f,sizeof l);
	for(int i=n;~i;i--){
		for(int j=0;j<21;j++)lst[i][j]=ll[j];
		ll[a[i]]=i;
	}
	for(int i=n;~i;i--){
		if(i>0&&i<n)l[a[i]][a[i+1]]=i;
		for(int j=0;j<21;j++)lst2[i][j]=l[a[i]][j];
	}
	for(int i=0;i<(1<<21);i++){
		int cnt=0,p=0;
		for(int j=0;j<21;j++)if(i&(1<<j))b[++cnt]=j;
		for(int j=0;j<21;j++){
			while(p<cnt&&b[p+1]<=j)p++;
			if(p==0)g[i][j]=i^(1<<j);
			else g[i][j]=i^(1<<b[p])^(1<<j);
		}
	}
	memset(f,-0x3f,sizeof f),f[0]=0;
	for(int i=0;i<(1<<21);i++)if(f[i]>=0){
		int minx=n;
		for(int j=0;j<21;j++)if(!(i&(1<<j)))for(int k=0;k<21;k++)if(!(i&(1<<k))){
			int p=lst[f[i]][j];
			if(p<=1e9)minx=min(minx,lst2[p][k]-1);
		}
		f[i]=minx;
		for(int j=0;j<21;j++)if(g[i][j]!=i){
			if(lst[f[i]][j]-f[i]<=2){
				f[g[i][j]]=max(f[g[i][j]],lst[f[i]][j]);
			}
		}
	}
	for(int i=0;i<(1<<21);i++)if(f[i]>=n-1)ans=min(ans,(int)__builtin_popcount(i));
	cout<<ans;
	return 0; 
}
```

---

## 作者：ty_mxzhn (赞：1)

我已经在钩偶爱后两题中取得了 $49$ 分的好成绩，你也快来试试吧！

题意简述：序列边支配集 LDS 最小值。

考虑这个回应过程贪心去做只有 $2^A$ 种状态，非常的可做。

设计 $f_{i,j}$ 表示选了 $i$ 状态是 $j$ 是否可达。直接转移，预处理后时间复杂度 $O(n2^A)$。可以拿 $46$ 分。

考虑省去 $i$ 这一维，设计 $f_j$ 表示状态是 $j$ 时最大的 $i$，转移的时候发现不能直接转移。

把选数变大到包含改一下形式，每次可以选数变大，也可以包含。

1. 选数变大。直接找 $x\in j,x+1 \notin j$ 然后操作即可。
2. 包含。对于 $f_j$ 直接往后快速选支配集直到不能选，这个过程中选到的都是 $j$ 里的数。

然后考虑包含这一步的优化。找出一个东西就是 $a_x \notin j,a_{x+1} \notin j,x\ge i$ 的最小 $x$。

考虑把 $(a_x,a_{x+1})$ 变成一个二元组 $(X,Y)$，预处理 $g_{i,X,Y}$ 表示 $i$ 以后这种二元组的答案。时间复杂度 $O(nA^2+2^AA^2)$ 可以拿 $72 \sim 82$ 分。

## 技巧 $1$

我们可以通过神秘东西优化复杂度。比如说使用 Ynoi 出现过的一个技巧就是把空间分块，每隔 $B$ 个位置存一次空间，查询的时候推到存的位置再查询。

时间复杂度 $O(\dfrac{n}{B}A^2+2^A(B+A^2))$，空间 $O(\dfrac{n}{B}A^2)$。$B=50$ 时可以通过。

## 技巧 $2$

我们可以先找到第一个 $X$，然后在这个位置的基础上找 $Y$。看起来和刚才的做法没有什么区别？但是其实这样子凭空省掉了一个维度。

时间复杂度 $O(nA+2^{A-2}A^2)$ 可以通过。

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
using namespace std;

int n,a[5000007];
int pi[57],dp[1<<21];
pii g[5000007][21];
bool ki(int msk,int y){
	if(y==-1) return 1;
	return (msk>>y)&1;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]--;
	for(int j=0;j<21;j++){
		int lst=-1;
		for(int k=0;k<21;k++) pi[k]=-1;
		for(int i=n;i>=0;i--){
			g[i][j]=mkp(lst,pi[a[i]]);
			if(i!=0&&a[i]==j) lst=i,pi[a[i-1]]=i-1;
		}
	}
	for(int j=0;j<(1<<21);j++){
		if(dp[j]==0&&j!=0) continue;
		int mx=n;
		for(int x=0;x<21;x++) if(!ki(j,x)){
			int q=g[dp[j]][x].fi;
			if(q==-1) continue;
			for(int y=0;y<21;y++) if(!ki(j,y)){
				int p=g[q][y].se;
				if(p==-1) continue;
				mx=min(mx,p-1);
			}
		}
		dp[j]=mx;
		for(int k=mx+1;k<=min(n,mx+2);k++){
			for(int i=a[k]-1;i>=-1;i--){
				if(!ki(j,i)) continue;
				dp[j^(1<<a[k])^(i>=0?1<<i:0)]=max(dp[j^(1<<a[k])^(i>=0?1<<i:0)],k);
				break;
			}
		}
	} 
	int ans=0x3f3f3f3f;
	for(int j=0;j<(1<<21);j++){
		if(dp[j]<n-1) continue;
		int ppc=0;
		for(int i=0;i<21;i++) if(ki(j,i)) ppc++;
		ans=min(ans,ppc); 
	}
	printf("%d\n",ans);
	return 0;
}
```

## 彩蛋

其实刚才 $O(na_i)$ 的部分，可以使用可持久化数组做到 $O(nf)$。其中 $f$ 是实现可持久化的复杂度。如果朴素实现是 $O(n\log n)$ 的，无法通过。

不过可持久化数组目前没有发现 $O(1)$ 做法，那就只能使用原做法了。

---

