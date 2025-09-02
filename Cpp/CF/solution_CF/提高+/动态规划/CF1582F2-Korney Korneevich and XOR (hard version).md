# Korney Korneevich and XOR (hard version)

## 题目描述

给一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$ ，寻找在 $a$ 的所有递增子序列（可以为空）的异或和中出现的数。

## 说明/提示

$1\le n\le10^6,0\le a_i\le5000$ 。
### 样例解释
对于第一个样例：
- 子序列 $\{\}$ 的异或和为 $0$ 。
- 子序列 $\{2\}$ 的异或和为 $2$ 。
- 子序列 $\{4\}$ 的异或和为 $4$ 。
- 子序列 $\{2,4\}$ 的异或和为 $6$ 。

其他子序列的异或和与上述其中一个子序列的异或和相等。

## 样例 #1

### 输入

```
4
4 2 2 4```

### 输出

```
4
0 2 4 6```

## 样例 #2

### 输入

```
8
1 0 1 7 12 5 3 2```

### 输出

```
12
0 1 2 3 4 5 6 7 10 11 12 13```

# 题解

## 作者：泥土笨笨 (赞：23)

本题比 `CF1582F1` 的数据有所加强， $n$ 的范围达到了 $10^6$ ，每个整数 $a_i$ 的范围也加到了 $5000$ ，考虑动态规划，一个一个数字的加进来，看看能组成的异或值会不会变多。


做题的时候的思路是这样走的，不想看的同学可以直接跳到下面正解的部分。先考虑一个复杂度高的算法，发现题目给的空间 `500M` 比较多，如果所有数字都是 $5000$ 以内的，则最终得到的异或值不会超过 $m = 1<<13$ ，空间足够开 $m \times m$ 的二维数组。

题目中有一个关键的话，我们选中数列中的一个子序列，这个子序列是严格上升的，那么对于每个子序列，我们可以记录当前的结尾。后面加入新的 $a_k$ 进来的时候，找前面的结尾比 $a_k$ 小的，可以接在它后面，得到更长的序列，而前面得到的异或值 $x$ ，我们可以得到新的异或值 $x \oplus a_k $，这里的 $\oplus$ 代表异或运算。

定义 $dp[i][j]$ 表示对于前 $k$ 个数字，当结尾是 $i$ 的时候，异或值能不能组成 $j$ ，如果能就记录 $1$ ，不能就记录 $0$ .那么当加入 $a_k$ 的时候，扫一遍这个数组的比 $a_k$ 小的行，再扫一遍每一列，如果 $dp[i][j]$ 是 $1$ ，就把 $dp[a_k][j \oplus a_k]$ 标记为 $1$ 。那么我们得到了一个复杂度是$O(n \times m^2)$的算法。

考虑优化，我们发现dp数组里面每个位置都只存 $0$ 和 $1$ ，信息密度比较低，每次扫一行去找 $1$ 的位置比较费时间。而且每次对于新加进来的数字 $a_k$ ，都要枚举前面的每一行，也是非常费时间。于是改一下定义的方式，不用二维数组，而是用`vector`数组。

**正解部分：**

定义：

`vector<int> l[MAXN];`

用 `l[i]` 这个 `vector` ，去装所有的结尾小于 $i$ 的子序列中，能得到哪些异或值。

然后枚举每一个 $a_k$ ，对于当前的 $a_k$ ，遍历一下 $l[a_k]$ ，把里面每个数字 $x$ 拿出来，再把 $x \oplus a_k$ 放到 $l[a_k+1],l[a_k+2]...l[m-1]$ 这些 `vector` 里面。我们发现，如果 $x$ 被从 $l[a_k]$ 中拿出来并且转移到别的位置以后，这个 $x$ 就可以从 $l[a_k]$ 这个 `vector` 中删掉了，因为如果下次有相同的 $a_k$ 进来，拿出来相同的 $x$ 去做转移，只会得到重复的结果。所以我们需要保证每个 `vector` 里面不进重复的元素，这个用一个二维数组标记一下就可以了。这样我们可以得到一个均摊复杂度 $O(m^3)$ 的做法，因为一共最多只有 $m^2$ 个数，每个数最多转移到 $m$ 个数。

