# [ARC125D] Unique Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc125/tasks/arc125_d

長さ $ N $ の整数列 $ A_1,A_2,\cdots,A_N $ が与えられます．

$ A $ の非空な部分列 $ s $ であって，以下の条件を満たすものの個数を $ 998244353 $ で割った余りを求めてください．

- $ A $ から $ s $ を取り出す方法が一意である． つまり，$ s=(s_1,s_2,\cdots,s_k) $ とした時，$ A_{idx(i)}=s_i $ ($ 1\ \leq\ i\ \leq\ k $)を満たす添字の列 $ 1\ \leq\ idx(1)\ <\ idx(2)\ <\ \cdots\ <\ idx(k)\ \leq\ N $ がちょうど一つ存在する．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N $
- 入力される値はすべて整数である

### Sample Explanation 1

以下の $ 5 $ つの部分列が条件を満たします． - $ (1,1) $ - $ (1,2) $ - $ (1,2,1) $ - $ (2) $ - $ (2,1) $ 部分列 $ (1) $ は取り出す方法が $ 2 $ 通りあるので条件を満たしません．

## 样例 #1

### 输入

```
3
1 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
4
4 2 1 3```

### 输出

```
15```

## 样例 #3

### 输入

```
12
1 2 3 6 9 2 3 3 9 6 1 6```

### 输出

```
1178```

# 题解

## 作者：Flandres (赞：4)

## Description

求一个序列中**只出现过一次**的非空子序列的数量。

----------------------------------------

## Solution

一眼 dp。

考场上 dp 状态设计的不好，白费劲推了半天 sad。

我们令 $f_{i}$ 表示**以i结尾的合法子序列数量**。同时对于每一个数值 $a_{i}$，记录其上一次出现的位置 $lst_{a_{i}}$。

不难发现，在 $lst_{a_{i}}$ 之前的答案对当前的答案是没有贡献的。（因为在 $lst_{a_{i}}$ 之前的答案加上 $lst_{a_{i}}$ 和加上 $i$ 是两个相同的子序列，不满足题意。）

所以我们容易得到转移方程：

$$f_{i}=\sum_{j=lst_{a_{i}}}^{i-1}f_{j}$$

然后在转移结束后把 $f_{lst_{a_{i}}}$ 的贡献清零，因为已经不可能再有以 $lst_{a_{i}}$ 结尾的合法序列了。

对于每一个**新出现的数值** $a_{i}$ 其初始状态为 $1$，即选择它本身

暴力转移会 TLE，可以使用树状数组优化，单点修改并且维护区间和。


```cpp
	n=read();
	for(rg u32 i=1;i<=n;++i)a[i]=read();
  	for(rg u32 i=1;i<=n;++i){
		if(!lst[a[i]]){dp[i]=1;}
		dp[i]=(dp[i]+BIT::query(i-1)-BIT::query(lst[a[i]]?lst[a[i]]-1:0))%mod;
		BIT::modify(i,dp[i]);
		BIT::modify(lst[a[i]],-dp[lst[a[i]]]);
		dp[lst[a[i]]]=0;
		lst[a[i]]=i;
	}
	std::cout<<(BIT::query(n)+mod)%mod;
```


---

## 作者：Conan15 (赞：2)

这题看上去很 DP，但是“**仅出现一次的子序列**”这个东西并不好刻画，我们考虑把它**转化**成另一种表现形式。\
反过来想：什么时候会出现**重复**的子序列呢？当前在 $i$ 这个位置，如果在后面有 $j \lt k$，并且 $a_j = a_k$，那么 $[1,i]$ 的子序列就可以和 $j,k$ 分别拼接得到重复的子序列。\
观察到 $a_j = a_k$，所以我们记 $lst_i$ 表示 $a_i$ 上一次出现的下标。

