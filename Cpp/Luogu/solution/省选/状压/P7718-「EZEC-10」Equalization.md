# 「EZEC-10」Equalization

## 题目描述

给你一个长为 $n$ 的数组 $a_1,a_2,\ldots,a_n$。

你可以任选三个整数 $l,r,x\ (1\le l\le r\le n$，$x\in \mathbb Z)$，并将 $a_l,a_{l+1},\ldots,a_r$ 均加上 $x$，称为一次操作。

问最少进行几次操作，才能使 $a$ 中所有元素均相等？并求出能使操作次数最少的不同方案数。

由于方案数可能很大，请对 $10^9+7$ 取模。

**两种方案相同，当且仅当两方案每次操作选择的 $(l,r,x)$ 均相同。**

**特别地，不进行任何操作也算一种方案。**

## 说明/提示

**【样例 1 解释】**

一种可行的方案为：$(l,r,x)=(1,1,1),(3,3,-1)$。

**【数据规模与约定】**

**本题采用捆绑测试。**

-  Subtask 1（1 point）：$n=2$。
-  Subtask 2（5 points）：$n=3$。
-  Subtask 3（14 points）：保证 $a$ 单调不升或单调不降。
-  Subtask 4（20 points）：$n\le 10$。
-  Subtask 5（20 points）：$n\le 16$。
-  Subtask 6（40 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le n\le 18$，$-10^9\le a\le 10^9$。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2
16```

# 题解

## 作者：tzc_wk (赞：9)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P7718)

一道挺有意思的题，现场切掉还是挺有成就感的。

首先看到区间操作我们可以想到差分转换，将区间操作转化为差分序列上的一个或两个单点操作，具体来说我们设 $b_i=a_{i+1}-a_i$，那么对于一次形如 $\forall i\in[l,r],a_i\leftarrow a_i+x$ 的操作三元组 $(l,r,x)$，我们有：

- $l=1,r=n$，等于啥也没干，那么我们显然不会选择这样的区间进行操作，否则就会浪费一次操作次数，所以我们 duck 不必考虑这种情况。
- $l=1,r\ne n$：相当于令 $b_{r}\leftarrow b_r-x$
- $l\ne 1,r=n$：相当于令 $b_{l-1}\leftarrow b_{l-1}+x$
- $l\ne 1,r\ne n$：相当于令 $b_{l-1}\leftarrow b_{l-1}+x,b_r\leftarrow b_r-x$

于是问题转化为：给定长度为 $n-1$ 的差分序列，每次可以进行以下两种操作之一：修改一个单点的值，或者指定三个整数 $x,y,z$，将 $b_x$ 改为 $b_x+z$，$b_y$ 改为 $b_y-z$，最少需要多少次操作才能将所有数变为 $0$。

直接处理不太容易，因此考虑挖掘一些性质。做过[这道题](https://www.luogu.com.cn/problem/P6775)的同学应该不难想到，我们可以在每次操作的两个点之间连一条边，如果咱们操作的是一个单点那么就连一条自环，这样显然会得到一张点数为 $n-1$，边数等于操作次数的图。那么有一个性质：在最优策略连出的图中，对于每个连通块 $(V',E')$，记 $S=\sum\limits_{x\in V'}b_x$，有

- 如果 $S=0$，那么该连通块必然是一棵树，耗费 $|V'|-1$ 次操作。
- 如果 $S\ne 0$，那么该连通块必然是一棵树加一个自环，耗费 $|V'|$ 次操作。

~~证明不会，感性理解一下即可~~

观察到这个性质之后，求解第一问就易如反掌了，注意到 $n$ 很小，因此考虑状压，记 $dp_S$ 表示将 $S$ 中的元素变为 $0$ 的最少操作次数，枚举子集转移即可，复杂度 $3^{n-1}$。

接下来考虑第二问，显然每次操作都是不同的，因此我们可以只用考虑操作方案的集合有哪些，最后乘个操作次数的阶乘即可。其次，如果我们能够知道对于一个连通块而言，将它按照最优策略变为 $0$ 的方案数，我们就能用乘法原理一边 DP 一遍记录将每个集合变为 $0$ 的最优策略的方案数了。因此考虑将每个集合变为 $0$ 的方案数，还是分 $S=0$ 和 $S\ne 0$ 两种情况处理：

- $S=0$，那么该连通块是一棵无根树，那么可以很自然地猜到应该跟什么有标号树计数有关，Prufer 序列算一算结果是 $|V'|^{|V'|-2}$，事实上结论也的确如此，这里稍微口胡一下证明：显然一个操作集合唯一对应一棵树，而对于一棵无根树而言，能够得到它的操作集合也是唯一的，证明可以通过构造方案说明：我们假设这棵树中编号最大（其实大不大无所谓，只要形成一个严格的偏序关系即可）的叶子节点为 $u$，与其相连的点为 $v$，那么我们必须让 $u$ 的权值变为 $0$，因为否则进行完此次操作之后，点 $u$ 就孤立了，无法再次通过两点的操作变回 $0$ 了，因此这次操作 $u$ 的权值必须减去 $a_u$，$v$ 的权值也就必然加上 $a_u$，如此进行下去直到还剩一个点为止，而由于该连通块中权值之和为 $0$，因此最终剩下的那个点权值也是 $0$，故我们构造出的方案合法。又因为我们每一次操作唯一，因此操作集合唯一；如果我们改变下操作的边集的顺序那么显然操作集合不会变，因此操作集合与无根树形成双射关系，证毕。
- $S\ne 0$，其实不过是在无根树的基础上加了一个自环，加这个自环的侯选位置总共有 $|V'|$ 个，再加上对于这个自环而言有两个区间能够改变差分序列上这个点的值（假设我们要改变 $b_x$，那么我们可以操作 $[1,x]$，也可以操作 $[x+1,n]$），因此还需乘个 $2$，总方案数 $2|V'|^{|V'|-1}$，如果你~~力求极致、追求严谨~~，那么也可以仿照 $S=0$ 的证明方式。

时间复杂度 $\mathcal O(3^{n-1})$。

```cpp
using namespace fastio;
const int MAXN=18;
const int MAXP=1<<17;
const int MOD=1e9+7;
const int INF=0x3f3f3f3f;
int n,a[MAXN+3],b[MAXN+3],m=0,c[MAXN+3],cnt[MAXP+5],fac[MAXN+5];
int f[MAXN+5],g[MAXN+5];
ll sum[MAXP+5];pii dp[MAXP+5];
inline int high(int x){return (!x)?-1:(31-__builtin_clz(x));}
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
void upd(pii &x,pii y,int v,int z){
	return (x.fi<y.fi+v)?void():(((x.fi==y.fi+v)?(x.se=(x.se+1ll*y.se*z)%MOD):
	(x.fi=y.fi+v,x.se=1ll*y.se*z%MOD)),void());
}
int main(){
	scanf("%d",&n);dp[0]=mp(0,1);
	for(int i=(fac[0]=1);i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	for(int i=2;i<=n;i++) g[i]=qpow(i,i-2),f[i]=2ll*g[i]*i%MOD;f[1]=2;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++) b[i]=a[i+1]-a[i];
	for(int i=1;i<n;i++) if(b[i]) c[++m]=b[i];
	for(int i=1;i<(1<<m);i++) dp[i].fi=INF;
	for(int i=1;i<(1<<m);i++){
		int pos=32-__builtin_clz(i&(-i));
		sum[i]=sum[i&(i-1)]+c[pos];
		cnt[i]=cnt[i&(i-1)]+1;
	}
	for(register int i=0;i<(1<<m);i++){
		register int rst=((1<<m)-1)^i;
		for(register int j=rst;j;j=(j-1)&rst){
			if(high(j)<high(i)) break;
			(!sum[j])?upd(dp[i|j],dp[i],cnt[j]-1,g[cnt[j]]):
			upd(dp[i|j],dp[i],cnt[j],f[cnt[j]]);
		}
	} printf("%d\n%d\n",dp[(1<<m)-1].fi,1ll*dp[(1<<m)-1].se*fac[dp[(1<<m)-1].fi]%MOD);
	return 0;
}
```



---

## 作者：Ecrade_ (赞：7)

### 定义

下文中 “A 状态” 表示满足所有数之和为 $0$ 的状态，“A 子集” 同理；“B 状态” 表示某最优方案中，去除所有 “A 状态” 后剩余的那个状态。

---
### **求最少操作次数**

对于静态区间加，我们很容易想到对数列的差分数组进行操作。

令 $d_i$ 表示 $a_{i+1}-a_i\ (i=1,2,...,n-1)$。

那么可将每次操作转化为：

$$\begin{cases}d_r:=d_r-x&l=1\\d_{l-1}:=d_{l-1}+x&r=n\\d_{l-1}:=d_{l-1}+x,d_r:=d_r-x&l\ne 1\ \text{and}\ r\ne n\end{cases}$$

换句话来说，就是每次你可以进行如下两种操作的其中一种：

- 任选两数 $p,q$，$d_p:=q$。

- 任选三数 $p,q,r$，$d_p:=d_p+r,d_q:=d_q-r$。

而根据题目，我们要将 $d$ 数组全变为 $0$。

不难发现，若每次都进行第一种操作，次数最多为 $n-1$。

观察可得，当 $d$ 中某个数为 $0$ 或者某些数之和为 $0$ 时，我们可以省去一次操作。

这样，我们的目标就是将 $d$ 数组尽可能多地划分为和为 $0$ 的组。

考虑状压。

令 $f_i$ 表示 A 状态为 $i$ 时，可**恰好**划分成和为 $0$ 的最大组数。

对所有 A 状态 $i$，将 $f_i$ 初始化为 $1$。

我们对所有 $i$ 的 A 子集 $j$ 进行如下转移：

$$f_i=\max(f_i,f_j+f_{i\ \text{xor} \ j})$$

答案即为 $n-1-\max\limits^{2^{n-1}-1}_{i=1} {f_i}$。

时间复杂度为 $O(3^{n-1})$。

---
### **求方案数**

我们只需计算本质不同的方案数，最后乘上最少操作次数的阶乘即可。

**先考虑 A 状态。**

令 $g_i$ 表示 A 状态为 $i$ 时，本质不同的方案数。

令 $bit_i$ 表示 A 状态为 $i$ 中数的个数。

对于 A 状态 $i$，若不考虑进一步划分，我们发现对 $i$ 中所有数进行第二种操作时最优。

在 $i$ 中，选定某个非 $0$ 的数 $x$ 后，再选择另一个非 $0$ 的数 $y$，将 $x$ 变为 $0$，$y$ 变为 $y+x$；……

如此重复进行下去，最终所有数均会变为 $0$。

此时，本质不同的方案数即为 $bit_i$ 点有标号树计数。（对于每个非根节点，其自身作为 $x$，其父节点作为 $y$。）

根据 prufer 序列可推得，方案数为 $bit_i^{bit_i-2}$。

故我们对所有 A 状态 $i$，将 $g_i$ 初始化为 $bit_i^{bit_i-2}$。

在更新 $f$ 数组时，可同时更新 $g$ 数组。

我们对所有 $i$ 的 A 子集 $j$ 进行如下转移：

$$\begin{cases}g_i:=g_i+g_j\times g_{i\ \text{xor} \ j}&f_i=f_j+f_{i\ \text{xor} \ j}\\g_i:=g_j\times g_{i\ \text{xor} \ j}&f_i<f_j+f_{i\ \text{xor} \ j}\end{cases}$$

而这样转移可能会重复计算。

故考虑只枚举不包含任何 A 子集的 $j$。

当然，每枚举一个 $j$，就要对所有 $i\ \text{xor}\ j$ 的子集进行标记，之后也就不会再枚举到 $i\ \text{xor}\ j$ 的子集了。

这样我们就成功避免了重复计算的问题。

**再考虑 B 状态。**

令 $c_i$ 表示 B 状态为 $i$ 时，本质不同的方案数。

不难发现，B 状态中所有数之和与 $a_1-a_n$ 相加恰为 $0$。

故将 B 状态再加入 $a_1-a_n$ 即可变为 A 状态。

沿用处理 A 状态的思路，而注意，当选中的 $x$ 或 $y$ 中有一个是 $a_1-a_n$ 时，就会存在两种可能的情况。

故在进行计算时，可以考虑将 $a_1-a_n$ 看作一个含两个点的连通块。

根据 prufer 序列可推得，$c_i=2\times (bit_i+2)^{bit_i-1}$。

**最后枚举所有能达到最少操作次数的状态。**

易得满足条件的状态 $i$ 贡献为 $g_i\times c_{n-1-bit_i}$。

将所有状态的贡献相加求和，再乘上最少操作次数的阶乘即为最终答案。

注意特判 $f$ 数组均为 $0$ 的情况，此时的答案为 $c_{n-1}$ 乘上最少操作次数的阶乘。

时间复杂度仍为 $O(3^{n-1})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,cnt,ans1,ans2,a[18],d[18],c[18],fact[18],power[18],f[1 << 17],g[1 << 17],v[1 << 17],val[1 << 17],bit[1 << 17],mod = 1e9 + 7;
inline ll read(){
   ll s = 0,w = 1;
   char ch = getchar();
   while (ch < '0'|| ch > '9'){ if (ch == '-') w = -1; ch = getchar();}
   while (ch >= '0'&& ch <= '9') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
   return s * w;
}
ll qp(ll x,ll y){
	ll a = 1,b = x;
	while (y){
		if (y & 1) a = a * b % mod;
		b = b * b % mod,y >>= 1;
	}
	return a;
}
int main(){
	n = read();
	for (ll i = 0;i < n;i += 1) a[i] = read();
	n -= 1;
	for (ll i = 0;i < n;i += 1) d[i] = a[i + 1] - a[i];
	c[0] = fact[0] = power[1] = 1;
	for (ll i = 1;i <= n;i += 1) fact[i] = fact[i - 1] * i % mod;
	for (ll i = 2;i <= n;i += 1) power[i] = qp(i,i - 2);
    for (ll i = 1;i <= n + 1;i += 1) c[i] = 2 * qp(i + 2,i - 1) % mod;
	for (ll i = 1;i < (1 << n);i += 1){
		ll sum = 0;
		for (ll j = 0;j < n;j += 1) if (i & (1 << j)) sum += d[j],bit[i] += 1;
		if (!sum) f[i] = 1,g[i] = power[bit[i]];
	}
	for (ll i = 1;i < (1 << n);i += 1) if (f[i]){
		bool fl = 1;
		for (ll j = (i - 1) & i;j;j = (j - 1) & i) if (f[j]){fl = 0; break;}
		val[i] = fl;
	}
	for (ll i = 1;i < (1 << n);i += 1) if (f[i]){
		for (ll j = i;j;j = (j - 1) & i) v[j] = 0;
		for (ll j = (i - 1) & i;j;j = (j - 1) & i) if (val[j] && !v[j]){
			if (f[j] + f[i ^ j] > f[i]) f[i] = f[j] + f[i ^ j],g[i] = g[j] * g[i ^ j] % mod;
			else if (f[j] + f[i ^ j] == f[i]) g[i] = (g[i] + g[j] * g[i ^ j] % mod) % mod;
			for (ll k = (i ^ j);k;k = (k - 1) & (i ^ j)) v[k] = 1;
		}
	}
	ans1 = n - *max_element(f,f + (1 << n));
	if (ans1 == n){cout<<n<<endl<<c[n] * fact[ans1] % mod; return 0;}
	for (ll i = 0;i < (1 << n);i += 1) if (f[i] == n - ans1) ans2 = (ans2 + g[i] * c[n - bit[i]] % mod) % mod;
	cout<<ans1<<endl<<ans2 * fact[ans1] % mod;
	return 0;
}
```