但是这个复杂度还是不够的，还需要继续优化。考虑一下当我们把某个异或值 $y$ 插入到 $l[a_k+1],l[a_k+2]...l[m-1]$ 这些 `vector` 里面以后，比如下次又要把同一个数字 $y$ 插入到 $l[a_k'+1],l[a_k'+2]...l[m-1]$ 这些 `vector` 里面，其实如果 $a_k'$ 比 $a_k$ 小，那么只需从 $a_k'$ 到 $a_k-1$ 这个范围内插入就行了。那么我们可以再开一个数组 `th` ， $th[i]$ 表示对于 $i$ 这个异或值，对于 $x>=th[i]$ ，所有的 $x$ 的 $l$ 列表里面都已经插入过 $i$ 了。这样均摊复杂度会降到$O(m^2)$


代码时间：
```
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int MAXN = 1 << 13;
int n;
vector<int> l[MAXN];//l[i]表示我们找到的子序列结尾小于i的时候，异或值可能是哪些
int th[MAXN];//th[i]表示对于i这个异或值，对于x>=th[i]，所有的x的l列表里面都已经插入过i了
int ans[MAXN];//每个异或值是否出现过

int main() {
    cin >> n;
    for (int i = 0; i < MAXN; ++i) {
        l[i].push_back(0);
        th[i] = MAXN;
    }
    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        for (int j = 0; j < l[a].size(); ++j) {
            int u = l[a][j];//当前可以得到u这个值
            int v = u ^ a;//可以转移去v
            ans[v] = 1;
            //此时l[a[i]+1]...l[MAXN-1]里面都可以添加一个v
            //之前th[v]以后的已经添加过了
            while (th[v] > a) {
                th[v]--;
                l[th[v]].push_back(v);
            }
        }
        l[a].clear();
        l[a].shrink_to_fit();
    }
    int cnt = 0;
    for (int i = 0; i < MAXN; ++i) {
        if (ans[i]) {
            cnt++;
        }
    }
    cout << cnt << endl;
    for (int i = 0; i < MAXN; ++i) {
        if (ans[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}
```




---

## 作者：Alex_Wei (赞：16)

