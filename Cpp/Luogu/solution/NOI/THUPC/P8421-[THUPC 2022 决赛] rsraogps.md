# [THUPC 2022 决赛] rsraogps

## 题目描述

给序列 $a_1,\dots,a_n$，$b_1,\dots,b_n$，$c_1,\dots,c_n$，

定义区间 $[l,r]$ 的价值为 $a_l,\dots,a_r$ 按位与，$b_l,\dots,b_r$ 按位或，$c_l,\dots,c_r$ 的最大公因数，这三者的乘积；

$m$ 次查询，每次查询给出区间 $[l,r]$，查询满足 $l\le l'\le r'\le r$ 的 $[l',r']$ 的价值之和。

## 说明/提示


$1\le n\le 10^6$

$1\le m\le 5\times 10^6$

$1\le a_i,b_i,c_i\le n$

$1\le l\le r\le n$

建议使用高效的输入输出方式。


## 样例 #1

### 输入

```
5 3
3 3 1 1 1
2 1 3 2 2
4 5 3 4 4
1 2
2 5
4 5
```

### 输出

```
48
63
24
```

# 题解

## 作者：gxy001 (赞：30)

首先考虑离线扫描线，扫描 $r$，然后对每个 $i$ 维护 $l\le i$ 的答案之和 $s_i$，这样答案就可以写为 $s_r-s_{l-1}$。

我们设 $A_i=a_i\operatorname{bitand} \cdots\operatorname{bitand} a_r$，$B_i=b_i\operatorname{bitor} \cdots\operatorname{bitor} b_r$，$C_i=\gcd(c_i,\cdots,c_r)$。

然后考虑 $r$ 向右移 $1$，这个时候 $s_i$ 的变化量，如果 $A_i,B_i,C_i$ 都没有发生变化，那么 $s_i$ 的变化量也和上次右移的时候一致，所以我们可以把每个 $s_i$ 写成 $p_ir+q_i$ 的形式，那么需要修改 $p_i,q_i$ 的 $i$ 就只有 $A_i,B_i,C_i$ 发生变化的部分，由于 $A_i,B_i,C_i$ 都只会发生 $O(\log v)$ 次修改（$v$ 是值域），所以总变化次数只有 $O(n\log v)$ 次，暴力修改即可。

查询是 $O(1)$ 的，所以总时间复杂度 $O(n\log v+m)$。

```cpp
#include<iostream>
#include<vector>
#include<utility>
using std::cin;
using std::cout;
#define int unsigned
int n,m,a[1000010],b[1000010],c[1000010];
int gcd(int x,int y){
	return x?gcd(y%x,x):y;
}
std::vector<std::pair<int,int>> vec[1000010];
int ans[5000010];
int T;
int val[1000010],ad[1000010],nt[1000010];
int query(int p){
	return val[p]+ad[p]*(T-nt[p]);
}
signed main(){
	std::ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1,l,r;i<=m;i++) cin>>l>>r,vec[r].emplace_back(l,i);
	for(int i=1;i<=n;i++){
		int p=i-1;
		while(p!=0){
			int u=a[p]&a[p+1];
			int v=b[p]|b[p+1];
			int w=gcd(c[p],c[p+1]);
			if(u==a[p]&&v==b[p]&&w==c[p]) break;
			a[p]=u,b[p]=v,c[p]=w;
			--p;
		}
		val[i]=query(i-1);
		for(int j=p+1;j<=i;j++){
			val[j]=query(j);
			ad[j]=ad[j-1]+a[j]*b[j]*c[j];
			nt[j]=T;
		}
		++T;
		for(auto [l,id]:vec[i]) ans[id]=query(i)-query(l-1);
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
	return 0;
}
```



---

## 作者：xfrvq (赞：13)

首先离线问题，考虑对区间右端点 $r$ 做 $1\to n$ 的扫描线。

扫描线过程中维护

+ ${a^\prime}_i=a_i\operatorname{and}\cdots\operatorname{and}a_r$
+ ${b^\prime}_i=b_i\operatorname{or}\cdots\operatorname{or}a_r$
+ ${c^\prime}_i=\gcd(c_i,\cdots,c_r)$

然后我们发现这样一个性质（？：随着 $r$ 的增大，

+ ${a^\prime}_i$ 的 $1$ 位会逐渐变成 $0$。
+ ${b^\prime}_i$ 的 $0$ 位会逐渐变成 $1$。
+ ${c^\prime}_i$ 的质因子会逐渐被去掉。