设 $dp_i$ 表示强制选择 $i$，以 $i$ 结尾的合法子序列数量。\
根据上述推理，$\forall j \in [1,lst_i)$ 对 $dp_i$ 是**没有贡献**的，因为这会导致出现重复子序列。\
而 $\forall j \in (lst_i,i)$ 对 $dp_i$ 是**有贡献**的，不会重复，直接加上即可。\
那 $dp_{lst_i}$ 呢？设 $i$ 这个位置是第 $c$ 次出现 $a_i$，则 $lst_i$ 位置是第 $c-1$ 次出现，即会拼接出一个长度为 $c-1$，全都是 $a_i$ 的子序列。\
然而 $a_i$ 的出现会导致长度为 $c-1$ 的子序列再出现一次，长度为 $c$ 的子序列出现第一次，**加减一就抵消了**。\
同理，以 $lst_i$ 结尾的所有合法子序列，由于 $a_i$ 的出现都会**被重复计数**，但是如果在 $lst_i$ 后面直接加上 $a_i$ 就会产生新的子序列。\
所以我们令 $dp_{lst_i} \to dp_i, dp_{lst_i} = 0$。

容易写出 $O(n^2)$ 的转移代码，但是 $n \leq 2 \times 10^5$。\
考虑优化，发现上述转移方程是**区间和，单点改**的形式，显然可以用**树状数组**优化。

代码中保留 $O(n^2)$ 部分转移，省略 Modint 定义部分。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 15, mod = 998244353;

template <class type,const type mod> struct Modint{ Conan15 qwq? };
typedef Modint<long long, mod> Mint;    //记得自定义 mod

int n, a[N];
int id[N], lst[N];
Mint dp[N], ans;

Mint tr[N];
void add(int x, Mint d) {
    for ( ; x < N; x += x & -x) tr[x] += d;
}
Mint query(int x) {
    if (x == -1) return 0;
    Mint res = 0;
    for ( ; x ; x -= x & -x) res += tr[x];
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        lst[i] = id[a[i]], id[a[i]] = i;
    }
    
    // for (int i = 1; i <= n; i++) {
    //     int pos = lst[i];
    //     for (int j = pos; j < i; j++) dp[i] += dp[j];
    //     if (!pos) dp[i]++;
    //     dp[pos] = 0;
    // }
    
    for (int i = 1; i <= n; i++) {
        int pos = lst[i];
        dp[i] = query(i - 1) - query(pos - 1);
        if (!pos) dp[i]++;
        else add(pos, -dp[pos]), dp[pos] = 0;
        add(i, dp[i]);
    }
    
    for (int i = 1; i <= n; i++) ans += dp[i];
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：int_R (赞：1)

场切模拟赛 T2。

找出 $A$ 中取出方案唯一的非空子序列 $s$ 的数量。

考虑 DP，根据某巨佬口中“很典的方式”定义状态 $f_i$ 表示以第 $i$ 个数结尾的满足条件的非空子序列的个数。同时定义 $pre_i$ 为 $\max\limits_{j\in [1,i-1],a_j = a_i} j$，即在 $i$ 之前最后一个相同的数的下标，若没有则记为 $0$。

对于一个 $i$，$pre_i>0$，那么 $f_i$ 就只能在 $[pre_i,i-1]$ 中转移，因为从 $[1,pre-1]$ 中转移的从 $f_{pre_i}$ 也可以转移，所以代表取出方案并不唯一。

同理对于一组 $i,j$，$j>i,pre_i>0$，$f_j$ 不能从 $f_{pre_i}$ 转移，因为从 $f_{pre_i}$ 转移过来的也能从 $f_i$ 转移，所以也代表取出方案不唯一。

所以对于一个 $i$，可以从 $\forall j\in[pre_i,i-1],j\ne pre_k(k\in[1,i-1])$ 中转移过来，可以列出状态转移方程。

$
f_i=\begin{cases}
\sum\limits_{j=pre_i}^{i-1} f_j\times [j\ne pre_k(k\in[1,i-1])] & (pre_i>0)\\
\sum\limits_{i=1}^{i-1} f_i\times [j\ne pre_k(k\in[1,i-1])]+1 & (pre_i=0)
\end{cases}
$