1582F2. [Korney Korneevich and XOR (hard version)](https://codeforces.com/contest/1582/problem/F2)

看到题目一个基本的想法是设 $f_{i,j}$ 表示是否存在以前 $i$ 位以 $j$ 结尾且异或和为 $k$ 的子序列，这样做复杂度爆炸，是 $nV^2$ 的（$V=2^{13}-1\geq \max a_i$），加上 bitset 优化可以通过 easy version。

实际上从前往后考虑的时候我们并不关心当前位置，因此实际有用的状态只有 $V^2$ 个：以哪个数结尾，以及异或和是多少。

但是这个状态设计有些鸡肋，我们没办法优化。换个 DP 方法：设 $f_{j,k}$ 表示是否存在以 $<j$ 的数结尾且异或和为 $k$ 的子序列。假设当前数为 $a_i$，那么枚举 $k$，若 $f_{a_i,k}=1$ 则更新 $f_{j,k\oplus a_i}\ (a_i<j\leq V)$。实际上对于相同的 $k\oplus a_i$ 我们并没有必要每次都从 $a_i$ 枚举到 $V$ 来更新，因为我们知道若 $f_{j,k}$ 被更新为 $1$，所以任何 $>j$ 的 $j’$ 的 $f_{j',k}$ 也一定是 $1$，不需要继续增大下去了。因此，记录一个 $mx_v$ 表示下一次遇到 $k\oplus a_i=v$ 的时候应该从 $a_i+1$ 枚举到 $mx_v$，然后用 $a_i$ 更新 $mx_v$ 即可。

此外，对于同一个 $a_i$ 的 $f_{a_i,k}$，若 $k$ 枚举过了就没有必要再枚举。故开一个桶 $buc_{a_i}$ 记录 $f_{a_i,k}$ 还没有被枚举过的 $k$ 有哪些，遇到 $a_i$ 就全部更新掉 $k\oplus a_i$ 然后把 $buc_{a_i}$ 清空。

复杂度分析：枚举复杂度：每个 $buc_{a_i}$ 最多存在过 $V$ 个数，共有 $a_i$ 个这样的桶。更新复杂度：每个 $v$ 的 $mx_v$ 会从 $V$ 枚举到 $0$，共有 $V$ 个这样的 $v$。因此时间复杂度为 $\mathcal{O}(n+V^2)$。

```cpp
const int V = 1 << 13;
int n, ans = 1, vis[V], mx[V];
vint buc[V];

int main() {
	cin >> n, vis[0] = 1;
	for(int i = 1; i < V; i++) buc[i].pb(0), mx[i] = V - 1;
	for(int i = 1; i <= n; i++) {
		int a = read();
		for(int it : buc[a]) {
			int p = it ^ a; ans += !vis[p], vis[p] = 1;
			while(mx[p] > a) buc[mx[p]--].pb(p); 
		} buc[a] = {};
	} cout << ans << endl;
	for(int i = 0; i < V; i++)
		if(vis[i]) cout << i << " ";
	cout << endl;
	return 0;
}
```

---

## 作者：Sol1 (赞：12)

~~来和泥土笨笨抢生意！~~

首先拿到题可以立刻想到一个简单的 DP：设 $f_{i,j,k}$ 表示前 $i$ 个数，最后一个值为 $j$，异或和是否可以为 $k$。如果可以则为 1，否则为 0。容易得到一个 $O(n\cdot v^2)$ 的做法。

考虑到结果为布尔值的 dp 一般都比较浪费，考虑利用贪心思想将其转化为最优化 DP。观察一下可以发现如果固定 $i,k$，则 $j$ 一定是一段前缀不可行，剩下的一段后缀可行；同时如果固定 $j,k$，则 $i$ 一定是一段前缀不可行，剩下的一段后缀可行。后者可以砍掉最多的状态，于是利用后者：将状态修改为 $f_{i,j}$ 表示所有最后一个数是 $i$，异或和是 $j$ 的子序列中最后一个数最靠前的位置是哪个。

然后尝试转移。可以递增枚举最后一个数的值 $i$，然后对于一个状态 $f_{i,j}$，如果往它后面接一个 $i+1$，则一定是 $f_{i,j}$ 后面第一个 $i+1$。于是开一个 vector 维护所有值出现的所有位置，转移时直接二分就可以做到 $O(v^2\log n)$。实际上跑的非常快。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

int dp[5005][8192], n, a[1000005];
bool ok[8192];
vector <int> v[5005];

inline void Read() {
	n = qread();
	for (int i = 1;i <= n;i++) {
		a[i] = qread();
		v[a[i]].push_back(i);
	}
}

inline void Solve() {
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 0;i <= 5000;i++) {
		for (int j = 0;j <= 8191;j++) {
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
			if (dp[i][j] <= n) ok[j] = 1;
			int x = upper_bound(v[i + 1].begin(), v[i + 1].end(), dp[i][j]) - v[i + 1].begin();
			if (x >= v[i + 1].size()) continue;
			dp[i + 1][j ^ (i + 1)] = min(dp[i + 1][j ^ (i + 1)], v[i + 1][x]);
		}
	}
	int sum = 0;
	for (int i = 0;i <= 8191;i++) sum += ok[i];
	cout << sum << endl;
	for (int i = 0;i <= 8191;i++) {
		if (ok[i]) cout << i << " ";
	}
	cout << endl;
}

int main() {
	Read();
	Solve();
	#ifdef CFA_44
	while (1);
	#endif
	return 0;
}
```

---

## 作者：orz_z (赞：10)

### CF1582F2 Korney Korneevich and XOR

由于值域较小，考虑在值域上搞事情。

记集合 $f[i]$ 包含当前以 $a$ 结尾的子序列的可能异或值，满足 $a<i$。

每读入一个 $a$，便对于 $b \in f[a],j\in[a+1,V]$，将 $a\oplus x$ 加入 $f[j]$。

考虑到每次即值域后缀集合加点，便对于每个异或出来的值 $p$，记 $mx_p$ 表示未添加 $p$ 的最小集合编号。

标记一下每次异或出来的值即可，时间复杂度 $\mathcal O(n + V^2)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

//#define int long long
typedef long long ll;
#define ha putchar(' ')
#define he putchar('\n')

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
		x = x * 10 + c - '0', c = getchar();
	return x * f;
}

inline void write(int x)
{
	if(x < 0)
	{
		putchar('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}

const int _ = 1 << 13;

int n, mx[_], ans = 1;

vector<int> d[_];

bool vis[_];

signed main()
{
	n = read();
	vis[0] = 1;
	for(int i = 1; i < _; ++i) d[i].push_back(0), mx[i] = _ - 1;
	for(int i = 1, x; i <= n; ++i)
	{
		x = read();
		for(int v : d[x])
		{
			int p = v ^ x; ans += !vis[p], vis[p] = 1;
			while(mx[p] > x) d[mx[p]--].push_back(p);
		}
		d[x] = {};
	}
	write(ans), he;
	for(int i = 0; i < _; ++i)
		if(vis[i]) write(i), ha;
	return 0;
}
```



---

## 作者：Shxt_Plus (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1582F2)

看到这道题，发现值域非常小，所以考虑用值域来解决这道题，考虑用数组 $b_i$ 来存 $i$ 这个数能异或的值，则对于每一个 $a_i$，先去用 $b_{a_i}$ 的值来更新答案，再将这个异或出来的值加入 $\sum_{i=a_i+1}^vb_i$，用 $vis[i][j]$ 表示在 $b_i$ 中 $j$ 有没有出现过，如果没有出现过就加入这个值，时间复杂度是 $O(n+v^3)$ 的，$v$ 为值域。

考虑优化，发现对于 $y$ 来说，每次更新的都是 $x-v$ 的，就导致重复了好多次，于是用 $las_i$ 表示 $i$ 已经更新过了 $las_i-v$，下次直接更新 $a_i+1-las_y$ 即可，对于每个数来说，最多更新过一次每个 $b_i$，所以时间复杂度是 $O(n+v^2)$ 的。

**CODE**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=8500;
int b[maxn][maxn],g[maxn],las[maxn];
bool v[maxn],v1[maxn][maxn];
int n;
int a[1000005];
signed main()
{

	for(int i=1;i<=8200;i++)
	{
		b[i][++g[i]]=0;
		las[i]=8200;
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	v[0]=true;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=g[a[i]];j++)
		{
			int y=a[i]^b[a[i]][j];
			v[y]=true;
			for(int k=a[i]+1;k<=las[y];k++)
			{
				if(!v1[k][y])v1[k][y]=1,b[k][++g[k]]=y;
			}
			las[y]=min(las[y],a[i]);
		}
		g[a[i]]=0;
	}
	int ans=0;
	for(int i=0;i<=8200;i++)if(v[i])ans++;
	cout<<ans<<endl;
	for(int i=0;i<=8200;i++)if(v[i])cout<<i<<" ";
	return 0;
} 
```


---

## 作者：cjrqwq (赞：2)

### 思路
dp 然后优化。

设 $dp_{i,j}=0/1$ 表示是否有末尾数 $<i$，异或和为 $j$ 的子序列。对于具体的数，其实不用关心。

假设现在处理 $a_i$，枚举异或和 $j$，那么所有 $dp_{k,j} \operatorname{xor} a_i|a_i<k<V,dp_j=1$ 都会被更新。

下面优化：

- 对于相同的异或和，如果 $f_{i,j}$ 已经被更新，那么 $f_{i+1 \sim V,j}$ 都被更新了，我们设立数组 $M_i$ 为需要枚举到 $M_{i}$。$M_{i+1}\sim V$ 无需枚举。

- 第二维的枚举太慢了，假如都是每个状态都是 $0$，就浪费时间。可以设一个 $f_{i,j}$，记录异或和为 $i$ 时要枚举哪些 $j$ 值。更新完就全部删除。（类似 spfa）

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10,M = 8192;
int n,v[M],m[M],ans=1;
vector<int>b[M];//每个<ai要枚举哪些 
int main() {
	cin>>n;
	v[0]=1;
	for(int i=1;i<=M-1;i++) {
		m[i]=M-1;b[i].push_back(0);
	}
	for(int i=1,t;i<=n;i++) {
		cin>>t;
		for(int j:b[t]) {
			int k=t^j;
			if(v[k]==0) ans++;
			v[k]=1;
			while(m[k]>t) b[m[k]--].push_back(k);
		}
		b[t].clear();
		b[t].push_back(0);
	}
	cout<<ans<<endl;
	for(int i=0;i<M;i++) if(v[i]) cout<<i<<" ";
	return 0;
}
```