---

## 作者：littleKtian (赞：6)

区间加不好直接搞，考虑先对原数组进行差分。

记 $b_i=a_i-a_{i-1}\left(1\leq i\leq n+1,a_0=a_{n+1}=0\right)$。那么对于每次的操作，相当于令 $b_i$ 加上 $x\left(x\in \mathbb Z\right)$，并让 $b_j\left(j>i\right)$ 减去 $x$。最后的目标相当于 $\forall 2\leq i\leq n,b_i=0$。

显然存在一种方案，每次对 $b_1$（或 $b_{n+1}$）和 $b_i(2\leq i\leq n)$ 进行一次操作，此时操作次数为 $n-1$。

发现对于下标集合 $S\subset \left[2,n\right]$，如果 $\sum\limits_{i\in S}b_i=0$，那么我们可以通过在这个集合内部进行操作，从而使操作次数减少 $1$。

所以最小操作次数就是 $n-d-1$，其中 $d$ 为最多能分出的**互不相交**的集合 $S$ 的个数。

设 $f_T$ 表示集合 $T$ 最多能划分出的集合 $S$ 的个数，其中**要求 $T$ 满足 $\sum\limits_{i\in T}b_i=0$**。可以 预处理+状压dp 在 $O(3^{n-1})$ 内求出所有的 $f_T$，最后 $k$ 即为所有 $f_T$ 的最大值。