考虑对区间求和进行优化，发现前缀和并不可行，所以我们使用树状数组，每次转移完后将 $t_i$ 设为 $f_i$，$t_{pre_i}$ 设为 $0$。查询 $\sum\limits_{j=pre_i}^{i-1} t_j $ 即可。

$
f_i=\begin{cases}
t(i-1,i)-t(pre_i-1,i) & (pre_i>0)\\
t(i-1,i)+1 & (pre_i=0)
\end{cases}
$

$
t(x,y)=\sum\limits_{i=1}^{x-1} f_i\times [i\ne pre_j(j\in[1,y-1])]
$

最后答案即 $t(n,n)$，也就是所有数字最后一个的 $f$ 值的和。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=2e5+10,MOD=998244353;
int n,a[MAXN],pre[MAXN],lst[MAXN];
long long f[MAXN],t[MAXN];
inline int lowbit(int x){return x&(-x);}
inline void change(int x,long long a)
{
	while(x<=n) t[x]+=a,t[x]%=MOD,x+=lowbit(x);
	return ;
}
inline long long query(int x)
{
	long long ans=0;
	while(x) ans+=t[x],ans%=MOD,x-=lowbit(x);
	return ans;
}
int main()
{
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>n;
	for(register int i=1;i<=n;++i) cin>>a[i],pre[i]=lst[a[i]],lst[a[i]]=i;//记录 pre[i]
	for(register int i=1;i<=n;++i)
	{
		if(pre[i])
		{
			f[i]=(query(i-1)-query(pre[i]-1))%MOD;
			change(pre[i],-f[pre[i]]);//这里要转移完成后再更新
		}
		else f[i]=(query(i-1)+1)%MOD;
		change(i,f[i]);//将 i 号节点更新
	}
	cout<<(query(n)+MOD)%MOD<<'\n';return 0; 
}
```


---

## 作者：白简 (赞：0)

设 $pre_i$ 表示在 $i$ 之前最后一个和 $i$ 相同的数的位置，$dp_i$ 表示第 $i$ 个数为结尾的序列的合法方案数。

对于 $pre_i = 0$，即在 $i$ 之前不存在与 $i$ 相同的数，$dp_i$ 由 $\left[ 1,i - 1 \right]$ 转移过来。由于这个数还没有在之前出现过，它本身也是一个合法序列，所以要加 $1$。

$$dp_i= \sum_{j=1}^{i-1}dp_j + 1$$

对于 $pre_i \neq 0$，即在 $i$ 之前存在与 $i$ 相同的数，那么我们考虑 $\left[ 1,pre_i - 1 \right]$ 这部分，由于 $i$ 已经在之前出现过了，这部分序列加上 $i$ 的部分在 $pre_i$ 已经处理过了，再加的话会导致重复。

考虑 $\left[ pre_i,i - 1 \right]$ 这部分，对于之前加过的单独的 $i$，这时候要 $-1$，但是又因为产生了新序列 $\left\{ pre_i,i \right\}$，这里要 $+1$，所以最终不加不减。

$$dp_i=\sum^{i-1}_{j=pre_i}dp_j$$

最后我们用树状数组对区间求和进行优化。

---

## 作者：Rolling_star (赞：0)

定义 dp 状态 $f_{i}$ 为以 $i$ 为结尾的独特序列个数，考虑转移。

设 $lst_i$ 为上一次出现数 $i$ 的地方，则 $a_i$ 的转移不能到 $lst_{a_i}$ 及之前，因为这样的话就会有并不独特的序列更新，而且在 $a_i$ 更新之后，$lst_{a_i}$ 不再产生贡献，因为只需要最后一个用来转移即可，所以转移方程如下：

$$f_i=\sum_{j=lst_{a_i}+1}^{a_i-1}f_j$$

因为要消去影响，所以每次转移之后 $f_{lst_{a_i}}=0$。

如果直接转移的话复杂度是 $O(n^2)$ 的，然后发现转移方程可以用树状数组维护，时间复杂度减为 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;

const int p=998244353;
int n,a[N],f[N],lst[N],ans;
struct FenwickTree{
    int c[N];
    int lowbit(int x){return x&(-x);}
    void update(int x,int val){if(!x) return; for(int i=x;i<=n;i+=lowbit(i)) c[i]=(c[i]+val+p)%p;}
    int query(int x){int ans=0;for(int i=x;i;i-=lowbit(i)) ans=(ans+c[i])%p;return ans;}
}T;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%lld",a+i);
    for(int i=1;i<=n;i++){
        if(!lst[a[i]]) f[i]=1;
        f[i]=(f[i]+(T.query(i-1)-T.query(max(0ll,lst[a[i]]-1))+p)%p)%p;
        T.update(i,f[i]);T.update(lst[a[i]],-f[lst[a[i]]]);lst[a[i]]=i;
    }
    for(int i=1;i<=n;i++)
        ans=(ans+f[lst[i]])%p;
    cout<<ans;
}
```