---

## 作者：InoueTakina (赞：1)

下文中 $\oplus$ 表示按位异或。

朴素的 dp 是容易的，我们记 $f(a_i,v)$ 表示是否存在以 $a_i$ 结尾的上升子序列满足异或和为 $v$。

朴素的转移是 $\mathcal{O}(nv^2)$ 的，但是我们注意到 $f(a_i,v)$ 会从所有的 $f(j,v\oplus a_i)$ 满足 $j<a_i$ 的位置转移过来，所以我们不妨对 $f(i,j)$ 的第一维做前缀或和，记作 $g(i,j)$，这样转移就变成了 $\mathcal{O}(nv)$，做前缀或和的过程可以用 `std::bitset` 优化，综合时间复杂度 $\mathcal{O}(nv+\frac{nv^2}{\omega})$，可以通过 easy ver.

我们可以尝试如何优化这个东西，一个可以被模式化思考的东西就是：类似于可以不可以这样 `bool` 类型的 dp，许多转移是重复的，也就是，一个位置只有在第一被赋值为 $1$ 的时候是有用的，之后他永远是 $1$，额外的更新只会增加时间复杂度。

我们把 $g(i,j)$ 分别表示为一个 $v\times v$ 的 $01$ 矩阵，那么对于 $g(i,j)$，每一列只关心行标号最小的一个 $1$，不妨记作 $mx_j$。每次 $f(i,j)$ 被更新为 $1$ 的时候，如果满足 $i<mx_j$，我们再更新其他的 $g(i,j)$，并更新 $mx_j$，这样我们就保证 $g(i,j)$ 的每个位置只更新了一次。