```cpp
	//代码中的f其实是对应元素的总和，ff才是上文中的f
	zt=1<<(n-1);
	for(int i=1;i<zt;i++)
	{
		int j=i&-i,xj=2;
		while(j!=(1<<(xj-2)))++xj;
		nn[i]=nn[i^j]+1,f[i]=f[i^j]+a[xj];
	}
	for(int i=1;i<zt;i++)if(f[i]==0)
	{
		for(int j=i;j;j=i&(j-1))if(f[j]==0)ff[i]=maxx(ff[i],ff[i^j]+1);
		d=maxx(d,ff[i]);
	}
```

现在考虑计算方案数，考虑先将操作从有序转为无序，最后乘上排列数（因为在操作次数最少的情况下必不可能出现相同的操作）。

假设对于每次操作 $(i,j,x)$，我们想象成在点 $i$ 和点 $j$ 之间连一条边权为 $x$ 的边。可以发现对于**所有我们划分出的集合 $S$**，其所表示的点集最后一定**连成了一棵树**。而对于其他**没有被划进任何一个集合**的点，一定**和点 $1$ 和点 $n+1$ 连成两棵树**，其中点 $1$ 和点 $n+1$ **分别在两棵树内**（这里的树都是有标号**无根树**）。

通过递归证明可以发现，只要连边方案确定，每条边的边权也唯一确定。