---

## 作者：NKL丶 (赞：0)

## Description

给出一个长度为 $N$ 的序列 $A$，求只出现过一次的子序列的数量，结果对质数取模。（$1 \leq N \leq 2 \times 10^5$，$1 \leq A_i \leq N$）

## Solution

我们通过观察可知，对于第 $x$ 位而言，合法的以它为结尾的子序列都可以从先前某些合法序列推出。

所以考虑DP，设 $f_x$ 表示到了第 $x$ 位时以 $A_x$ 结尾的子序列的数量。

通过分析性质，可以发现对于第 $i$ 位而言，若在它之前 $A_i$ 已经重复出现过，不妨令其位置为 $lst$，那么之前以 $A_{lst}$ 结尾的所有子序列均不合法。

因此可以得出转移方程： $f_x = \sum\limits^{x-1}_{i=lst}f_i$，因此记录下所有数最近一次出现的位置，使用树状数组维护 $f$ 的区间和，同时单点修改清除 $f_{lst}$ 的数据即可。

## [Code](https://www.luogu.com.cn/paste/bi6jzyut)

---

## 作者：5k_sync_closer (赞：0)

设 $f_i$ 表示 $[1,i]$ 中以 $a_i$ 结尾的唯一子序列个数，则有 $f_i=\sum\limits_{j\in[p_{a_i},i),j=p_{a_j}}f_j$，其中 $p_j$ 表示 $[1,i]$ 中 $j$ 的最后一次出现位置。

维护 $c_i=\begin{cases}f_i&i=p_{a_i}\\0&i\ne p_{a_i}\end{cases}$，则 $f_i=\sum\limits_{j=p_{a_i}}^{i-1}c_j$。

发现每次转移需要查询 $c_i$ 区间和，然后单点更新 $c_i$，BIT 维护 $c_i$ 即可。

```cpp
#include <cstdio>
#define M 998244353
#define int long long
int n, q, a[200050], p[200050], f[200050], c[200050];
void C(int x, int k)
{
    for (++x; x <= n + 1; x += x & -x)
        c[x] = (c[x] + k) % M;
}
int Q(int x)
{
    int q = 0;
    for (++x; x; x &= x - 1)
        q = (q + c[x]) % M;
    return q;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    C(0, f[0] = 1);
    for (int i = 1; i <= n; ++i)
    {
        f[i] = (Q(i) + M - Q(p[a[i]] - 1)) % M;
        if (p[a[i]])
            C(p[a[i]], M - f[p[a[i]]]);
        C(p[a[i]] = i, f[i]);
    }
    for (int i = 1; i <= n; ++i)
        if (i == p[a[i]])
            q = (q + f[i]) % M;
    printf("%lld", q);
    return 0;
}
```


---