考虑如何保证 $f(i,j)$ 的每个位置只被更新一次，注意到 $g(i,j)$ 被贡献到的位置是固定的，也就是说 $g(i,j)$ 只会向 $f(i,j\oplus i)$ 转移，那么，我们对于每个 $g(i,j)$，记录 $j$ 是否没转移过，另外，只有当 $g(i,j)=1$ 时，这个 $j$ 才有转移的必要，故综合时间复杂度为 $\mathcal{O}(n+v^2)$。





---

## 作者：RockyYue (赞：0)

#### 1582F2

给定 $a_{1\dots n}$，求所有是其某个递增子序列异或和的数（题中包含 $0$），$n\le 10^6,0\le a_i\le 5000$。

#### Sol

- 想到处理到 $i$ 时枚举前面的 $j<i$，$i$ 加入 $j$ 结尾子序列得到新子序列，于是设 $f_{i,j}$ 为 $a_i$ 作序列结尾时可否使子序列异或和为 $j$，转移中 $f_{i,j}\stackrel \lor \longleftarrow f_{k,j\oplus a_i}(k<i,a_k<a_i)$。
- 思考这样慢的原因，在于信息密度过小，不值得为了寻找一个为 $1$ 的位遍历所有 $k$，同时复杂度不宜到 $O(nV)$。
- 考虑两种，第一种设 $f_{i,j}$ 表示 $a_{1\dots i}$ 内考虑，要达到异或和为 $j$ 的最小结尾值，至少 $O(nV)$，难以优化。第二种，设集合 $f_i$ 表示值 $i$ 作结尾可以得到的所有异或和，在当前处理下标范围内考虑。
  - 转移时需要枚举上一个结尾值 $<a_i$，考虑优化状态，设其为 $<i$ 的值作结尾，则转移时对于所有 $x\in f_{a_i}$，将 $x\oplus a_i$ 加入 $f_{a_i+1\dots }$。