每个集合 $S$ 内连边的方案数显然为 $k^{k-2}$（其中 $k$ 为 $S$ 的元素个数）。设 $g_T$ 表示集合 $T$ 的连边方案数（$T$ 要求如上），用和上面类似的方法也可以在 $O(3^{n-1})$ 内推出。

```cpp
	//fff即为上文的g，初始化fff[0]=1
	for(int i=1;i<=n;i++)kk[i]=P(i,max(i-2,0))
	for(int i=1;i<zt;i++)if(f[i]==0)
	{
		//固定某位枚举子集，以防计算重复
		int ti=i&-i,es=i^ti;
		if(f[ti]==0&&ff[i]==ff[es]+1)fff[i]=fff[es];
		for(int j=es;j;j=es&(j-1))
		{
			int tj=j^ti;
			if(f[tj]==0&&ff[i]==ff[i^tj]+1)fff[i]=(fff[i]+1ll*fff[i^tj]*kk[nn[tj]])%p;
		}
	}
```

对于最后部分，可以考虑在点 $1$ 和点 $n+1$ 之间连边后计算连边方案数。如果考场上临时想不到或者忘了怎么算也可以去掉点 $1$ 和点 $n+1$ 来划分成若干棵**有根树**，计算出每部分的方案数相乘后再 $\times 2^t$（$t$ 为树的个数），也可以做到 $O(3^{n-1})$。
```cpp
	//ffff即为上文所述的东西，计算方式和fff基本一致，同样要初始化ffff[0]=1
	for(int i=1;i<=n;i++)kkk[i]=2ll*P(i,i-1)%p;
	for(int i=1;i<zt;i++)
	{
		int ti=i&-i,es=i^ti;
		ffff[i]=2ll*ffff[es]%p;
		for(int j=es;j;j=es&(j-1))
		{
			int tj=j^ti;
			ffff[i]=(ffff[i]+1ll*ffff[i^tj]*kkk[nn[tj]])%p;
		}
	}
```
最后枚举所有 $f_T=d$ 的 $T$，将两部分结果相乘累加即可得到操作无序时的方案数，乘上 $(n-d-1)!$即为答案。

