# [ABC284Ex] Count Unlabeled Graphs

## 题目描述

你需要通过以下一系列操作生成一个图。

- 自由选择一个没有顶点标签的 $N$ 个顶点的简单无向图。
- 给图的每个顶点各写上一个不超过 $K$ 的正整数。要求 $1$ 到 $K$ 的每个正整数都必须被写在某个顶点上，不能有遗漏。

请计算通过上述操作可能得到的不同图的数量，并对 $P$ 取模后输出（$P$ 是**素数**）。

注意，如果两个图可以分别给顶点加上标签 $v_1, v_2, \dots, v_N$，使得满足以下条件，则认为这两个图是相同的：

- 对于所有 $1 \leq i \leq N$，顶点 $v_i$ 上写的数在两个图中相同。
- 对于所有 $1 \leq i < j \leq N$，$v_i$ 和 $v_j$ 之间是否有边在两个图中相同。

## 说明/提示

## 限制

- $1 \leq K \leq N \leq 30$
- $10^8 \leq P \leq 10^9$
- $P$ 是素数
- 输入的所有值均为整数

## 样例解释 1

满足条件的图有如下 $4$ 种。 ![image](https://img.atcoder.jp/ghi/abc283h_43c4abe0e541b7ebeaa8db2854cece91caeca71f03f452ca13c11e82f85e3a56.png)

## 样例解释 2

满足条件的图有如下 $12$ 种。 ![image2](https://img.atcoder.jp/ghi/abc284h2_ca96b7cb451b0e495209e3e201576d278de3fb823e5d2404bbce5d9f704e3259.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 1 998244353```

### 输出

```
4```

## 样例 #2

### 输入

```
3 2 998244353```

### 输出

```
12```

## 样例 #3

### 输入

```
5 5 998244353```

### 输出

```
1024```

## 样例 #4

### 输入

```
30 15 202300013```

### 输出

```
62712469```

# 题解

## 作者：xtx1092515503 (赞：3)

本质不同计数。显然要 burnside 或 polya。

> 本人的 [洛谷日报](https://www.luogu.com.cn/blog/Troverld/qun-lun-xue-xi-bi-ji) 记载了相关内容。

我们考虑强行为无标号图定一个 $1\sim n$ 的标号，然后为每个标号的点染一种颜色。

这样之后，考虑一个标号的置换，并计算其不动点。

置换下的不动点有什么要求呢？

- 经置换前后的两个点颜色应相同。
- 若边 $(i,j)$ 存在，则边 $(p_i,p_j)$ 存在，其中 $p$ 为枚举的置换。

颜色相同的要求很简单，就是置换内部的每个环，其中所有元素颜色相同。换句话说，若置换固定，则上色的过程就是：

- 有 $a$ 个环，要染成 $b$ 种颜色，使得每种颜色都至少出现一次。

简单容斥一下，可得方案数为
$$
\sum\limits_{i=0}^b\dbinom bii^a(-1)^{b-i}
$$
然后是边的要求。我们将边分为两类：环内部的边，以及两个环之间的边。

首先是环内边。我们不妨将环中点顺次标号为 $0,1,\dots,t-1$。则，环中若存在一条边 $(i,(i+k)\bmod t)$，则对于所有的 $i$，均存在这样一条边。显然对于每个 $k$，这些边要么全出现，要么全不出现，所以方案数即为 $2^{k\text{的个数}}$。而，$k$ 和 $t-k$ 其实是本质相同的；于是，事实上仅有 $k\in[1,\left\lfloor\dfrac t2\right\rfloor]$ 才有效，于是方案数即为 $2^{\left\lfloor t/2\right\rfloor}$。

环间边更简单。设两个环的大小分别为 $x$ 和 $y$，则若 $x$ 中某个点 $i$ 向 $y$ 中某个点 $j$ 连一条边，则连向的不止是 $j$，还有 $j+\gcd(x,y),j+2\gcd(x,y),\dots$。于是其实只有 $\gcd(x,y)$ 种不同的剩余类，每种剩余类要么全选要么全不选，所以方案数直接就是 $2^{\gcd(x,y)}$。

我们已经可以对一个 $p$ 算答案了。但是我们显然无法枚举全体 $p$；但是，注意到我们只关系 $p$ 中的环大小构成的可重集，而所有这样的可重集的方案数其实是 $\text{划分数}(n)$ 的。于是我们直接大力枚举划分数，然后在内部暴力枚举两个环算方案即可。复杂度 $O(\text{划分数}(n)n^2)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,mod,p[40],res;
int ksm(int x,int y=mod-2){int z=1;for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)z=1ll*z*x%mod;return z;}
bool vis[40];
int fac[40],inv[40];
int C(int x,int y){return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
vector<int>v;
void mina(){
	// for(auto x:v)printf("%d ",x);puts("");
	int way=1,rem=n;
	for(int l=0,r=0;l<v.size();l=r){
		for(;r<v.size()&&v[l]==v[r];r++);
		for(int j=l;j<r;j++)way=1ll*way*C(rem,v[j])%mod*fac[v[j]-1]%mod,rem-=v[j];
		way=1ll*way*inv[r-l]%mod;
	}
	// printf("<%d>\n",way);
	int ser=0,qwq=1;
	for(int i=0;i<=m;i++){
		int val=1ll*ksm(i,v.size())*C(m,i)%mod;
		if((m-i)&1)(ser+=mod-val)%=mod;else(ser+=val)%=mod;
	}
	for(auto a:v){
		int tot=0;
		for(int i=1;i<=(a>>1);i++)tot++;
		qwq=1ll*qwq*ksm(2,tot)%mod;
	}
	for(int i=0;i<v.size();i++)for(int j=i+1;j<v.size();j++){
		int x=v[i],y=v[j];
		qwq=1ll*qwq*ksm(2,__gcd(x,y))%mod;
	}
	// printf("<%d,%d>\n",ser,qwq);
	ser=1ll*ser*qwq%mod*way%mod;
	(res+=ser)%=mod;
}
void dfs(int rem,int lim){
	// printf("dfs:%d,%d:",rem,lim);for(auto x:v)printf("%d ",x);puts("");
	if(!rem)return mina();
	for(int i=1;i<=lim&&i<=rem;i++)
		v.push_back(i),dfs(rem-i,i),v.pop_back();
}
int main(){
	scanf("%d%d%d",&n,&m,&mod);
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n;i;i--)inv[i-1]=1ll*inv[i]*i%mod;
	dfs(n,n);
	printf("%d\n",1ll*res*inv[n]%mod);
	return 0;
}
```



---

## 作者：xlpg0713 (赞：0)

求出点数为 $n$，每个点都染 $1$ 到 $k$ 中的一种颜色，且每种颜色都出现的图的同构计数。要求同构，考虑使用群论知识。

# 题解
考虑 $k=1$，即[图的同构计数](https://www.luogu.com.cn/problem/P4727)，做法可以参考我的[博客](https://www.luogu.com.cn/blog/xlpg0713/p4128p4727-post)，这里只把式子写出来。以下的一些说法均可以在博客中找到出处。

$ans=\sum\limits_{(a_1,a_2\cdots a_m)\land\sum a_i=n}\frac{2^{\sum\lfloor\frac{a_i}{2}\rfloor+\sum\limits_{i\ne j}\gcd(a_i,a_j)}}{\prod a_i\prod c_i!}$。$c_i$ 表示 $\sum\limits_j[a_j=i]$。

再看这题，我们需要考虑一种点置换下不动点的数量，发现这等价于满足边轮换中的边存在状态相同（即图的同构计数）的同时，加上每个点轮换颜色相同这一条限制。

于是要求出 $m$ 个轮换，染 $k$ 种颜色，每种颜色都要出现的情况数，用最基础的容斥得：$\sum\limits_{i=0}^{k}\operatorname{C}(k,i)\times i^m\times (-1)^{k-i}$。

然后这题做完了

```cpp
#include<iostream>
#include<algorithm>
int n, k, p, rs, fc[50], iv[50], a[50], c[50];
inline int qp(int a, int b){int r=1;
	for(; b; b >>= 1, a = 1ll * a * a % p)
		b & 1 ? r = 1ll * r * a % p : 0; return r;
}
inline int C(int n, int m){return 1ll*fc[n]*iv[m]%p*iv[n-m]%p;} 
inline void dfs(int x, int sm, int t){ 
	if(sm == n){
		if (x < k) return;
		int o = 0, y = 1, z = 0;
		for(int i = 1; i <= x; i++) o += a[i] >> 1, y = 1ll * y * a[i] % p;
		for(int i = 1; i <= t; i++) y = 1ll * y * fc[c[i]] % p;
		for(int i = 1; i <= x; i++) for(int j = i+1; j <= x; j++) o += std::__gcd(a[i], a[j]);
		for(int i = 0, o; i <= k; i++){
			o = 1ll * C(k, i) * qp(i, x) % p;
			if((k-i) & 1) z = (z + p - o) % p;
			else z = (z + o) % p;
		}
		rs = (rs + 1ll * qp(2, o) * qp(y, p-2) % p * z % p) % p;
		return;
	}
	for(int i = t; i <= n-sm; i++)
		a[x+1] = i, ++c[i], dfs(x+1, sm+i, i), --c[i];
}
int main(){
	std::cin >> n >> k >> p; fc[0] = iv[0] = 1;
	for(int i = 1; i <= n; i++)
		fc[i] = 1ll * fc[i-1] * i % p,
		iv[i] = 1ll * iv[i-1] * qp(i, p-2) % p;
	dfs(0, 0, 1); std::cout << rs << '\n';
}
```

---

## 作者：zhouyuhang (赞：0)

注意到 $k=1$ 时即为 [无标号无向图计数](https://www.luogu.com.cn/problem/P4727)，考虑使用相同方法。快进到对于置换 $g$ 计算稳定子个数。我们可以将图在 $g$ 作用后同构拆解为 图的边同构 和 图的颜色同构。对于边同构而言，容易得到与原题相同的结论：若 $g$ 可以被拆为 $c(g)$ 个轮换，第 $i$ 个轮换大小为 $b_i$，则可以将边划分为 $l=\sum_{i=1}^{c(g)}\lfloor\frac{b_i}{2}\rfloor+\sum_{i=1}^{c(g)}\sum_{j=1}^{i-1}\gcd(b_i,b_j)$ 个等价类，每个等价类必然全选或全不选，因此有 $2^l$ 种边同构的图。而对于本题所增加的颜色同构，不难发现若一种染色方法在置换 $g$ 作用下是稳定子，那么同一轮换内的点所染颜色必然相同，至于 “所有 $k$ 种颜色均出现” 的限制不难二项式反演去掉。具体而言，染色方法共有 $\sum_{i=0}^k(-1)^i\binom{c(g)}{i}(k-i)^{c(g)}$ 种。由于边的同构和颜色的同构之间相互独立，因此稳定子数量即为这两者的乘积。照搬原题做法，枚举分拆计算贡献，即可做到 $O(p(n)n^2)$，其中 $p(n)$ 为分拆数。

---