- 这样的复杂度是 $O(nV^2)$，未见优化，原因在于元素加入集合这一步，和最初转移中找 $f_{i,j}$，其对所有后面可能有贡献的位贡献，这两种本质是一样的。
- 但是这位我们提供了建模，异或在此处并无明显形式，故可以直接看做每次将一个集合中所有数做某种操作后加入后缀集合，共操作 $n$ 次，集合数量和大小都是 $O(V)$ 的。
- 你发现即使每个数插入每个集合一次，也只需要至多 $V^2$ 次，这是符合要求的，原先方法的不优之处就在于重复插入次数过多。由于插入的是后缀的集合，优化只需要对于每个值 $v$ 记录 $g_v$，表示最小的，满足所有 $i\ge g(v)$ 均有 $v$ 已经插入 $f_i$ 的数，可以 $O(V^2)$。

---

## 作者：lfxxx (赞：0)

考虑在值域上 dp。

不妨记录 $dp_{i,j}$ 表示考虑值域 $[0,i]$ 内的数，想要凑出异或和为 $j$ 的子序列，子序列最后一个位置最靠前是哪个位置。

那么 $dp_{i,j}$ 由 $dp_{i-1,j \oplus a_i}$ 更新而来，具体来说记录 $S_v$ 表示所有值为 $v$ 的下标位置，那么就是在 $S_{a_i}$ 找到 $dp_{i-1,j \oplus a_i}$ 的后继更新状态，时间复杂度 $O(n + V^2 \log n)$。

[代码](https://codeforces.com/contest/1582/submission/280516760)

---

## 作者：happybob (赞：0)

很显然的一个题。

注意到复杂度不允许 $O(nV)$ 或以上，于是考虑一些更好的状态表示。

定义 $f_{i,j}$ 为布尔变量，表示若子序列每个数都不超过 $i$，且 $i$ 选了，能否异或出 $j$。同时记录一下 $g_{i,j}$ 表示若 $f_{i,j}$ 为真，则子序列的末尾最小可以在哪里。转移的时候类似子序列自动机，在 `vector` 上二分即可。

复杂度 $O(n+V^2 \log V)$。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <set>
#include <vector>
using namespace std;

const int N = 1e6 + 5, M = 8192;

int a[N], n;
bool f[M][M];
int pos[M][M], minn[M];
vector<int> ve[M];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	set<int> ans;
	ans.insert(0);
	for (int i = 1; i <= n; i++) cin >> a[i], ve[a[i]].emplace_back(i), ans.insert(a[i]);
	f[0][0] = 1;
	memset(pos, 0x3f, sizeof pos);
	memset(minn, 0x3f, sizeof minn);
	pos[0][0] = minn[0] = 0;
	for (int i = 1; i < M; i++)
	{
		if (ve[i].empty()) continue;
		for (int j = 0; j < M; j++)
		{
			int place = minn[j ^ i];
			if (place <= n)
			{
				auto it = upper_bound(ve[i].begin(), ve[i].end(), place);
				if (it != ve[i].end())
				{
					f[i][j] |= 1;
					pos[i][j] = min(pos[i][j], *it);
				}
			}
		}
		for (int j = 0; j < M; j++)
		{
			if (f[i][j]) minn[j] = min(minn[j], pos[i][j]), ans.insert(j);
		}
	}
	cout << ans.size() << "\n";
	for (auto& j : ans) cout << j << " ";
	cout << "\n";
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：0)