复杂度 $O(3^{n-1})$。

---

## 作者：5ab_juruo (赞：3)

给一种 $O(2^nn^2)$ 的做法。

首先还是将数组差分，然后把一次操作视为连一条边，算上 $0,n$ 两个点，整个图就是一个森林，且 $0,n$ 不在一个连通块内。此时给定树结构的话，可以唯一推出每条边的边权。

最小化边数等价于最大化连通块数。先不考虑所有与 $0,n$ 有连边的连通块，则在其余的连通块中，点权和均为 $0$。设 $f_{S,c}$ 为，当前选了的点的集合为 $S$，最后一个集合的大小为 $c$ 时，最大的连通块数及方案数。转移时枚举下一个点，同时若当前 $S$ 的和为 $0$，则将 $c$ 置零，连通块数加一，方案数乘上 $c^{c-2}/c!$（一个大小为 $c$ 的集合会被枚举 $c!$ 次）。

统计答案时，枚举与 $0,n$ 有连边的点集 $S$，假装 $0,n$ 在一个连通块，则这一部分的连边方案数为 $2(|S|+2)^{|S|-1}$。若最大能产生 $k$ 个和为 $0$ 的连通块，则还要给答案除掉 $k!$。

最后还要乘上操作次数的阶乘，因为操作顺序不一样是两种方案。