而这三者的变化次数都是 $\log n$ 级别。

我们维护 $s_i$ 为左端点 $\le i$，右端点 $\le r$ 的区间价值总和，对于 $L,R$ 的询问，答案就是 $s_{R}-s_{L-1}$。

考虑 $r$ 的一次右移对 ${a^\prime}_i,{b^\prime}_i,{c^\prime}_i$ 的影响，进而考虑对 $s_i$ 的影响（其实就是 $[i,r+1],[i+1,r+1],\cdots,[r+1,r+1]$ 的价值和）。

根据上面的性质，我们发现：对于 ${a^\prime}_i,{b^\prime}_i,{c^\prime}_i$ 而言，在 $i$ 很靠近 $r$ 时影响很大，而每远离一点影响就比前一次小。到达一个位置 $p$ 之后就再也没有影响了。

并且，有影响的位置每次都是 $O(\log n)$ 个，因此可以考虑对于每次移动 $r$，都暴力遍历找到 $p$，复杂度是 $O(n\log n)$ 的。然后对于 $p,\cdots,r$ 的位置，暴力计算新价值和。

那 $1,\cdots,p-1$ 的位置的答案怎么办呢？我们发现这一轮没有影响他们的答案，所以他们的答案更新其实和上一轮修改的答案更新是一样的，不需要再计算。

于是我们给每个位置都打上标记，代表它上一次修改增加的价值和 $w$，同时多维护一个上一轮修改的时间 $t$，那么 $r$ 时刻总体答案可以理解为 $s_i+(r-t)\times w$。

当然暴力计算答案这一步要先把之前打的标记的贡献算到 $s_i$ 里面去，再把新的贡献打在标记里面。

分析一下时间。我们枚举 $p$ 这步就 $O(n\log n)$ 了，按位与和按位或作为位运算是 $O(1)$ 的。$\gcd$ 看起来复杂度不太对，但是总共只会有 $O(\log n)$ 个因子，你用辗转相除求 $\gcd$ 即使求 $\log n$ 次也只有 $O(\log n)$ 的计算量。

---

## 作者：北射天狼 (赞：12)