直到过了也没算出我的复杂度是多少，感觉有可能是 $O(V^2\log V)$ 的（？）

一个非常 naive 的做法。设 $f_i$ 是得到 $i$ 的最小下标，从小到大枚举用来转移的数字 $V$，然后暴力转移 $f_{i\oplus V}=\min\{f_{i\oplus V},P_{i,V}\}$，其中 $P_{i,V}$ 表示 $f_i$ 之后出现的第一个数字 $V$ 的位置，通过二分查找得到。由于钦定了从小到大的枚举顺序，所以就不用考虑子序列递增这一要求了。

[提交记录](https://codeforces.com/contest/1582/submission/270975906)

---

## 作者：Fireworks_Rise (赞：0)

# 闲话

- 当你亲身去感受程序运行的过程后，你会感觉很神奇！！！

# 解析思路

[CF1582F2 Korney Korneevich and XOR](https://www.luogu.com.cn/problem/CF1582F2)

观察数据可以发现 $0 \le a_i \le 5000$，$a_i$ 的值这么小，很明显是个提示啊！！！

往值域上想，可以先定义集合 $f_i$ 为所有以 $j \in [1,i-1]$ 结尾的子序列的异或值。

再考虑转移，一开始肯定想暴力枚举，对于每个 $a_i$，将 $a_i \oplus k$ 加入 $f_j$ 中，$k \in f_{a_i}$，由于要求序列是按数值递增排列的，所以还需满足 $a_i < j \le V$，此处的 $V$ 是 $8200$。

这里需说明，若用 vector 来存集合 $f_i$ 可能会导致超时，所以我们选用数组进行操作...

我们发现这样去做时间复杂度为 $O(n + V^3)$，明显会超时，再考虑优化，可以发现每个 $a_i$ 所加入的集合是个后缀，这样不仅浪费时间而且还对答案没有任何多的贡献，所以可以再此处进行优化。

设定 $last_i$	表示异或和为 $i$ 所覆盖后缀的左端点，加入 $i$ 后更新 $last_i$ 即可。

满打满算异或后需要 $13$ 位二进制，因为 $2^{12} \le 5000 \le 2^{13} \le 8200$，所以我们开数组是只需要开到 $8200$ 即可，注意不要开 long long，否则有可能会爆炸（亲身体验）。

贴上蒟蒻的 code，细节看程序...

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int V=8210;
int n,a[N],last[V];
int f[V][V],g[V];
bool vis[V],isIn[V][V];
inline void init_() {
	for(int i=1;i<=8200;i++) {
		f[i][++g[i]]=0;
		last[i]=8200; 
	}
}
signed main() {
	init_();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	vis[0]=1;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=g[a[i]];j++) {
			int x=a[i]^f[a[i]][j];
			vis[x]=1;
			for(int k=a[i]+1;k<=last[x];k++) {
				if(!isIn[k][x]) {
					isIn[k][x]=1;
					f[k][++g[k]]=x;
				}
			}
			last[x]=min(a[i],last[x]);
		}
		g[a[i]]=0;
	}
	int ans=0;
	for(int i=0;i<=8200;i++)
		ans+=vis[i];
	printf("%d\n",ans);
	for(int i=0;i<=8200;i++)
		if(vis[i]) printf("%d ",i);
	printf("\n"); 
	return 0;
} 
```

---

## 作者：lhyuu (赞：0)

$a_i\in [0,5000]$，则若干数异或和 $\le 8192$ (即 $2^{13}$)。

定义集合 $f_i$ 为所有以 $j\in [1, i-1]$ 结尾的子序列的异或值。

考虑转移，对于当前 $a_i$，将 $a \oplus k$ 加入 $f_j$ 中，满足 $k \in f_{a_i},a_i<j\le V$。

这么做的复杂度玄学，考虑加一些条件，如我们不希望 $f_i$ 出现重复的数，因为同一个数异或 $i$ 的贡献不会发生改变，并且对于 $a \oplus k$，发现它加入的集合是一个后缀，记 $las_i$ 表示异或和为 $i$ 所覆盖后缀的左端点，加入 $i$ 后更新 $las_i$ 即可。

现在的复杂度，$f_i$ 至多 $V$ 个数，对于每个异或和只会转移 $V$ 次，所以总复杂度为 $O(n+V^2)$。

```
#include<bits/stdc++.h>
#define pii pair<int, int>
#define mpr make_pair
#define x first
#define y second
#define up(i, a, b) for(int i = a; i <= (int)b; ++i)
#define dn(i, a, b) for(int i = a; i >= (int)b; --i)
#define vc vector
#define pb push_back
#define itset set< int >::iterator
#define lowbit(x) (x & -x)