```cpp
using ll = long long;
const int max_n = 18, max_s = 1 << max_n, mod = 1e9 + 7;

struct info
{
	int mx, cnt;
	info(int _x = -1, int _y = -1) : mx(_x), cnt(_y) { }
	void add(const info& ox)
	{
		if (ox.mx > mx)
			*this = ox;
		else if (ox.mx == mx)
			cnt = (cnt + ox.cnt) % mod;
	}
	info ext(int x) {
		return { mx, int(1ll * cnt * x % mod) };
	}
};

int a[max_n], fac[max_n], ifac[max_n];
ll sm[max_s];
info f[max_s / 2][max_n], g[max_s];

ll qpow(ll bs, ll ix)
{
	ll cur = 1, mul = bs, ret = 1;
	while (cur <= ix)
	{
		if (cur & ix)
			ret = (ret * mul) % mod;
		mul = (mul * mul) % mod;
		cur <<= 1;
	}
	
	return ret;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 1; i < n; i++)
		a[i - 1] = a[i] - a[i - 1];
	n--;
	
	int lim = 1 << n;
	for (int i = 1; i < lim; i++)
	{
		int x = __lg(i);
		sm[i] = sm[i ^ (1 << x)] + a[x];
	}
	
	fac[0] = 1;
	for (int i = 0; i < n; i++)
		fac[i + 1] = 1ll * fac[i] * (i + 1) % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i > 0; i--)
		ifac[i - 1] = 1ll * ifac[i] * i % mod;
	
	for (int i = 0; i < n; i++)
		f[1 << i][1] = { 0, 1 };
	g[0] = { 0, 1 };
	for (int i = 1; i < lim; i++)
	{
		if (sm[i] == 0)
		{
			for (int k = 1; k <= n; k++)
				g[i].add(f[i][k].ext(1ll * qpow(k, k - 2) * ifac[k] % mod));
			g[i].mx++;
			for (int x = 0; x < n; x++)
				if ((((lim - 1) ^ i) >> x) & 1)
					f[i | (1 << x)][1].add(g[i]);
		}
		for (int c = __builtin_popcount(i); c > 0; c--)
			for (int k = 0; k < n; k++) if (!((i >> k) & 1))
				f[i | (1 << k)][c + 1].add(f[i][c]);
	}
	
	info ans = { -1, 0 };
	for (int i = 0; i < lim; i++)
	{
		info t = g[i];
		int x = __builtin_popcount((lim - 1) ^ i);
		t.cnt = 1ll * t.cnt * (x ? 2 * qpow(x + 2, x - 1) : 1) % mod;
		ans.add(t);
	}
	cout << n - ans.mx << "\n" << 1ll * ans.cnt * fac[n - ans.mx] % mod * ifac[ans.mx] % mod << "\n";
	
	return 0;
}
```