[题目链接](https://www.luogu.com.cn/problem/P8421)

这篇题解主要对 [xfrvq](https://www.luogu.com.cn/blog/368107/solution-p8421) 的题解进行补充。

我们不难可以发现，每一次询问是有一定联系的，看起来可以从一个询问推出另一个询问，所以我们将所有询问离线处理。

对于每一个右端点 $r$，维护一个数组 $s_i\space(1 \le i \le r)$，其意义是区间 $[l',r']\space (1\le l' \le i,l'\le r'\le r)$ 的价值总和。于是，对于每一次询问 $l,r$，答案就是 $s_r - s_{l-1}$，因为 $s_r$ 中区间左端点小于等于 $l-1$ 的会被 $s_{l-1}$ 减去，所以很显然答案就是上式。不断扩展右端点到 $r$，更新右端点为 $r$ 的答案即可求解。

当我们扩展右端点的时候，显然 $s_i$ 的值也会相应的发生变化，这时候该怎么办呢？

我们再维护三个数组：

* $a'_i = a_i \operatorname{and} a_{i+1} \cdots \operatorname{and} a_r$

* $b'_i = b_i \operatorname{or} b_{i+1} \cdots \operatorname{or} b_r$

* $c'_i = \operatorname{gcd}(c_i,c_i+1,\cdots,c_r)$

$r$ 是我们枚举的右端点。

用一个变量 $p$ 找到第一个在 $r$ 扩展时没有变化的 $a'_p,b'_p,c'_p$。

我们可以发现，在 $a'_i,b'_i,c'_i$ 进行操作的时候，变化的总是越来越少。例如：

$a'_i$ 的 $0$ 的位数越来越多，$b'_i$ 的 $1$ 的位数越来越多，$c'_i$ 的质因数越来越少。在 $r$ 扩展过程中找到 $p$ 的期望复杂度为 $O(n\operatorname{log}n)$。

* Q.为什么在 $r$ 扩展过程中找到 $p$ 的期望复杂度为 $O(n\operatorname{log}n)$ ？

* A. 很显然，在 $a',b'$ 进行位运算时，一共有 $O(\operatorname{log}n)$ 位，最多有 $\operatorname{log}n$ 次修改。而 $c'_i$ 取公因数在最劣情况（也就是为 $2^k$ 时）修改最多也只会有 $\operatorname{log}n$ 次修改。所以在 $r$ 扩展过程中找到 $p$ 的期望复杂度为 $O(n\operatorname{log}n)$。修改也最多会有 $O(n\operatorname{log}n)$ 次。




显然，当我们扩展了 $r$，对于 $s_i$，它新增了区间 $[1,r+1],[2,r+1],[3,r+1],\cdots,[i,r+1]$。

如果 $i \le p$，那么很显然无论 $r$ 往下扩展多少次，$s_i$ 的增加的量都不会变，因为很显然的有 $[1,r] = [1,r+1],[2,r] = [2,r+1], \cdots [i,r] = [i,r+1] \space (i \le p)$。其中 $s_i$ 增加的量为等式右边的和。

于是我们就可以维护一个 $s_i$ 最后被更改的时间 $timer_i$ 以及他的增加的量 $add_i$。这样，等我们在时间 $T$ 修改 $s_i$ 时，我们就得出 $s_i = s_i + add_i \times(T - timer_i-1)$。

自己开动脑筋，如果我们不修改，会发生什么呢？答案在博客最底部。

那么对于 $i > p$，现在我们怎么计算 $s_i$ 呢？

对于扩展 $r$ 后任意 $s_i$ 的增加量有 $[j,r+1]\space (p+1\le j \le i)$ 我们可以发现，咦？这不就是 $a'_j \times b'_j \times c'_j$ 吗？

那么是不是？

$$add_i=\sum_{j=p+1}^{j\le i}[j,r+1] =  \sum_{j=p+1}^{j\le i} a'_j\times b'_j \times c'_j$$

那么每一个 $s_i$ 的增加量也被我们算出来了！

代码：

```
#include <bits/stdc++.h>
#define int unsigned
#define re register
using namespace std;
inline int read(){
	int s = 0,f = 1;char c = getchar();
	while (!isdigit(c)){if (c == '-')f = -1;c = getchar();}
	while (isdigit(c)){s = (s << 3) + (s << 1) + (c ^ 48);c = getchar();}
	return s*f;
}
const int N = 1e6 + 5;
int n,m;
struct node{
	int id,l;
};
vector<node> vec[N];
int a[N],b[N],c[N];
int val[N],timer[N],t,add[N];
//这里的 s[i] = val[i] + 时间 * add[N];
//val[i] 的定义有点抽象，这里可以理解为辅助得出 s 的一个数组。也就是加上增加量之前的 s。
int ans[5 * N];
int solve(int j){
	return val[j] + (t - timer[j]) * add[j];
}
int gcd(int x,int y){
	if (y == 0)
	    return x;
	return gcd(y,x%y);
}
signed main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
    n = read();m = read();
    for (re int i=1;i<=n;++i)a[i] = read();
    for (re int i=1;i<=n;++i)b[i] = read();
    for (re int i=1;i<=n;++i)c[i] = read();
    for (re int i=1,l,r;i<=m;++i){
    	l = read(); r = read();
    	vec[r].push_back((node){i,l});
	}
	for (re int i=1;i<=n;++i){
		int p = i-1;
		while (p != 0){
			int a1 = a[p] & a[p+1];
			int b1 = b[p] | b[p+1];
			int c1 = gcd(c[p],c[p+1]);
			if (a1 == a[p] && b1 == b[p] && c1 == c[p])
	    		break;
			a[p] = a1,b[p] = b1,c[p] = c1;
			p--;
		}
		val[i] = solve(i-1);
        //s[i] = s[i-1] + add[i];显然先把 s[i-1] 赋值，因为后赋值会额外计算一个 add[i-1] 
		for (re int j=p+1;j<=i;++j){
			val[j] = solve(j);
			add[j] = add[j-1] + a[j] * b[j] * c[j];
			timer[j] = t;
		}
		++t;//因为前面更新的是 t-1,所以时间增加放在这里
		for (node k:vec[i])
		    ans[k.id] = solve(i) - solve(k.l - 1);
	}
	for (re int i=1;i<=m;++i)
	    std::cout << ans[i] << '\n';
	return 0;
}

```

上方问题的答案：如果我们不及时更新 $s_i$，就会把前面更新的值给多加，而这很显然是错误的。

如果你还有什么疑惑，或者是看完本题解还有不理解，或是发现本题解有误，欢迎指出，我写的时候头也有点晕晕的。


---

## 作者：樱雪喵 (赞：4)

看起来不太好做，考虑找特殊性质。

以按位与运算为例，当区间左端点 $l$ 固定，向右延伸 $r$ 的过程中，区间按位与的结果至多只会改变 $\log n$ 次（考虑每次在二进制中把一个 $1$ 变成 $0$）。另外两种运算是同理的。

这启发我们使用扫描线来维护答案。  
设现在处理到右端点 $r$，设 $s_i$ 表示所有 $i= L$，$ R\le r$ 的区间 $[L,R]$ 的答案之和。则询问 $[l,r]$ 的答案即为 $s_r-s_{l-1}$。  

当 $r$ 右移一位时，根据上述的性质，我们只需要对区间值改变的位置暴力修改，可以保证至多修改 $n\log n$ 次。其余位置本质上是一个区间加法，需要通过打标记记录增加的次数和值。

```cpp
#define int uint
const int N=5e6+5;
int n,m,a[N],b[N],c[N];
int ans[N];
struct node{int l,r,id;};
vector<node> q[N];
int s[N],tag[N],tim[N];
il int get(int x,int t) {return s[x]+(t-tim[x])*tag[x];}
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++) b[i]=read();
    for(int i=1;i<=n;i++) c[i]=read();
    for(int i=1;i<=m;i++)
    {
        int l=read(),r=read();
        q[r].push_back({l,r,i});
    }
    for(int i=1;i<=n;i++)
    {
        int pos=i,A=a[i],B=b[i],C=c[i];
        while(--pos)
        {
            A&=a[pos],B|=b[pos],C=__gcd(C,c[pos]);
            if(A==a[pos]&&B==b[pos]&&C==c[pos]) break;
            a[pos]=A,b[pos]=B,c[pos]=C;
        }
        s[i]=get(i-1,i-1); if(!pos) pos++;
        for(int j=pos;j<=i;j++)
        {
            s[j]=get(j,i-1);
            tag[j]=tag[j-1]+a[j]*b[j]*c[j];
            tim[j]=i-1;
        }
        for(auto x:q[i]) ans[x.id]=get(i,i)-get(x.l-1,i);
    }
    for(int i=1;i<=m;i++) printf("%u\n",ans[i]);
    return 0;
}
```

---

## 作者：happybob (赞：3)

考虑离线。

我们从小到大枚举 $R$，考虑令 $s_i$ 为 $l \leq i$，且 $r \in [l, R]$ 的答案。可以发现对于询问 $l,r$，答案即为 $s_r - s_{l-1}$。

接着我们考虑当 $R \leftarrow R+1$ 时，对 $s$ 的影响。

令 $R \leftarrow R+1$，可以发现对于 $s_i$，增加的贡献应该为 $[i,R],[i-1,R],\cdots,[1,R]$ 的区间的价值之和。

可以发现，随着这个区间扩大，在 $O(\log v)$ 的次数内，按位与、按位或和 $\gcd$ 都会在某个区间 $[p,R]$ 和 $[p,R-1]$ 相等。

那么往前，$[p-1,R],[p-2,R],\cdots,[1,R]$ 都会满足这样的性质。也就是贡献和上一次是一样的。

所以我们只需要暴力找到这个点 $p$，然后对于 $s_p \sim s_R$ 暴力算贡献。

对于 $s_1 \sim s_{p-1}$，其贡献和上一次他被暴力算的贡献是一样的。只需要令 $t_i$ 为 $i$ 被暴力算的时间戳即可。

整体的复杂度应该是 $O(n \log v)$ 的。$O(\log v)$ 是暴力求 $p$ 的复杂度。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <numeric>
#include <vector>
using namespace std;

const int N = 5e6 + 5;

struct qer
{
	int l, id;
	qer(int _l, int _i) : l(_l), id(_i) {}
	qer() {}
};

int n, m;
int a[N], b[N], c[N];
long long ans[N], val[N], q[N];
const long long MOD = 1LL << 32LL;
unsigned int tm[N], idx;

#define qr(p) (val[p] + q[p] * (idx - tm[p]) % MOD) % MOD

unsigned int ne[N], h[N], id;
qer e[N];

struct ios {
	inline char read() {
		static const int IN_LEN = 4500000;
		static char buf[IN_LEN], * s, * t;
		return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
	}
	template <typename _Tp> inline ios& operator >> (_Tp& x) {
		static char c11, boo;
		for (c11 = read(), boo = 0; !isdigit(c11); c11 = read()) {
			if (c11 == -1)return *this;
			boo |= c11 == '-';
		}
		for (x = 0; isdigit(c11); c11 = read())x = x * 10 + (c11 ^ '0');
		boo && (x = -x);
		return *this;
	}
}io;

int main()
{
	memset(h, -1, sizeof h);
	io >> n >> m;
	for (int i = 1; i <= n; i++) io >> a[i];
	for (int i = 1; i <= n; i++) io >> b[i];
	for (int i = 1; i <= n; i++) io >> c[i];
	for (int i = 1; i <= m; i++)
	{
		int l, r;
		io >> l >> r;
		e[id] = qer(l, i);
		ne[id] = h[r];
		h[r] = id++;
	}
	for (unsigned int i = 1; i <= n; i++)
	{
		unsigned int nowj = i;
		for (unsigned int j = i - 1; j >= 1; j--)
		{
			unsigned int na(a[j] & a[j + 1]), nb(b[j] | b[j + 1]), nc(__gcd(c[j], c[j + 1]));
			if (na == a[j] && nb == b[j] && nc == c[j]) break;
			nowj = j; // 找到 p 
			a[j] = na, b[j] = nb, c[j] = nc; // 后缀一段的答案 
		}
		val[i] = qr(i - 1);
		for (int j = nowj; j <= i; j++)
		{
			val[j] = qr(j); // 先算一次之前的贡献 
			q[j] = q[j - 1] + 1LL * a[j] * b[j] * c[j]; // 把累计贡献加上去 
			q[j] %= MOD;
			tm[j] = idx;
		}
		idx++; // 增加时间戳，以保证 a[j] * b[j] * c[j] 的贡献 
		for (int j = h[i]; ~j; j = ne[j])
		{
			qer k = e[j];
			ans[k.id] = (qr(i) - qr(k.l - 1) + MOD) % MOD;
		}
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
```


---

## 作者：w33z8kqrqk8zzzx33 (赞：0)

令 $A[l:r]$，$B[l:r]$，$C[l:r]$ 为 $l\dots r$ 的按位与，按位或，和公约数。当固定 $l$，最多有 $O(\log n)$ 个不同的 $A[l:r]$，$B[l:r]$，$C[l:r]$，于是有 $O(\log n)$ 个不同的价值，并且每一个价值对应一个 $r$ 区间。

我们可以对 $l=n\to 1$ 扫描线并同时维护 $s_r$ 为 $[l:r],[l+1:r],\dots,[r:r]$ 所有区间价值之和；当更新 $l+1\to l$ 需要对 $s$ 的 $O(\log n)$ 个区间加对应价值。

询问答案对应当时候的 $l$ 的 $s[l:r]$ 之和，可以使用树状数组维护，时间复杂度 $O(n\log^2 n+q\log n)$。可以用 p8283 trick 做到 $O((n+q)\log n)$。

---

## 作者：elbissoPtImaerD (赞：0)

好题。

考虑离线：

- Kira：统计一个区间 $[l,r]$ 的所有子区间权值和可以转化为 $f_{r,r}-f_{r,l-1}$，其中 $f_{i,j}$ 表示 $l\le i,r \le j$ 的区间 $[l,r]$ 的权值和。

然后考虑已知 $f_r$ 快速计算 $f_{r+1}$。

对于 $f_{r,i} \to f_{r+1,i}$，其增加了 $[i,r+1]$，$\forall i\in[1,r+1]$ 的区间的权值。

按位与，按位或，$\gcd$，很难不让人想到势能分析。

不难得出，$f_{r,i} \to f_{r+1,i}$ 时，必定存在一个 $p\in[1,r+1]$，使得：$\forall i<p$，$[i,r+1]$ 的权值和 $[i,r]$ 相同，且 $\forall i \in[p,r+1]$，$[i,r+1]$ 的权值与 $[i,r]$ 不同。

而且这个 $p$ 和 $r+1$ 的距离还很近，是 $\mathcal{O(\log n)}$ 级别的。

这启发我们对于 $[1,p)$ 的新增权值用懒标记的思想维护，$[p,r+1]$ 的暴力修改。

具体地，我们先将询问离线按 $r$ 升序排序，然后对于每个 $r$，暴力地找到对应的 $p$，对 $[1,r]$ 从 $p$ 劈开分成两部分处理。我们记录懒标记的标记时间戳，$[1,p)$ 段不用管，$[p,r+1]$ 段暴力修改时直接更新懒标记和对应的标记时刻，查询时用当前时刻减去标记时刻即可得知懒标记的作用时长。

复杂度 $\mathcal{O(n\log V + m\log m)}$。

细节看代码。

```cpp
const int N=1e6+3,M=5e6+3;
int n,m,a[N],b[N],c[N],t[N];
sd array<int,3>q[M];
ui s[N],ans[M],tg[N];
il ui _Q(int x,ui tt){return s[x]+tg[x]*(tt-t[x]);}
il void Solve()
{
  rd(n),rd(m);
  for(int i=1;i<=n;++i) rd(a[i]);
  for(int i=1;i<=n;++i) rd(b[i]);
  for(int i=1;i<=n;++i) rd(c[i]);
  for(int i=1,l,r;i<=m;++i) rd(l),rd(r),q[i]={r,l,i};
  sd stable_sort(q+1,q+m+1);
  for(int r=1,i=0,pos;r<=n;++r)
  {
    for(pos=r;pos-1;--pos)
    {
      if((a[pos]&a[pos-1])==a[pos-1]&&(b[pos]|b[pos-1])==b[pos-1]&&sd __gcd(c[pos],c[pos-1])==c[pos-1]) break;
      a[pos-1]&=a[pos],b[pos-1]|=b[pos],c[pos-1]=sd __gcd(c[pos],c[pos-1]);
    }
    s[r]=_Q(r-1,r);
    for(int j=pos;j<=r;++j) s[j]=_Q(j,r),tg[j]=tg[j-1]+1ull*a[j]*b[j]*c[j],t[j]=r;
    for(;i<m&&r==q[i+1][0];++i,ans[q[i][2]]=_Q(q[i][0],r+1)-_Q(q[i][1]-1,r+1));
  }
  for(int i=1;i<=m;++i) wrt(ans[i],'\n');
  return;
}
```

[$\color{green}{\checkmark}$](https://www.luogu.com.cn/record/129162200)。

---

## 作者：zzx0102 (赞：0)

神题，太神了。

考虑扫描线。

考虑当 $r$ 变大时，答案的变化量。

那么与，或，$\gcd$ 的每个值都只会最多修 $\log w$ 次，$w$ 为值域。

证明很平凡，考虑或运算每一位都变成 $1$ 就不会变了。

与运算变成 $0$ 也不会变了，$\gcd$ 变成 $1$ 就不会变了，因为 $\gcd(1,x)=x$。

查询是 $\mathcal{O}(1)$ 的，总复杂度 $\mathcal{O}(n\log w)$。

考虑每次修改都暴力修改，然后维护前缀和相减一下就好了。

从 $r$ 开始，每次都访问到三个值都没有改变时结束停止算贡献。

这样至多有 $\mathcal{O}(\log n)$ 个断点，复杂度是对的。

代码是 Ynoi 的，有点丑，见谅。

[CODE](https://www.luogu.com.cn/paste/w51s778g)

---

## 作者：aaaaaaaawsl (赞：0)

~~不要脸的把自己加强版的题解拿过来了（X。~~

--------

### 分析题意

题意：给定三个序列 $a_1\dots,b_1\dots,c_1\dots$，第一个序列做按位与，第二个序列做按位或，第三个序列做最大公因数。

一个区间的价值是区间内的三者值的积。给定区间，查询区间内所有子区间价值的和。

首先分开考虑三个操作。

在从 $1$ 到 $n$ 移动 $r$ 的过程中，设

$$A_i = \bigwedge_{j = i}^{r}a_j$$

$$B_i = \bigvee_{j = i}^{r}a_j$$

$$C_i = \gcd_{j = i}^{r}a_j$$

表示从 $i$ 到 $r$ 这一段区间的三个操作的值。

注意到 $A_i, B_i, C_i$ 的值最多变化 $O(\log n)$ 次。

因为对于 $n$ 的二进值一共有 $\log n$ 位，$A$ 操作使之趋于全一， $B$ 操作使之趋于全零。并且趋势只会加深。而对于 $C$ 操作来说，一个数的因子最多 $O(\log)$ 个。

下面设 $V_i = A_i \times B_i \times C_i$

表示从 $i$ 到 $r$ 区间的值（而不是答案）。

现在把 $V_i$ 取前缀和，设 

$$ S_i = \sum_{j = 1}^{i}V_i $$

这样，当我们枚举到 $r$ 的时候，询问 $l,r$ 的答案就是此时的 $S_r - S_{l-1}$。

那么现在大体思路就有了。预处理查询，循环 $r$，维护 $S$。

那么怎么维护 $S$ 呢？

因为这些值的变化次数都是 $O(\log)$ 的，所以最多 $3\log n$ 个断点，在两个断点之间的值都是相等的，这些区间可以通过上一个断点的值，断点之间的长度算出。

当 $r$ 变化后，$V_i$ 的变化一定是一段后缀（显然，因为前面的数没有变）。

所以我们从当前的 $r$ 开始枚举，直到 $A_i, B_i, C_i$ 的值和上一个 $r$ 的完全一样，把之前的答案先加上。后面这段变化的暴力统计即可。

--------
因为听老师讲的，所以代码应该很相似（我太弱了。

不用这些常熟优化应该也能过。
### Code

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int unsigned int 

using namespace std;

namespace FastIO {
    char buf[1 << 9], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
    int p, p3 = -1;
    void read() {}
    void print() {}
    inline int getc() {
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 9, stdin), p1 == p2) ? EOF : *p1++;
    }
    inline void flush() {
        fwrite(buf2, 1, p3 + 1, stdout), p3 = -1;
       
    }
    template <typename T, typename... T2>
    inline void read(T &x, T2 &...oth) {
        int f = 0;
        x = 0;
        char ch = getc();
        while (!isdigit(ch)) {
            if (ch == '-') f = 1;
            ch = getc();
        }
        while (isdigit(ch)) {
            x = (x << 1) + (x << 3) + (ch ^ '0');
            ch = getc();
        }
        x = f ? -x : x;
        read(oth...);
    }
    template <typename T, typename... T2>
    inline void print(T x, T2... oth) { 
        if (p3 > 1 << 20) 
            flush();
        if (x < 0)
            buf2[++p3] = 45, x = -x; 
        do {
            a[++p] = x % 10 + 48;
        } while (x /= 10);
        do {
            buf2[++p3] = a[p];
        } while (--p);
        buf2[++p3] = hh; 
        print(oth...);
    }
}
#define read FastIO::read
#define print FastIO::print


const int N = 1e6 + 10;
const int M = 5e6 + 10;

int a[N], b[N], c[N], l[M], r[M];
int tot[N], id[M], sum[N], num[N];
int tim[N];
int n, m, ans[M];

int gcd(int a, int b){
	return !b ? a : gcd(b, a % b);
}

signed main(){
	read(n); read(m); 
	for(register int i = 1; i <= n; ++ i) read(a[i]);
	for(register int i = 1; i <= n; ++ i) read(b[i]);
	for(register int i = 1; i <= n; ++ i) read(c[i]);
	for(register int i = 1; i <= m; ++ i) read(l[i]), read(r[i]), tot[r[i]] ++;
	for(register int i = 1; i <= n; ++ i) tot[i] += tot[i - 1];
	for(register int i = 1; i <= m; ++ i) id[tot[r[i] - 1] ++ ] = i;
	for(register int i = 1, j = 0; i <= n; ++ i){
		register int p = i;
		while(-- p){
			register int A = a[p] & a[p + 1], B = b[p] | b[p + 1], C = gcd(c[p], c[p + 1]);
			if(A == a[p] && B == b[p] && C == c[p]) break;
			a[p] = A, b[p] = B, c[p] = C;
		}
		sum[i] = sum[i - 1] + num[i - 1] * (i - 1 - tim[i - 1]);
		for(; ++ p <= i; ){
			sum[p] += num[p] * (i - 1 - tim[p]);
			tim[p] = i - 1;
			num[p] = num[p - 1] + a[p] * b[p] * c[p];
		}
		register int tmp = sum[i] + num[i] * (i - tim[i]);
		for(; j < tot[i - 1]; ++ j){
			ans[id[j]] = tmp - sum[l[id[j]] - 1] - num[l[id[j]] - 1] * (i - tim[l[id[j]] - 1]);
		}
	}
	for(register int i = 1; i <= m; ++ i) print(ans[i]);
	FastIO :: flush();
}

```


---