using namespace std;

const int MN = 1e6 + 5;
const int V = 8192;

int n;
vc<int> f[V + 5];
int vis[V + 5]; vc<int> ans;
int las[V + 5];

signed main(){
	scanf("%d", &n);
	int m = 0;
	ans.pb(0);
	vis[0] = 1;
	up(i, 1, V) f[i].pb(0), las[i] = V + 1;
	int cnt = 0;
	up(i, 1, n){
		int x; scanf("%d", &x);
		for(auto y : f[x]){
			if(!vis[y ^ x]){
				ans.pb(y ^ x);
				vis[y ^ x] = 1;
			}
			int l = las[y ^ x];
			up(j, x + 1, las[y ^ x] - 1){
				f[j].pb(y ^ x);
				cnt++;
			}
			las[y ^ x] = min(x + 1, las[y ^ x]);
		}
		f[x].clear();
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size());
	for(auto y : ans) printf("%d ", y);
	
	return 0;
}
```


---

## 作者：kkxacj (赞：0)

##### 思路

发现值域很小，只有 $5000$，构成的最大数也只会为 $8192$。

考虑设 $w_i$ 表示结尾 $<i$ 的数能构成那些异或值，每个只会有 $8192$ 个数，可以用 `vector` 存，对于第 $i$ 个数 $a_i$，如果能构成异或值 $z$，那么对 $w_{a_I}$ 到 $w_{5000}$ 都有贡献，然后记 $v_i$ 为异或值为 $i$ 的数已经处理了 $w_{v_i}$ 到 $w_{5000}$ 的，这样时间复杂度是 $O \left ( 5000\times8192 \right ) $ 的，然后就可以过了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10,M = 8192;
int n,a[N],v[M+10],ans[M+10],cnt;
vector<int>w[M+10];
int main() 
{
	scanf("%d",&n);
	for(int i = 0;i < M;i++) w[i].push_back(0),v[i] = M-1;
	ans[0] = 1,cnt = 1;
	for(int i = 1;i <= n;i++) 
	{
		scanf("%d",&a[i]);
		for(int j = 0;j < w[a[i]].size();j++) 
		{
			int x = w[a[i]][j]^a[i];
			if(!ans[x]) cnt++;
			ans[x] = 1;
			while(v[x]>a[i]) w[--v[x]].push_back(x);
		}
		w[a[i]].clear();
	}
	printf("%d\n",cnt);
	for(int i = 0;i < M;i++) if(ans[i]) printf("%d ",i);
} 
```

---