---

## 作者：IdnadRev (赞：0)

差分一下，我们能进行的是单点修改，以及 $a_x+v,a_y-v$。

经典模型，把操作作为有向边建出来，每个连通块要么是树（如果是树，那么和要为 $0$），要么是树以及一次单点修改，更多边一定严格劣。

第一问很容易 $O(3^n)$ 合并集合解决，第二问是类似的，我们只需解决一个大小为 $c$ 的集合操作的方案数：

- 树：对于一种确定加边方案，其边权唯一确定，于是方案数 $c^{c-2}$。
- 非树：任意点都能作为单点修改的位置，而单点修改有两种（$[1,x],[x+1,n]$），于是方案数 $2c^{c-1}$。

复杂度 $O(3^n)$。

代码：
```cpp
#include<stdio.h>
#include<iostream>
#define lowbit(x) x&(-x)
#define inf 1000000000
using namespace std;
const int maxn=19,maxt=1<<maxn,mod=1000000007;
int n,m,cs;
int a[maxn],fac[maxn],v1[maxn],v2[maxn],bitcnt[maxt],lg[maxt],v[maxt];
long long sum[maxt];
pair<int,int>f[maxt];
int ksm(int a,int b) {
	int res=1;
	while(b) {
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
inline void update(int x,int y,int a,int b) {
	if(f[x].first==f[y].first+a)
		f[x].second=(f[x].second+1ll*f[y].second*b)%mod;
	if(f[x].first>f[y].first+a)
		f[x].first=f[y].first+a,f[x].second=1ll*f[y].second*b%mod;
}
int main() {
	scanf("%d",&n),fac[0]=fac[1]=1,v2[1]=2;
	for(int i=2; i<=n; i++)
		fac[i]=1ll*fac[i-1]*i%mod,v1[i]=ksm(i,i-2),v2[i]=2ll*v1[i]*i%mod;
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]);
	for(int i=1; i<n; i++)
		if(i<n&&a[i]!=a[i+1])
			v[1<<cs]=a[i+1]-a[i],cs++;
	m=(1<<cs)-1,f[0]=make_pair(0,1),lg[0]=-1;
	for(int i=1; i<=m; i++) {
		f[i].first=inf,lg[i]=lg[i>>1]+1;
		bitcnt[i]=bitcnt[i>>1]+(i&1),sum[i]=sum[i^lowbit(i)]+v[lowbit(i)];
	}
	for(int S=0; S<=m; S++)
		for(int i=(m^S); i&&lg[i]>=lg[S]; i=(i-1)&(m^S))
			update(S|i,S,bitcnt[i]-(sum[i]==0),(sum[i]==0? v1:v2)[bitcnt[i]]);
	printf("%d\n%d\n",f[m].first,1ll*f[m].second*fac[f[m].first]%mod);
	return 0;
}
```

---

